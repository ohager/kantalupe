#include "PluginPool.h"
#include "PluginInterface.h"
#include "PluginInterfaceSurveyExport.h"
#include "global.h"

#include <QtCore>

START_NS

PluginPool * PluginPool::sInstance=0x0;

PluginPool * PluginPool::instance()
{
	if(!sInstance)
	{
		// load once and only!
		sInstance = new PluginPool();
		sInstance->loadPlugins();
	}
	return sInstance;
}


QList<PluginInterfaceSurveyExport*> PluginPool::surveyExportPlugins() const
{
	QList<PluginInterfaceSurveyExport*> result;
	QList<PluginInterface*> plugins = mPlugins.values(SurveyExport);
	foreach(PluginInterface * p , plugins)
	{
		result.push_back(static_cast<PluginInterfaceSurveyExport*>(p));
	}
	return result;
}


PluginPool::PluginPool()
{
}

PluginPool::~PluginPool()
{
	/* from qt-doc:
	[Don't try to delete the root component. Instead rely on that unload() will automatically delete it when needed.]
	foreach(PluginInterface * p, mPlugins)
	{
		delete p; p=0x0;
	}
	*/
	mPlugins.clear();

}

void PluginPool::destroy()
{
	delete sInstance;
	sInstance = 0x0;
}


void PluginPool::loadPlugins()
{

	QDir pluginsDir = QDir(qApp->applicationDirPath());
	pluginsDir.cd(global::R.getValue("general/pluginbasedir"));
	pluginsDir.cd(global::R.getValue("pluginexport/directory"));

	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
	{
		QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
		if(QObject *pluginObj = loader.instance() )
		{
			PluginInterfaceSurveyExport * plugin = qobject_cast<PluginInterfaceSurveyExport*>(pluginObj);
			mPlugins.insertMulti(SurveyExport, plugin);
		}
	}
}

END_NS

