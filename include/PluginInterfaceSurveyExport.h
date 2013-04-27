#ifndef SURVEYEXPORTINTERFACE_H
#define SURVEYEXPORTINTERFACE_H

#include "PluginInterface.h"
#include "AbstractTreeModelVisitor.h"
#include <QtPlugin>

class QIODevice;
class QWidget;

namespace k{

class AbstractTreeModel;

/** @ingroup plugins
  The interface for surveys export plugins.
  @author O. Haeger
  */
class PluginInterfaceSurveyExport : public PluginInterface, public AbstractTreeModelVisitor
{
public:

	/**
	  @return A file filter descriptor. See also QFile for such filter.
	  */
	virtual QString fileFilter() const = 0;

	/**
	  The icon file name according to the X Resource Sytem (xrs)
	  That is, of form "<prefix>/<alias>"
	  The resource must exist and be registered in kantalupe's resource file.
	  The icon represents the plugin in the kantalupe editor.
	  */
	virtual QString iconResourceName() const = 0;

	/**
	  The name used additionally to icon representation.
	  */
	virtual QString name() const = 0;

	/**
	  A tooltip explaining briefly this plugin
	  */
	virtual QString tooltip() const = 0;

	/**
	  The page widget, that is shown when plugin is activated.
	  The page will be embedded in a vertical box layout.
	  You must create the widget here each call. Do not construct once and return
	  its reference only, as this leads to undefined behaviour.
	  @par Do @e not do this:
	  @code
	  QWidget * MyPlugin::pageWidget()
	  {
		if(!mWidget) // bad idea!
		{
			mWidget = new QWidget();
			// ...
		}
		return mWidget;
	  }
	  @endcode
	  */
	virtual QWidget * pageWidget() = 0;

	/**
	  Exports the survey to given I/O Device.
	  @param survey The survey object model
	  @param out The device where shall be exported
	  @return @e true, if export was successful, otherwise @e false
	  */
	virtual bool doExport(AbstractTreeModel * survey, QIODevice * out)=0;
};


} // eons

Q_DECLARE_INTERFACE(k::PluginInterfaceSurveyExport, "com.clayhouse.kantalupe.edit.PluginInterfaceSurveyExport/1.0")


#endif // SURVEYEXPORTINTERFACE_H
