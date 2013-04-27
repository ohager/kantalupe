#include "ProposalTreeWidget.h"
#include "global.h"
#include "Overlay.h"


#include <QtGui>

START_NS

ProposalTreeWidget::ProposalTreeWidget(QWidget * p)
	: QTreeWidget(p),
	mOverlay(new Overlay(this)),
	  mAddRemoveEnabled(false),
	  mSolutionSelectionMultiple(true)
	//mSolutionDelegate(new SolutionCheckDelegate(this) )
{
	setDragEnabled(true);
	setDragDropMode(InternalMove);
	viewport()->setAcceptDrops(true);
	setDropIndicatorShown(true);
	setSelectionMode(SingleSelection);
	setEditTriggers(AllEditTriggers);
	// maintain order accordingly to ColumnId, ColumnProposalText, etc.
	setHeaderLabels( QStringList() << tr("Id") << tr("Text") << tr("Solution") );
	setRootIsDecorated(false);
	setWordWrap(true);
	overlay()->setText( tr("Right click to add new proposal") );


	connect(this, SIGNAL(itemSelectionChanged()),this, SLOT(onSelectionChange()));
	connect(this, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(onItemChange(QTreeWidgetItem*,int)));
	connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onClicked(QTreeWidgetItem*,int)));

}

void ProposalTreeWidget::addProposalItem(const Proposal &proposal, bool solution)
{

	QTreeWidgetItem * item = new QTreeWidgetItem();
	item->setFlags(  Qt::ItemIsEnabled | Qt::ItemIsSelectable  );
	addTopLevelItem(item);

	item->setText(ColumnProposalText, proposal.text);
	//item->setText(ColumnId, proposal.id); will be reset by renumber()

	setItemSolution(item, solution);

	renumber(); // resets id
	resizeColumnToContents(ColumnId);
	overlay()->hide();
}

void ProposalTreeWidget::newProposalItem()
{
	Proposal p;
	p.text = tr("New proposal");

	addProposalItem(p, false);

}



types::Proposals ProposalTreeWidget::getProposals() const
{
	types::Proposals props;
	for(int i=0; i< topLevelItemCount(); ++i)
	{
		QTreeWidgetItem * item = topLevelItem(i);
		Proposal p;

		p.id = item->text(ColumnId);
		p.text = item->text(ColumnProposalText);
		props << p;
	}

	return props;
}

types::Solutions ProposalTreeWidget::getSolutions() const
{
	types::Solutions sols;
	for(int i=0; i< topLevelItemCount(); ++i)
	{
		QTreeWidgetItem * item = topLevelItem(i);
		if(itemIsSolution(item)){
			sols << item->text(ColumnId);
		}
	}

	return sols;
}


bool ProposalTreeWidget::isProposalSolution(const Proposal & p) const
{
	for(int i=0; i< topLevelItemCount(); ++i)
	{
		QTreeWidgetItem * item = topLevelItem(i);
		if(item->text(ColumnId)==p.id){
			return itemIsSolution(item);
		}
	}
	return false;
}

Proposal ProposalTreeWidget::getProposalData(int row) const
{
	QTreeWidgetItem * item = itemFromRow(row);
	Q_ASSERT(item);
	Proposal p;

	p.id = item->text(ColumnId);
	p.text = item->text(ColumnProposalText);
	//p.solution = itemIsSolution(item);

	return p;
}

/*
void ProposalTreeWidget::incept(const types::ProposalData & src,QTreeWidgetItem * dest) const
{
	Q_ASSERT(dest);

	dest->setText(ColumnProposalText, src.text);
	dest->setText(ColumnId, src.id);

	setItemSolution(dest, src.solution);
}

void ProposalTreeWidget::extract(const QTreeWidgetItem * src, types::ProposalData & dest) const
{
	 Q_ASSERT(src);

	 dest.id = src->text(ColumnId);
	 dest.text = src->text(ColumnProposalText);
	 dest.solution = itemIsSolution(src);

}
*/

int ProposalTreeWidget::selectedRow() const
{
	QModelIndex index = selectedIndexes().first();
	return index.isValid() ?  index.row() : -1;

}

QModelIndex ProposalTreeWidget::indexFromRow(int r) const
{
	return model()->index(r, 0);
}

QTreeWidgetItem * ProposalTreeWidget::itemFromRow(int r) const
{
	return itemFromIndex( indexFromRow(r) );
}

