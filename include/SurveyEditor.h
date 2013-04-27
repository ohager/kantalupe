#ifndef SURVEYEDITOR_H
#define SURVEYEDITOR_H

#include <QWidget>

class QToolBar;

namespace k{

class SurveyView;
class SurveyTree;
class TreeItem;

class SurveyEditor : public QWidget
{
    Q_OBJECT
signals:
	void clickedItem(TreeItem *);
	void selectedItem(TreeItem*);

public:
	explicit SurveyEditor(QWidget *parent = 0);

	inline SurveyView * surveyView() { return mSurveyView; }
	SurveyTree * surveyTree();

public slots:
	void setSurveyTree(SurveyTree *);
protected slots:
	void onSelectedItem(TreeItem*);

private:
	void setupUi();

private:
	SurveyView * mSurveyView;
	QToolBar * mTaskBar;
	/*
	QAction * mActionNewCategory,
			* mActionNewGroup,
			* mActionNewMatrix,
			* mActionNewMatrixProblem,
			* mActionNewProblem;
	*/
};

}// eons
#endif // SURVEYEDITOR_H
