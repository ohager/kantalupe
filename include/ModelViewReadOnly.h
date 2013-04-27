#ifndef MODELVIEWREADONLY_H
#define MODELVIEWREADONLY_H

#include "TreeView.h"
#include "global.h"

namespace k{

class Overlay;
class ModelTree;
class TreeItem;

/**
  The read only model view. The model view does not support
  any (ui-based) editing capabilities. To provide a model view
  with editing capabilities use ModelView instead.
  @author Oliver Haeger
  */
class ModelViewReadOnly : public TreeView{

	Q_OBJECT
signals:
	void entered(TreeItem *);
public:
	ModelViewReadOnly(QWidget * parent=0);
	void setModel(QAbstractItemModel *model);
	ModelTree * modelTree();
	const QModelIndex & selectedIndex() const { return mSelectedIndex; }
public slots:
	void loadModel();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void contextMenuEvent( QContextMenuEvent * event );
	void resizeEvent(QResizeEvent *);

protected slots:
	void  setSelectedIndex(const QModelIndex & index) { mSelectedIndex = index; }

private slots:
	void __clicked(QModelIndex);
	void __entered(QModelIndex);
	void __selectionChanged(const QItemSelection &,const QItemSelection &);
private:
	QModelIndex mSelectedIndex;
	QPoint mStartDragPosition;
};


} //eons

#endif // MODELVIEW_H
