#include "SurveyExportLimeSurvey.h"

#include <QtGui>

namespace k{

SurveyExportLimeSurvey::SurveyExportLimeSurvey() :
	_pageWidget(0x0)
{
}

SurveyExportLimeSurvey::~SurveyExportLimeSurvey()
{
}
QString SurveyExportLimeSurvey::fileFilter() const  { return tr("LimeSurvey Survey (*.lss)"); }
QString SurveyExportLimeSurvey::iconResourceName() const { return "pluginexport/limesurvey"; }
QString SurveyExportLimeSurvey::name() const { return "LimeSurvey"; }
QString SurveyExportLimeSurvey::tooltip() const { return tr("Exports to LimeSurvey XML (need LimeSurvey Version 1.9+)"); }
QWidget * SurveyExportLimeSurvey::pageWidget()
{
	QWidget * widget = new QWidget();

	widget->setLayout(new QVBoxLayout());
	widget->layout()->addWidget( new QLabel("Implement the limesurvey plugin!!!"));


	return widget;
}

SurveyExportLimeSurvey::TraversalType SurveyExportLimeSurvey::visit(TreeItem * item)
{
	return TraversalEnd;
}

void SurveyExportLimeSurvey::leave(TreeItem * item)
{

}


bool SurveyExportLimeSurvey::doExport(AbstractTreeModel * survey, QIODevice * out)
{
	Q_ASSERT(survey);
	Q_ASSERT(out);

	if(out->isOpen())
	{
		out->close();
	}

	if(!out->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return false;
	}

	// go on!

	return false;
}


} // eons

Q_EXPORT_PLUGIN2(export_limesurvey, k::SurveyExportLimeSurvey)

