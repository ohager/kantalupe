#include "ItemEditorMatrixPage.h"
#include "PlainTextEdit.h"
#include "LineEdit.h"
#include "ImageListWidget.h"
#include "WidgetExtension.h"
#include "WxListenerImageListWidget.h"
#include "Overlay.h"
#include "global.h"

#include "TreeItemProtocol.h"
#include "TreeItem.h"

#include "SignalBlocker.h"

#include <QtGui>

START_NS

ItemEditorMatrixPage::ItemEditorMatrixPage(QWidget * parent) :
    EditorBasePage(parent)
{
	setupUi();
}

bool ItemEditorMatrixPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}

void ItemEditorMatrixPage::update(TreeItem *item)
{
	EditorBasePage::update(item);

	SignalBlocker b( QList<QObject*>() <<
					mNameLineEdit <<
					mQuestionTextEdit <<
					mHintTextEdit <<
					mImageList
					);
	Q_UNUSED(b)
	mImageList->clear();
	if(item->getItemType()==tip::ItemMatrix)
	{
		Matrix m;
		tip::extract(item, m);

		mNameLineEdit->setText( m.name );
		mQuestionTextEdit->document()->setPlainText( m.text );
		mHintTextEdit->document()->setPlainText( m.hint );


		foreach(const QString &imgurl, m.images)
		{
			mImageList->addImage(imgurl);
		}
	}
}


// -------------------------- protected -------------------------
void ItemEditorMatrixPage::commit(TreeItem *item) const
{
	EditorBasePage::commit(item);

	if(item->getItemType()==tip::ItemMatrix)
	{
		Matrix m;
		tip::extract(item, m); // get current item values

		m.name = mNameLineEdit->text();
		m.text = mQuestionTextEdit->document()->toPlainText();
		m.hint = mHintTextEdit->document()->toPlainText();

		m.images.clear();
		for(int i=0; i<mImageList->count(); ++i)
		{
			const QListWidgetItem * item = mImageList->item(i);
			m.images << mImageList->imageUrl(item);
		}

		tip::incept(m, item);
	}
}

// -------------------------- privates --------------------------
void ItemEditorMatrixPage::setupUi(){
	QLayout * layout = new QVBoxLayout();

	mNameLineEdit = new LineEdit(this);
	mNameLineEdit->overlay()->setText(tr("Enter a name"));
	mNameLineEdit->setMaxLength(128);
	mQuestionTextEdit = new PlainTextEdit(this);
	mQuestionTextEdit->overlay()->setText(tr("Enter the question text"));
	mHintTextEdit = new PlainTextEdit(this);
	mHintTextEdit->overlay()->setText(tr("Enter a hint"));

	mImageList = new ImageListWidget(0, this);
	WidgetExtension * wxe = new WidgetExtension( mImageList,
												 WidgetExtension::AlwaysVisible | WidgetExtension::ShowDropIndicator,
													 this);
	wxe->setListener( new WxListenerImageListWidget() );

	setCommitDelay(500);
	connect(mNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mQuestionTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));
	connect(mHintTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));
	connect(mImageList, SIGNAL(contentChanged()), this, SLOT(commit()));

	layout->addWidget(mNameLineEdit);
	layout->addWidget(mQuestionTextEdit);
	layout->addWidget(mHintTextEdit);
	layout->addWidget(mImageList);
	setLayout(layout);

}

END_NS
