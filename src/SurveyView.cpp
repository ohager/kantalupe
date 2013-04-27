#include "SurveyView.h"
#include "global.h"

#include "WidgetExtension.h"
#include "Overlay.h"
#include "DragStartedEvent.h"
#include "TreeItemProtocol.h"
#include "SurveyTree.h"
#include "SurveyTreeDelegate.h"


#include "ReadPolicyXml.h"
#include "WritePolicyXml.h"
#include "WritePolicyQueXml.h"

#include "ShortMessage.h"

#include <QtGui>

START_NS


class WxListenerSurveyView : public WxListenerDefault{
public:
	bool isAcceptingMime(WidgetExtension * wx, const QMimeData * mime) const
	{
		// we make use of the qt's dnd support for model/view...
		// delegating the format request to the view's model
		SurveyView * widget= (SurveyView*)wx->widget();
		QStringList formats= mime->formats();
		foreach(const QString & format,formats )
		{
			if(widget->model()->mimeTypes().contains(format))
				return true;
		}
		return false;
	}

	void onDragStopped(WidgetExtension *wx, DragStoppedEvent *e)
	{
		SurveyView * surveyview = (SurveyView*)wx->widget();
		Q_ASSERT(surveyview);

		SurveyTreeDelegate * delegate = (SurveyTreeDelegate *)surveyview->itemDelegate();
		Q_ASSERT(delegate);


		// since, I had problems with the update for the delegate (artifacts)
		// and I could'nt convince the viewer to update even with repaint() (????)
		// I use this disable/enable-'trick'
		surveyview->setUpdatesEnabled(false);
		delegate->unmarkAllItemTypes();
		surveyview->setUpdatesEnabled(true);
	}

	void onDragStarted(WidgetExtension *wx, DragStartedEvent *e)
	{
		QDataStream data(e->mimeData()->data(mime::DndTreeItemType));

		int itype;
		data >> itype;
		tip::ItemType type = (tip::ItemType)itype;
		SurveyView * surveyview = (SurveyView*)wx->widget();
		// since, I had problems with the update for the delegate (artifacts)
		// and I could'nt convince the viewer to update even with repaint() (????)
		// I use this disable/enable-'trick'
		surveyview->setUpdatesEnabled(false);
		Q_ASSERT(surveyview);

		SurveyTreeDelegate * delegate = (SurveyTreeDelegate *)surveyview->itemDelegate();
		Q_ASSERT(delegate);

		//delegate->unmarkAllItemTypes();
		if(type == tip::ItemModel)
		{
			// nothing
			return;
		}
		else if(type == tip::ItemCategory)
		{
			delegate->markItemType(tip::ItemSurvey);
			delegate->markItemType(tip::ItemCategory);
		}
		else if(type == tip::ItemGroup)
		{
			delegate->markItemType(tip::ItemCategory);
		}
		else if(type == tip::ItemMatrix)
		{
			//delegate->markItemType(tip::ItemCategory);
			delegate->markItemType(tip::ItemGroup);
		}
		else if(type == tip::ItemMatrixProblem)
		{
			delegate->markItemType(tip::ItemMatrix);
		}
		else if(type == tip::ItemProblem)
		{
			//delegate->markItemType(tip::ItemCategory);
			delegate->markItemType(tip::ItemGroup);
		}

		WxListenerDefault::onDragStarted(wx,e);
		// small trick.. even repainting does not help on updateproblem with delegate
		surveyview->setUpdatesEnabled(true);
	}


};

// ---------------------------------------- END LISTENER IMPL ---------------------------------------

