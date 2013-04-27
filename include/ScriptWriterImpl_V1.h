#ifndef SCRIPTWRITERIMPL_V1_H
#define SCRIPTWRITERIMPL_V1_H

#include "ScriptReaderWriter.h"

class QIODevice;

namespace k{

class Script;

/**
  Script write implementation.
  @version 1
  @author O. Hager
  */
class ScriptWriterImpl_V1 : public ScriptReaderWriter::WriterInterface
{
public:
	static const int ImplVersion = 1;
	ScriptWriterImpl_V1();
	bool write(const Script & script, QIODevice * out);
	void prepare(Script & script) const;
};

} /// eons

#endif // SCRIPTWRITER_APILVL_1_H
