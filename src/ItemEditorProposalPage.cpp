#include "ItemEditorProposalPage.h"
#include "PlainTextEdit.h"
#include "ProposalTreeWidget.h"
#include "ImageListWidget.h"
#include "LineEdit.h"
#include "Overlay.h"
#include "WidgetExtension.h"
#include "WxListenerImageListWidget.h"
#include "global.h"

#include "TreeItemProtocol.h"
#include "TreeItem.h"

#include "SignalBlocker.h"

#include <QtGui>

START_NS

ItemEditorProposalPage::ItemEditorProposalPage(QWidget * parent)
	: EditorBasePage(parent),
	mProposalOverview(0x0),
	mProposalTextEdit(0x0)
{
	setupUi();
}

ItemEditorProposalPage::~ItemEditorProposalPage()
{

}

bool ItemEditorProposalPage::isAcceptingMime(const QMimeData *m) const
{
	return false;
}

// interface implementation
void ItemEditorProposalPage::commit(TreeItem * item) const
{
	EditorBasePage::commit(item);
	tip::ItemType type = item->getItemType();
	if(type == tip::ItemMatrix)
	{
		Matrix obj;
		tip::extract(item, obj); // get current data
		obj.proposals = mProposalOverview->getProposals();
		obj.isMultipleChoice = mMultipleChoiceCheck->isChecked();
		tip::incept(obj, item); // commit
	}
	else if(type == tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj); // get current data
		obj.proposals = mProposalOverview->getProposals();
		obj.solutions = mProposalOverview->getSolutions();
		obj.isMultipleChoice = mMultipleChoiceCheck->isChecked();
		tip::incept(obj, item); // commit
	}
	else if(type == tip::ItemMatrixProblem)
	{
		MatrixProblem obj;
		tip::extract(item, obj); // get current data
		obj.solutions = mProposalOverview->getSolutions();
		tip::incept(obj, item); // commit
	}



}
void ItemEditorProposalPage::update(TreeItem * item)
{
	EditorBasePage::update(item);

	SignalBlocker b( QList<QObject*>() <<
					mProposalOverview <<
					mMultipleChoiceCheck
					);

	Q_UNUSED(b)

	mProposalOverview->setUpdatesEnabled(false);
	mProposalOverview->clear();
	tip::ItemType type = item->getItemType();
	if(type == tip::ItemMatrix)
	{
		Matrix obj;
		tip::extract(item, obj);
		mMultipleChoiceCheck->setVisible(true);
		mMultipleChoiceCheck->setChecked( obj.isMultipleChoice );
		mProposalOverview->setSolutionSelectionMultiple( obj.isMultipleChoice );
		mProposalOverview->setColumnHidden(ProposalTreeWidget::ColumnSolutionCheck, true);
		mProposalOverview->setAddRemoveEnabled(true);
		foreach(const Proposal & p, obj.proposals) // are ordered (and must be)
		{
			mProposalOverview->addProposalItem(p, false); // solution does not matter!
		}
	}
	else if(type == tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj);

		mMultipleChoiceCheck->setVisible(true);
		mMultipleChoiceCheck->setChecked( obj.isMultipleChoice );
		mProposalOverview->setSolutionSelectionMultiple( obj.isMultipleChoice );
		mProposalOverview->setColumnHidden(ProposalTreeWidget::ColumnSolutionCheck, false);

		mProposalOverview->setAddRemoveEnabled(true);
		foreach(const Proposal & p, obj.proposals) // are ordered (and must be)
		{
			mProposalOverview->addProposalItem(p, obj.solutions.contains( p.id ));
		}
	}
	else if(type == tip::ItemMatrixProblem)
	{
		MatrixProblem obj;
		tip::extract(item, obj);

		/*
		matrix problems do not have their own proposals. they are provided by their matrix.
		while proposals are added on matrix item edit, the solutions are set with each new
		problem.
		*/
		mMultipleChoiceCheck->setVisible(false);
		mProposalOverview->setColumnHidden(ProposalTreeWidget::ColumnSolutionCheck, false);
		mProposalOverview->setAddRemoveEnabled(false);

		// get related matrix, to fetch its proposals
		TreeItem * mitem = (TreeItem*)item->parent();
		Q_ASSERT(mitem);
		Matrix matrix;
		tip::extract(mitem, matrix);

		if(matrix.proposals.empty()){
			mProposalOverview->overlay()->setText(tr("Please add proposals to related Matrix item"));
		}
		else{
			mProposalOverview->setSolutionSelectionMultiple( matrix.isMultipleChoice );
			foreach(const Proposal & p, matrix.proposals) // are ordered (and must be)
			{
				mProposalOverview->addProposalItem(p, obj.solutions.contains( p.id ));
			}
		}

	}

	mProposalOverview->resizeColumnToContents(ProposalTreeWidget::ColumnId);
	mProposalOverview->resizeColumnToContents(ProposalTreeWidget::ColumnProposalText);
	mProposalOverview->resizeColumnToContents(ProposalTreeWidget::ColumnSolutionCheck);
	mProposalOverview->setUpdatesEnabled(true);
}