void ProposalTreeWidget::setProposalItemText(int row, const QString & text)
{
	QTreeWidgetItem * item = itemFromRow(row);
	Q_ASSERT(item);
	item->setText(ColumnProposalText, text);
}


bool ProposalTreeWidget::itemIsSolution(QTreeWidgetItem * item) const
{
	Q_ASSERT(item);
	return item->data(ColumnSolutionCheck, SolutionCheckRole).toBool();
}

void ProposalTreeWidget::clearSolutionSelection(){
	QString icon(  global::R.getValue("icon/false")	);

	QPixmap pix;
	if(!QPixmapCache::find(icon,&pix) )
	{
		pix = QPixmap(icon).scaled( QSize(24,24),  Qt::KeepAspectRatio,  Qt::SmoothTransformation);
		QPixmapCache::insert(icon, pix);
	}

	// set all others to false, iff not empty
	for(int i=0; i<topLevelItemCount(); ++i)
	{
		QTreeWidgetItem * child = topLevelItem(i);
		child->setIcon(ColumnSolutionCheck, QIcon(pix));
		child->setData(ColumnSolutionCheck, SolutionCheckRole, false);
	}
}

void ProposalTreeWidget::setItemSolution(QTreeWidgetItem * item, bool solution){

	Q_ASSERT(item);


	if(!isSolutionSelectionMultiple() && solution)
	{
		clearSolutionSelection();
	}

	QString icon( solution ?
				  global::R.getValue("icon/correct") :
				  global::R.getValue("icon/false")	  );

	QPixmap pix;
	if(!QPixmapCache::find(icon,&pix) )
	{
		pix = QPixmap(icon).scaled( QSize(24,24),  Qt::KeepAspectRatio,  Qt::SmoothTransformation);
		QPixmapCache::insert(icon, pix);
	}
	item->setIcon(ColumnSolutionCheck, QIcon(pix));
	item->setData(ColumnSolutionCheck, SolutionCheckRole, solution);

}
// ------------------------- SLOTS --------------------------------
void ProposalTreeWidget::onClicked(QTreeWidgetItem * item ,int column)
{
	Q_ASSERT(item);
	if(column == ColumnSolutionCheck)
	{
		// toggle Solution
		setItemSolution( item, !itemIsSolution(item) );
	}
}

void ProposalTreeWidget::renumber()
{
	int nitems = topLevelItemCount();
	for(int r=0; r<nitems; ++r){	QTreeWidgetItem * item = topLevelItem(r);
		item->setText(ColumnId, QString::number(r+1) );
	}
}


void ProposalTreeWidget::onActionClear()
{
	clear();
	overlay()->show();

}

void ProposalTreeWidget::onActionRemove()
{

	Q_ASSERT_X(mClickedIndex.isValid(), "ProposalTreeWidget::onActionRemove","Invalid model index");

	model()->removeRow( mClickedIndex.row() );
	overlay()->setVisible( model()->rowCount()==0 );
	renumber();
}


void ProposalTreeWidget::onSelectionChange()
{
	emit rowSelected( selectedRow() );
}

void ProposalTreeWidget::onItemChange(QTreeWidgetItem * item, int column)
{
	/*
	if(column == ColumnSolutionCheck)
	{
		int r = indexFromItem(item).row();
		emit solutionCheckToggled( r, itemIsSolution( r ) );
	}
	*/
}

// ------------------------- EVENTS ------------------------------
void ProposalTreeWidget::showEvent(QShowEvent *)
{
	overlay()->center();
}

void ProposalTreeWidget::resizeEvent(QResizeEvent *)
{
	overlay()->center();
}

void ProposalTreeWidget::moveEvent(QMoveEvent *)
{
	overlay()->center();
}



void ProposalTreeWidget::contextMenuEvent(QContextMenuEvent * e)
{
	mClickedIndex = indexAt( e->pos() );

	if(!isAddRemoveEnabled())
		return;

	QMenu menu(this);
	menu.addAction(tr("Add Proposal"), this, SLOT(newProposalItem()));
	if(model()->rowCount())
	{
		menu.addAction(tr("Clear"), this, SLOT(onActionClear()));
	}

	if(mClickedIndex.isValid())
	{
		menu.addAction(tr("Remove"), this, SLOT(onActionRemove()));
	}

	menu.raise(); // cover overlay
	menu.exec( mapToGlobal(e->pos()) );

}

END_NS
