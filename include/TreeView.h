#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class QStandardItemModel;

namespace k{

class Overlay;
/**
  TreeView with extended features. This view is considered to be used with QStandardItemModel.
  @author O. Haeger
	*/
class TreeView : public QTreeView
{
    Q_OBJECT
public:

    explicit TreeView(QWidget *parent = 0);
	~TreeView();

	/**
	  Convenience method.
	  @param index The index for the item to be checked
	  @return @e true, if item for index is collapsed, otherwise @e false.
	  @see setItemCollapsed()
	  */
	static bool isItemCollapsed(const QModelIndex & index);
	static void setItemCollapsed(const QModelIndex & index, bool elapsed);

	// override
	void setModel(QAbstractItemModel *model);

	/**
	  Subclasses may use the overlay. Per default it is enabled, but
	  disables automatically on inserted items respectively appears if
	  underlying model holds any items.
	  */
	Overlay * overlay() const { return mOverlay; }

protected:
	void showEvent(QShowEvent *);
	void moveEvent(QMoveEvent *);
	void resizeEvent(QResizeEvent *);

private slots:
	void __rowsInserted(const QModelIndex & parent);
	void __rowsRemoved();
	void __expanded(QModelIndex);
	void __collapsed(QModelIndex);

private:
	Overlay * mOverlay;
};


} // eons

#endif // TREEVIEW_H
