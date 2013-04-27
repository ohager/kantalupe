#include "ReadPolicyBinary.h"
#include "ReadPolicyBinaryImpl_V1.h"
#include "ModelInsertionInterface.h"
#include "global.h"

START_NS

ReadPolicyBinary::ReadPolicyBinary() :
	mImpl(new ReadPolicyBinaryImpl_V1())
{
}

ReadPolicyBinary::~ReadPolicyBinary()
{
	delete mImpl; mImpl = 0x0;
}

bool ReadPolicyBinary::read(QIODevice * in ,ModelInsertionInterface * inserter, const QModelIndex & parent) const
{
	return mImpl->read( in, inserter, parent);
}

END_NS

