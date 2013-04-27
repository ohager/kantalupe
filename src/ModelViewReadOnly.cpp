#include "ModelViewReadOnly.h"
#include "global.h"
#include "Overlay.h"
#include "ModelTree.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include "ReadPolicyXml.h"
#include "ReadPolicyBinary.h"
#include "ShortMessage.h"
#include "ModelTreeDelegate.h"
#include "VisitorNumberCategories.h"
#include "Drag.h"
#include "DragUtility.h"

#include <QtGui>

START_NS

ModelViewReadOnly::ModelViewReadOnly(QWidget * parent):
	TreeView(parent)
{
	setHeaderHidden(true);
	//header()->setResizeMode(QHeaderView::Stretch);
	setRootIsDecorated(false);
	setIndentation(0);
	setExpandsOnDoubleClick(true);
	setItemDelegateForColumn(0, new ModelTreeDelegate());
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	setSelectionMode( SingleSelection );
	setSelectionBehavior(SelectRows);
	// we disable the provided dnd features,
	// as we use a proprietary solution
	setDragDropMode(QAbstractItemView::DragDrop);
	setDragEnabled(true);
	setAcceptDrops(false);


	overlay()->setText(tr("Please load a model"));

	connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(__clicked(QModelIndex)));
}

void ModelViewReadOnly::setModel(QAbstractItemModel *model){
	TreeView::setModel(model);
	connect(this->selectionModel(), SIGNAL(	selectionChanged(const QItemSelection &,const QItemSelection &)),
			this, SLOT(__selectionChanged(const QItemSelection &,const QItemSelection &)));


}

ModelTree * ModelViewReadOnly::modelTree()
{
	return (ModelTree *)model();
}

// ---------------------------- events ---------------------
void ModelViewReadOnly::mouseMoveEvent(QMouseEvent *event)
{
	QModelIndex dragged = indexAt(event->pos());
	if(!dragged.isValid())
	{
		qDebug("ModelViewReadOnly: invalid index..");
		QTreeView::mouseMoveEvent(event);
		return;
	}

	// we implement our own drag shit here
	if( DragUtility::confirmDrag(event) )
	{
		qDebug("ModelViewReadOnly: mouse move event!");
		ModelTree *  mtd=modelTree();

		Q_ASSERT(mtd);

		// single selection only. so we care only for on index and delegate to model!
		QMimeData * mimedata = mtd->mimeData( QModelIndexList() << dragged );
		DragUtility::executeDrag(this, mimedata, Qt::CopyAction);
		event->accept();
	}

}

void ModelViewReadOnly::mousePressEvent(QMouseEvent *event)
{
	DragUtility::announceDrag(event);
	QTreeView::mousePressEvent(event);
}

void ModelViewReadOnly::resizeEvent(QResizeEvent *)
{

	header()->resizeSection(0, width() );

}

void ModelViewReadOnly::contextMenuEvent( QContextMenuEvent * event )
{
	//Q_ASSERT_X(modelTreeData(),"ModelViewReadOnly::contextMenuEvent", "Model is NULL");

	QMenu menu;
	menu.addAction(tr("Load"), this, SLOT(loadModel()));
	menu.exec( mapToGlobal(event->pos()));

}

// ----------------------------- slots ------------------------------

void ModelViewReadOnly::loadModel()
{
	QString selectedFilter;
	QString filename = QFileDialog::getOpenFileName(this, tr("Load Model"), QString("./models"),
			tr("Kantalupe Models(*.%1 *.%2").arg(file::SuffixXml).arg(file::SuffixModelBinary), &selectedFilter );
	if(filename.isEmpty())
		return;

	bool ok = false;
	if(filename.endsWith(file::SuffixXml))
	{
		QFile infile(filename);
		ReadPolicyXml policy;
		ok = modelTree()->load(&infile, policy);

	}
	else if(filename.endsWith( file::SuffixModelBinary) )
	{
		QFile infile(filename);
		ReadPolicyBinary policy;
		ok = modelTree()->load(&infile, policy );
	}

	ShortMessage::showMessage(this,  ok ? tr("Model loaded") : tr("Sorry, loading failed") );
}

void ModelViewReadOnly::__clicked(QModelIndex index) // is private
{
	if(index.isValid())
	{
		TreeItem * item = modelTree()->itemFromIndexAsTreeItem(index);
		emit entered(item);
	}
}

void ModelViewReadOnly::__entered(QModelIndex index) // is private
{
	if(index.isValid())
	{
		TreeItem * item = modelTree()->itemFromIndexAsTreeItem(index);
		emit entered(item);
	}
}

void ModelViewReadOnly::__selectionChanged(const QItemSelection & s,const QItemSelection & d)
{
	Q_UNUSED(d)

	if(s.indexes().isEmpty())
		return;

	QModelIndex index = s.indexes().at(0); // single selection mode only
	if(index.isValid())
	{
		setSelectedIndex(index);
		TreeItem * item =  modelTree()->itemFromIndexAsTreeItem(index);
		emit entered(item);
	}
}

END_NS

