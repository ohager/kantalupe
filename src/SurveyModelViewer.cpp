#include "SurveyModelViewer.h"
#include "global.h"
#include "ModelViewReadOnly.h"
#include "ModelTree.h"
#include "TreeItem.h"

#include <QtGui>

START_NS


SurveyModelViewer::SurveyModelViewer(QWidget *parent) :
	QWidget(parent), mModelView(0x0), mModelTreeData(0x0)
{
	setupUi();
}


void SurveyModelViewer::setupUi()
{
	QLayout * layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	mModelView = new ModelViewReadOnly(this);
	mModelTreeData= new ModelTree();
	mModelView->setModel( mModelTreeData );
	connect(mModelView,SIGNAL(entered(TreeItem*)), this, SLOT(onSelectedItem(TreeItem*)));

	layout->addWidget(mModelView);

	//	more
}

void SurveyModelViewer::onSelectedItem(TreeItem *item){

	Q_ASSERT(item);

	tip::ItemType type = item->getItemType();
	if(type == tip::ItemModel)
	{
	}
	else if(type == tip::ItemCategory)
	{
	}
	else if(type == tip::ItemGroup)
	{
	}
	else if(type == tip::ItemMatrix)
	{
	}
	else
	{
	}
	emit selectedItem(item);
}

END_NS

