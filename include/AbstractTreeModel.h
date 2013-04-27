#ifndef ABSTRACTTREEMODEL_H
#define ABSTRACTTREEMODEL_H

#include <QStandardItemModel>
#include "ModelInsertionInterface.h"

class QStandardItem;
class QIODevice;

namespace k{

class TreeItem;
class AbstractTreeModelVisitor;


/**
  A generic tree-structured model
  @author O. Haeger
  */
class AbstractTreeModel : public QStandardItemModel, public ModelInsertionInterface
{
    Q_OBJECT
public slots:
	void removeItem(const QModelIndex & itemindex);
public:
	/**
	  Constructs the tree data (model) with a first item, i.e. Model
	  */
	explicit AbstractTreeModel(QObject *parent = 0);

	virtual ~AbstractTreeModel();

	/**
	  Per definitionem the root item is the <e>one and only child</e> of invisibleRootItem().
	  @return The one and only child of invisibleRootItem()
	  */
	TreeItem * rootItem() const;
public:

	/**
	  Writes the model data to given QIODevice.
	  @param out The output device, where the model's representation will be written.
	  @param policy The write policy. must implement the following method:</br>
	   @codeline bool write(const AbstractTreeModel *, QIODevice*) const;
	  @return @e true, if succesfully written, otherwise false;
	  */
	template<typename WritePolicy>
	bool save(QIODevice * out, WritePolicy & policy) const{
		return policy.write(this, out);
	}

	/**
	  Reads the model data from given QIODevice.
	  @param in The input device
	  @param policy The read policy. must implement the following method:</br>
	   @codeline bool read(QIODevice*, ModelInsertionInterface *) const;
	  @return @e true, if succesfully written, otherwise false;
	  */
	template<typename ReadPolicy>
	bool load(QIODevice * in, ReadPolicy & policy){
		clear();
		return policy.read(in, this);
	}

	TreeItem * itemFromIndexAsTreeItem(const QModelIndex & index) const;

	/**
	  Entry point for tree traversal using a visitor object.
	  @param visitor The visitor instance
	  @param [optional] start The start node. It is possible to begin the traversal at any node within the tree.
	  If @e start=0x0 the traversal begins at the tree root, i.e. it's the same like traverse(myvisitor, invisibleRootItem());
	  @note Visitor won't be deleted when finished.
	  */
	void traverse(AbstractTreeModelVisitor * visitor, TreeItem * start = 0x0);

	// --- dnd support
	/*
	QStringList mimeTypes() const;
	QMimeData * mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
	*/
protected:
	/**
	  Convenience method to convert the passed index into an Item object.
	  It useful to use in conjunction with newInsert-Methods from ModelInsertionInterface
	  */
	QStandardItem * getParentForInsert(const QModelIndex & parentindex) const;
};

} // eons

#endif // MODELTREEDATA_H
