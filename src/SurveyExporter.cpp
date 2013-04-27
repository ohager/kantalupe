#include "SurveyExporter.h"
#include "global.h"

#include "SurveyTree.h"
#include "SurveyView.h"
#include "SurveyExportSelector.h"

#include "PluginInterfaceSurveyExport.h"

#include "ShortMessage.h"

#include <QtGui>

START_NS

SurveyExporter::SurveyExporter(SurveyExportSelector * selector,  QWidget *parent)
	: QWidget(parent),
	  mSurveyView(0x0),
	  _exportSelector(selector),
	  mTaskBar(0x0),
	  mActionExport(0x0)
{
	Q_ASSERT(_exportSelector);
	setupUi();
}


SurveyTree * SurveyExporter::surveyTree()
{
	return static_cast<SurveyTree*>(mSurveyView->model());
}


void SurveyExporter::setSurveyTree(SurveyTree * stree)
{
	mSurveyView->setUpdatesEnabled(false);
	mSurveyView->model()->deleteLater();
	stree->setParent(mSurveyView);
	mSurveyView->setModel(stree);
	mSurveyView->expandAll();
	mSurveyView->setUpdatesEnabled(true);

}


void SurveyExporter::setupUi()
{

	QLayout * layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	mSurveyView = new SurveyView(this);
	mSurveyView->setModel( new SurveyTree(mSurveyView) );

	mTaskBar = new QToolBar(this);
	mTaskBar->setIconSize( QSize(48,48) );

	mActionExport = mTaskBar->addAction(
					QIcon(global::R.getValue("icon/exporttask")),
					tr("Export"),
					this,
					SLOT(doExport()));

	//connect(mSurveyView, SIGNAL(loaded(bool)), mActionExport, SLOT(setEnabled(bool)));

	layout->addWidget(mTaskBar);
	layout->addWidget(mSurveyView);
}



void SurveyExporter::doExport()
{
	if(mSurveyView->surveyTree()->rootItem()->rowCount()==0)
	{
		ShortMessage::showMessage(this, tr("Please, load a survey first"));
		return;
	}

	PluginInterfaceSurveyExport * plugin = exportSelector()->getSelectedPlugin();

	QString filename = QFileDialog::getSaveFileName(this,
				tr("Export Survey for %1").arg(plugin->name()),
				QString("./exports"),
				plugin->fileFilter());

	if(filename.isEmpty())
		return;

	QFile out(filename);
	if(plugin->doExport(surveyTree(), &out))
	{
		ShortMessage::showMessage(this, tr("Survey exported successfully"));
	}
	else
	{
		ShortMessage::showMessage(this, tr("Sorry, Survey export failed."));
	}
}



END_NS


