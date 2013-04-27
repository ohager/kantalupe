#include "WritePolicyXmlImpl_V1.h"
#include "AbstractTreeModel.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include "global.h"

#include <QDate>

START_NS

const char * WritePolicyXmlImpl_V1::Version = "1";

WritePolicyXmlImpl_V1::WritePolicyXmlImpl_V1() :
	mHasError(false)
{
}

bool WritePolicyXmlImpl_V1::write(AbstractTreeModel * mtd, QIODevice *out)
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

bool WritePolicyXmlImpl_V1::write(TreeItem * startnode, QIODevice *out)
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


AbstractTreeModelVisitor::TraversalType WritePolicyXmlImpl_V1::visit(TreeItem * item){
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
		Category obj;
		tip::extract(item, obj);
		writeItem(obj);

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
		Q_ASSERT_X(false,"WritePolicyXmlImpl_V1","Unknown item...*zonk*");
	}

	return AbstractTreeModelVisitor::TraversalContinue;
}

void WritePolicyXmlImpl_V1::leave(TreeItem *item)
{
	// model/survey item opened <Content>-Tag, which must not be closed, when leaving model item.
	tip::ItemType type = item->getItemType();
	if(type!=tip::ItemModel ||	type!=tip::ItemSurvey)
		mWriter.writeEndElement();
}

// ------------------------ write item methods ---------------------------------
void WritePolicyXmlImpl_V1::writeAffiliation(const Affiliation & aff)
{
	mWriter.writeStartElement("Affiliation");

	mWriter.writeTextElement("FirstName", aff.firstname );
	mWriter.writeTextElement("LastName", aff.lastname );
	mWriter.writeTextElement("EMail",aff.email);
	mWriter.writeTextElement("Phone",aff.telephone);

	mWriter.writeEndElement();

}



void WritePolicyXmlImpl_V1::writeProperties(const types::Properties & props)
{
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
}

void WritePolicyXmlImpl_V1::writeImages(const types::Images & imgs)
{
	mWriter.writeStartElement("ImageList");
	foreach(const QString & img, imgs)
	{
		mWriter.writeTextElement("Image", img);
	}
	mWriter.writeEndElement();
}


void WritePolicyXmlImpl_V1::writeSolutions(const types::Solutions & sols)
{
	mWriter.writeStartElement("SolutionList");
	foreach(const QString & s, sols)
	{
		mWriter.writeStartElement("Solution");
		mWriter.writeAttribute("idref", s);
		mWriter.writeEndElement();
	}
	mWriter.writeEndElement();
}

void WritePolicyXmlImpl_V1::writeProposals(const types::Proposals & props)
{
	mWriter.writeStartElement("ProposalList");

	foreach(const Proposal & p, props)
	{
		mWriter.writeStartElement("Proposal");
		mWriter.writeAttribute("id", p.id);
		mWriter.writeCharacters(p.text);
		mWriter.writeEndElement();
	}
	mWriter.writeEndElement();
}


void WritePolicyXmlImpl_V1::writeItem(const Model & obj)
{
	mWriter.writeStartElement("KModel");
	mWriter.writeAttribute("name",obj.name);
	mWriter.writeAttribute("version", Version );
	mWriter.writeStartElement("Functional");
	mWriter.writeStartElement("UidGeneration");

	QString uidmode;
	switch(obj.uidMode)
	{
	case Model::UidManual:
		uidmode = "manual";
		break;
	case Model::UidHash:
		uidmode = "hash";
		break;
	default:
		Q_ASSERT_X(false, "WritePolicyXmlImpl_V1","Unsupported UidMode");
	}

	mWriter.writeAttribute("mode", uidmode);
	mWriter.writeEndElement(); // UidGeneration
	mWriter.writeEndElement(); // Functional
	mWriter.writeStartElement("Content");
}

void WritePolicyXmlImpl_V1::writeItem(const Survey & obj)
{
	mWriter.writeStartElement("KSurvey");
	mWriter.writeAttribute("name",obj.name);
	mWriter.writeAttribute("version", Version );
	mWriter.writeAttribute("lastmodified", QDate::currentDate().toString(Qt::ISODate));
	mWriter.writeStartElement("Meta");

	writeAffiliation(obj.affiliation);

	mWriter.writeTextElement("Welcome", obj.texts.welcome);
	mWriter.writeTextElement("Thank", obj.texts.thank);
	mWriter.writeTextElement("Remind", obj.texts.remind);

	mWriter.writeEndElement(); // Meta
	mWriter.writeStartElement("Content");
}

void WritePolicyXmlImpl_V1::writeItem(const Category & obj)
{
	mWriter.writeStartElement("Category");
	mWriter.writeAttribute("name",obj.name);
	mWriter.writeTextElement("Description", obj.description);
	writeProperties( obj.properties );
}

void WritePolicyXmlImpl_V1::writeItem(const Group & obj)
{
	mWriter.writeStartElement("Group");
	mWriter.writeAttribute("name",obj.name);	
	mWriter.writeTextElement("Description", obj.description);
	writeProperties( obj.properties );
}

void WritePolicyXmlImpl_V1::writeItem(const Matrix & obj)
{
	mWriter.writeStartElement("Matrix");
	mWriter.writeAttribute("name",obj.name);
	mWriter.writeAttribute("multiple", obj.isMultipleChoice ? "true" : "false");
	writeProperties(obj.properties);
	mWriter.writeTextElement("Text", obj.text);
	mWriter.writeTextElement("Hint", obj.hint);
	writeImages(obj.images);
	writeProposals(obj.proposals);
}

void WritePolicyXmlImpl_V1::writeItem(const MatrixProblem & obj)
{
	mWriter.writeStartElement("MatrixProblem");
	mWriter.writeAttribute("uid",obj.uid);
	writeProperties(obj.properties);
	mWriter.writeTextElement("Text", obj.text);
	writeSolutions(obj.solutions);
}

void WritePolicyXmlImpl_V1::writeItem(const Problem & obj)
{
	mWriter.writeStartElement("Problem");
	mWriter.writeAttribute("uid",obj.uid);
	mWriter.writeAttribute("multiple", obj.isMultipleChoice ? "true" : "false");
	writeProperties(obj.properties);
	mWriter.writeTextElement("Text", obj.text);
	mWriter.writeTextElement("Hint", obj.hint);
	writeImages(obj.images);
	writeProposals(obj.proposals);
	writeSolutions(obj.solutions);

}


END_NS
