#ifndef SURVEYTREE_H
#define SURVEYTREE_H

#include "AbstractTreeModel.h"
#include "SurveyTreeItemFactory.h"


namespace k{

class SurveyTree : public AbstractTreeModel
{
	Q_OBJECT
public:
	explicit SurveyTree(QObject * parent=0x0);
	~SurveyTree();

	// AbstractTreeModel Implementation
	QStandardItem * insertNewCategory(const Category & obj, const QModelIndex & parentindex);
	QStandardItem * insertNewGroup(const Group & obj, const QModelIndex & parentindex);
	QStandardItem * insertNewMatrix(const Matrix & obj, const QModelIndex & index);
	QStandardItem * insertNewProblem(const Problem & obj, const QModelIndex & index);
	QStandardItem * insertNewMatrixProblem(const MatrixProblem & m, const QModelIndex & index);
	QStandardItem * insertNewModel(const Model & m);
	QStandardItem * insertNewSurvey(const Survey & s);


	// drag and drop implementation
	QStringList mimeTypes() const;
	Qt::DropActions supportedDropActions() const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
private:
	SurveyTreeItemFactory mItemFactory;
};


} // eons

#endif // SURVEYTREE_H
