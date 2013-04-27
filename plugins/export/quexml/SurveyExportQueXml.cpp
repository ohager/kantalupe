#include "SurveyExportQueXml.h"
#include "AbstractTreeModel.h"
#include "TreeItem.h"
#include "WritePolicyQueXml.h"

#include <QtGui>
#include <QXmlStreamWriter>

namespace k{

SurveyExportQueXml::SurveyExportQueXml() :
	_pageWidget(0x0)
{
}

SurveyExportQueXml::~SurveyExportQueXml()
{
}
QString SurveyExportQueXml::fileFilter() const  { return tr("QueXML Survey (*.xml)"); }
QString SurveyExportQueXml::iconResourceName() const { return "pluginexport/quexml"; }
QString SurveyExportQueXml::name() const { return "QueXML"; }
QString SurveyExportQueXml::tooltip() const { return tr("Exports to QueXML"); }
QWidget * SurveyExportQueXml::pageWidget()
{
	QWidget * widget = new QWidget();

	widget->setLayout(new QVBoxLayout());
	widget->layout()->addWidget( new QLabel("Currently nothing to setup. Exports still works"));


	return widget;
}

SurveyExportQueXml::TraversalType SurveyExportQueXml::visit(TreeItem * item)
{
	//tip::ItemType type = item->getItemType();

	return TraversalEnd;
}

void SurveyExportQueXml::leave(TreeItem * item)
{

}


bool SurveyExportQueXml::doExport(AbstractTreeModel * survey, QIODevice * out)
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

	// using a
	WritePolicyQueXml policy;
	return survey->save(out, policy);
}


} // eons

Q_EXPORT_PLUGIN2(export_quexml, k::SurveyExportQueXml)

