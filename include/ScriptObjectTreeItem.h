#ifndef SCRIPTOBJECTTREEITEM_H
#define SCRIPTOBJECTTREEITEM_H

#include <QObject>
#include "TreeItemProtocol.h"

namespace k{

class TreeItem;

/**
  @ingroup scriptapi
  @defgroup itemprops Static Item Properties
  The script object for TreeItem. This item is passed to the
  Script API. The item is an proxy object for TreeModel items.
  Additionally, to static properties a TreeItem might provide dynamic
  properties, defined by user in the TreeModel object.
  These properties can be accessed in the same manner like the static
  properties.
  @author O. Haeger
  */
class ScriptObjectTreeItem : public QObject
{
	Q_OBJECT
	/** @ingroup itemprops
	  The item's type, which is currently one of the following values:
	- @c category
	- @c group
	- @c matrix
	- @c matrixproblem
	- @c problem
	- @c model
	- @c survey
	  */
	Q_PROPERTY(QString type READ getItemType)
	/** @ingroup itemprops
	  The item's name. Dependent of the type a 'name' can be either an item's
	  name or in case of (matrix)problem items the  @e Uid.
	  - @c name when item is model, survey, category, group, or matrix
	  - @c uid when item is matrixproblem, or problem
	  */
	Q_PROPERTY(QString name READ getName)
	/** @ingroup itemprops
	  The item's selection state. Selected items will be added to the
	  survey instance that is to be generated via the script.
	  */
	Q_PROPERTY(bool selected READ isSelected WRITE setSelected )
public:

	ScriptObjectTreeItem(TreeItem * item,QObject * parent=0x0);

	QString getItemType();
	QString getName();

	bool isSelected() const;
	void setSelected(bool);

	types::Properties getProperties() const;

private:
	void initialize();
private:
	TreeItem * mItem;

};

} // eons

#endif // SCRIPTOBJECTTREEITEM_H
