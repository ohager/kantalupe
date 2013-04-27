#ifndef SurveyExporter_H
#define SurveyExporter_H

#include "AbstractEditor.h"
class QToolBar;

namespace k {

class SurveyTree;
class SurveyView;
class SurveyExportSelector;

class SurveyExporter : public QWidget
{
    Q_OBJECT
public:
	SurveyExporter(SurveyExportSelector * exportselector, QWidget *parent = 0);
	inline SurveyView * surveyView() { return mSurveyView; }
	SurveyTree * surveyTree();
	SurveyExportSelector * exportSelector() { return _exportSelector; }

public slots:
	void setSurveyTree(SurveyTree *);

protected slots:
	void doExport();

private:
	void setupUi();


private:
	SurveyView * mSurveyView;
	SurveyExportSelector * _exportSelector;
	QToolBar * mTaskBar;
	QAction * mActionExport;
};

} /// eons

#endif // SurveyExporter_H
