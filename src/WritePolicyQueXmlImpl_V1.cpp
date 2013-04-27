#include "WritePolicyQueXmlImpl_V1.h"
#include "AbstractTreeModel.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
//#include "global.h"

#include <QDate>

namespace k{

const char * WritePolicyQueXmlImpl_V1::Version = "1";

WritePolicyQueXmlImpl_V1::WritePolicyQueXmlImpl_V1() :
	mHasError(false)
{
}

bool WritePolicyQueXmlImpl_V1::write(AbstractTreeModel * mtd, QIODevice *out)
{
	if(out->isOpen())
		out->close();
	if(!out->open(QIODevice::WriteOnly))
	{
		qDebug("Could not open device");
	}

	mWriter.setDevice(out);
	mWriter.setCodec("utf-8");
	mWriter.setAutoFormatting(true);
	mWriter.setAutoFormattingIndent(-1); // 1 tab indent
	mWriter.writeStartDocument();
	mtd->traverse(this);
	mWriter.writeEndDocument();

	out->close();
	return !mHasError;
}

bool WritePolicyQueXmlImpl_V1::write(TreeItem * startnode, QIODevice *out)
{

	if(out->isOpen())
		out->close();
	if(!out->open(QIODevice::WriteOnly))
	{
		qDebug("Could not open device");
	}

	mWriter.setDevice(out);
	mWriter.setCodec("utf-8");
	mWriter.setAutoFormatting(true);
	mWriter.setAutoFormattingIndent(-1); // 1 tab indent
	mWriter.writeStartDocument();


	AbstractTreeModel * mtd = (AbstractTreeModel*)startnode->model();
	mtd->traverse(this, startnode);
	mWriter.writeEndDocument();


	out->close();
	return !mHasError;

}


AbstractTreeModelVisitor::TraversalType WritePolicyQueXmlImpl_V1::visit(TreeItem * item){
	tip::ItemType type = item->getItemType();
	if(type == tip::ItemModel)
	{

		Model obj;
		tip::extract(item, obj);
		writeItem(obj);
	}
	else if(type == tip::ItemSurvey)
	{
		Survey obj;
		tip::extract(item, obj);
		writeItem(obj);
	}
	else if(type == tip::ItemCategory )
	{
		// categories are not written, as QueXML does not support recursive data structure
		/*
		Category obj;
		tip::extract(item, obj);
		writeItem(obj);
		*/

	}
	else if(type == tip::ItemGroup)
	{
		Group obj;
		tip::extract(item, obj);
		writeItem(obj);

	}
	else if(type == tip::ItemMatrix)
	{
		Matrix obj;
		tip::extract(item, obj);
		writeItem(obj);

	}
	else if(type == tip::ItemMatrixProblem)
	{
		MatrixProblem obj;
		tip::extract(item, obj);
		writeItem(obj);

	}
	else if( type == tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj);
		writeItem(obj);

	}
	else
	{
		Q_ASSERT_X(false,"WritePolicyQueXmlImpl_V1","Unknown item...*zonk*");
	}

	return AbstractTreeModelVisitor::TraversalContinue;
}

void WritePolicyQueXmlImpl_V1::leave(TreeItem *item)
{

	// response must be AFTER subquestion (that is MatrixProblem)
	tip::ItemType type = item->getItemType();
	if(type==tip::ItemMatrix)
	{
		Matrix obj;
		tip::extract(item, obj);

		mWriter.writeStartElement("response");
		// has only one response....so we use question uid!
		mWriter.writeAttribute("varName", obj.name );
		mWriter.writeStartElement("fixed");

		writeProposals(obj.proposals);

		mWriter.writeEndElement(); // fixed
		mWriter.writeEndElement(); // response

	}

	// close the opened tags
	mWriter.writeEndElement();

}

// ------------------------ write item methods ---------------------------------
void WritePolicyQueXmlImpl_V1::writeAffiliation(const Affiliation & aff)
{
	mWriter.writeStartElement("investigator");
	mWriter.writeAttribute("id","1");

	mWriter.writeStartElement("name");
	mWriter.writeTextElement("salutation", "" );
	mWriter.writeTextElement("firstName", aff.firstname );
	mWriter.writeTextElement("lastName", aff.lastname );
	mWriter.writeEndElement(); // name

	mWriter.writeTextElement("organisation", "");

	mWriter.writeStartElement("address");
	mWriter.writeTextElement("street", "" );
	mWriter.writeTextElement("suburb", "" );
	mWriter.writeTextElement("postcode", "0"); // must be a number
	mWriter.writeTextElement("country", "");
	mWriter.writeEndElement(); // address

	mWriter.writeTextElement("phoneNumber",aff.telephone);
	mWriter.writeTextElement("faxNumber", "");
	mWriter.writeTextElement("emailAddress",aff.email);
	mWriter.writeTextElement("website","");

	mWriter.writeEndElement(); // investigator

	// datacollector is identical with investigator for our purposes
	mWriter.writeStartElement("dataCollector"); //
	mWriter.writeAttribute("id","1");

	mWriter.writeStartElement("name");
	mWriter.writeTextElement("salutation", "" );
	mWriter.writeTextElement("firstName", aff.firstname );
	mWriter.writeTextElement("lastName", aff.lastname );
	mWriter.writeEndElement(); // name

	mWriter.writeTextElement("organisation", "");

	mWriter.writeStartElement("address");
	mWriter.writeTextElement("street", "" );
	mWriter.writeTextElement("suburb", "" );
	mWriter.writeTextElement("postcode", "0");
	mWriter.writeTextElement("country", "");
	mWriter.writeEndElement(); // address

	mWriter.writeTextElement("phoneNumber",aff.telephone);
	mWriter.writeTextElement("faxNumber", "");
	mWriter.writeTextElement("emailAddress",aff.email);
	mWriter.writeTextElement("website","");

	mWriter.writeEndElement(); // datacollector


}



