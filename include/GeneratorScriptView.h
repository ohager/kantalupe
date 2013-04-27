#ifndef GENERATORSCRIPTVIEW_H
#define GENERATORSCRIPTVIEW_H

#include "TreeView.h"
#include "Script.h"

class QStandardItem;

namespace k{



class GeneratorScriptView : public TreeView
{
	Q_OBJECT
signals:
	void itemSelected(QStandardItem *);
	void scriptActivated(const QString &);
public:
	enum DataRoles{
		RoleAuthor = Qt::UserRole,
		RoleDescription,
		RoleProgram,
		RoleVersion,
		RoleApiLevel,
		RoleName,
		RoleLastEdited
	};

	GeneratorScriptView(QWidget * parent);
	void addScripts(const types::ScriptList & scriptlist);

	QStandardItem * selectedItem() const { return mSelectedItem; }

	/**
	  @return The data field from recently selected item, or empty string iff no item is selected.
	  */
	QString getDataOfSelectedItem(DataRoles d) const;

protected:
	void resizeEvent(QResizeEvent *);
	void contextMenuEvent(QContextMenuEvent *);
	void mouseDoubleClickEvent(QMouseEvent *event);
	QStandardItem * getTopLevelItem(int row, int column) const;
protected slots:
	void onSelectedItem(QItemSelection selected,QItemSelection deselected);
	void onRunSelectedScript();
private:
	QStandardItem * mSelectedItem;

};

} // eons

#endif // GENERATORSCRIPTVIEW_H
