#ifndef MODELINSERTIONINTERFACE_H
#define MODELINSERTIONINTERFACE_H

class QStandardItem;
class QModelIndex;

namespace k{


class Category;
class Group;
class Matrix;
class Problem;
class Model;
class MatrixProblem;
class Survey;
// todo: add Survey

/**
  Interface for item insertion in QStandardItemModel instances.
  @author O. Haeger
  */
class ModelInsertionInterface
{
public:

	virtual ~ModelInsertionInterface(){}
	/**
	  Adds a category(group,matrix, etc.) object at given index.
	  @param obj The category(group,matrix, etc.) object
	  @param parentindex The position where it will be added, i.e. the position of its parent item.
	  @return The new item, if successfully inserted, otherwise 0.
	  */
	virtual QStandardItem * insertNewCategory(const Category & obj, const QModelIndex & parentindex) =0;
	virtual QStandardItem * insertNewGroup(const Group & obj, const QModelIndex & parentindex)=0;
	virtual QStandardItem * insertNewMatrix(const Matrix & obj, const QModelIndex & index)=0;
	virtual QStandardItem * insertNewProblem(const Problem & obj, const QModelIndex & index)=0;
	virtual QStandardItem * insertNewMatrixProblem(const MatrixProblem & m, const QModelIndex & index)=0;

	/**
	  Adds a model object at top level node
	  @param m Model object
	  @return The new item, if successfully inserted otherwise 0.
	  */
	virtual QStandardItem * insertNewModel(const Model & m)=0;

	/**
	  Adds a survey object at top level node
	  @param m Model object
	  @return The new item, if successfully inserted otherwise 0.
	  */

	virtual QStandardItem * insertNewSurvey(const Survey & s)=0;

};

} // eons

#endif // ITEMMODELINSERTIONINTERFACE_H
