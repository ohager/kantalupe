#ifndef ABSTRACTTREEMODELVISITOR_H
#define ABSTRACTTREEMODELVISITOR_H

namespace k{

class TreeItem;

/**
  Base Class for TreeItem traversal (using visitor pattern)
  Subclass and implement visit().
  @par Traversal Policies
  The traversal can be controlled by return codes.
  -# TraversalContinue Continues the traversal normally.
  -# TraversalIgnoreSubtree The subtree of current item will not be entered, but next sibling
  -# TraversalEnd Immediately, stops any traversal
  @author O. Haeger
  */
class AbstractTreeModelVisitor
{
public:
	enum TraversalType{
		TraversalContinue=0x1, ///< Normal traversal, including depth
		TraversalIgnoreSubtree, ///< Traversal stops here ignoring the subtree, but will continue on siblings
		TraversalEnd ///< Traversal ends immediately
	};

	/**
	  Called whenever @e item is visited (entered)
	  @param item The visited item
	  @return the traversal type indicating how to continue.
	  @see leave()
	  */
	virtual TraversalType visit(TreeItem * item) =0;
	/**
	  Called whenever visited @e item is about to be left
	  @param item The visited item
	  */
	virtual void leave(TreeItem * item) =0;
};


} // eons
#endif // ABSTRACTMODELTREEDATAVISITOR_H