SurveyView::SurveyView(QWidget *parent) :
	TreeView(parent)
{
	setHeaderHidden(true);
	//header()->setResizeMode(QHeaderView::Stretch);
	setRootIsDecorated(false);
	setIndentation(0);
	setExpandsOnDoubleClick(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setSelectionMode( QAbstractItemView::SingleSelection );
	setSelectionBehavior( QAbstractItemView::SelectRows);
	setDragEnabled(false); // its false now... but may change for internal move!
	setDragDropMode(QAbstractItemView::DropOnly);
	setDropIndicatorShown(false); // we use our proprietary widget extension
	setAcceptDrops(true);

	setItemDelegate( new SurveyTreeDelegate() );

	WidgetExtension * wx = new WidgetExtension(this,
						WidgetExtension::AlwaysVisible |
						WidgetExtension::ShowDropIndicator);
	wx->setListener( new WxListenerSurveyView() );



	overlay()->setText(tr("Please add items"));
}


SurveyTree * SurveyView::surveyTree() { return (SurveyTree*)model(); }


void SurveyView::setModel(QAbstractItemModel *model){
	TreeView::setModel(model);
	connect(this->selectionModel(), SIGNAL(	selectionChanged(const QItemSelection &,const QItemSelection &)),
			this, SLOT(__selectionChanged(const QItemSelection &,const QItemSelection &)));


}



// ----------------------------------- SLOTS ---------------------------------------

void SurveyView::loadSurvey()
{
	/*
	QString filename = QFileDialog::getOpenFileName(this, tr("Load Survey"), QString("./surveys"),
			QString("%1 %2").arg(file::FilterXml).arg(file::FilterSurveyBinary), &selectedFilter );
	*/
	QString filename = QFileDialog::getOpenFileName(this, tr("Load Survey"), QString("./surveys"),
			tr( "Surveys (*.%1)" ).arg(file::SuffixXml));
	if(filename.isEmpty())
		return;

	if(filename.endsWith(file::SuffixXml))
	{
		QFile infile(filename);
		ReadPolicyXml policy;

		bool ok = surveyTree()->load(&infile, policy);
		emit loaded(ok);
		ShortMessage::showMessage(this,  ok ? tr("Survey loaded") : tr("Sorry, loading failed") );

	}
	else if(filename.endsWith(file::SuffixSurveyBinary))
	{
		qDebug("Survey Binary loading not implemented yet");
	}


}

void SurveyView::saveAsSurvey(){

	QString selectedFilter;
	/*
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Model as..."), QString("./surveys"),
			QString("%1 %2").arg(file::FilterXml).arg(file::FilterSurveyBinary), &selectedFilter );
	*/
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Model as..."), QString("./surveys"),
			file::FilterXml, &selectedFilter );
	if(filename.isEmpty())
		return;

	if(selectedFilter==file::FilterXml)
	{
		filename = filename.endsWith(file::SuffixXml) ? filename : filename.append(file::SuffixXml);
		QFile outfile(filename);
		WritePolicyXml policy;
		bool ok = surveyTree()->save(&outfile, policy);
		emit saved(ok);
		ShortMessage::showMessage(this, ok ? tr("Survey saved") : tr("Sorry, saving failed") );
	}
	else if(selectedFilter==file::FilterSurveyBinary) // not supported yet
	{
		filename = filename.endsWith(file::SuffixSurveyBinary) ? filename : filename.append(file::SuffixSurveyBinary);

		qDebug("Survey Binary saving not implemented yet");

	}


}




// -------------------------------- events ---------------------------------

void SurveyView::resizeEvent(QResizeEvent *)
{
	header()->resizeSection(0, width() );
}

void SurveyView::contextMenuEvent( QContextMenuEvent * event )
{
	QMenu menu;



	menu.addAction(tr("Load"), this, SLOT(loadSurvey()));
	menu.addAction(tr("Save as"), this, SLOT(saveAsSurvey()));
	menu.addSeparator();
	mClickedIndex = indexAt(event->pos());
	if(mClickedIndex.isValid())
	{

		menu.addAction(tr("Remove Item"), this, SLOT(onActionRemove()));
	}
	menu.addAction(tr("Clear Survey"), this, SLOT(onActionClear()));

	menu.exec( mapToGlobal(event->pos()));
}

/*
void SurveyView::dragMoveEvent(QDragMoveEvent * e)
{

}
*/

// ------------------------------------ slots ------------------------------------

void SurveyView::onActionRemove()
{
	surveyTree()->removeRow(mClickedIndex.row(), mClickedIndex.parent());
	// override default behaviour as we have our custum root item
	overlay()->setVisible( surveyTree()->rootItem()->rowCount()==0 );

}

void SurveyView::onActionClear(){

	if(QMessageBox::question(0x0, tr("Delete all survey items"), tr("Do you really want to delete all items?"),
						  tr("Delete"), tr("Cancel"))==0)
	{
		setUpdatesEnabled(false);
		surveyTree()->clear();
		surveyTree()->deleteLater();
		setModel( new SurveyTree() );
		setUpdatesEnabled(true);
	}
	else{
		ShortMessage::showMessage(this, tr("Action cancelled"), 1000);
	}
}

// ----------------------------------- privates ---------------------------------

void SurveyView::__clicked(QModelIndex index) // is private
{
	if(index.isValid())
	{
		TreeItem * item = surveyTree()->itemFromIndexAsTreeItem(index);
		emit entered(item);
	}
}

void SurveyView::__entered(QModelIndex index) // is private
{
	if(index.isValid())
	{
		TreeItem * item = surveyTree()->itemFromIndexAsTreeItem(index);
		emit entered(item);
	}
}

void SurveyView::__selectionChanged(const QItemSelection & s,const QItemSelection & d)
{
	Q_UNUSED(d)

	if(s.indexes().isEmpty())
		return;

	QModelIndex index = s.indexes().at(0); // single selection mode only
	if(index.isValid())
	{
		//setSelectedIndex(index);
		TreeItem * item =  surveyTree()->itemFromIndexAsTreeItem(index);
		emit entered(item);
	}
}

END_NS
