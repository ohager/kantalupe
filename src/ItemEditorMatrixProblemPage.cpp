#include "ItemEditorMatrixProblemPage.h"

#include "global.h"
#include <QtGui>

#include "Application.h"
#include "ImageListWidget.h"
#include "PlainTextEdit.h"
#include "LineEdit.h"
#include "Overlay.h"
#include "WidgetExtension.h"
#include "WxListenerImageListWidget.h"

#include "UidGenerator.h"

#include "TreeItemProtocol.h"
#include "TreeItem.h"

#include "SignalBlocker.h"


START_NS




// -------------------------------------------------------

ItemEditorMatrixProblemPage::ItemEditorMatrixProblemPage(QWidget * p)
	: EditorBasePage(p)
{
	setupUi();

}


ItemEditorMatrixProblemPage::~ItemEditorMatrixProblemPage()
{
}

void ItemEditorMatrixProblemPage::setupUi()
{
	QVBoxLayout * mainlayout = new QVBoxLayout();

	mUidLineEdit = new LineEdit();
	mUidLineEdit->overlay()->setText(tr("Enter unique id"));

	mQuestionTextEdit = new PlainTextEdit();
	mQuestionTextEdit->overlay()->setText(tr("Enter problem text")	);


	mainlayout->addWidget(mUidLineEdit);
	mainlayout->addWidget(mQuestionTextEdit);

	// connections
	connect(mQuestionTextEdit, SIGNAL(textChanged()), this, SLOT(onQuestionTextChanged()));

	// commitment connections
	setCommitDelay(500);
	connect(mUidLineEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mQuestionTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));


	setLayout(mainlayout);
}

bool ItemEditorMatrixProblemPage::isAcceptingMime(const QMimeData *m) const{
	return false;
}

void ItemEditorMatrixProblemPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);

	if(item->getItemType() == tip::ItemMatrixProblem){

		MatrixProblem m;
		tip::extract(item, m); // initialize with current values

		m.text = mQuestionTextEdit->document()->toPlainText();
		m.uid = mUidLineEdit->text();

		tip::incept(m, item);
	}
}

void ItemEditorMatrixProblemPage::update(TreeItem * item)
{
	EditorBasePage::update(item);
	SignalBlocker b( QList<QObject*>() <<
						mQuestionTextEdit <<
						mUidLineEdit
					);
	Q_UNUSED(b)
	if(item->getItemType() == tip::ItemMatrixProblem){

		MatrixProblem m;
		tip::extract(item, m);
		mUidLineEdit->setText(m.uid);
		mQuestionTextEdit->document()->setPlainText( m.text );

		// enable or disable uid input
		Model mdl;
		tip::extract( item->getTreeItem(), mdl);
		mUidLineEdit->setEnabled(mdl.uidMode==Model::UidManual);

	}
}


bool ItemEditorMatrixProblemPage::isUidAutoGeneration() const
{
	return !mUidLineEdit->isEnabled();
}

// ----------------------------- SLOTS ------------------------------------
void ItemEditorMatrixProblemPage::onQuestionTextChanged()
{

	if(isUidAutoGeneration())
	{
		QString uid ( UidGenerator().generate(mQuestionTextEdit->document()->toPlainText()) );
		if(uid.isEmpty())
		{
			mUidLineEdit->clear();
		}
		else
		{
			mUidLineEdit->setText( uid );
		}
	}
}

END_NS

