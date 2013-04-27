#ifndef SURVEYEXPORTLIMESURVEY_H
#define SURVEYEXPORTLIMESURVEY_H

#include <QObject>

#include "SurveyExportInterface.h"

namespace k{

class SurveyExportQueXml : public QObject, public SurveyExportInterface
{
	Q_OBJECT
	Q_INTERFACES( SurveyExportInterface );
public:

	SurveyExportQueXml();
	~SurveyExportQueXml();

	virtual QString & iconResourceName() const;
	virtual QString & name() const;
	virtual QString & tooltip() const;
	virtual QWidget * pageWidget() const;
	virtual bool doExport(AbstractTreeModel * survey, QIODevice * out);
protected:
	QWidget * createPageWidget();
private:
	QWidget * mPageWidget;
};

} // eons

#endif // SURVEYEXPORTLIMESURVEY_H
