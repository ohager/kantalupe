#ifndef READPOLICYBinary_H
#define READPOLICYBinary_H

#include <QModelIndex>

class QIODevice;


namespace k{
class ModelInsertionInterface;
class ReadPolicyBinaryImpl_V1;
class TreeItem;

/**
  Binary Write policy for ModelTreeData.
  @author O. Haeger
  */
class ReadPolicyBinary
{
public:
	ReadPolicyBinary();
	~ReadPolicyBinary();
	/**
	  Reads (Deserializes) the data from device inserts the result into given target.
	  @param in The input device
	  @param inserter The target object, that will be populated
	  @param [optional] parent The parent index, where the reader will start to insert!
	  */
	bool read(QIODevice * in, ModelInsertionInterface * inserter,  const QModelIndex & parent=QModelIndex()) const;
private:
	mutable ReadPolicyBinaryImpl_V1 * mImpl;
};


} //eons

#endif // READPOLICYBinary_H
