#ifndef SURVEYEXPORTSMSSURVEY_H
#define SURVEYEXPORTSMSSURVEY_H

#include <QObject>

#include "PluginInterfaceSurveyExport.h"

namespace k{

class SurveyExportSmsSurvey : public QObject, public PluginInterfaceSurveyExport
{
	Q_OBJECT
	Q_INTERFACES( k::PluginInterfaceSurveyExport );
	PLUGIN_ID(SurveyExportSmsSurvey, 1.0)
public:
	SurveyExportSmsSurvey();
	~SurveyExportSmsSurvey();

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

#endif // SURVEYEXPORTSMSSURVEY_H
