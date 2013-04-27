#ifndef SURVEYEXPORTLIMESURVEY_H
#define SURVEYEXPORTLIMESURVEY_H

#include <QObject>

#include "PluginInterfaceSurveyExport.h"

namespace k{

class SurveyExportLimeSurvey : public QObject, public PluginInterfaceSurveyExport
{
	Q_OBJECT
	Q_INTERFACES( k::PluginInterfaceSurveyExport );
	PLUGIN_ID(SurveyExportLimeSurvey, 1.0)
public:
	SurveyExportLimeSurvey();
	~SurveyExportLimeSurvey();

	virtual QString fileFilter() const;
	virtual QString iconResourceName() const;
	virtual QString name() const;
	virtual QString tooltip() const;
	virtual QWidget * pageWidget();
	virtual bool doExport(AbstractTreeModel * survey, QIODevice * out);

	virtual TraversalType visit(TreeItem * item);
	virtual void leave(TreeItem * item);
protected:
	QWidget * createPageWidget();

private:
	QWidget * _pageWidget;
};

} // eons

#endif // SURVEYEXPORTLIMESURVEY_H
