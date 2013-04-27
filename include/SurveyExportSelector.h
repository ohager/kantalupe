#ifndef SURVEYEXPORTSELECTOR_H
#define SURVEYEXPORTSELECTOR_H

#include <QHash>

#include "AbstractEditor.h"

class QIODevice;

namespace k{

class AbstractTreeModel;
class PluginInterfaceSurveyExport;

class SurveyExportSelector : public AbstractEditor
{
    Q_OBJECT
public:
	SurveyExportSelector(QWidget *parent = 0);
	PluginInterfaceSurveyExport * getSelectedPlugin() const;

protected:
	virtual void aboutToChangePage(QWidget * page);
private:
	void setupUi();

	QHash<int, PluginInterfaceSurveyExport*> mPluginMap;
};

} //eons

#endif // SURVEYEXPORTSELECTOR_H
