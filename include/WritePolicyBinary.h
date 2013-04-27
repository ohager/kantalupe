#ifndef WRITEPOLICYBinary_H
#define WRITEPOLICYBinary_H

class QIODevice;

namespace k{
class AbstractTreeModel;
class TreeItem;
class WritePolicyBinaryImpl_V1;
/**
  Binary Write policy for ModelTreeData and its subtrees
  @author O. Haeger
  */
class WritePolicyBinary
{
public:
	WritePolicyBinary();
	~WritePolicyBinary();
	/**
	  Writes the entire tree to device.
	  */
	bool write(const AbstractTreeModel * model, QIODevice * out) const;


private:
	mutable WritePolicyBinaryImpl_V1 * mImpl;
};


} //eons

#endif // WRITEPOLICYBinary_H
