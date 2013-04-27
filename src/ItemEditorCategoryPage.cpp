#include "ItemEditorCategoryPage.h"
#include "PlainTextEdit.h"
#include "LineEdit.h"
#include "Overlay.h"
#include "global.h"

#include "AbstractTreeModel.h"
#include "VisitorNumberCategories.h"
#include "TreeItemProtocol.h"
#include "TreeItem.h"
#include "SignalBlocker.h"


#include <QtGui>

START_NS

ItemEditorCategoryPage::ItemEditorCategoryPage(QWidget * parent)
	: EditorBasePage(parent) {

	setupUi();
}

ItemEditorCategoryPage::~ItemEditorCategoryPage()
{

}

bool ItemEditorCategoryPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}


void ItemEditorCategoryPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);
	if(item->getItemType()==tip::ItemCategory)
	{
		Category c;
		tip::extract(item, c);
		c.description = mDescriptionTextEdit->document()->toPlainText();
		c.name = mNameLineEdit->text();
		tip::incept(c, item);
		// need to update the numbering
		VisitorNumberCategories v;
		item->treeModel()->traverse(&v);
	}

}
void ItemEditorCategoryPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	SignalBlocker b(  QList<QObject*>()
						<< mNameLineEdit
						<< mDescriptionTextEdit	);
	Q_UNUSED(b)

	if(item->getItemType()==tip::ItemCategory)
	{
		Category c;
		tip::extract(item, c);
		mDescriptionTextEdit->document()->setPlainText(c.description);
		mNameLineEdit->setText(c.name);
	}
}

void ItemEditorCategoryPage::setupUi()
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

