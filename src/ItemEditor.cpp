#include "ItemEditor.h"
#include "global.h"

#include "ItemEditorModelPage.h"
#include "ItemEditorProblemPage.h"
#include "ItemEditorCategoryPage.h"
#include "ItemEditorGroupPage.h"
#include "ItemEditorPropertiesPage.h"
#include "ItemEditorProposalPage.h"
#include "ItemEditorMatrixPage.h"
#include "ItemEditorMatrixProblemPage.h"
#include "WidgetExtension.h"
#include <QtGui>

#include "TreeItem.h"
#include "TreeItemProtocol.h"
START_NS



ItemEditor::ItemEditor(QWidget * parent)
	: QWidget(parent, 0x0),
	mModelButton(0x0),
	mCategoryButton(0x0),
	mMatrixButton(0x0),
	mMatrixProblemButton(0x0),
	mGroupButton(0x0),
	mProblemButton(0x0),
	mProposalButton(0x0),
	mPropertiesButton(0x0),
	  mPageModel(0),
	  mPageProblem(0),
	  mPageCategory(0),
	  mPageMatrix(0),
	  mPageMatrixProblem(0),
	  mPageGroup(0),
	  mPageProposal(0),
	  mPageProperties(0)

{
	setupUi();
}

void ItemEditor::setupUi()
{

	mContentsWidget = new QListWidget();
	mContentsWidget->setObjectName("itemEditorMenu");
	mContentsWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	mContentsWidget->setViewMode(QListView::IconMode);
	mContentsWidget->setIconSize(QSize(48, 48));
	mContentsWidget->setUniformItemSizes(true);
	mContentsWidget->setMovement(QListView::Static);
	mContentsWidget->setFixedHeight(90);
	mContentsWidget->setSpacing(8);
	mContentsWidget->setWrapping(false);
	mContentsWidget->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	mContentsWidget->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
	//mContentsWidget->layout()->setAlignment(Qt::AlignCenter);
	mPagesWidget = new QStackedWidget();
	//mPagesWidget->setContentsMargins(0,4,0,0);

	// need to maintain the order according to itemcreation

	mPageModel = mPagesWidget->addWidget( new ItemEditorModelPage() );
	mPageCategory = mPagesWidget->addWidget( new ItemEditorCategoryPage() );
	mPageGroup = mPagesWidget->addWidget( new ItemEditorGroupPage() );
	mPageMatrix = mPagesWidget->addWidget( new ItemEditorMatrixPage() );
	mPageMatrixProblem = mPagesWidget->addWidget( new ItemEditorMatrixProblemPage() );
	mPageProblem = mPagesWidget->addWidget( new ItemEditorProblemPage() );
	mPageProposal = mPagesWidget->addWidget( new ItemEditorProposalPage() );
	mPageProperties = mPagesWidget->addWidget( new ItemEditorPropertiesPage() );


	createItems();
	mContentsWidget->setCurrentRow(0);

	/*
	QPushButton * commitbtn = new QPushButton(tr("Commit"));
	QPushButton * resetbtn = new QPushButton(tr("Reset"));
	connect(commitbtn, SIGNAL(clicked()), this, SLOT(commit()));
	//connect(resetbtn, SIGNAL(clicked()), this, SLOT(reset()));
	QHBoxLayout * btnbox = new QHBoxLayout();
	btnbox->setAlignment(commitbtn, Qt::AlignRight);
	btnbox->setAlignment(resetbtn, Qt::AlignRight);
	*/

	QVBoxLayout *vlayout= new QVBoxLayout;
	vlayout->setMargin(0);
	vlayout->setSpacing(0);
	vlayout->addWidget(mContentsWidget);
	vlayout->addWidget(mPagesWidget);
	//vlayout->addLayout(btnbox);

	/*
	QVBoxLayout *mainlayout = new QVBoxLayout;
	mainlayout->addLayout(hlayout);
	*/
	setLayout(vlayout);

	//setEnabled(false);
	//QTimer::singleShot(0,this, SLOT(openEditorCategory()));
}

