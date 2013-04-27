#include "PropertyEditWidget.h"
#include "Overlay.h"
#include "global.h"
#include <QtGui>

START_NS

PropertyEditWidget::PropertyEditWidget(QWidget * parent)
	: QTreeWidget(parent),
	mOverlay(new Overlay(this))
{
	setupUi();

}

void PropertyEditWidget::setupUi()
{
	setDragDropMode(QAbstractItemView::NoDragDrop);
	setEditTriggers(QAbstractItemView::DoubleClicked);
	// maintain order according to enum{Key, Value, Description}
	setHeaderLabels( QStringList() << tr("Property") << tr("Value") << tr("Description"));
	overlay()->setText( tr("Right click to add property") );

}


void PropertyEditWidget::addProperty(const Property & p)
{
	addTopLevelItem( createItem(p) );
	overlay()->hide();
}

types::Properties PropertyEditWidget::getProperties() const
{
	types::Properties props;

	const int nitems = topLevelItemCount();
	for(int i = 0; i< nitems; ++i)
	{
		QTreeWidgetItem * item = topLevelItem(i);
		Property p;
		p.key = item->text(Key);
		p.value = item->text(Value);
		p.description = item->text(Description);
		props.insert(p.key, p);

	}
	return props;
}

// --------------------------- EVENTS -------------------------------


void PropertyEditWidget::contextMenuEvent(QContextMenuEvent * e)
{

	mClickedIndex = indexAt( e->pos() );
	QMenu menu(this);
	menu.addAction(tr("Add Property"), this, SLOT(onActionAddProperty()));
	if(topLevelItemCount())
	{
		menu.addAction(tr("Clear"), this, SLOT(onActionClear()));
	}

	if(mClickedIndex.isValid())
	{
		menu.addAction(tr("Edit"), this, SLOT(onActionEditProperty()));
		menu.addAction(tr("Remove"), this, SLOT(onActionRemoveProperty()));
	}

	menu.raise(); // cover overlay
	menu.exec( mapToGlobal(e->pos()) );
}

void PropertyEditWidget::showEvent(QShowEvent *)
{
	overlay()->center();
}

void PropertyEditWidget::resizeEvent(QResizeEvent *)
{
	overlay()->center();
}

void PropertyEditWidget::moveEvent(QMoveEvent *)
{
	overlay()->center();
}




// ------------------------------ SLOTS ------------------------------------------

void PropertyEditWidget::onActionAddProperty()
{
	Property p;
	p.key = tr("<Double click to edit>");
	p.value =	p.key;
	p.description =  p.key;
	addProperty(p);
}

void PropertyEditWidget::onActionEditProperty()
{
	Q_ASSERT_X(mClickedIndex.isValid(), "PropertyEditWidget::onActionEditProperty()" ,"Invalid model index");

	QTreeWidgetItem * item = itemFromIndex(mClickedIndex);
	editItem(item, mClickedIndex.column());

}

void PropertyEditWidget::onActionRemoveProperty()
{
	Q_ASSERT_X(mClickedIndex.isValid(), "PropertyEditWidget::onActionRemoveProperty()" ,"Invalid model index");

	model()->removeRow( mClickedIndex.row() );
	overlay()->setVisible( model()->rowCount()==0 );
}

void PropertyEditWidget::onActionClear()
{
	clear();
	mOverlay->show();
}


// ------------------------------------- PRIVATES --------------------------------------
QTreeWidgetItem * PropertyEditWidget::createItem(const Property & p)
{
	QTreeWidgetItem * item = new QTreeWidgetItem();

	item->setFlags( Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
	item->setText(Key, p.key );
	item->setText(Value, p.value );
	item->setText(Description, p.description );


	return item;
}


END_NS
