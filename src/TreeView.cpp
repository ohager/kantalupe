#include "TreeView.h"
#include <QStandardItemModel>
#include <QHeaderView>
#include "TreeItemProtocol.h"
#include "global.h"

#include "Overlay.h"



START_NS


TreeView::TreeView(QWidget *parent) :
	QTreeView(parent),
	mOverlay(new Overlay(this))
{
	mOverlay->setText(tr("Set a model"));
	mOverlay->show();
	connect(this, SIGNAL(expanded(QModelIndex)), this, SLOT(__expanded(QModelIndex)));
	connect(this, SIGNAL(collapsed(QModelIndex)), this, SLOT(__collapsed(QModelIndex)));

}

TreeView::~TreeView()
{
	mOverlay->deleteLater();
}

bool TreeView::isItemCollapsed(const QModelIndex & index) //static
{
	Q_ASSERT(index.isValid());

	QStandardItem * item = ((QStandardItemModel*)index.model())->itemFromIndex(index);
	return item->data(tip::MetaRoleCollapsed).toBool();
}


void TreeView::setItemCollapsed(const QModelIndex & index, bool elapsed) //static
{
	Q_ASSERT(index.isValid());

	QStandardItem * item = ((QStandardItemModel*)index.model())->itemFromIndex(index);
	return item->setData(elapsed, tip::MetaRoleCollapsed);
}

void TreeView::setModel(QAbstractItemModel *model){
	QTreeView::setModel(model);
	connect(model, SIGNAL(rowsInserted(const QModelIndex&, int,int)), this, SLOT(__rowsInserted(QModelIndex)));
	connect(model, SIGNAL(rowsRemoved(const QModelIndex&, int,int)), this, SLOT(__rowsRemoved()));
}

// ------------------------------- events -----------------------------------------------

void TreeView::showEvent(QShowEvent *)
{
	overlay()->center();
}

void TreeView::resizeEvent(QResizeEvent *)
{
	overlay()->center();

}

void TreeView::moveEvent(QMoveEvent *)
{
	overlay()->center();
}

// ------------------------- private signals -----------------------



void TreeView::__rowsInserted(const QModelIndex & parent){
	overlay()->hide();
	expand(parent);
}

void TreeView::__rowsRemoved(){
	overlay()->setVisible( model()->rowCount()==0);
}



void TreeView::__collapsed(QModelIndex index)
{
	setItemCollapsed(index, true);
}

void TreeView::__expanded(QModelIndex index)
{
	setItemCollapsed(index, false);
}




END_NS

