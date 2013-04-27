#ifndef WRITEPOLICYXML_H
#define WRITEPOLICYXML_H

class QIODevice;

namespace k{
class AbstractTreeModel;
class TreeItem;
class WritePolicyXmlImpl_V1;
/**
  XML Write policy for ModelTreeData and its subtrees
  @author O. Haeger
  */
class WritePolicyXml
{
public:
	WritePolicyXml();
	~WritePolicyXml();
	/**
	  Writes the entire tree to device.
	  */
	bool write(const AbstractTreeModel * model, QIODevice * out) const;

	/**
	  Writes the a partial tree to device beginning at @e startnode
	  */
	bool write(const TreeItem * startnode, QIODevice * out) const;
private:
	mutable WritePolicyXmlImpl_V1 * mImpl;
};


} //eons

#endif // WRITEPOLICYXML_H
