#ifndef PLUGINPOOL_H
#define PLUGINPOOL_H

#include <QHash>

namespace k{

class PluginInterface;
class PluginInterfaceSurveyExport;

/** @ingroup plugins
  The singleton plugin pool that provides access to all available plugins.
  @todo Extend when more plugin types shoiuld be suppported
  @author O. Haeger
  */
class PluginPool
{
public:
	/**
	  Destroys the pool and releases allocated resources.
	  */
	static void destroy();
	/**
	  @return The instance. Plugins are loaded layzily, i.e. on first call
	  */
	static PluginPool * instance();

	/**
	  @return The survey export plugins.
	  */
	QList<PluginInterfaceSurveyExport*> surveyExportPlugins() const;

	// more types here!

private:

	enum PluginType{ // plugin type
		SurveyExport=1
		// more types here
	};

    PluginPool();
	~PluginPool();
	void loadPlugins(); // extend when more types come up

	QHash<PluginType, PluginInterface*> mPlugins;
	static PluginPool * sInstance;
};

} //eons

#endif // PLUGINPOOL_H
