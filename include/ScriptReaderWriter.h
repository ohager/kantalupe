#ifndef SCRIPTREADERWRITER_H
#define SCRIPTREADERWRITER_H




class QIODevice;

namespace k{

class Script;

/**
  Class for reading and writing Script objects.

  @author O Haeger
  */
class ScriptReaderWriter
{
public:
	class ReaderInterface {	virtual bool read(Script & script, QIODevice * in)=0;	};
	class WriterInterface {	virtual bool write(const Script & script, QIODevice * out)=0;	};
public:
	static const int ScriptFormatID; ///< identfier for script format id on reading/writing
	explicit ScriptReaderWriter();

public:
	/**
	  Reads a script from given device.
	  @param [in] script The target object
	  @param in The input device
	  @return @e true, if successfully loaded.
	  @see write
	*/
	bool read(Script & script, QIODevice * in);

	/**
	  Writes a script to given device.
	  @param script The script object to be written
	  @param in The output device
	  @return @e true, if successfully written.
	  */
	bool write(const Script & script, QIODevice * out);

};

} // eons

#endif // SCRIPTREADERWRITER_H
