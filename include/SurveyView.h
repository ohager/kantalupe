#ifndef SURVEYVIEW_H
#define SURVEYVIEW_H

#include "TreeView.h"

namespace k{

class SurveyTree;
class TreeItem;

/**
  The view for SurveyTree instances.
  */
class SurveyView : public TreeView
{
    Q_OBJECT
signals:
	void entered(TreeItem *);
	void loaded(bool ok);
	void saved(bool ok);
public:
	explicit SurveyView(QWidget *parent = 0);

	SurveyTree * surveyTree();
	void setModel(QAbstractItemModel *model);
public slots:
	void loadSurvey();
	void saveAsSurvey();
protected:
	void contextMenuEvent( QContextMenuEvent * event );
	void resizeEvent(QResizeEvent *);
	//void dragEnterEvent(QDragEnterEvent *event);
	/*
	void dragMoveEvent(QDragMoveEvent * e);
	void dropEvent(QDropEvent *event);
	*/
protected slots:
	void __clicked(QModelIndex);
	void __entered(QModelIndex);
	void __selectionChanged(const QItemSelection &,const QItemSelection &);

	void onActionRemove();
	void onActionClear();
private:
	QModelIndex mClickedIndex;
};

} // eons
#endif // SURVEYVIEW_H