void WritePolicyQueXmlImpl_V1::writeProperties(const types::Properties & props)
{
	/*
	mWriter.writeStartElement("PropertyList");
	foreach(const Property & p, props)
	{
		mWriter.writeStartElement("Property");
		mWriter.writeAttribute("key", p.key);
		mWriter.writeAttribute("value",p.value);
		mWriter.writeCharacters(p.description);
		mWriter.writeEndElement();
	}
	mWriter.writeEndElement();
	*/
}

void WritePolicyQueXmlImpl_V1::writeImages(const types::Images & imgs)
{
	/* @todo how to export the images?
	mWriter.writeStartElement("ImageList");
	foreach(const QString & img, imgs)
	{
		mWriter.writeTextElement("Image", img);
	}
	mWriter.writeEndElement();
	*/
	qDebug("Image writing not supported yet...");
}



void WritePolicyQueXmlImpl_V1::writeProposals(const types::Proposals & props)
{
	int value = 0;
	foreach(const Proposal & p, props)
	{
		mWriter.writeStartElement("category");
		mWriter.writeTextElement("label", p.text);
		mWriter.writeTextElement("value", QString::number(++value) );
		mWriter.writeEndElement(); // category
	}
}


void WritePolicyQueXmlImpl_V1::writeItem(const Model & obj)
{
	mWriter.writeStartElement("questionnaire");
	mWriter.writeTextElement("title", obj.name);
	mWriter.writeTextElement("subtitle", QString());
	mWriter.writeAttribute("name",obj.name);

	// model does not provide any affiliation yet... so we use empty/dummy affiliation
	writeAffiliation(Affiliation());
}

void WritePolicyQueXmlImpl_V1::writeItem(const Survey & obj)
{
	mWriter.writeStartElement("questionnaire");
	mWriter.writeAttribute("name",obj.name);
	mWriter.writeTextElement("title", obj.name);
	mWriter.writeTextElement("subtitle", QString());

	writeAffiliation( obj.affiliation );

	mWriter.writeStartElement("questionnaireInfo");
	mWriter.writeTextElement("position", "before" );
	mWriter.writeTextElement("text",  obj.texts.welcome);
	mWriter.writeTextElement("administration",  "self");
	mWriter.writeEndElement(); // questionnaireinfo

	mWriter.writeStartElement("questionnaireInfo");
	mWriter.writeTextElement("position", "after" );
	mWriter.writeTextElement("text",  obj.texts.thank);
	mWriter.writeTextElement("administration",  "self");
	mWriter.writeEndElement(); // questionnaireinfo

	// no remind?

	//mWriter.writeStartElement("Content");
}

/*
void WritePolicyQueXmlImpl_V1::writeItem(const Category & obj)
{
	// categories are not written, as QueXML does not support recursive data structure

	mWriter.writeStartElement("Category");
	mWriter.writeAttribute("name",obj.name);
	mWriter.writeTextElement("Description", obj.description);
	writeProperties( obj.properties );
}
*/

void WritePolicyQueXmlImpl_V1::writeItem(const Group & obj)
{
	mWriter.writeStartElement("section");

	mWriter.writeStartElement("sectioninfo");
	mWriter.writeTextElement("position", "title" );
	mWriter.writeTextElement("text",  obj.name);
	mWriter.writeTextElement("administration",  "self");
	mWriter.writeEndElement(); // sectioninfo

}

void WritePolicyQueXmlImpl_V1::writeItem(const Matrix & obj)
{
	mWriter.writeStartElement("question");
	//mWriter.writeAttribute("id",obj.name);

	mWriter.writeTextElement("Text", obj.text);

	mWriter.writeStartElement("directive");
	mWriter.writeTextElement("position", "during");
	mWriter.writeTextElement("text", obj.hint);
	mWriter.writeTextElement("administration",  "self");
	mWriter.writeEndElement(); // directive



	/*
	mWriter.writeStartElement("Matrix");
	mWriter.writeAttribute("name",obj.name);
	mWriter.writeAttribute("multiple", obj.isMultipleChoice ? "true" : "false");
	writeProperties(obj.properties);
	mWriter.writeTextElement("Text", obj.text);
	mWriter.writeTextElement("Hint", obj.hint);
	writeImages(obj.images);
	writeProposals(obj.proposals);
	-*/
}

void WritePolicyQueXmlImpl_V1::writeItem(const MatrixProblem & obj)
{
	mWriter.writeStartElement("subQuestion");
	mWriter.writeAttribute("varName",QString("_%1").arg(obj.uid));
	mWriter.writeTextElement("Text", obj.text);
	//mWriter.writeEndElement(); // subQuestion
}

void WritePolicyQueXmlImpl_V1::writeItem(const Problem & obj)
{
	mWriter.writeStartElement("question");
	//mWriter.writeAttribute("id",obj.uid);
	//mWriter.writeAttribute("multiple", obj.isMultipleChoice ? "true" : "false");
	//writeProperties(obj.properties);
	mWriter.writeTextElement("text", obj.text);

	mWriter.writeStartElement("directive");
	mWriter.writeTextElement("position", "during");
	mWriter.writeTextElement("text", obj.hint);
	mWriter.writeTextElement("administration",  "self");
	mWriter.writeEndElement(); // directive

	mWriter.writeStartElement("response");
	mWriter.writeAttribute("varName", obj.uid );
	mWriter.writeStartElement("fixed");

	writeProposals(obj.proposals);

	mWriter.writeEndElement(); // fixed
	mWriter.writeEndElement(); // response

	writeImages(obj.images);

	//writeSolutions(obj.solutions);

}


} // eons
