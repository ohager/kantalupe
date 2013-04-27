#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>

/** @defgroup plugins Plugin System
  The kantalupe editor can be extended by plugins. It is possible to add for example new export
  formats. This sections describes how to develop custom plugins for kantalupe-edit.
	The current version supports plugin for following tasks:
	- Survey Export
  */

/** @ingroup plugins
  A macro that helps to generate a consistent plugin id.
  @param classname The classname of your plugin
  @param version The version
  @code
  class MyPlugin : public PluginInterface, [..]
  {
	PLUGIN_ID(MyPlugin, 1.0)
  public:
		// ...
  };
  */
#define PLUGIN_ID(classname,version) public: QString id() const { return "plugin.kantalupe."#classname"/"#version; }

namespace k{



/**
  @ingroup plugins
  Interface for Plugins, that can be used with PluginPool
  A plugin that is maintained by PluginPool needs an unique identifier.
  For convenience and consistency it is recommended to use the @ref PLUGIN_ID macro in
  PluginInterface based implementations.
  @author O. Haeger
  */
class PluginInterface
{
public:
	/**
	  A unique identifier.
	  @see also @ref PLUGIN_ID()
	  */
	virtual QString id() const=0;
};

} // eons

//Q_DECLARE_INTERFACE(k::PluginInterface, "com.clayhouse.kantalupe.PluginInterface/1.0")

#endif // PLUGININTERFACE_H
