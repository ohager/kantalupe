#ifndef MODELTREEITEMFACTORY_H
#define MODELTREEITEMFACTORY_H

#include "TreeItemFactory.h"

namespace k{


/**
  The factory for item creation.
  The factory takes advantage of the protocol's implicit type-conversion capabilities.
  So, all types supported by ModelTreeDataItemProtocol, can be put into createItem().
  @par Example
  @code
  Category catObj;
  Group groupObj,
  //...
  // the compiler will know what to do here!
  ModelTreeDataItem * catItem = ModelTreeDataItemFactory().createItem(catObj);
  ModelTreeDataItem * groupItem = ModelTreeDataItemFactory().createItem(groupObj);
  @endcode
  @see TreeItemProtocol
  @author O. Haeger
  */
class ModelTreeItemFactory : public TreeItemFactory
{
public:
	ModelTreeItemFactory();

	void applyStyle(TreeItem * item);
protected:
	static void fontStyle(const QString & style, const QString & size, QFont & f);
	static Qt::Alignment align(const QString & alignment);
};

}

#endif // MODELTREEDATAITEMFACTORY_H
