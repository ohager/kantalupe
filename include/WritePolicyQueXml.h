#ifndef WRITEPOLICYQUEXML_H
#define WRITEPOLICYQUEXML_H

class QIODevice;

namespace k{
class AbstractTreeModel;
class TreeItem;
class WritePolicyQueXmlImpl_V1;

/**
  QueXML Write policy for ModelTreeData and its subtrees
  For more information about QueXML have a look
  at http://quexml.sourceforge.net/
  QueXML is published under GNU GPL v2.
  @author O. Haeger
  */
class WritePolicyQueXml
{
public:
	WritePolicyQueXml();
	~WritePolicyQueXml();
	/**
	  Writes the entire tree to device.
	  */
	bool write(const AbstractTreeModel * model, QIODevice * out) const;

	/**
	  Writes the a partial tree to device beginning at @e startnode
	  */
	bool write(const TreeItem * startnode, QIODevice * out) const;
private:
	mutable WritePolicyQueXmlImpl_V1 * mImpl;
};


} //eons


#endif // WRITEPOLICYQUEXML_H
