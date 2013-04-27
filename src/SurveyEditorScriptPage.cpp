#include "SurveyEditorScriptPage.h"
#include "global.h"

#include "WidgetExtension.h"
#include "ShortMessage.h"
#include "ScriptTextEdit.h"
#include "ScriptEngine.h"
#include "ScriptConsoleEdit.h"
#include "ScriptInfoWidget.h"
#include "ScriptReaderWriter.h"
#include "Script.h"

#include <QtGui>

START_NS



SurveyEditorScriptPage::SurveyEditorScriptPage(QWidget * parent)
	: EditorBasePage(parent),
	  mToolBar(new QToolBar(this)),
	  mActionDeploy(0x0),
	  mScriptEdit(new ScriptTextEdit(this)),
	  mScriptEngine(new ScriptEngine(this)),
	  mScriptConsole(new ScriptConsoleEdit(this)),
	  mScriptInfoEdit(new ScriptInfoWidget(this)),
	  mScriptEditTab(new QTabWidget(this))
{
	connect(mScriptEngine, SIGNAL(surveyGenerated(SurveyTree*)), this, SIGNAL(surveyGenerated(SurveyTree*)));
	connect(mScriptEngine, SIGNAL(msgDebug(QString)), mScriptConsole, SLOT(appendDebugText(QString)));
	connect(mScriptEngine, SIGNAL(msgWarning(QString,int)), mScriptConsole, SLOT(appendWarningText(QString,int)));
	connect(mScriptEngine, SIGNAL(msgException(QString,int)), mScriptConsole, SLOT(appendExceptionText(QString,int)));
	connect(mScriptEngine, SIGNAL(msgSuccess(QString)), mScriptConsole, SLOT(appendSuccessText(QString)));
	connect(mScriptEngine, SIGNAL(msgInformation(QString)), mScriptConsole, SLOT(appendPlainText(QString)));
	connect(mScriptEdit, SIGNAL(textChanged()), this, SLOT(onEditedScript()));
	setupUi();
}

SurveyEditorScriptPage::~SurveyEditorScriptPage()
{
}

bool SurveyEditorScriptPage::isAcceptingMime(const QMimeData *m) const
{
	// we will accept mime, yes!
	return false;
}


void SurveyEditorScriptPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);

	/* todo */
}
void SurveyEditorScriptPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	/* todo */
}

void SurveyEditorScriptPage::setupUi()
{
	QLayout * layout = new QVBoxLayout();
	mToolBar->setIconSize( QSize(48,48) );
	mToolBar->addAction(QIcon(global::R.getValue("icon/scripteditorrun")),
						tr("Run Script"),
						this,SLOT(onActionRunScript()));
	mToolBar->addAction(QIcon(global::R.getValue("icon/scripteditornew")),
						tr("New Script"),
						this,SLOT(onActionNewScript()));
	mToolBar->addAction(QIcon(global::R.getValue("icon/scripteditorload")),
						tr("Load Script"),
						this,SLOT(onActionLoadScript()));
	mToolBar->addAction(QIcon(global::R.getValue("icon/scripteditorsave")),
						tr("Save Script"),
						this,SLOT(onActionSaveScript()));

	mActionDeploy  = mToolBar->addAction(QIcon(global::R.getValue("icon/scripteditordeploy")),
										 tr("Deploy Script"),
										 this,SLOT(onActionDeployScript()));
	connect(mScriptEngine, SIGNAL(scriptFinished(bool)), mActionDeploy, SLOT(setEnabled(bool)));
	mActionDeploy->setEnabled(false);
	mActionDeploy->setToolTip(tr("Deploy script"));

	mScriptEditTab->setTabPosition(QTabWidget::East);
	mScriptEditTab->addTab(mScriptEdit, tr("Script Code"));
	mScriptEditTab->addTab(mScriptInfoEdit, tr("Deploy Information"));

	mScriptInfoEdit->setLastEdited( QDate::currentDate() );
	mScriptInfoEdit->setVersion( "1.0" );

	QSplitter * splitter = new QSplitter(this);
	splitter->setOrientation(Qt::Vertical);
	splitter->addWidget(mScriptEditTab);
	splitter->addWidget(mScriptConsole);
	splitter->setStretchFactor(0,4);
	splitter->setStretchFactor(1,1);

	layout->addWidget(mToolBar);
	layout->addWidget(splitter);
	setLayout(layout);

	onActionNewScript();

}

