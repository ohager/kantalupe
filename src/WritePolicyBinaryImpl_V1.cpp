#include "WritePolicyBinaryImpl_V1.h"
#include "AbstractTreeModel.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include "global.h"

#include "WritePolicyXmlImpl_V1.h"

#include <QDate>
#include <QDir>
#include <QDataStream>
#include <QBuffer>
#include <QStringList>
#include <QCryptographicHash>

START_NS

// need this overwritten class for rewrite the image urls.
class PrivateWritePolicyXml_V1 : public WritePolicyXmlImpl_V1
{
	public:

	/**
	  @param imageroot The new root path for the images. It be with '/' at end.
	  */
	PrivateWritePolicyXml_V1(const QString & imageroot) :
		WritePolicyXmlImpl_V1(),
		mImageRoot(imageroot)
	{
		Q_ASSERT(imageroot.endsWith('/'));
	}

	// overwrite
	void writeImages(const types::Images & imgs)
	{
		mWriter.writeStartElement("ImageList");
		foreach(const QString & img, imgs)
		{
			QFileInfo fi(img);
			mWriter.writeTextElement("Image", mImageRoot + fi.fileName());
		}
		mWriter.writeEndElement();
	}
private:
	QString mImageRoot;
};

// -----------------------------------------------------------------------------

const char * WritePolicyBinaryImpl_V1::Version = "1";
const char * WritePolicyBinaryImpl_V1::FormatId = "KModel";



WritePolicyBinaryImpl_V1::WritePolicyBinaryImpl_V1() :
	mHasError(false)
{
}

bool WritePolicyBinaryImpl_V1::write(AbstractTreeModel * mtd, QIODevice *out)
{
	if(out->isOpen())
		out->close();
	if(!out->open(QIODevice::WriteOnly))
	{
		qDebug("Could not open device");
	}

	// preparations

	mtd->traverse(this);

	// write data
	QDataStream outstream(out);
	QString rootpath=QString("%1/%2.res/").arg(QDir::tempPath()).arg(mName);
	PrivateWritePolicyXml_V1 xmlwriter( rootpath );
	QBuffer buf;
	xmlwriter.write(mtd, &buf);
	QByteArray hash = QCryptographicHash::hash(buf.data(), QCryptographicHash::Sha1);
	outstream << QString(FormatId) << rootpath << hash << qCompress(buf.data());

	// write
	writeImages(mImageUrlList, outstream);


	out->close();
	return !mHasError;
}


AbstractTreeModelVisitor::TraversalType WritePolicyBinaryImpl_V1::visit(TreeItem * item){
	tip::ItemType type = item->getItemType();

	if(type == tip::ItemModel)
	{
		Model obj;
		tip::extract(item, obj);
		mName = obj.name;
	}
	else if(type == tip::ItemSurvey)
	{
		Survey obj;
		tip::extract(item, obj);
		mName = obj.name;
	}
	else if(type == tip::ItemMatrix)
	{
		Matrix obj;
		tip::extract(item, obj);
		mImageUrlList.append( obj.images );
	}
	else if(type == tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj);
		mImageUrlList.append( obj.images );

	}


	return AbstractTreeModelVisitor::TraversalContinue;
}

void WritePolicyBinaryImpl_V1::leave(TreeItem *item)
{
}



// ------------------------ write item methods ---------------------------------


void WritePolicyBinaryImpl_V1::writeImages(const QStringList & imageurls, QDataStream & outstream)
{
	foreach(const QString & imgurl, imageurls)
	{
		QImage imagefile(imgurl);
		if(!imagefile.isNull())
		{
			outstream << QFileInfo(imgurl).fileName() << imagefile;
		}
	}
}



END_NS
