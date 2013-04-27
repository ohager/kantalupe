#include "XrsLoaderQt.h"


XrsLoaderQt::XrsLoaderQt() 
	: mXrsLoader(new XrsLoader2())
{

}
	
XrsLoaderQt::~XrsLoaderQt() 
{ 
	delete mXrsLoader; mXrsLoader=0x0;
	qDebug("XrsLoader deleted...");
}


QString XrsLoaderQt::id() const 
{ 
	return QString::fromAscii( mXrsLoader->getId().c_str() );
}


bool XrsLoaderQt::load(const QString & xrsfilename, QString * err, QString * detail )
{
	std::string stde, stdd;
	bool ok = mXrsLoader->load( xrsfilename.toAscii().data() , &stde, &stdd );
	*err=stde.c_str();
	if(detail)
		*detail = stdd.c_str();
	return ok;
}

QStringList XrsLoaderQt::getPrefixes() const
{
	return fromStdList(mXrsLoader->getPrefixes());
}

QStringList XrsLoaderQt::getAliases(const QString & prefix) const
{
	return fromStdList(mXrsLoader->getAliases(prefix.toAscii().data()));
}

QString XrsLoaderQt::getValue(const QString & qname,  XrsLoader2::ResourceType * type) const
{
	return mXrsLoader->getValue( qname.toAscii().data(), type ).c_str();
}

QString XrsLoaderQt::getValue(const QString & prefix, const QString & alias, XrsLoader2::ResourceType * type) const
{
	return mXrsLoader->getValue( prefix.toAscii().data() , alias.toAscii().data(), type ).c_str();
	
}

QStringList XrsLoaderQt::fromStdList(const std::list<std::string> & stdlist)
{
	QStringList list;
	std::list<std::string>::const_iterator it=stdlist.begin(), end=stdlist.end();
	while(it!=end)
	{
		list.append( (*it++).c_str() );
	}
	return list; // implicitely shared...fast return!
}
/*
QStringList getAliases(const QString & prefix) const;
	
QString getValue(const QString & qname, ResourceType * type=0) const;

QString getValue(const QString & prefix, const QString & alias, XrsLoader2::ResourceType * type=0) const;



bool checkVersion(const QString & version);
*/
