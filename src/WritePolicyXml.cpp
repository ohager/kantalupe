#include "WritePolicyXml.h"
#include "WritePolicyXmlImpl_V1.h"
#include "global.h"

START_NS

WritePolicyXml::WritePolicyXml() :
	mImpl(new WritePolicyXmlImpl_V1())
{
}

WritePolicyXml::~WritePolicyXml()
{
	delete mImpl; mImpl=0x0;
}


bool WritePolicyXml::write(const AbstractTreeModel * model, QIODevice *out) const
{
	return mImpl->write(const_cast<AbstractTreeModel*>(model), out);
}

bool WritePolicyXml::write(const TreeItem * startnode, QIODevice * out) const
{
	return mImpl->write(const_cast<TreeItem*>(startnode), out);
}


END_NS