void ItemEditor::changePage(QListWidgetItem *current,
							QListWidgetItem *previous)
{
	qDebug("Page change request: from %i to %i", mContentsWidget->row(previous), mContentsWidget->row(current));
	if (!current)
			current = previous;

	mPagesWidget->setCurrentIndex(mContentsWidget->row(current));
}

void ItemEditor::createItems()
{
	QFont f;
	f.setBold(true);

	// keep order to button's creation in setupUi()
	mModelButton = new QListWidgetItem(mContentsWidget);
	mModelButton->setIcon(QIcon(global::R.getValue("icon/itemeditormodel")));
	mModelButton->setText(tr("Model"));
	mModelButton->setFont(f);
	mModelButton->setToolTip(tr("Edit the Model"));
	mModelButton->setTextAlignment(Qt::AlignHCenter);
	mModelButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mModelButton->setHidden(true);


	mCategoryButton = new QListWidgetItem(mContentsWidget);
	mCategoryButton->setIcon(QIcon(global::R.getValue("icon/itemeditorcategory")));
	mCategoryButton->setText(tr("Category"));
	mCategoryButton->setFont(f);
	mCategoryButton->setToolTip(tr("Edit the category"));
	mCategoryButton->setTextAlignment(Qt::AlignHCenter);
	mCategoryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mCategoryButton->setHidden(true);

	mGroupButton = new QListWidgetItem(mContentsWidget);
	mGroupButton->setIcon(QIcon(global::R.getValue("icon/itemeditorgroup")));
	mGroupButton->setText(tr("Group"));
	mGroupButton->setFont(f);
	mGroupButton->setToolTip(tr("Edit the category"));
	mGroupButton->setTextAlignment(Qt::AlignHCenter);
	mGroupButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mGroupButton->setHidden(true);

	mMatrixButton = new QListWidgetItem(mContentsWidget);
	mMatrixButton->setIcon(QIcon(global::R.getValue("icon/itemeditormatrix")));
	mMatrixButton->setText(tr("Matrix"));	
	mMatrixButton->setFont(f);
	mMatrixButton->setToolTip(tr("Edit the matrix item"));
	mMatrixButton->setTextAlignment(Qt::AlignHCenter);
	mMatrixButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mMatrixButton->setHidden(true);

	mMatrixProblemButton = new QListWidgetItem(mContentsWidget);
	mMatrixProblemButton->setIcon(QIcon(global::R.getValue("icon/itemeditormatrixproblem")));
	mMatrixProblemButton->setText(tr("Matrix Problem"));
	mMatrixProblemButton->setFont(f);
	mMatrixProblemButton->setToolTip(tr("Edit the matrix problem item"));
	mMatrixProblemButton->setTextAlignment(Qt::AlignHCenter);
	mMatrixProblemButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mMatrixProblemButton->setHidden(true);


	mProblemButton = new QListWidgetItem(mContentsWidget);
	mProblemButton->setIcon(QIcon(global::R.getValue("icon/itemeditorproblem")));
	mProblemButton->setText(tr("Problem"));
	mProblemButton->setFont(f);
	mProblemButton->setToolTip(tr("Edit the question of current item"));
	mProblemButton->setTextAlignment(Qt::AlignHCenter);
	mProblemButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mProblemButton->setHidden(true);

	mProposalButton = new QListWidgetItem(mContentsWidget);
	mProposalButton->setIcon(QIcon(global::R.getValue("icon/itemeditoranswer")));
	mProposalButton->setText(tr("Proposals"));
	mProposalButton->setToolTip(tr("Edit the proposals/answers of current item"));
	mProposalButton->setTextAlignment(Qt::AlignHCenter);
	mProposalButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mProposalButton->setHidden(true);

	mPropertiesButton= new QListWidgetItem(mContentsWidget);
	mPropertiesButton->setIcon(QIcon(global::R.getValue("icon/itemeditorprops")));
	mPropertiesButton->setText(tr("Properties"));
	mPropertiesButton->setToolTip(tr("Edit the properties of current item"));
	mPropertiesButton->setTextAlignment(Qt::AlignHCenter);
	mPropertiesButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mPropertiesButton->setHidden(true);


	connect(mContentsWidget,
			SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
			this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
}


void ItemEditor::openEditor(TreeItem * item)
{
	setEnabled(true);
	tip::ItemType type = item->getItemType();
	if(type==tip::ItemModel)
	{
		Model m;
		tip::extract(item, m);
		openEditorModel();
	}
	else if(type==tip::ItemCategory)
	{
		Category c;
		tip::extract(item, c);
		openEditorCategory();
	}
	else if(type==tip::ItemGroup)
	{
		Group g;
		tip::extract(item, g);
		openEditorGroup();
	}
	else if(type==tip::ItemMatrix)
	{
		Matrix m;
		tip::extract(item, m);
		openEditorMatrix();
	}
	else if(type==tip::ItemMatrixProblem)
	{
		MatrixProblem m;
		tip::extract(item, m);
		openEditorMatrixProblem();
	}
	else if(type==tip::ItemProblem)
	{
		Problem p;
		tip::extract(item, p);
		openEditorProblem();
	}


	updateEditor(item);
}

void ItemEditor::updateEditor(TreeItem * item)
{
	// broadcast
	for(int i=0; i< mPagesWidget->count(); ++i)
	{
		EditorBasePage * page = (EditorBasePage*)mPagesWidget->widget(i);
		page->update(item);
	}
}

void ItemEditor::commit()
{
	// broadcast
	for(int i=0; i< mPagesWidget->count(); ++i)
	{
		((EditorBasePage*)mPagesWidget->widget(i))->commit();
	}
}


void ItemEditor::openEditorModel()
{
	mModelButton->setHidden(false);
	mCategoryButton->setHidden(true);
	mMatrixButton->setHidden(true);
	mMatrixProblemButton->setHidden(true);
	mGroupButton->setHidden(true);
	mProblemButton->setHidden(true);
	mProposalButton->setHidden(true);
	mPropertiesButton->setHidden(true);

	mContentsWidget->setCurrentItem(mModelButton);
}


void ItemEditor::openEditorCategory()
{
	mModelButton->setHidden(true);
	mCategoryButton->setHidden(false);
	mMatrixButton->setHidden(true);
	mMatrixProblemButton->setHidden(true);
	mGroupButton->setHidden(true);
	mProblemButton->setHidden(true);
	mProposalButton->setHidden(true);
	mPropertiesButton->setHidden(false);

	mContentsWidget->setCurrentItem(mCategoryButton);
}

void ItemEditor::openEditorMatrix()
{
	mModelButton->setHidden(true);
	mCategoryButton->setHidden(true);
	mMatrixButton->setHidden(false);
	mMatrixProblemButton->setHidden(true);
	mGroupButton->setHidden(true);
	mProblemButton->setHidden(true);
	mProposalButton->setHidden(false);
	mPropertiesButton->setHidden(false);

	mContentsWidget->setCurrentItem(mMatrixButton);
}

void ItemEditor::openEditorGroup()
{
	mModelButton->setHidden(true);
	mCategoryButton->setHidden(true);
	mMatrixButton->setHidden(true);
	mMatrixProblemButton->setHidden(true);
	mGroupButton->setHidden(false);
	mProblemButton->setHidden(true);
	mProposalButton->setHidden(true);
	mPropertiesButton->setHidden(false);

	mContentsWidget->setCurrentItem(mGroupButton);
}

void ItemEditor::openEditorProblem()
{
	mModelButton->setHidden(true);
	mCategoryButton->setHidden(true);
	mMatrixButton->setHidden(true);
	mMatrixProblemButton->setHidden(true);
	mGroupButton->setHidden(true);
	mProblemButton->setHidden(false);
	mProposalButton->setHidden(false);
	mPropertiesButton->setHidden(false);

	mContentsWidget->setCurrentItem(mProblemButton);

}

void ItemEditor::openEditorMatrixProblem()
{
	mModelButton->setHidden(true);
	mCategoryButton->setHidden(true);
	mMatrixButton->setHidden(true);
	mMatrixProblemButton->setHidden(false);
	mGroupButton->setHidden(true);
	mProblemButton->setHidden(true);
	mProposalButton->setHidden(false);
	mPropertiesButton->setHidden(false);

	mContentsWidget->setCurrentItem(mMatrixProblemButton);

}




END_NS
