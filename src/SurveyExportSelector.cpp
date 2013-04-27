#include "SurveyExportSelector.h"
#include "global.h"
#include "EditorBasePage.h"

#include "PluginPool.h"
#include "PluginInterfaceSurveyExport.h"

#include <QtGui>

START_NS

SurveyExportSelector::SurveyExportSelector(QWidget *parent) :
    AbstractEditor(parent)
{
	setupUi();
}

void SurveyExportSelector::setupUi()
{
	//loadPlugins();
	QList<PluginInterfaceSurveyExport*> plugins = PluginPool::instance()->surveyExportPlugins();
	foreach(PluginInterfaceSurveyExport * plugin, plugins)
	{
		QString name = plugin->name();
		QString tooltip = plugin->tooltip();
		QString riconname = plugin->iconResourceName();

		int index = addPage(plugin->pageWidget(), QIcon(global::R.getValue(riconname)), name, tooltip);
		mPluginMap.insert(index, plugin);
	}


	pageSelector()->setCurrentRow(0);


}

PluginInterfaceSurveyExport * SurveyExportSelector::getSelectedPlugin() const
{
	int cindex = pageSelector()->currentIndex().row();
	return mPluginMap.value(cindex);
}



// --------------------------- events -----------------------------

void SurveyExportSelector::aboutToChangePage(QWidget * page)
{


}



END_NS
