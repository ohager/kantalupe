#include "ItemEditorModelPage.h"
#include "global.h"

#include "LineEdit.h"
#include "Overlay.h"
#include "SignalBlocker.h"
#include "ModelTree.h"
#include "TreeItemProtocol.h"
#include "TreeItem.h"

#include "VisitorGenerateHashUid.h"

#include <QtGui>

START_NS

ItemEditorModelPage::ItemEditorModelPage(QWidget *parent) :
	EditorBasePage(parent),
	mNameTextEdit(0x0),
	mUidModeComboBox(0x0)

{
	setupUi();
}


void ItemEditorModelPage::setupUi()
{
	QBoxLayout * layout = new QVBoxLayout();

	mNameTextEdit = new k::LineEdit(this);
	mNameTextEdit->overlay()->setText(tr("Enter model name"));


	// item uid descriptors are in conformance to kml's <UidGeneration mode="">
	QLayout * uidlayout = new QHBoxLayout();
	QLabel * uidtext = new QLabel(tr("Select the kind of Unique Identifier generation"),this);

	mUidModeComboBox = new QComboBox(this);
	mUidModeComboBox->addItem(tr("Manual"), Model::UidManual);
	mUidModeComboBox->addItem(tr("Automatic Hash"), Model::UidHash);
	mUidModeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

	uidlayout->addWidget(uidtext);
	uidlayout->addWidget(mUidModeComboBox);

	setCommitDelay(500);
	connect(mNameTextEdit, SIGNAL(textChanged(QString)), this, SLOT(delayedCommit()));
	connect(mUidModeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeUidMode()));

	layout->addWidget(mNameTextEdit);
	layout->addLayout(uidlayout);
	layout->addStretch();
	setLayout(layout);
	// think about statistics item
}

bool ItemEditorModelPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}

void ItemEditorModelPage::update(TreeItem * item)
{
	EditorBasePage::update(item);
	SignalBlocker b( QList<QObject*>() <<
					mUidModeComboBox <<
					mNameTextEdit
					);
	Q_UNUSED(b);
	if(item->getItemType()==tip::ItemModel){
		Model m;
		tip::extract(item, m);

		int index = mUidModeComboBox->findData((int)m.uidMode);
		mUidModeComboBox->setCurrentIndex(index);
		mNameTextEdit->setText( m.name );
	}
}


void ItemEditorModelPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);
	if(item->getItemType()==tip::ItemModel){
		Model m;
		tip::extract(item, m);

		int index = mUidModeComboBox->currentIndex();
		m.uidMode = (Model::UidMode)mUidModeComboBox->itemData(index).toInt();
		m.name = mNameTextEdit->text();

		tip::incept(m, item);
	}
}

// ---------------------------- slots -------------------------------------
void ItemEditorModelPage::onChangeUidMode(){

	int index = mUidModeComboBox->currentIndex();
	Model::UidMode uidmode = (Model::UidMode)mUidModeComboBox->itemData(index).toInt();
	if(uidmode == Model::UidManual)
		return;

	// else
	int btn = QMessageBox::question(this, tr("Automatic Uid Generation Request"),
						  tr("Automatic generation mode for Unique Identifiers\n"
							 "will overwrite all identifiers of the entire model.\n\n"
							 "Do you really pretend to do this?"),
							tr("Yes"), tr("No"),QString(),1  );

	if(btn == 0) // 'yes'
	{
		if(uidmode == Model::UidHash)
		{
			TreeItem * modelitem = buddyItem();
			ModelTree * model= (ModelTree *)modelitem->model();

			VisitorGenerateHashUid genhashes;
			model->traverse( &genhashes );
			commit(modelitem);
		}
	}
	else
	{
		/* do nothing */
	}
}

END_NS

