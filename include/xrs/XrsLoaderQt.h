#ifndef __XrsLoaderQt_H
#define __XrsLoaderQt_H

#include <QString>
#include <QStringList>

#include "XrsLoader2.h"
/**
A Qt wrapper for Xrs Loading system.
It provides a Qt-based interface of the pure std::cpp based XrsLoader2
@note Converting STL stuff to QString(List)'s produces some additional overhead, such
as (iterative) copying. Keep that in mind, if you plan to make excessive use of this wrapper.
It is always a good idea to locally cache (that is, within your scope) the values prior to multiple use.
@author O. Haeger
*/
class XrsLoaderQt
{
public:

	XrsLoaderQt();
	~XrsLoaderQt();

	/**
	@return The id of the XRS document
	*/
	QString id() const;


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
	@param [out] type The resource's type, that will be returned on invocation. 
	Can be null, e.g. if user has a priori knowledge about type (slightly faster).
	@return The value of a specified Prefix and alias. If an empty string is returned, 
	and if @e type is not null it becomes XrsLoader2::Invalid.	*/
	QString getValue(const QString & qname, XrsLoader2::ResourceType * type=0) const;

	/**
	@param prefix The prefix
	@param alias The alias
	@param [out] type The resource's type, that will be returned on invocation. 
	Can be null, e.g. if user has a priori knowledge about type (slightly faster).
	@return The value of a specified Prefix and alias. If an empty string is returned, 
	and if @e type is not null it becomes XrsLoader2::Invalid.
	*/
	QString getValue(const QString & prefix, const QString & alias, XrsLoader2::ResourceType * type=0) const;

	/**
	Loads a XRS file.
	@param xrsfilename
	@param [out] err The error, if one occurred
	@param [out] detail The error details, if wished.
	@return @e true, if successfully loaded, otherwise false.
	Aside the normal load failures, a version conflict might lead to false result also.
	*/
	bool load(const QString & xrsfilename, QString * err, QString * detail=0x0  );


	/**
	Checks version of Xui against implementation version.
	@param version The document's version.
	@return @e true, if version check passed.
	*/
	static bool checkVersion(const QString & version);
protected:
	/**
	Converts a STL string list to QStringList.
	Although Qt offers a fromStdList method, it can happen that STL compatibility is disabled.
	This method is used to maintain compatibility even with non-STL compiled Qt-Versions.
	*/
	static QStringList fromStdList(const std::list<std::string> & stdlist);
private:
	XrsLoader2 * mXrsLoader;

};

#endif // __XrsLoaderQt_H


