#include "WritePolicyBinary.h"
#include "WritePolicyBinaryImpl_V1.h"
#include "global.h"

START_NS

WritePolicyBinary::WritePolicyBinary() :
	mImpl(new WritePolicyBinaryImpl_V1())
{
}

WritePolicyBinary::~WritePolicyBinary()
{
	delete mImpl; mImpl=0x0;
}


bool WritePolicyBinary::write(const AbstractTreeModel * model, QIODevice *out) const
{
	return mImpl->write(const_cast<AbstractTreeModel*>(model), out);
}



END_NS
