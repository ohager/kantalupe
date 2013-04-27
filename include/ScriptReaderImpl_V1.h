#ifndef SCRIPTREADERIMPL_V1_H
#define SCRIPTREADERIMPL_V1_H

#include "ScriptReaderWriter.h"

class QIODevice;

namespace k{

class Script;

class ScriptReaderImpl_V1 : public ScriptReaderWriter::ReaderInterface
{
public:
	static const int ImplVersion = 1;
	ScriptReaderImpl_V1();
	bool read(Script & script, QIODevice * in);
};

} // eons

#endif // SCRIPTREADERIMPL_H
