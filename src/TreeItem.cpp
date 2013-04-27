#include "TreeItem.h"
#include "AbstractTreeModel.h"
//#include "global.h"

namespace k{

TreeItem::TreeItem() :
	QStandardItem(), mItemType(tip::ItemUnspecified) {}

TreeItem::TreeItem( const QString & text ) :
	QStandardItem(text), mItemType(tip::ItemUnspecified) {}

TreeItem::TreeItem( const QIcon & icon, const QString & text ) :
	QStandardItem(icon, text), mItemType(tip::ItemUnspecified) {}


TreeItem * TreeItem::getTreeItem() const
{
	Q_ASSERT(model());

	return (TreeItem *)model()->invisibleRootItem()->child(0);
}


AbstractTreeModel * TreeItem::treeModel() const
{
	Q_ASSERT(model());
	return 	(AbstractTreeModel*)model();

}

AbstractTreeModelVisitor::TraversalType TreeItem::acceptVisitor(AbstractTreeModelVisitor* visitor)
{
	AbstractTreeModelVisitor::TraversalType type = visitor->visit(this); // dispatch
	if(	type == AbstractTreeModelVisitor::TraversalEnd 	)
	{
		visitor->leave(this);
		return AbstractTreeModelVisitor::TraversalEnd;
	}
	else if( type == AbstractTreeModelVisitor::TraversalIgnoreSubtree)
	{
		visitor->leave(this);
		return AbstractTreeModelVisitor::TraversalContinue;
	}

	// traverse subtree
	int nitems = rowCount();
	for(int i=0; i<nitems; ++i)
	{
		type = ((TreeItem*)child(i))->acceptVisitor(visitor);
		if(type != AbstractTreeModelVisitor::TraversalContinue)
		{
			visitor->leave(this);
			return type;
		}
	}
	visitor->leave(this);
	return AbstractTreeModelVisitor::TraversalContinue;
}

} // eons


