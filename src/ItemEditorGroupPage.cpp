#include "ItemEditorGroupPage.h"
#include "PlainTextEdit.h"
#include "LineEdit.h"
#include "Overlay.h"
#include "global.h"

#include "TreeItemProtocol.h"
#include "TreeItem.h"

#include "SignalBlocker.h"

#include <QtGui>

START_NS

ItemEditorGroupPage::ItemEditorGroupPage(QWidget * parent)
	: EditorBasePage(parent)
{
	setupUi();
}

ItemEditorGroupPage::~ItemEditorGroupPage()
{

}

bool ItemEditorGroupPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}

// interface implementation
void ItemEditorGroupPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);

	if(item->getItemType()==tip::ItemGroup)
	{
		Group g;
		tip::extract(item, g);
		g.description = mDescriptionTextEdit->document()->toPlainText();
		g.name = mNameLineEdit->text();
		tip::incept(g, item);
	}
}
void ItemEditorGroupPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	SignalBlocker b(  QList<QObject*>()
						<< mNameLineEdit
						<< mDescriptionTextEdit	);
	Q_UNUSED(b)

	if(item->getItemType()==tip::ItemGroup)
	{
		Group g;
		tip::extract(item, g);
		mDescriptionTextEdit->document()->setPlainText(g.description);
		mNameLineEdit->setText(g.name);
	}
}

// -------------------------------- privates ------------------------------------

void ItemEditorGroupPage::setupUi()
{
	QLayout * layout = new QVBoxLayout();

	mNameLineEdit = new LineEdit(this);
	mNameLineEdit->overlay()->setText(tr("Enter a name"));
	mNameLineEdit->setMaxLength(128);
	mDescriptionTextEdit = new PlainTextEdit(this);
	mDescriptionTextEdit->overlay()->setText(tr("Enter a description"));

	setCommitDelay(500);
	connect(mNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mDescriptionTextEdit, SIGNAL(textChanged()), this, SLOT(delayedCommit()));

	layout->addWidget(mNameLineEdit);
	layout->addWidget(mDescriptionTextEdit);
	setLayout(layout);

}


END_NS

