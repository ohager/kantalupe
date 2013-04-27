#ifndef TREEITEM_H
#define TREEITEM_H

#include <QStandardItem>

#include "AbstractTreeModelVisitor.h"
#include "TreeItemProtocol.h"

namespace k{

class AbstractTreeModel;

/**
  The model's item.
  Use the ModelTreeDataItemFactory for item creation.
  @author O. Haeger
  */
class TreeItem : public QStandardItem
{
public:


	TreeItem( );
	TreeItem( const QString & text );
	TreeItem( const QIcon & icon, const QString & text );

	/**
	  Sets the items type
	  @param type The type identifier
	  @see getItemType()
	  */
	inline void setItemType(tip::ItemType type) { mItemType = type; }

	/**
	  Gets the items type
	  @return type The type identifier
	  @see setItemType()
	  */
	inline tip::ItemType  getItemType() const { return mItemType; }



	/**
	  @return The model item, which is, like the invisible root item, unique for each ModelTreeData
	  */
	TreeItem * getTreeItem() const;

	AbstractTreeModel * treeModel() const;


	/**
	  Entry point for ModelTreeDataVisitor object.
	  @param v The visitor object
	  */
	AbstractTreeModelVisitor::TraversalType acceptVisitor(AbstractTreeModelVisitor * v);
private:
	tip::ItemType  mItemType;
};

} // eons

#endif // MODELTREEDATAITEM_H
