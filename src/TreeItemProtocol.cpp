#include "TreeItemProtocol.h"
//#include "global.h"
#include "TreeItem.h"

namespace k{

#define inceptMeta(src,dest) (dest)->setData( (src).collapsed, MetaRoleCollapsed )
#define extractMeta(src,dest) (dest).collapsed = (src)->data( MetaRoleCollapsed ).toBool()

void TreeItemProtocol::incept(const Model & src, TreeItem * dest)
{
	inceptMeta(src,dest);

	dest->setItemType( ItemModel );
	dest->setText(src.name);
	dest->setData((int)src.uidMode,RoleUidMode);
}


void TreeItemProtocol::incept(const Survey & src, TreeItem * dest)
{
	inceptMeta(src,dest);

	dest->setItemType( ItemSurvey );
	dest->setText(src.name);
	dest->setData(src.lastmodifieddate, RoleDate);

	QByteArray data;
	serializeProperties(src.properties, data);
	dest->setData(data, RoleProperties);
	serializeAffiliation(src.affiliation, data);
	dest->setData(data, RoleAffiliation);
	serializeSurveyTexts(src.texts, data);
	dest->setData(data, RoleTexts);
}


void TreeItemProtocol::incept(const Category & src, TreeItem * dest)
{
	inceptMeta(src,dest);

	dest->setItemType( ItemCategory );
	dest->setText(src.name); // this is for view only, and may be changed by delegates or visitors
	dest->setData(src.name, RoleTexts);  // here we maintain the clean text data
	dest->setToolTip(src.description);
	QByteArray data;
	serializeProperties(src.properties, data);
	dest->setData(data,RoleProperties);
}

void TreeItemProtocol::incept(const Group & src, TreeItem * dest)
{
	inceptMeta(src,dest);

	dest->setItemType( ItemGroup );
	dest->setText(src.name);
	dest->setToolTip(src.description);
	QByteArray data;
	serializeProperties(src.properties, data);
	dest->setData(data,RoleProperties);
}

void TreeItemProtocol::incept(const Matrix & src, TreeItem * dest)
{
	inceptMeta(src,dest);

	dest->setItemType( ItemMatrix );
	dest->setText(src.text);
	dest->setToolTip(src.name);
	dest->setData(src.hint, RoleHint );
	dest->setData( src.isMultipleChoice, RoleMultipleChoice);

	QByteArray data;
	serializeProperties(src.properties, data);
	dest->setData(data,RoleProperties);

	serializeProposals(src.proposals, data);
	dest->setData(data, RoleProposals);

	serializeImages(src.images, data);
	dest->setData(data, RoleImages );
}

void TreeItemProtocol::incept(const MatrixProblem & src, TreeItem * dest)
{
	inceptMeta(src,dest);

	dest->setItemType( ItemMatrixProblem );
	dest->setText( src.text );
	dest->setData( src.uid, RoleUid );

	QByteArray data;
	serializeProperties(src.properties, data);
	dest->setData(data,RoleProperties);

	serializeSolutions(src.solutions, data);
	dest->setData( data, RoleSolutions );
}


void TreeItemProtocol::incept(const Problem & src, TreeItem * dest)
{
	inceptMeta(src,dest);

	dest->setItemType( ItemProblem );
	dest->setText( src.text );
	dest->setToolTip( src.hint );
	dest->setData( src.uid, RoleUid );
	dest->setData( src.isMultipleChoice, RoleMultipleChoice);
	QByteArray data;
	serializeProperties(src.properties, data);
	dest->setData(data,RoleProperties);

	serializeProposals(src.proposals, data);
	dest->setData(data, RoleProposals);

	serializeImages(src.images, data);
	dest->setData(data, RoleImages );

	serializeSolutions(src.solutions, data);
	dest->setData( data, RoleSolutions );

}


// ------------------------------------- extractors ------------------------------------------

bool TreeItemProtocol::extract(const TreeItem * src, Model & dest )
{
	extractMeta(src,dest);

	if(src->getItemType() == ItemModel)
	{
		dest.name = src->text();
		dest.uidMode = (Model::UidMode)src->data(RoleUidMode).toInt();
		return true;
	}
	qDebug("Passed item is not of type 'Model'");
	return false;
}


bool TreeItemProtocol::extract(const TreeItem * src, Survey & dest )
{
	extractMeta(src,dest);

	if(src->getItemType() == ItemSurvey)
	{
		dest.name = src->text();
		dest.lastmodifieddate = src->data(RoleDate).toString();

		deserializeAffiliation(src->data(RoleAffiliation).toByteArray(), dest.affiliation);
		deserializeSurveyTexts(src->data(RoleTexts).toByteArray(), dest.texts);
		deserializeProperties(src->data(RoleProperties).toByteArray(), dest.properties);
		return true;
	}
	qDebug("Passed item is not of type 'Survey'");
	return false;
}

bool TreeItemProtocol::extract(const TreeItem * src, Category & dest )
{
	extractMeta(src,dest);

	if(src->getItemType() == ItemCategory)
	{
		dest.name = src->data(RoleTexts).toString();
		dest.description = src->toolTip();
		deserializeProperties(src->data(RoleProperties).toByteArray(), dest.properties);
		return true;
	}
	qDebug("Passed item is not of type 'Category'");
	return false;

}


bool TreeItemProtocol::extract(const TreeItem * src, Group & dest )
{
	extractMeta(src,dest);

	if(src->getItemType() == ItemGroup)
	{
		dest.name = src->text();
		dest.description = src->toolTip();
		deserializeProperties(src->data(RoleProperties).toByteArray(), dest.properties);
		return true;
	}
	qDebug("Passed item is not of type 'Group'");
	return false;

}

bool TreeItemProtocol::extract(const TreeItem * src, Matrix & dest )
{
	extractMeta(src,dest);

	if(src->getItemType()== ItemMatrix)
	{

		dest.name = src->toolTip();
		dest.text = src->text();
		dest.hint = src->data(RoleHint).toString();
		dest.isMultipleChoice = src->data(RoleMultipleChoice).toBool();
		deserializeImages( src->data(RoleImages).toByteArray(), dest.images );
		deserializeProperties( src->data(RoleProperties).toByteArray(), dest.properties );
		deserializeProposals(src->data(RoleProposals).toByteArray(), dest.proposals );

		return true;
	}
	qDebug("Passed item is not of type 'Matrix'");
	return false;

}

bool TreeItemProtocol::extract(const TreeItem * src, MatrixProblem & dest )
{
	extractMeta(src,dest);

	if(src->getItemType()== ItemMatrixProblem)
	{
		dest.uid = src->data(RoleUid).toString();
		dest.text = src->text();
		deserializeProperties( src->data(RoleProperties).toByteArray(), dest.properties );
		deserializeSolutions( src->data(RoleSolutions).toByteArray(), dest.solutions  );
		return true;
	}
	qDebug("Passed item is not of type 'MatrixProblem'");
	return false;

}

bool TreeItemProtocol::extract(const TreeItem * src, Problem & dest )
{
	extractMeta(src,dest);

	if(src->getItemType()== ItemProblem)
	{
		dest.uid = src->data(RoleUid).toString();
		dest.text = src->text();
		dest.hint = src->toolTip();
		dest.isMultipleChoice = src->data(RoleMultipleChoice).toBool();
		deserializeProperties( src->data(RoleProperties).toByteArray(), dest.properties );
		deserializeImages( src->data(RoleImages).toByteArray(), dest.images );
		deserializeProposals( src->data(RoleProposals).toByteArray(), dest.proposals  );
		deserializeSolutions( src->data(RoleSolutions).toByteArray(), dest.solutions  );
		return true;
	}
	qDebug("Passed item is not of type 'Problem'");
	return false;

}


// ------------------------------------- serialize --------------------------------------------

void TreeItemProtocol::serializeAffiliation(const Affiliation & src, QByteArray & dest)
{
	dest.clear();
	QDataStream stream(&dest, QIODevice::WriteOnly);
	stream << src.email << src.firstname << src.lastname << src.telephone;
}

void TreeItemProtocol::serializeSurveyTexts(const SurveyTexts & src, QByteArray & dest)
{
	dest.clear();
	QDataStream stream(&dest, QIODevice::WriteOnly);
	stream << src.remind << src.thank << src.welcome;
}

void TreeItemProtocol::serializeProperties(const types::Properties & src, QByteArray & dest)
{
	dest.clear();
	QDataStream stream(&dest, QIODevice::WriteOnly);
	foreach (const k::Property & p, src) {
		stream << p.key << p.value << p.description;
	}

	//dest = dest);

}

void TreeItemProtocol::serializeSolutions(const types::Solutions & src, QByteArray & dest)
{
	dest.clear();
	QDataStream stream(&dest, QIODevice::WriteOnly);
	foreach (const QString & s, src) {
		stream << s;
	}
	//dest = qCompress(dest);
}

void TreeItemProtocol::serializeProposals(const types::Proposals & src, QByteArray & dest)
{
	dest.clear();
	QDataStream stream(&dest, QIODevice::WriteOnly);
	foreach (const k::Proposal & p, src) {
		stream << p.id << p.text;
	}

	//dest = qCompress(dest);

}

void TreeItemProtocol::serializeImages(const types::Images & src, QByteArray & dest)
{
	dest.clear();
	QDataStream stream(&dest, QIODevice::WriteOnly);
	foreach (const QString & imageurl, src) {
		stream << imageurl;
	}

	//dest = qCompress(dest);

}

// ------------------- deserialization

void TreeItemProtocol::deserializeAffiliation(const QByteArray & src, Affiliation & dest )
{
	QDataStream stream(src);
	stream >> dest.email >> dest.firstname >> dest.lastname >> dest.telephone;
}


void TreeItemProtocol::deserializeSurveyTexts(const QByteArray & src, SurveyTexts & dest )
{
	QDataStream stream(src);
	stream >> dest.remind >> dest.thank >> dest.welcome ;
}

void TreeItemProtocol::deserializeProperties(const QByteArray & src, types::Properties & dest )
{
	//QDataStream stream(qUncompress(src));
	QDataStream stream(src);
	while(!stream.atEnd())
	{
		k::Property p;
		stream >> p.key >> p.value >> p.description;
		dest.insert(p.key,p);
	}
}

void TreeItemProtocol::deserializeProposals(const QByteArray & src, types::Proposals & dest)
{
	//QDataStream stream(qUncompress(src));
	QDataStream stream(src);
	while(!stream.atEnd())
	{
		k::Proposal p;
		stream >> p.id >> p.text;
		dest << p;
	}
}


void TreeItemProtocol::deserializeSolutions(const QByteArray & src, types::Solutions & dest)
{
	//QDataStream stream(qUncompress(src));
	QDataStream stream(src);
	while(!stream.atEnd())
	{
		QString s;
		stream >> s;
		dest<< s;
	}
}


void TreeItemProtocol::deserializeImages(const QByteArray & src, types::Images & dest)
{
	//QDataStream stream(qUncompress(src));
	QDataStream stream(src);
	while(!stream.atEnd())
	{
		QString imageurl;
		stream >> imageurl;
		dest << imageurl;
	}
}


} // eons


