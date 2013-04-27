#include "UidGenerator.h"
#include "UidGeneratorImpl.h"
#include "global.h"

UidGenerator::UidGenerator()
	: _impl(&UidGeneratorImpl::instance())
{
}

UidGenerator::~UidGenerator(){ _impl = 0x0; }

QString UidGenerator::generate(const QString & in) const
{
	return _impl->generateAsHash(in);
}
