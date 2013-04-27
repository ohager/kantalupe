#include "XrsLoader.h"

#include <QCoreApplication>
#include <QFile>

const char * XrsLoader::MajorVersion="1";
const char * XrsLoader::MinorVersion="0";

bool XrsLoader::checkVersion(const QString & version)
{
	
	int majx=version.indexOf(QChar('.'));
	QString major=version.left(majx);
	
	return major == MajorVersion;

}


bool XrsLoader::load(const QString & fn, QString * err)
{
	QString e;
	int line=0;
	QFile xrs(fn);
	if(!xrs.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		*err = QString( QCoreApplication::tr("Could not find XRS-File '%1'.").arg(fn));
		return false;
	}

	
	if(mDoc.setContent(&xrs, &e, &line))
	{

		QDomElement root=mDoc.documentElement();
		QString version=root.attribute("version");
		if(!checkVersion(version))
		{
			*err = QString( QCoreApplication::tr(
							"XRS Version conflict in file '%1'.\n"
							"Recent version is %2.x and Version %3 is not supported."
							).arg(fn).arg(MajorVersion).arg(version) );
			return false;
		}

		mId = root.attribute("id");
		return true;
	}
	*err = QString( QCoreApplication::tr("XML-Error in '%1' at line %2:\n%3").arg(fn).arg(line).arg(e));
	return false;
}

QStringList XrsLoader::getPrefixes() const
{
	QStringList prefixes;
	QDomNodeList nl=mDoc.documentElement().elementsByTagName("set");
	int n= nl.size();
	for(int i=0; i<n; ++i)
	{
		QDomElement e=nl.at(i).toElement();
		prefixes.append(e.attribute("prefix"));
	}

	return prefixes;
}

QStringList XrsLoader::getAliases(const QString & prefix) const
{
	QStringList aliases;
	QDomNodeList nl=mDoc.documentElement().childNodes();
	int n= nl.size();
	for(int i=0; i<n; ++i)
	{
		QDomElement e=nl.at(i).toElement();
		if(!e.isNull() && e.attribute("prefix")==prefix)
		{
			QDomNodeList nla= e.childNodes();
			int k=nla.size();
			for(int j=0; j<k;++j)
			{
				QDomElement a=  nla.at(j).toElement();
				if(!a.isNull())
				{
					aliases.append(a.attribute("alias"));
				}
			}
			break;
		}
	}
	return aliases;
}
	
QString XrsLoader::getValue(const QString & qname, ResourceType * type) const
{
	int del=qname.indexOf(QChar('/'));
	QString prefix = qname.left( del ),
			alias = qname.right( qname.size()-(del+1) );
	return getValue(prefix, alias, type);
}

QString XrsLoader::getValue(const QString & prefix, const QString & alias, ResourceType * type) const
{

	QDomNodeList nl=mDoc.documentElement().childNodes();
	int n= nl.size();
	for(int i=0; i<n; ++i)
	{
		QDomElement e=nl.at(i).toElement();
		if(!e.isNull() && e.attribute("prefix")==prefix)
		{
			QDomNodeList nla= e.childNodes();
			int k= nla.size();
			for(int j=0; j<k;++j)
			{
				QDomElement a=  nla.at(j).toElement();
				QString attr=a.attribute("alias");
				if(!a.isNull() && attr==alias)
				{
					if(type)
						*type= getResourceType(a);

					return a.text();
				}
			}
		}
	}
	return QString();
}

XrsLoader::ResourceType XrsLoader::getResourceType(QDomElement e) const
{
	QString tag=e.attribute("type");
	ResourceType t=Invalid;
	if(tag == "file")
	{
		t=File;
	}
	else if(tag == "image")
	{
		t=Image;
	}
	else if(tag == "text" )
	{
		t=Text;
	}
	
	return  t;
}
