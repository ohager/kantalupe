#include "ScriptReaderImpl_V1.h"
#include "global.h"
#include "Script.h"

#include <QIODevice>
#include <QBuffer>
#include <QDataStream>
#include <QDebug>

START_NS

ScriptReaderImpl_V1::ScriptReaderImpl_V1(){}

bool ScriptReaderImpl_V1::read(Script & script, QIODevice * in)
{
	Q_ASSERT(in);

	if(in->isOpen())
		in->close();

	if(!in->open(QIODevice::ReadOnly))
		return false;


/*
from writer impl:
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
  */

	QByteArray raw = qUncompress(in->readAll());
	QDataStream instream(raw);
	int formatid=0,implversion=0;

	instream >> formatid >> implversion;
	if(formatid!=ScriptReaderWriter::ScriptFormatID)
	{
		qDebug() << "Incompatible Format.";
		return false;
	}

	if(implversion!=ImplVersion)
	{
		qDebug() << "Incompatible version: " << ImplVersion << " expected, but " << implversion << " obtained.";
		return false;
	}

	instream >> script.apilevel;

	QByteArray databuf;
	instream >> databuf;
	script.author = QString(databuf);

	instream >> databuf;
	script.description = QString(databuf);

	instream >> script.lastEdited; // directly, is of QDate

	instream >> databuf;
	script.name = QString(databuf);

	instream >> databuf;
	script.program = QString(databuf);

	instream >> databuf;
	script.version = QString(databuf);

	return true;

}


END_NS


