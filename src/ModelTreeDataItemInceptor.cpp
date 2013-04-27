#include "ModelTreeDataItemInceptor.h"
#include "global.h"
#include "ModelTreeDataItem.h"
#include "ModelTreeDataItemProtocol.h"
#include "PlainStructures.h"

START_NS

ModelTreeDataItemInceptor::ModelTreeDataItemInceptor()
{
}

void ModelTreeDataItemInceptor::incept(const Category & src, ModelTreeDataItem * dest)
{
	dest->setItemType( global::ItemCategory );
	dest->setText(src.name);
	dest->setToolTip(src.description);
	dest->setData(serializeProperties(src.properties),ModelTreeDataItemProtocol::Properties);
}

void ModelTreeDataItemInceptor::incept(const Group & src, ModelTreeDataItem * dest)
{
	dest->setItemType( global::ItemGroup );
	dest->setText(src.name);
	dest->setToolTip(src.description);
	dest->setData(serializeProperties(src.properties),ModelTreeDataItemProtocol::Properties);
}

void ModelTreeDataItemInceptor::incept(const Matrix & src, ModelTreeDataItem * dest)
{
	dest->setItemType( global::ItemMatrix );
	dest->setText(src.name);
	dest->setToolTip(src.text);
	dest->setData(src.hint, ModelTreeDataItemProtocol::Hint );
	dest->setData(serializeProperties(src.properties),ModelTreeDataItemProtocol::Properties);
	dest->setData(serializeProposals(src.proposals), ModelTreeDataItemProtocol::Proposals);
	dest->setData(serializeImages( src.images ), ModelTreeDataItemProtocol::Images );
}

void ModelTreeDataItemInceptor::incept(const MatrixProblem & src, ModelTreeDataItem * dest)
{
	dest->setItemType( global::ItemMatrixProblem );
	dest->setText( src.text );
	dest->setData( src.uid, ModelTreeDataItemProtocol::Uid );
	dest->setData( serializeProperties( src.properties ), ModelTreeDataItemProtocol::Properties );
	dest->setData( serializeSolutions( src.solutions ), ModelTreeDataItemProtocol::Solutions );
}


void ModelTreeDataItemInceptor::incept(const Problem & src, ModelTreeDataItem * dest)
{
	dest->setItemType( global::ItemProblem );
	dest->setText( src.text );
	dest->setToolTip( src.hint );
	dest->setData( src.uid, ModelTreeDataItemProtocol::Uid );
	dest->setData( serializeProperties( src.properties ), ModelTreeDataItemProtocol::Properties );
	dest->setData( serializeImages( src.images ), ModelTreeDataItemProtocol::Images );
	dest->setData( serializeProposals( src.proposals ), ModelTreeDataItemProtocol::Proposals );
	dest->setData( serializeSolutions( src.solutions ), ModelTreeDataItemProtocol::Solutions );

}

// ------------------------------------- Privates --------------------------------------------


QByteArray ModelTreeDataItemInceptor::serializeProperties(const types::Properties & properties)
{
	QByteArray serialized;
	QDataStream stream(&serialized, QIODevice::WriteOnly);
	foreach (types::PropertyData p, properties) {
		stream << p.key << p.value << p.description;
	}

	return qCompress(serialized);

}

QByteArray ModelTreeDataItemInceptor::serializeSolutions(const types::Solutions & solutions)
{
	QByteArray serialized;
	QDataStream stream(&serialized, QIODevice::WriteOnly);
	foreach (const QString & s, solutions) {
		stream << s;
	}

	return qCompress(serialized);
}

QByteArray ModelTreeDataItemInceptor::serializeProposals(const types::Proposals & proposals)
{
	QByteArray serialized;
	QDataStream stream(&serialized, QIODevice::WriteOnly);
	foreach (types::ProposalData p, proposals) {
		stream << p.id << p.text;
	}

	return qCompress(serialized);

}

QByteArray ModelTreeDataItemInceptor::serializeImages(const types::Images & images)
{
	QByteArray serialized;
	QDataStream stream(&serialized, QIODevice::WriteOnly);
	foreach (const QString & imageurl, images) {
		stream << imageurl;
	}

	return qCompress(serialized);

}



END_NS
