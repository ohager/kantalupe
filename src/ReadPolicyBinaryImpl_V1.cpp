#include "ReadPolicyBinaryImpl_V1.h"
#include "WritePolicyBinaryImpl_V1.h"
#include "ReadPolicyXml.h"
#include "ModelInsertionInterface.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include <QApplication>
#include <QDir>
#include <QBuffer>
#include <QImage>
#include <QString>
#include <QCryptographicHash>

#include "global.h"
START_NS

const char * ReadPolicyBinaryImpl_V1::Version = "1";

ReadPolicyBinaryImpl_V1::ReadPolicyBinaryImpl_V1() : mModel(0x0){

}

bool ReadPolicyBinaryImpl_V1::read(QIODevice * in, ModelInsertionInterface * mtd, const QModelIndex & parent)
{
	Q_ASSERT(mtd);
	Q_ASSERT(in);

	if(in->isOpen())
		in->close();

	if(!in->open(QIODevice::ReadOnly))
	{
		QString what=QApplication::translate("errmsg","Cannot open IO-Device!");
		MessageHandler::error("ReadPolicyBinaryImpl_V1","read", what, in->errorString());
		return false;
	}


	QDataStream instream(in);

	QByteArray data, hash;
	QString rootpath, formatid;
	instream >> formatid >> rootpath >> hash >> data;
	data = qUncompress(data);

	// from write
	// outstream << FormatId << rootpath << hash << qCompress(buf.data());
	if(WritePolicyBinaryImpl_V1::FormatId != formatid ||
		QCryptographicHash::hash(data, QCryptographicHash::Sha1) != hash
			)
	{
		QString what=QApplication::translate("errmsg","Unknown File format.");
		MessageHandler::error("ReadPolicyBinaryImpl_V1","read", what, in->errorString());
		return false;
	}


	copyImages(rootpath, instream);


	QBuffer xmlbuf(&data);

	ReadPolicyXml xmlreader;
	xmlreader.read(&xmlbuf, mtd, parent);


	in->close();
	return true;
}

void ReadPolicyBinaryImpl_V1::copyImages(const QString & rootpath, QDataStream & instream)
{
	QDir rootdir;
	rootdir.mkpath(rootpath);

	while(!instream.atEnd())
	{
		QImage image;
		QString imgurl, tempimage;
		instream >> imgurl >> image;
		tempimage = rootpath + imgurl;
		image.save( tempimage );
	}
}

END_NS
