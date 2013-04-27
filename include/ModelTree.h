#ifndef MODELTREEDATA_H
#define MODELTREEDATA_H

#include "AbstractTreeModel.h"
#include "ModelTreeItemFactory.h"


class QStandardItem;
class QIODevice;

namespace k{

class Category;
class Group;
class Matrix;
class Problem;
class Model;
class MatrixProblem;
class TreeItem;
class AbstractTreeModelVisitor;


/**
  The tree-structured data for the 'k-Model'.

  @author O. Haeger
  */
class ModelTree : public AbstractTreeModel
{
    Q_OBJECT
public:
	/**
	  Constructs the tree data (model) with a first item, i.e. Model
	  */
    explicit ModelTree(QObject *parent = 0);

	~ModelTree();


public:




	/**
	  Adds a category(group,matrix, etc.) object at index @e at as one kind of InsertMode.
	  @param obj The category(group,matrix, etc.) object
	  @param parentindex The position where it will be added, i.e. the position of its parent item.
	  @return The new item, if successfully inserted, otherwise 0.
	  @see insertNewGroup(), insertNewMatrix(), insertProblem()
	  */
	QStandardItem * insertNewCategory(const Category & obj, const QModelIndex & parentindex);
	QStandardItem * insertNewGroup(const Group & obj, const QModelIndex & parentindex);
	QStandardItem * insertNewMatrix(const Matrix & obj, const QModelIndex & index);
	QStandardItem * insertNewProblem(const Problem & obj, const QModelIndex & index);
	QStandardItem * insertNewMatrixProblem(const MatrixProblem & m, const QModelIndex & index);
	QStandardItem * insertNewModel(const Model & m);
	QStandardItem * insertNewSurvey(const Survey &s); ///< not supported method!

	// --- dnd support
	QStringList mimeTypes() const;
	QMimeData * mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

private:
	ModelTreeItemFactory mItemFactory;
};

} // eons

#endif // MODELTREEDATA_H
