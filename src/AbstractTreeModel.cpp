#include "AbstractTreeModel.h"
#include "TreeItem.h"
//#include "AbstractTreeModelItemFactory.h"
#include "AbstractTreeModelVisitor.h"

//#include "global.h"
#include "ProtocolTypes.h"

//#include "WritePolicyXml.h"

#include <QStandardItem>
#include <QBuffer>
#include <QMimeData>

namespace k{

AbstractTreeModel::AbstractTreeModel(QObject *parent) :
    QStandardItemModel(parent)
{



}

AbstractTreeModel::~AbstractTreeModel()
{
	//qDebug("AbstractTreeModel deleted...");
}

TreeItem * AbstractTreeModel::rootItem() const
{
	return (TreeItem*)invisibleRootItem()->child(0);
}


void AbstractTreeModel::traverse(AbstractTreeModelVisitor * visitor, TreeItem * start)
{
	start = start ? start : rootItem();
	start->acceptVisitor(visitor);
}

TreeItem* AbstractTreeModel::itemFromIndexAsTreeItem(const QModelIndex & index) const
{
	return (TreeItem*)itemFromIndex(index);
}

QStandardItem * AbstractTreeModel::getParentForInsert(const QModelIndex & parentindex) const
{
	QStandardItem * parent = 0;
	if(!parentindex.isValid())
	{
		parent = invisibleRootItem();
	}
	else
	{
		parent = itemFromIndex(parentindex);
		Q_ASSERT_X(parent,"AbstractTreeModel::getParentForInsert","Item is Null");

	}
	return parent;
}

//--------------------------------- slots ------------------------------------------
void AbstractTreeModel::removeItem(const QModelIndex & itemindex)
{
	removeRow(itemindex.row(), itemindex.parent());
}


} // eons