void ItemEditorProposalPage::setupUi()
{
	QLayout * layout = new QVBoxLayout();

	mMultipleChoiceCheck = new QCheckBox(tr("These proposals are 'multiple choice'"), this);
	mMultipleChoiceCheck->setChecked(false);
	connect(mMultipleChoiceCheck, SIGNAL(clicked(bool)), this, SLOT(onMultipleChoiceClicked(bool)));

	QSplitter * splitter = new QSplitter(Qt::Vertical,this);
	splitter->setChildrenCollapsible(false);

	mProposalOverview = new k::ProposalTreeWidget(this);
	connect(mProposalOverview, SIGNAL(rowSelected(int)),this, SLOT(onSelectedRow(int)));
	//connect(mProposalOverview, SIGNAL(itemChanged(QTreeWidgetItem*,int)),this, SLOT(onItemChanged(QTreeWidgetItem*,int)));
	connect(mProposalOverview, SIGNAL(itemChanged(QTreeWidgetItem*,int)),this, SLOT(delayedCommit()));
	connect(mProposalOverview, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(onDoubleClickedProposal(QModelIndex)));


/*
	mEditPart = new QWidget(this);
	mEditPart->setEnabled(false);
*/
	mProposalTextEdit = new PlainTextEdit(this);
	mProposalTextEdit->overlay()->setText(tr("Enter a proposal text"));
	mProposalTextEdit->setEnabled(false);
	connect(mProposalTextEdit,SIGNAL(textChanged()),this, SLOT(onProposalTextChanged()));
/*
	QLayout * sublayout = new QVBoxLayout();
	sublayout->addWidget(mProposalTextEdit);

	mEditPart->setLayout(sublayout);
*/
	/*
	mImageListWidget = new ImageListWidget(1,this);
	mImageListWidget->setFlow(ImageListWidget::TopToBottom);
	mImageListWidget->setFixedWidth(90);
	mImageListWidget->setIconSize(QSize(64,64));
	mImageListWidget->setImageLabelingEnabled(false);
	WidgetExtension * wxe = new WidgetExtension(mImageListWidget,;
												k::WidgetExtension::ShowDropIndicator);
	wxe->setListener( new k::WxListenerImageListWidget() );
	connect(mImageListWidget,SIGNAL(contentChanged()),this, SLOT(onProposalImageChanged()));


	mSolutionCheck = new QCheckBox(this);
	mSolutionCheck->setText("This proposal is a solution");
	mSolutionCheck->setChecked(false);
	connect(mSolutionCheck,SIGNAL(toggled(bool)),this, SLOT(onSolutionCheckChanged(bool)));

	QGridLayout * sublayout = new QGridLayout();
	sublayout->setMargin(0);

	sublayout->addWidget(mProposalTextEdit,0,0);
	sublayout->addWidget(mImageListWidget,0,1);
	sublayout->addWidget(mSolutionCheck,1,0);
	mEditPart->setLayout(sublayout);
	*/

	splitter->addWidget(mProposalOverview);
	splitter->addWidget(mProposalTextEdit);
	//splitter->addWidget(mEditPart);


	layout->addWidget(mMultipleChoiceCheck);
	layout->addWidget(splitter);

	setLayout(layout);

}


// ---------------------------------------------- SLOTS -----------------------------

void ItemEditorProposalPage::onDoubleClickedProposal(QModelIndex clicked)
{
	mProposalTextEdit->setFocus(Qt::TabFocusReason);
	mProposalTextEdit->textCursor().setPosition( mProposalTextEdit->document()->characterCount() );
}

void ItemEditorProposalPage::onMultipleChoiceClicked(bool multiple){
	mProposalOverview->setSolutionSelectionMultiple(multiple);
	mProposalOverview->clearSolutionSelection();
}

/*
void ItemEditorProposalPage::onItemChanged(QTreeWidgetItem * item, int column)
{
	Q_UNUSED(item)
	if(column==k::ProposalTreeWidget::ColumnSolutionCheck)
	{
		types::Solutions sols=mProposalOverview->getSolutions();
		//mMultipleChoiceCheck->setChecked(sols.count()>1);
	}
}
*/
void ItemEditorProposalPage::onSelectedRow(int r)
{
//	mEditPart->setEnabled(true);

	Proposal p = mProposalOverview->getProposalData(r);

	mProposalTextEdit->setEnabled(true);
	mProposalTextEdit->document()->setPlainText( p.text );

	/*
	mSolutionCheck->setChecked( mProposalOverview->itemIsSolution(r) );
	// next op would signal a contentChanged signal... which in turn would clear
	// the image for the row @e r... so we block signal
	mImageListWidget->blockSignals(true);
	mImageListWidget->removeAllImages();
	mImageListWidget->blockSignals(false);
	QString imgfile(mProposalOverview->itemProposalImageFile(r));
	qDebug("image file: %s", imgfile.toAscii().data());
	if(!imgfile.isNull())
	{
		mImageListWidget->addImage( imgfile );
	}
	*/

}

void ItemEditorProposalPage::onProposalTextChanged()
{

	mProposalOverview->setProposalItemText(mProposalOverview->selectedRow(),
										mProposalTextEdit->document()->toPlainText());
}


/*
void ItemEditorProposalPage::onProposalImageChanged()
{

	QString imgurl =
			mImageListWidget->count()== 0 ? QString() :
			mImageListWidget->imageUrl( mImageListWidget->item(0) );// has only one image
	qDebug("on image change file: %s", imgurl.toAscii().data());
	mProposalOverview->setItemProposalImageFile(mProposalOverview->selectedRow(), imgurl);
}


void ItemEditorProposalPage::onSolutionCheckChanged(bool checked)
{
	//mProposalOverview->setItemIsSolution(mProposalOverview->selectedRow(), checked);

}
*/

END_NS

