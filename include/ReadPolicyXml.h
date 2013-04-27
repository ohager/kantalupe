#ifndef READPOLICYXML_H
#define READPOLICYXML_H

#include <QModelIndex>

class QIODevice;


namespace k{
class ModelInsertionInterface;
class ReadPolicyXmlImpl_V1;
class TreeItem;

/**
  XML Write policy for ModelTreeData.
  @author O. Haeger
  */
class ReadPolicyXml
{
public:
	ReadPolicyXml();
	~ReadPolicyXml();
	/**
	  Reads (Deserializes) the data from device inserts the result into given target.
	  @param in The input device
	  @param inserter The target object, that will be populated
	  @param [optional] parent The parent index, where the reader will start to insert!
	  */
	bool read(QIODevice * in, ModelInsertionInterface * inserter,  const QModelIndex & parent=QModelIndex()) const;
private:
	mutable ReadPolicyXmlImpl_V1 * mImpl;
};


} //eons

#endif // READPOLICYXML_H
