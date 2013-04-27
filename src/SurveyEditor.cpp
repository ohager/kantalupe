#include "SurveyEditor.h"
#include "global.h"

#include "TreeItem.h"
#include "SurveyView.h"
#include "SurveyTree.h"

#include "WritePolicyXml.h"

#include <QtGui>

START_NS

SurveyEditor::SurveyEditor(QWidget *parent) :
    QWidget(parent)
{
	setupUi();
}

void SurveyEditor::onSelectedItem(TreeItem * item)
{
	// eventually some code
	emit selectedItem(item);
}

void SurveyEditor::setupUi()
{
	QLayout * layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	mSurveyView = new SurveyView(this);
	mSurveyView->setModel( new SurveyTree(mSurveyView) );


	//mTaskBar = new QToolBar(this);
	//mTaskBar->setIconSize( QSize(48,48) );

	connect(mSurveyView,SIGNAL(entered(TreeItem*)), this, SLOT(onSelectedItem(TreeItem*)));

	//layout->addWidget(mTaskBar);
	layout->addWidget(mSurveyView);
}

SurveyTree * SurveyEditor::surveyTree()
{
	return mSurveyView->surveyTree();
}

void SurveyEditor::setSurveyTree(SurveyTree * stree)
{
	mSurveyView->setUpdatesEnabled(false);
	mSurveyView->model()->deleteLater();
	stree->setParent(mSurveyView);
	mSurveyView->setModel(stree);
	mSurveyView->expandAll();
	mSurveyView->setUpdatesEnabled(true);
	/*
	WritePolicyXml policy;
	QFile out("survey.xml");
	mSurveyTree->save(&out, policy);
	*/


}


END_NS
