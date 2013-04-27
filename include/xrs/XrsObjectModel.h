#ifndef __XrsObjectModel_H
#define __XrsObjectModel_H

#include "AbstractObjectModel.h"
#include "xrs.hxx"
/**
The implementation for the Xrs (XML Ressource System) object structure.
@note This implementation bases on CodeSynthesis XML-to-C++-Mapping tool.
@author O. Haeger
*/
class XrsObjectModel : public AbstractObjectModel< xrs* >
{
public:

	XrsObjectModel();
	~XrsObjectModel();

	/**
	Reads an XRS file. Prior existing object models are released.
	@param xrsstream The XRS input stream
	@param streamname
	@param @e true, on success.
	*/
	bool read(std::istream & xrsstream, const char * streamname);

	/**
	@return The Xrs Model ist read-only. This method always returns false
	*/
	bool write(std::ostream & out, const char * streamname);


};


#endif // __XrsObjectModel_H


