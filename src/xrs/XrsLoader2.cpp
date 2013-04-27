#include "XrsLoader2.h"

/*
#include <QCoreApplication>
#include <QFile>
*/

#include <sstream>
#include <string>
using namespace std;

const char * XrsLoader2::MajorVersion="1";
const char * XrsLoader2::MinorVersion="0";

bool XrsLoader2::checkVersion(const string & version)
{
	int majx=version.find_first_of('.');
	return version.compare(0,majx,MajorVersion)==0;
}


bool XrsLoader2::load(const string & fn, string * err, string * detail)
{
	// todo: implement the compressed version!
	
	if( !mXom.readFile(fn.c_str()) ) // load the object model
	{
		if(err)
		{
			mXom.getError(err, detail);
		}
		return false;
	}

	//ok
	xrs * root=mXom.getRoot();
	
	const string & version = root->version();
	if( !checkVersion(version) ) // version check
	{
		stringstream stream;
		stream  << "XRS Version conflict in file '" << fn.c_str() << "'.";
		*err = stream.str();
		if(detail)
		{
			stringstream det;
			det << "Current version is " << MajorVersion << 
						".x and Version " << version << 
						" is not supported.";
			
			*detail = det.str();
		}
		return false;
	}
	return true;
}

std::string XrsLoader2::getId() const
{
	if( mXom.isNull() )
	{
		return string();
	}
	return mXom.getRoot()->id();
}

StringList XrsLoader2::getPrefixes() const
{
	StringList prefixes;
	if(mXom.isNull())
		return prefixes;

	const xrs * root = mXom.getRoot();
	const xrs::ResourceSet_sequence & sets = root->ResourceSet();
	xrs::ResourceSet_const_iterator it= sets.begin(), end = sets.end();
	while(it!=end)
	{
		const ResourceSet & set= *it++;
		prefixes.push_back( set.prefix() );
	}
	return prefixes;
}

StringList XrsLoader2::getAliases(const string & prefix) const
{
	StringList aliases;
	if(mXom.isNull())
		return aliases;
	
	
	const xrs * root = mXom.getRoot();
	const xrs::ResourceSet_sequence & sets = root->ResourceSet();
	xrs::ResourceSet_const_iterator it= sets.begin(), end = sets.end();
	while(it!=end)
	{
		const ResourceSet & set= *it++;
		if(set.prefix() == prefix)
		{
			// get all aliases
			const ResourceSet::Resource_sequence & reses = set.Resource();
			ResourceSet::Resource_const_iterator rit= reses.begin(), rend = reses.end();
			while(rit!=rend)
			{
				const Resource & resource = *rit++;
				aliases.push_back( resource.alias() );
			}
			break;
		}
	}

	return aliases;
}
	
string XrsLoader2::getValue(const string & qname, ResourceType * type) const
{
	/*
	int del=qname.indexOf(QChar('/'));
	QString prefix = qname.left( del ),
			alias = qname.right( qname.size()-(del+1) );
	return getValue(prefix, alias, type);
	*/

	int del = qname.find_first_of( '/' );
	string prefix = qname.substr(0,del);
	string alias = qname.substr(del+1); // skip '/'

	return getValue(prefix,alias,type);
}

string XrsLoader2::getValue(const string & prefix, const string & alias, ResourceType * type) const
{

	const xrs * root = mXom.getRoot();
	const xrs::ResourceSet_sequence & sets = root->ResourceSet();
	xrs::ResourceSet_const_iterator it= sets.begin(), end = sets.end();
	while(it!=end)
	{
		const ResourceSet & set= *it++;
		if(set.prefix() == prefix)
		{
			// get all aliases
			const ResourceSet::Resource_sequence & reses = set.Resource();
			ResourceSet::Resource_const_iterator rit= reses.begin(), rend = reses.end();
			while(rit!=rend)
			{
				const Resource & resource = *rit++;
				if(resource.alias() == alias)
				{
					if(type)
					{	
						switch(resource.type())
						{
						case ResourceTypes::file:
							*type = File;
							break;
						case ResourceTypes::image:
							*type = Image;
							break;
						case ResourceTypes::text:
							*type = Text;
						default:
							*type = Invalid;
						}
					} // end if(type)
					return resource;
				}
			}
		}
	}

	if(type)
	{
		*type = Invalid;
	}
	return string();
}
