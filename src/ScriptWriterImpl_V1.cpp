#include "ScriptWriterImpl_V1.h"
#include "global.h"

#include "Script.h"

#include <QIODevice>
#include <QBuffer>
#include <QDataStream>

START_NS

ScriptWriterImpl_V1::ScriptWriterImpl_V1() {}


void ScriptWriterImpl_V1::prepare(Script & script) const
{
	static const char * InvValue = "#INV";
	// fill empty parts
	script.apilevel = script.apilevel<=0 ? 1 : script.apilevel;
	script.author = script.author.isEmpty() ? InvValue : script.author;
	script.description = script.description.isEmpty() ? InvValue : script.description;
	script.name = script.name.isEmpty() ? InvValue : script.name;
	script.name = script.name.isEmpty() ? "1.0" : script.name;
	script.program = script.program.isEmpty() ? "/* no script */" : script.program;
	script.lastEdited = QDate::currentDate();
}

bool ScriptWriterImpl_V1::write(const Script & script, QIODevice * out)
{
	Q_ASSERT(out);

	if(out->isOpen())
		out->close();

	if(!out->open(QIODevice::WriteOnly))
		return false;


	//prepare(const_cast<Script &>(script));

	QBuffer buf;
	buf.open(QIODevice::WriteOnly);

	QDataStream outstream(&buf);

	outstream << ScriptReaderWriter::ScriptFormatID
				<< ImplVersion
			  << script.apilevel
			  << script.author.toAscii()
			  << script.description.toAscii()
			  << script.lastEdited
			  << script.name.toAscii()
			  << script.program .toAscii()
				<< script.version.toAscii();

	return out->write(qCompress(buf.buffer()))!=-1;

}

END_NS
