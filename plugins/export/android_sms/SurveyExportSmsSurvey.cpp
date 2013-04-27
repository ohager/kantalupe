#include "SurveyExportSmsSurvey.h"
#include "AbstractTreeModel.h"
#include "TreeItem.h"

#include <QtGui>

namespace k{

SurveyExportSmsSurvey::SurveyExportSmsSurvey() :
	_pageWidget(0x0)
{
}

SurveyExportSmsSurvey::~SurveyExportSmsSurvey()
{
}
QString SurveyExportSmsSurvey::fileFilter() const  { return tr("SmsSurvey (*.xml)"); }
QString SurveyExportSmsSurvey::iconResourceName() const { return "pluginexport/smssurvey"; }
QString SurveyExportSmsSurvey::name() const { return "SmsSurvey"; }
QString SurveyExportSmsSurvey::tooltip() const { return tr("Exports to SmsSurvey for Android(tm)"); }
QWidget * SurveyExportSmsSurvey::pageWidget()
{
	QWidget * widget = new QWidget();

	widget->setLayout(new QVBoxLayout());
	widget->layout()->addWidget( new QLabel("Not implemented yet"));


	return widget;
}

SurveyExportSmsSurvey::TraversalType SurveyExportSmsSurvey::visit(TreeItem * item)
{
	//tip::ItemType type = item->getItemType();

	return TraversalEnd;
}

void SurveyExportSmsSurvey::leave(TreeItem * item)
{

}


bool SurveyExportSmsSurvey::doExport(AbstractTreeModel * survey, QIODevice * out)
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

	return false;
}


} // eons

Q_EXPORT_PLUGIN2(export_smssurvey, k::SurveyExportSmsSurvey)

