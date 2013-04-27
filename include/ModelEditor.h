#ifndef MODELEDITOR_H
#define MODELEDITOR_H


#include <QWidget>


class QToolBar;


namespace k{

class TaskDialog;
class ModelView;
class ModelTree;
class TreeItem;

class ModelEditor : public QWidget
{
    Q_OBJECT
signals:
	void clickedItem(TreeItem *);
	void selectedItem(TreeItem*);

public:
	explicit ModelEditor(QWidget *parent = 0);

	inline ModelView * modelView() { return mModelView; }
	inline ModelTree * modelTree() { return mModelTreeData; }

protected slots:
	void onSelectedItem(TreeItem*);
private:
	void setupUi();

private:
	ModelView * mModelView;
	ModelTree * mModelTreeData;
	QToolBar * mTaskBar;
	QAction * mActionNewCategory,
			* mActionNewGroup,
			* mActionNewMatrix,
			* mActionNewMatrixProblem,
			* mActionNewProblem;
};

} // eons

#endif // MODELEDITOR_H
