#include "GeneratorScriptView.h"
#include "global.h"

#include <QtGui>

START_NS

GeneratorScriptView::GeneratorScriptView(QWidget * parent )
	: TreeView(parent), mSelectedItem(0x0)
{

	setSelectionMode( QAbstractItemView::SingleSelection );
	setAlternatingRowColors(true);
}


void GeneratorScriptView::addScripts(const types::ScriptList & scriptlist)
{
	if(model())
	{
		model()->deleteLater();
	}

	QStandardItemModel * model = new QStandardItemModel();
	QStringList headerlabels;
	headerlabels << tr("Name") << tr("Last Edited") << tr("API Level");
	model->setHorizontalHeaderLabels(headerlabels);

	foreach(const Script & script, scriptlist)
	{
		QList<QStandardItem*> row;
		QStandardItem * name = new QStandardItem(script.name);
		QStandardItem * edited = new QStandardItem(script.lastEdited.toString(global::DateFormat));
		QStandardItem * apilevel = new QStandardItem(QString::number(script.apilevel));


		name->setData(script.author, RoleAuthor);
		name->setData(script.description, RoleDescription);
		name->setData(script.program, RoleProgram);
		name->setData(script.version, RoleVersion);

		row << name << edited << apilevel;
		model->appendRow(row);
	}

	model->sort(0);


	setUpdatesEnabled(false);
	setModel(model);
	connect(selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
			this, SLOT(onSelectedItem(QItemSelection,QItemSelection)));
	expandAll();
	setUpdatesEnabled(true);

	resizeColumnToContents(2);
	resizeColumnToContents(1);
}


QString GeneratorScriptView::getDataOfSelectedItem(DataRoles role) const
{
	static int 	ColumnName = 0,
				ColumnLastEdited = 1,
				ColumnApiLevel = 2;

	if(!mSelectedItem)
		return QString();

	QStandardItem * i = mSelectedItem;

	switch(role)
	{
	case RoleAuthor:
	case RoleDescription:
	case RoleProgram:
	case RoleVersion:
		return i->data(role).toString();
	case RoleName:
		return getTopLevelItem(i->row(), ColumnName)->text();
	case RoleApiLevel:
		return getTopLevelItem(i->row(), ColumnApiLevel)->text();
	case RoleLastEdited:
		return getTopLevelItem(i->row(), ColumnLastEdited)->text();
	default:
		return QString();
	}

}

QStandardItem * GeneratorScriptView::getTopLevelItem(int row, int column) const
{

	QStandardItemModel * smodel = (QStandardItemModel*)model();
	return smodel->invisibleRootItem()->child(row, column);
}

// ---------------------------------- SLOTS -----------------------------------
void GeneratorScriptView::onSelectedItem(QItemSelection selected,QItemSelection deselected)
{
	Q_UNUSED(deselected);
	mSelectedItem = 0x0;
	if(selected.isEmpty())
		return;
	int srow = selected.indexes().at(0).row(); // single selection only
	QStandardItem * item  = getTopLevelItem(srow, 0);
	if(item)
	{
		mSelectedItem = item;
		emit itemSelected(item);
	}

}


void GeneratorScriptView::onRunSelectedScript()
{
	Q_ASSERT(mSelectedItem);
	emit scriptActivated(getDataOfSelectedItem(RoleProgram));
}

// -------------------------------- events ----------------------------

void GeneratorScriptView::resizeEvent(QResizeEvent *)
{
	int cw = columnWidth(2) + columnWidth(1);
	setColumnWidth(0, width() - cw - 2);
}


void GeneratorScriptView::contextMenuEvent(QContextMenuEvent * e)
{
	QModelIndex index = indexAt(e->pos());

	if(!index.isValid())
		return;

	mSelectedItem = getTopLevelItem(index.row(),0);
	if(mSelectedItem)
	{
		QMenu menu;
		menu.addAction(tr("Run Script"),this,SLOT(onRunSelectedScript()));
		menu.exec(mapToGlobal(e->pos()));
	}

	e->accept();
}

void GeneratorScriptView::mouseDoubleClickEvent(QMouseEvent * e)
{
	QModelIndex index = indexAt(e->pos());
	if(!index.isValid())
		return;

	mSelectedItem = getTopLevelItem(index.row(),0);
	if(mSelectedItem)
	{
		onRunSelectedScript();
	}
	e->accept();
}

END_NS
