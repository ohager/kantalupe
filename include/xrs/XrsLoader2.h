#ifndef __XrsLoader2_H
#define __XrsLoader2_H
/*
#include <QDomDocument>
#include <QDomElement>
*/
#include "XrsObjectModel.h"
#include "xrs.hxx"
#include <string>
#include <list>


typedef std::list<std::string> StringList;



/**
This class loads xrs files.
An XRS file is a description for resources like icons and images.
It allows a convenient access to such resources like it is provided
by the Qt's resource system. 
The main advantage over Qt resource system is:
As XRS expects the resources separated from the application, thus are not compiled,
changes can be done without recompilation. The disadvantage is, that your resources
are accessible by others.
@note This is a highly efficient variant based on CodeSynthesis XML/C++ Tree
*/
class XrsLoader2
{
public:

	enum ResourceType{
		Invalid=-1,
		File =0,
		Image,
		Text
	};

	/**
	The version for this loader;
	*/
	static const char * MajorVersion, *MinorVersion;

	
	/**
	@return The id of the XRS document
	*/
	std::string getId() const;


	/**
	@return The iterator to the first Prefix element;
	*/
	StringList getPrefixes() const;

	/**
	@return A list of all available aliases within the given prefix;
	*/
	StringList getAliases(const std::string & prefix) const;
	
	/**
	Method is provided for convenience.
	@param qname A full qualified name, which includes the prefix. This is written in form
	of "prefix/alias"
	@param [out] rtype The resource's type, that will be returned on invocation
	@return The value of a specified Prefix
	*/
	std::string  getValue(const std::string & qname, ResourceType * type=0) const;

	/**
	@param prefix The prefix
	@param alias The alias
	@param [out] rtype The resource's type, that will be returned on invocation. 
	Can be null, e.g. if user has a priori knowledge about type (slightly faster).
	@return The value of a specified Prefix and alias. If an empty string is returned, 
	and if @e type is not null it becomes XrsLoader2::Invalid.
	*/
	std::string getValue(const std::string &, const std::string & alias, XrsLoader2::ResourceType * type=0x0) const;

	
	/**
	@return The resource type of passed dom element.
	*/
	//ResourceType getResourceType(QDomElement e) const;

	/**
	Loads a XRS file.
	@param xrsfilename
	@param [out] err The error, if one occurred, as brief description
	@param [out] detail The error details, if wished.
	@return @e true, if successfully loaded, otherwise false.
	Aside the normal load failures, a version conflict might lead to false result also.
	*/
	bool load(const std::string & xrsfilename, std::string * err, std::string * detail=0x0 );


	/**
	Checks version of XRS against implementation version.
	@param version The document's version.
	@return @e true, if version check passed.
	*/
	static bool checkVersion(const std::string & version);
private:
	XrsObjectModel mXom;
	std::string mId;
};


#endif // __XrsLoader2_H




