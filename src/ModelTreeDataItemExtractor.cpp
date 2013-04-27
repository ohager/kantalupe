#include "ModelTreeDataItemExtractor.h"
#include "global.h"
#include "ModelTreeDataItem.h"
#include "ModelTreeDataItemProtocol.h"
#include "PlainStructures.h"

START_NS

ModelTreeDataItemExtractor::ModelTreeDataItemExtractor()
{
}

bool ModelTreeDataItemExtractor::extract(const ModelTreeDataItem * src, Category & dest )
{

	if(src->getItemType() == global::ItemCategory)
	{
		dest.name = src->text();
		dest.description = src->toolTip();
		dest.properties = deserializeProperties(src->data(ModelTreeDataItemProtocol::Properties).toByteArray());
		return true;
	}
	qDebug("Passed item is not of type 'Category'");
	return false;

}


bool ModelTreeDataItemExtractor::extract(const ModelTreeDataItem * src, Group & dest )
{
	if(src->getItemType() == global::ItemGroup)
	{
		dest.name = src->text();
		dest.description = src->toolTip();
		dest.properties = deserializeProperties(src->data(ModelTreeDataItemProtocol::Properties).toByteArray());
		return true;
	}
	qDebug("Passed item is not of type 'Group'");
	return false;

}

bool ModelTreeDataItemExtractor::extract(const ModelTreeDataItem * src, Matrix & dest )
{
	if(src->getItemType()== global::ItemMatrix)
	{

		dest.name = src->text();
		dest.text = src->toolTip();
		dest.hint = src->data(ModelTreeDataItemProtocol::Hint).toString();
		dest.images = deserializeImages( src->data(ModelTreeDataItemProtocol::Images).toByteArray() );
		dest.properties = deserializeProperties( src->data(ModelTreeDataItemProtocol::Properties).toByteArray());
		dest.proposals = deserializeProposals(src->data(ModelTreeDataItemProtocol::Proposals).toByteArray());

		return true;
	}
	qDebug("Passed item is not of type 'Matrix'");
	return false;

}

bool ModelTreeDataItemExtractor::extract(const ModelTreeDataItem * src, MatrixProblem & dest )
{
	if(src->getItemType()== global::ItemMatrixProblem)
	{
		dest.uid = src->data(ModelTreeDataItemProtocol::Uid).toString();
		dest.text = src->text();
		dest.properties =  deserializeProperties( src->data(ModelTreeDataItemProtocol::Properties).toByteArray() );
		dest.solutions = deserializeSolutions( src->data(ModelTreeDataItemProtocol::Solutions).toByteArray() );
		return true;
	}
	qDebug("Passed item is not of type 'MatrixProblem'");
	return false;

}

bool ModelTreeDataItemExtractor::extract(const ModelTreeDataItem * src, Problem & dest )
{
	if(src->getItemType()== global::ItemProblem)
	{
		dest.uid = src->data(ModelTreeDataItemProtocol::Uid).toString();
		dest.text = src->text();
		dest.hint = src->toolTip();
		dest.properties =  deserializeProperties( src->data(ModelTreeDataItemProtocol::Properties).toByteArray() );
		dest.images = deserializeImages( src->data(ModelTreeDataItemProtocol::Images).toByteArray());
		dest.proposals = deserializeProposals( src->data(ModelTreeDataItemProtocol::Proposals).toByteArray() );
		dest.solutions = deserializeSolutions( src->data(ModelTreeDataItemProtocol::Solutions).toByteArray() );
		return true;
	}
	qDebug("Passed item is not of type 'Problem'");
	return false;

}

// -------------------------------- Privates ------------------------------------

types::Properties ModelTreeDataItemExtractor::deserializeProperties(const QByteArray & sprops)
{
	types::Properties props;
	QDataStream stream(qUncompress(sprops));
	while(!stream.atEnd())
	{
		types::PropertyData p;
		stream >> p.key >> p.value >> p.description;
		props.insert(p.key,p);
	}

	return props;

}

types::Proposals ModelTreeDataItemExtractor::deserializeProposals(const QByteArray & sprops)
{
	types::Proposals props;
	QDataStream stream(qUncompress(sprops));
	while(!stream.atEnd())
	{
		types::ProposalData p;
		stream >> p.id >> p.text;
		props << p;
	}

	return props;
}


types::Solutions ModelTreeDataItemExtractor::deserializeSolutions(const QByteArray & ssols)
{
	types::Solutions sols;
	QDataStream stream(qUncompress(ssols));
	while(!stream.atEnd())
	{
		QString s;
		stream >> s;
		sols << s;
	}

	return sols;
}
types::Images ModelTreeDataItemExtractor::deserializeImages(const QByteArray & simages)
{
	types::Images images;
	QDataStream stream(qUncompress(simages));
	while(!stream.atEnd())
	{
		QString imageurl;
		stream >> imageurl;
		images << imageurl;
	}

	return images;
}

END_NS