void SurveyEditorScriptPage::onActionNewScript()
{
	mScriptEdit->clear();
	QFile stub(global::R.getValue("script/template_api_lvl1"));
	if(stub.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		mScriptEdit->setPlainText( stub.readAll() );
	}
	else
	{
		qDebug() << "Could not open script template file: " << stub.fileName();
	}
}

void SurveyEditorScriptPage::onActionRunScript()
{
	QString script = mScriptEdit->document()->toPlainText();
	int apilevel;
	mScriptEngine->runScript(script, &apilevel);
	mScriptInfoEdit->setApiLevel(apilevel);

}


void SurveyEditorScriptPage::onActionSaveScript(){

	Script script = mScriptInfoEdit->toScript();
	script.lastEdited = QDate::currentDate();
	script.program = mScriptEdit->toPlainText();
	// when saving as draft we dont care for completeness of data

	QString filename = QFileDialog::getSaveFileName(this, tr("Save Script As Draft"), QString("./scripts/drafts"),
			file::FilterScript);
	if(filename.isEmpty())
		return;

	filename = filename.endsWith(file::SuffixScript) ? filename : filename.append(file::SuffixScript);
	QFile outfile(filename);
	bool ok = false;
	if(outfile.open(QIODevice::WriteOnly))
	{
		ScriptReaderWriter writer;
		ok = writer.write(script, &outfile);
	}

	ShortMessage::showMessage(this, ok ? tr("Script draft saved") : tr("Sorry, saving failed") );

}


void SurveyEditorScriptPage::onActionLoadScript(){

	// loading script either from drafts or deployed
	QString filename = QFileDialog::getOpenFileName(this, tr("Load Script"), QString("./scripts"),
			file::FilterScript);

	if(filename.isEmpty())
		return;

	bool ok = false;
	QFile infile(filename);
	if(infile.open(QIODevice::ReadOnly))
	{
		ScriptReaderWriter reader;
		Script script;
		if(reader.read(script, &infile))
		{
			mScriptInfoEdit->fromScript(script);
			mScriptEdit->setPlainText( script.program );
			ok = true;
		}
	}

	ShortMessage::showMessage(this,  ok ? tr("Script loaded") : tr("Sorry, loading failed") );

}

void SurveyEditorScriptPage::onActionDeployScript()
{
	Script script = mScriptInfoEdit->toScript();
	script.program = mScriptEdit->toPlainText();

	if(script.isComplete())
	{
		QString filename = QFileDialog::getSaveFileName(this, tr("Deploy Script"), QString("./scripts/deployed"),
				file::FilterScript);
		if(filename.isEmpty())
			return;

		filename = filename.endsWith(file::SuffixScript) ? filename : filename.append(file::SuffixScript);
		QFile outfile(filename);
		bool ok = false;
		if(outfile.open(QIODevice::WriteOnly))
		{
			ScriptReaderWriter writer;
			ok = writer.write(script, &outfile);
		}

		ShortMessage::showMessage(this, ok ? tr("Script deployed") : tr("Sorry, deploying failed") );
		emit scriptDeployed(filename);
	}
	else
	{
		mScriptEditTab->setCurrentWidget( mScriptInfoEdit );
		ShortMessage::showMessage(this, tr("Please, complete Script information first"));
	}


}


void SurveyEditorScriptPage::onEditedScript()
{
	mActionDeploy->setEnabled(false);
}

END_NS

