#include "ScriptReaderWriter.h"
#include "ScriptReaderImpl_V1.h"
#include "ScriptWriterImpl_V1.h"
#include "Script.h"

#include "global.h"

START_NS

const int ScriptReaderWriter::ScriptFormatID = 0x1337;

ScriptReaderWriter::ScriptReaderWriter()
{
}


bool ScriptReaderWriter::read(Script & s, QIODevice * in)
{
	ScriptReaderImpl_V1 reader;
	return reader.read(s,in);
}

bool ScriptReaderWriter::write(const Script & s, QIODevice * out)
{
	ScriptWriterImpl_V1 writer;
	return writer.write(s, out);
}


END_NS
