#include "SurveyEditorGeneratorPage.h"
#include "ScriptListLoaderThread.h"
#include "global.h"

#include <QItemSelection>
#include <QStandardItemModel>
#include <QModelIndexList>
#include <QtGui>


#include "GeneratorScriptView.h"
#include "ShortMessage.h"
#include "Overlay.h"
#include "Script.h"
#include "ScriptReaderWriter.h"
#include "ScriptEngine.h"
#include "PlainTextEdit.h"
#include "LineEdit.h"

START_NS




SurveyEditorGeneratorPage::SurveyEditorGeneratorPage(QWidget * parent)
	: EditorBasePage(parent),
	  mScriptLoader(0x0),
	  mScriptView(new GeneratorScriptView(this)),
	  mAuthorEdit(0x0),
	  mDescriptionEdit(0x0),
	  mVersionEdit(0x0),
	  mScriptEngine(new ScriptEngine(this))
{

	connect(mScriptView, SIGNAL(itemSelected(QStandardItem*)), this, SLOT(onSelectedItem(QStandardItem*)));
	connect(mScriptView, SIGNAL(scriptActivated(QString)), this, SLOT(runScript(QString)));
	connect(mScriptEngine, SIGNAL(surveyGenerated(SurveyTree*)), this, SIGNAL(surveyGenerated(SurveyTree*)));
	setupUi();
}

SurveyEditorGeneratorPage::~SurveyEditorGeneratorPage()
{
	}

void SurveyEditorGeneratorPage::stopScriptLoader()
{
	if(mScriptLoader)
	{
		if(mScriptLoader->isRunning())
		{
			mScriptLoader->stop();
		}
		mScriptLoader->deleteLater();
		mScriptLoader=0x0;
	}
}

void SurveyEditorGeneratorPage::initScriptLoader()
{
	stopScriptLoader();

	mScriptLoader = new ScriptListLoaderThread(global::R.getValue("script/deploydir"));
	connect(mScriptLoader, SIGNAL(started()), mScriptView->overlay(), SLOT(show()));
	connect(mScriptLoader, SIGNAL(finished()), mScriptView->overlay(), SLOT(hide()));
	connect(mScriptLoader, SIGNAL(finished()), this, SLOT(onScriptsLoaded()));
}

void SurveyEditorGeneratorPage::closeEvent(QCloseEvent * e)
{
	stopScriptLoader();
	e->accept();
}

bool SurveyEditorGeneratorPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}


void SurveyEditorGeneratorPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);

	/* todo */
}
void SurveyEditorGeneratorPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	/* todo */
}

void SurveyEditorGeneratorPage::updateScriptList()
{
	stopScriptLoader();
	initScriptLoader();
	mScriptLoader->start();
}



void SurveyEditorGeneratorPage::setupUi()
{
	QBoxLayout * vlayout = new QVBoxLayout();
	QBoxLayout * infolayout = new QVBoxLayout();
	QBoxLayout * hlayout = new QHBoxLayout();

	QToolBar * toolbar = new QToolBar(this);
	toolbar->setIconSize( QSize(48,48) );
	toolbar->addAction(QIcon(global::R.getValue("icon/scripteditorrun")),
						tr("Run Script"),
						this,SLOT(onActionRunScript()));

	Overlay * o =mScriptView->overlay();
	o->setMovie( new QMovie( global::R.getValue("animation/loading") ));
	o->movie()->start();
	o->hide();


	mDescriptionEdit = new PlainTextEdit(this);
	mDescriptionEdit->overlay()->setText( tr("Description") );
	mDescriptionEdit->setToolTip( mDescriptionEdit->overlay()->text() );
	mDescriptionEdit->setReadOnly(true);

	mAuthorEdit = new LineEdit(this);
	mAuthorEdit->overlay()->setText( tr("Author") );
	mAuthorEdit->setToolTip( mAuthorEdit->overlay()->text() );
	mAuthorEdit->setReadOnly(true);

	mVersionEdit = new LineEdit(this);
	mVersionEdit->overlay()->setText( tr("Version") );
	mVersionEdit->setToolTip( mVersionEdit->overlay()->text() );
	mVersionEdit->setReadOnly(true);

	vlayout->addWidget(toolbar);

	hlayout->addWidget(mScriptView);

	infolayout->addWidget(mDescriptionEdit);
	infolayout->addWidget(mAuthorEdit);
	infolayout->addWidget(mVersionEdit);
	infolayout->addStretch();

	hlayout->addLayout(infolayout);
	vlayout->addLayout(hlayout);

	setLayout(vlayout);
	updateScriptList();
}


void SurveyEditorGeneratorPage::runScript(const QString &program)
{

	if(!mScriptEngine->runScript(program))
	{
		ShortMessage::showMessage( this, tr("Sorry, script contains errors.\nPlease, edit script and redeploy the script."), 2500 );
	}
	else
	{
		ShortMessage::showMessage( this, tr("Script successfully executed."));
	}

}


// ------------------------------------ SLOTS --------------------------------

void SurveyEditorGeneratorPage::onActionRunScript()
{
	QString program = mScriptView->getDataOfSelectedItem( GeneratorScriptView::RoleProgram );
	if(!program.isEmpty())
	{
		runScript(program);
	}
	else
	{
		ShortMessage::showMessage(this, tr("Please, select a script first"));
	}
}

void SurveyEditorGeneratorPage::onSelectedItem(QStandardItem * item)
{
	if(item)
	{
		mAuthorEdit->setText( mScriptView->getDataOfSelectedItem(GeneratorScriptView::RoleAuthor) );
		mVersionEdit->setText( mScriptView->getDataOfSelectedItem(GeneratorScriptView::RoleVersion) );
		mDescriptionEdit->setPlainText( mScriptView->getDataOfSelectedItem(GeneratorScriptView::RoleDescription));
	}
}

void SurveyEditorGeneratorPage::onScriptsLoaded()
{
	mScriptView->addScripts(mScriptLoader->getScriptList());

	/*
	if(mScriptView->model())
	{
		mScriptView->model()->deleteLater();
	}

	QStandardItemModel * model = new QStandardItemModel();
	QStringList headerlabels;
	headerlabels << tr("Name") << tr("Last Edited") << tr("API Level");
	model->setHorizontalHeaderLabels(headerlabels);

	ScriptList scriptlist = mScriptLoader->getScriptList();
	foreach(const Script & script, scriptlist)
	{
		QList<QStandardItem*> row;
		QStandardItem * name = new QStandardItem(script.name);
		QStandardItem * edited = new QStandardItem(script.lastEdited.toString(global::DateFormat));
		QStandardItem * apilevel = new QStandardItem(QString::number(script.apilevel));


		name->setData(script.author, RoleAuthor);
		name->setData(script.description, RoleDescription);
		name->setData(script.program, RoleProgram);
		name->setData(script.version, RoleVersion);

		row << name << edited << apilevel;
		model->appendRow(row);
	}

	model->sort(0);


	mScriptView->setUpdatesEnabled(false);
	mScriptView->setModel(model);
	connect(mScriptView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
			this, SLOT(onSelectedItem(QItemSelection,QItemSelection)));
	mScriptView->expandAll();
	mScriptView->setUpdatesEnabled(true);

	mScriptView->resizeColumnToContents(2);
	mScriptView->resizeColumnToContents(1);
	*/

}

END_NS

