#include "ItemEditorProblemPage.h"

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

ItemEditorProblemPage::ItemEditorProblemPage(QWidget * p)
	: EditorBasePage(p)
{
	setupUi();

}


ItemEditorProblemPage::~ItemEditorProblemPage()
{
}

void ItemEditorProblemPage::setupUi()
{
	QVBoxLayout * mainlayout = new QVBoxLayout();


	mUidTextEdit = new LineEdit();
	mUidTextEdit->overlay()->setText( tr("Unique Id") );
	WidgetExtension * wxuid = new WidgetExtension(mUidTextEdit, WidgetExtension::AlwaysVisible, this);
	Q_UNUSED(wxuid);


	mQuestionTextEdit = new PlainTextEdit();
	mQuestionTextEdit->overlay()->setText(tr("Enter question text")	);

	mHintTextEdit = new PlainTextEdit();
	mHintTextEdit->overlay()->setText( tr("Enter hint text") );

	mImageList = new ImageListWidget(0, this);
	WidgetExtension * wxe = new WidgetExtension( mImageList,
												 WidgetExtension::AlwaysVisible | WidgetExtension::ShowDropIndicator,
													 this);
	wxe->setListener( new WxListenerImageListWidget() );

	mainlayout->addWidget(mUidTextEdit);
	mainlayout->addWidget(mQuestionTextEdit,2);
	mainlayout->addWidget(mHintTextEdit,1);
	mainlayout->addWidget(mImageList);

	// connections
	connect(mQuestionTextEdit, SIGNAL(textChanged()), this, SLOT(onQuestionTextChanged()));

	// commitment connections
	setCommitDelay(500);
	connect(mUidTextEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mQuestionTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));
	connect(mHintTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));
	connect(mImageList, SIGNAL(contentChanged()), this, SLOT(commit()));

	setLayout(mainlayout);
}

bool ItemEditorProblemPage::isAcceptingMime(const QMimeData *m) const{
	return false;
}

void ItemEditorProblemPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);

	if(item->getItemType() == tip::ItemProblem){

		Problem p;
		tip::extract(item, p); // initialize with current values

		p.uid = mUidTextEdit->text();
		p.text = mQuestionTextEdit->document()->toPlainText();
		p.hint = mHintTextEdit->document()->toPlainText();
		p.images.clear();
		for(int i=0; i<mImageList->count(); ++i)
		{
			const QListWidgetItem * item = mImageList->item(i);
			p.images << mImageList->imageUrl(item);
		}

		tip::incept(p, item);
	}
}

void ItemEditorProblemPage::update(TreeItem * item)
{
	EditorBasePage::update(item);
	SignalBlocker b( QList<QObject*>() <<
						mUidTextEdit <<
						mQuestionTextEdit <<
						mHintTextEdit <<
						mImageList
					);
	Q_UNUSED(b)
	mImageList->clear();
	if(item->getItemType() == tip::ItemProblem){

		Problem p;
		tip::extract(item, p);

		mUidTextEdit->setText( p.uid );
		mQuestionTextEdit->document()->setPlainText( p.text );
		mHintTextEdit->document()->setPlainText( p.hint );

		foreach(const QString& image, p.images)
		{
			mImageList->addImage(image);
		}

		// enable or disable uid input
		Model m;
		tip::extract( item->getTreeItem(), m);
		mUidTextEdit->setEnabled(m.uidMode==Model::UidManual);

	}

}

bool ItemEditorProblemPage::isUidAutoGeneration() const
{
	return !mUidTextEdit->isEnabled();
}

// ----------------------------- SLOTS ------------------------------------


void ItemEditorProblemPage::onQuestionTextChanged()
{
	if(isUidAutoGeneration())
	{
		QString uid ( UidGenerator().generate(mQuestionTextEdit->document()->toPlainText()) );
		if(uid.isEmpty())
		{
			mUidTextEdit->clear();
		}
		else
		{
			mUidTextEdit->setText( uid );
		}
	}
}

END_NS
