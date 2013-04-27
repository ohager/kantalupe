#include "ReadPolicyXml.h"
#include "ReadPolicyXmlImpl_V1.h"
#include "ModelInsertionInterface.h"
#include "global.h"

START_NS

ReadPolicyXml::ReadPolicyXml() :
	mImpl(new ReadPolicyXmlImpl_V1())
{
}

ReadPolicyXml::~ReadPolicyXml()
{
	delete mImpl; mImpl = 0x0;
}

bool ReadPolicyXml::read(QIODevice * in ,ModelInsertionInterface * inserter, const QModelIndex & parent) const
{
	return mImpl->read( in, inserter, parent);
}

END_NS

