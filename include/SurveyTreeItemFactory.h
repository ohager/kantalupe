#ifndef SURVEYITEMFACTORY_H
#define SURVEYITEMFACTORY_H

#include "TreeItemFactory.h"

namespace k{

class SurveyTreeItemFactory : public TreeItemFactory
{
public:
	SurveyTreeItemFactory();
	void applyStyle(TreeItem *item);

protected:
	static void fontStyle(const QString & cstyle, const QString & size, QFont & f);
	static Qt::Alignment align(const QString &ca) ;
};

} // eons

#endif // SURVEYITEMFACTORY_H
