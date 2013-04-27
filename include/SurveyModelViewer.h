#ifndef SURVEYMODELVIEWER_H
#define SURVEYMODELVIEWER_H


#include <QWidget>


class QToolBar;


namespace k{

class ModelViewReadOnly;
class ModelTree;
class TreeItem;

class SurveyModelViewer: public QWidget
{
    Q_OBJECT
signals:
	void clickedItem(TreeItem *);
	void selectedItem(TreeItem*);

public:
	explicit SurveyModelViewer(QWidget *parent = 0);

	inline ModelViewReadOnly * modelView() { return mModelView; }
	inline ModelTree * modelTreeData() { return mModelTreeData; }

protected slots:
	void onSelectedItem(TreeItem*);
private:
	void setupUi();

private:
	ModelViewReadOnly * mModelView;
	ModelTree * mModelTreeData;
};

} // eons

#endif // MODELEDITOR_H
