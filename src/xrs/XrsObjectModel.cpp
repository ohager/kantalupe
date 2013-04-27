#include "XrsObjectModel.h"
//#include "global.h"
#include "xrs.hxx" // the auto generated code from CodeSynthesis
#include "xrs-pimpl.hxx"

#include <sstream>
#include <fstream>

XrsObjectModel::XrsObjectModel()
{
	setRoot(0x0);
}

XrsObjectModel::~XrsObjectModel()
{
	// clean up, note that we released the auto_ptr<>
	xrs * root = getRoot();
	delete root; root=0x0;
}


bool XrsObjectModel::read(std::istream & input, const char * streamname)
{
	setNull(true);
	try
	{
		xrs_paggr xrsp;
		xml_schema::document_pimpl doc( xrsp.root_parser(), xrsp.root_name() );
		xrsp.pre();
		doc.parse( input );
		setRoot( xrsp.post() );
		setNull(false);
	}
	catch( const xml_schema::parser_exception & pe )
	{
		std::stringstream stream;
		if (streamname)
			stream << "Error while parsing '" << streamname << "'";
		else
			stream << "Error while parsing";

		setErrorBrief( stream.str() );
	
		std::stringstream strdetail;
		strdetail << "The parsing error at line " << pe.line() << " is:\n"  << pe.text();
		setErrorDetails( strdetail.str() );
	}
	return !isNull();
}


bool XrsObjectModel::write(std::ostream & out, const char * streamname)
{

	// read-only model
	setErrorBrief("Xrs is read-only");
	setErrorDetails("This implementation does not support serialization.");
	return false;
}
