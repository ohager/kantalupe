#ifndef TREEITEMFACTORY_H
#define TREEITEMFACTORY_H

#include "TreeItem.h"
#include "TreeItemProtocol.h"

namespace k{

/**
  Default item factory implementation.
  To fill a created item with its data the underlying TreeItemProtocol::incept method is used.
  While the content is defined by the protocol a user might implement applyStyle() for customized
  item's appearance.
  Hint: Subclasses could implement a singleton pattern.
  @author O. Haeger
  */
class TreeItemFactory
{
public:
	TreeItemFactory() {};
	virtual ~TreeItemFactory() { }

	/**
	Item factory method.
	This template method takes advantage of the 'type-variant' inception methods of TreeItemProtocol.
	@param obj The data object used for item creation.
	If the protocol does not support @e obj of type @e T the compiler will complain.
	@return The new item with the passed usage data from @e obj.
	@see applyStyle()
	*/
	template<typename T>
	TreeItem * createItem(const T & obj)
	{
		TreeItem * item = new TreeItem();
		item->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
		tip::incept(obj,item);
		applyStyle(item);
		return item;
	}

	/**
	  It is possible to define a custom style for an item.
	  The default implementation does nothing, i.e. is empty.
	  @param item The item that shall be styled.
	  @note applyStyle is called right before createItem() returns the recently created item.
	  */
	virtual void applyStyle(TreeItem * item){ Q_UNUSED(item); }


};

} // eons

#endif // TREEITEMFACTORY_H
