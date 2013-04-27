#include "UidGeneratorImpl.h"

UidGeneratorImpl UidGeneratorImpl::sInstance;

UidGeneratorImpl::UidGeneratorImpl()
{
}

UidGeneratorImpl & UidGeneratorImpl::instance()
{
	return sInstance;
}



QString UidGeneratorImpl::generateAsHash(const QString & input) const
{

	if(input.isEmpty())
		return QString();

	QString uid( QString::number(qHash(input), 16) );
	QSet<QString>::const_iterator it = mGenerated.find(input);
	if(it != mGenerated.end())
	{
		uid = *it;
	}
	else
	{
		mGenerated.insert(uid);
	}
	return uid;

}


