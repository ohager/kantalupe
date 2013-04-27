#ifndef __XrsLoader_H
#define __XrsLoader_H

#include <QDomDocument>
#include <QDomElement>
#include <QStringList>



/**
This class loads xrs files.
An XRS file is a description for resources like icons and images.
It allows a convenient access to such resources like it is provided
by the Qt's resource system. 
The main advantage over Qt resource system is:
As XRS expects the resources separated from the application, thus are not compiled,
changes can be done without recompilation. The disadvantage is, that your resources
are accessible by others.
*/
class XrsLoader
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
	inline const QString & id() const { return mId; }


	/**
	@return A list of available prefixes
	*/
	QStringList getPrefixes() const;

	/**
	@return A list of all available aliases within the given prefix;
	*/
	QStringList getAliases(const QString & prefix) const;
	
	/**
	Method is provided for convenience.
	@param qname A full qualified name, which includes the prefix. This is written in form
	of "prefix/alias"
	@param [out] rtype The resource's type, that will be returned on invocation
	@return The value of a specified Prefix
	*/
	QString getValue(const QString & qname, ResourceType * type=0) const;

	/**
	@param prefix The prefix
	@param alias The alias
	@param [out] rtype The resource's type, that will be returned on invocation
	@return The value of a specified Prefix
	*/
	QString getValue(const QString & prefix, const QString & alias, ResourceType * type=0) const;

	/**
	@return The resource type of passed dom element.
	*/
	ResourceType getResourceType(QDomElement e) const;

	/**
	Loads a XRS file.
	@param xrsfilename
	@param [out] err The error, if one occurred
	@return @e true, if successfully loaded, otherwise false.
	Aside the normal load failures, a version conflict might lead to false result also.
	*/
	bool load(const QString & xrsfilename, QString * err );


	/**
	Checks version of Xui against implementation version.
	@param version The document's version.
	@return @e true, if version check passed.
	*/
	static bool checkVersion(const QString & version);
private:
	QString mId;
	QDomDocument mDoc;
};


#endif // __XrsLoader_H
