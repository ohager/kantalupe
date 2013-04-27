#ifndef __AbstractObjectModel_H
#define __AbstractObjectModel_H

#include <fstream>
#include <sstream>
/**
An interface designed for loading and  saving @e recursive object models (e.g. W3C DOMs, or even arbitrary models).
As a recursive structure is expected this object model just holds the root of the recursive structure.
@author O. Haeger
*/
template<typename O>
class AbstractObjectModel
{
public:
	/**
	Creates a null object model.
	*/
	AbstractObjectModel() : mNull(true) {} 
	virtual ~AbstractObjectModel() { }
	

	/**
	@return @e true, if no root object is avaible, e.g. if read() failed.
	*/
	inline bool isNull() const  { return mNull; }
	/**
	@return The root object of the XML hierarchy, which is the document node.
	*/
	inline const O & getRoot() const { return mRoot; }
	inline O & getRoot() { return mRoot; }
	
	/**
	Sets the new root object.
	@param root The new root object.
	*/
	void setRoot(const O & root) {  mRoot = root; }
	//void setRoot(XmlObject & root) {  mRoot = root; }
	
	/**
	Reads a stream with object model data.
	When reading was successful, the root element is available via getRoot()
	and this instance is not null.
	@param instream The input stream
	@param streamname A name for the input stream. Can be null!
	This name is used on exception handling to indentify the stream, i.e. file name
	@return @e true, if parsing was successful.
	@see read(std::ostream &, const char *), setNull(), isNull(), setRoot()
	*/
	virtual bool read(std::istream & instream, const char * streamname)=0;

	/**
	Provided for convenience. Reads a file. 
	@param filename The filename of the file.
	@return @e true, on success.
	@see setNull(), isNull(), setRoot()
	*/
	virtual bool readFile(const char * filename)
	{
		setNull(true);
		// check if file exists!
		std::ifstream file;
		file.open(filename, std::ios::in);
		if( !file.is_open() )
		{
			std::stringstream stream;
			stream << "Error while parsing file '" << filename << "'.";
			setErrorBrief( stream.str() );
			setErrorDetails("Could not open file!");
			return false;
		}

		return read(file, filename);
	}

	/**
	Writes the object model to a file.
	@param filename The filename of the target file.
	@param @e true, on success.
	*/
	virtual bool write(std::ostream & outstream, const char * streamname)=0;
	
	/**
	Provided for convenience. Writes model to a file. 
	@param filename The filename of the file.
	@return @e true, on success.
	@see write(std::ostream &, const char *), setNull(), isNull(), setRoot()
	*/
	virtual bool writeFile(const char * filename)
	{
		
		setNull(true);
		// check if file exists!
		std::ofstream file;
		file.open(filename, std::ios::out | std::ios::trunc);
		if( !file.is_open() )
		{
			std::stringstream stream;
			stream << "Error while writing file '" << filename << "'.";
			setErrorBrief( stream.str() );
			setErrorDetails("Could not open file!");
			return false;
		}

		return write(file, filename);
	}
	/**
	If had an error on read() or write() you can get the occured error with.
	@param [out] brief A brief human readable text about occured error while reading or writing.
	@param [out] details A detailed description of occurences.
	*/
	void getError(std::string * brief, std::string * details) const
	{
		*brief = mErrorBrief;
		*details = mErrorDetails;
	}
protected:
	void setErrorBrief(const std::string & msg) { mErrorBrief=msg; }
	void setErrorDetails(const std::string & msg) { mErrorDetails=msg; }

	/**
	Sets the object model to null. Use this in your implementation to indicate
	a null object model,e.g.on your load implementation-
	*/
	void setNull(bool isnull) { mNull = isnull; }

private:
	std::string mErrorBrief, mErrorDetails;
	bool mNull;
	O mRoot;
};


#endif // __XmlObjectModel_H
