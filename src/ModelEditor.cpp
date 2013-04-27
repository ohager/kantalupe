#include "ModelEditor.h"
#include "global.h"
#include "ModelView.h"
#include "ModelTree.h"
#include "TreeItem.h"

#include "ModalLabel.h"

#include <QtGui>

START_NS


ModelEditor::ModelEditor(QWidget *parent) :
	QWidget(parent), mModelView(0x0), mModelTreeData(0x0), mTaskBar(0x0)
{
	setupUi();
}


void ModelEditor::setupUi()
{
	QLayout * layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	mModelView = new ModelView(this);
	mModelTreeData= new ModelTree(mModelView); // bind model to view
	mModelView->setModel( mModelTreeData );
	//connect(mModelView,SIGNAL(entered(ModelTreeDataItem*)), this, SIGNAL(selectedItem(ModelTreeDataItem*)));
	connect(mModelView,SIGNAL(entered(TreeItem*)), this, SLOT(onSelectedItem(TreeItem*)));
	//connect(mModelView,SIGNAL(clicked(ModelTreeDataItem*)),this,SIGNAL(clickedItem(ModelTreeDataItem*)));

	//connect(mModelView->modelTreeData(),SIGNAL(addedItem(ModelTreeDataItem*)),this,SIGNAL(addedItem(ModelTreeDataItem*)));

	mTaskBar = new QToolBar(this);
	mTaskBar->setIconSize( QSize(48,48) );
	mActionNewCategory = mTaskBar->addAction(
					QIcon(global::R.getValue("icon/itemeditorcategory")),
					tr("Add category"),
					mModelView,	SLOT(addNewCategory()));

	mActionNewGroup = mTaskBar->addAction(
					QIcon(global::R.getValue("icon/itemeditorgroup")),
					tr("Add category"),
					mModelView, SLOT(addNewGroup()));


	mActionNewMatrix= mTaskBar->addAction(
					QIcon(global::R.getValue("icon/itemeditormatrix")),
					tr("Add matrix"),
					mModelView, SLOT(addNewMatrix()));


	mActionNewMatrixProblem = mTaskBar->addAction(
					QIcon(global::R.getValue("icon/itemeditormatrixproblem")),
					tr("Add matrix problem"),
					mModelView, SLOT(addNewMatrixProblem()));

	mActionNewProblem = mTaskBar->addAction(
					QIcon(global::R.getValue("icon/itemeditorproblem")),
					tr("Add problem"),
					mModelView, SLOT(addNewProblem()));

	// disable all initially
	mActionNewCategory->setEnabled(false);
	mActionNewGroup->setEnabled(false);
	mActionNewMatrix->setEnabled(false);
	mActionNewMatrixProblem->setEnabled(false);
	mActionNewProblem->setEnabled(false);

	layout->addWidget(mTaskBar);
	layout->addWidget(mModelView);

	//	more
}

void ModelEditor::onSelectedItem(TreeItem *item){

	Q_ASSERT(item);

	tip::ItemType type = item->getItemType();
	if(type == tip::ItemModel)
	{
		mActionNewCategory->setEnabled(true);
		mActionNewGroup->setEnabled(false);
		mActionNewMatrix->setEnabled(false);
		mActionNewMatrixProblem->setEnabled(false);
		mActionNewProblem->setEnabled(false);
	}
	else if(type == tip::ItemCategory)
	{
		mActionNewCategory->setEnabled(true);
		mActionNewGroup->setEnabled(true);
		mActionNewMatrix->setEnabled(false);
		mActionNewMatrixProblem->setEnabled(false);
		mActionNewProblem->setEnabled(false);
	}
	else if(type == tip::ItemGroup)
	{
		mActionNewCategory->setEnabled(false);
		mActionNewGroup->setEnabled(false);
		mActionNewMatrix->setEnabled(true);
		mActionNewMatrixProblem->setEnabled(false);
		mActionNewProblem->setEnabled(true);
	}
	else if(type == tip::ItemMatrix)
	{
		mActionNewCategory->setEnabled(false);
		mActionNewGroup->setEnabled(false);
		mActionNewMatrix->setEnabled(false);
		mActionNewMatrixProblem->setEnabled(true);
		mActionNewProblem->setEnabled(false);
	}
	else {
		mActionNewCategory->setEnabled(false);
		mActionNewGroup->setEnabled(false);
		mActionNewMatrix->setEnabled(false);
		mActionNewMatrixProblem->setEnabled(false);
		mActionNewProblem->setEnabled(false);

	}
	emit selectedItem(item);
}

END_NS

