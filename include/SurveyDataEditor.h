#ifndef SurveyEditor_H
#define SurveyEditor_H

#include <QWidget>
#include "WidgetExtension.h"

class QListWidget;
class QListWidgetItem;
class QStackedWidget;

namespace k{

class TreeItem;
class SurveyTree;

/**
	The page-based data editor with for a survey.
	@author O. Haeger
  */
class SurveyDataEditor : public QWidget//, private k::WidgetExtension
{
	Q_OBJECT
signals:
	/**
	  Emitted whenever a survey was generated automatically
	  */
	void surveyGenerated(SurveyTree*);
public:

	SurveyDataEditor(QWidget * parent=0x0);

	void setScriptEditorVisible(bool visible);

public slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);

	/**
	  Opens the editor.
	  @param item The selected item from survey view
	  */
	void openEditor(TreeItem * item);
	void commit();

protected:
	void updateEditor(TreeItem * item);
	void setupUi();

private:

	void createItems();

	QListWidget *mContentsWidget;
	QStackedWidget *mPagesWidget;

	QListWidgetItem * mButtonModel,
					* mButtonMeta,
					* mButtonGenerator,
					* mButtonScript;

	int mPageModel,
		mPageMeta,
		mPageGenerator,
		mPageScript;
};

} // eons

#endif // SurveyEditor_H
