#include "WritePolicyQueXml.h"
#include "WritePolicyQueXmlImpl_V1.h"


namespace k{

WritePolicyQueXml::WritePolicyQueXml() :
	mImpl(new WritePolicyQueXmlImpl_V1())
{
}

WritePolicyQueXml::~WritePolicyQueXml()
{
	delete mImpl; mImpl=0x0;
}


bool WritePolicyQueXml::write(const AbstractTreeModel * model, QIODevice *out) const
{
	return mImpl->write(const_cast<AbstractTreeModel*>(model), out);
}

bool WritePolicyQueXml::write(const TreeItem * startnode, QIODevice * out) const
{
	return mImpl->write(const_cast<TreeItem*>(startnode), out);
}


} // eons
