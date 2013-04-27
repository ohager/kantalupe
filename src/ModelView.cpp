#include "ModelView.h"
#include "ModelTree.h"
#include "TreeItem.h"
#include "WritePolicyXml.h"
#include "WritePolicyBinary.h"
#include "VisitorNumberCategories.h"
#include "ShortMessage.h"
#include "Overlay.h"
#include "Drag.h"
#include <QtGui>

START_NS

ModelView::ModelView(QWidget * parent):
	ModelViewReadOnly(parent)
{
	overlay()->setText(tr("Right click on model item to add items"));

}



// ---------------------------- events ---------------------





void ModelView::contextMenuEvent( QContextMenuEvent * event )
{
	Q_ASSERT_X(modelTree(),"ModelView::contextMenuEvent", "Model is NULL");

	mClickedIndex = this->indexAt(event->pos());

	QMenu menu;
	tip::ItemType type = tip::ItemUnspecified;
	// item dependent click
	if(mClickedIndex.isValid())
	{
		//setSelectedIndex(index);
		TreeItem * item = modelTree()->itemFromIndexAsTreeItem(mClickedIndex);
		Q_ASSERT_X(item,"ModelView::contextMenuEvent","Item is NULL");
		type = item->getItemType();
		menu.addActions(getActionsByItemType(type,&menu));
		menu.addSeparator();
		menu.addAction(tr("Remove Item"), this, SLOT(onActionRemove()));


	}
	menu.addAction(tr("Clear Model"), this, SLOT(onActionClear()));
	menu.addSeparator();
	// general actoins
	menu.addAction(tr("Load"), this, SLOT(loadModel()));
	menu.addAction(tr("Save as..."), this, SLOT(saveAsModel()), QKeySequence::SaveAs);
	menu.exec( mapToGlobal(event->pos()));

}

// ----------------------------- slots ------------------------------

void ModelView::saveAsModel(){
	QString selectedFilter;
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Model as..."), QString("./models"),
			QString("%1;;%2").arg(file::FilterModelBinary).arg(file::FilterXml), &selectedFilter );
	if(filename.isEmpty())
		return;

	bool ok = false;
	if(selectedFilter==file::FilterXml)
	{
		filename = filename.endsWith(file::SuffixXml) ? filename : filename.append(file::SuffixXml);
		QFile outfile(filename);
		WritePolicyXml policy;
		ok = modelTree()->save(&outfile, policy);

	}
	else if(selectedFilter==file::FilterModelBinary)
	{
		filename = filename.endsWith(file::SuffixModelBinary) ? filename : filename.append(file::SuffixModelBinary);

		QFile outfile(filename);
		WritePolicyBinary policy;
		ok = modelTree()->save(&outfile, policy);


	}

	ShortMessage::showMessage(this, ok ? tr("Model saved") : tr("Sorry, saving failed") );


}


void ModelView::addNewModel()
{
	Model m;
	m.name = tr("New Model");
	m.uidMode = Model::UidManual;
	modelTree()->insertNewModel(m);
}

void ModelView::addNewCategory()
{
	Category c;
	c.description = tr("New category description");
	c.name = tr("New category name");
	modelTree()->insertNewCategory( c, selectedIndex() );

	// renumber all categories
	VisitorNumberCategories v;
	modelTree()->traverse(&v);
}

void ModelView::addNewGroup()
{

	Group g;
	g.description = tr("New group description");
	g.name = tr("New group name");
	modelTree()->insertNewGroup( g, selectedIndex() );
}


void ModelView::addNewMatrix()
{
	Matrix m;
	m.isMultipleChoice = false;
	m.name = tr("New matrix");
	m.text = tr("New matrix text");
	m.hint = tr("New matrix hint");

	modelTree()->insertNewMatrix( m, selectedIndex() );
}

void ModelView::addNewProblem()
{
	Problem p;
	p.uid = global::InvalidUid;
	p.text = tr("New problem text");
	modelTree()->insertNewProblem( p, selectedIndex() );
}

void ModelView::addNewMatrixProblem()
{
	MatrixProblem p;
	p.uid = global::InvalidUid;
	p.text = tr("New matrix problem text");
	modelTree()->insertNewMatrixProblem( p, selectedIndex() );
}
// ------------------------------ slots --------------------------------

void ModelView::onActionRemove()
{
	modelTree()->removeRow(mClickedIndex.row(), mClickedIndex.parent());
	// override default behaviour as we have our custum root item
	overlay()->setVisible( modelTree()->rootItem()->rowCount()==0 );
}

void ModelView::onActionClear(){

	if(QMessageBox::question(0x0, tr("Delete all model items"), tr("Do you really want to delete all items?"),
						  tr("Delete"), tr("Cancel"))==0)
	{
		setUpdatesEnabled(false);
		modelTree()->clear();
		modelTree()->deleteLater();
		setModel( new ModelTree() );
		setUpdatesEnabled(true);
	}
	else{
		ShortMessage::showMessage(this, tr("Action cancelled"), 1000);
	}
}


// ----------------------------- private ------------------------------



types::Actions ModelView::getActionsByItemType(tip::ItemType type, QObject * parent) const
{
	types::Actions actions;
	if(type == tip::ItemModel)
	{
		QAction * newcat = new QAction( tr("Add Category"), parent );
		connect(newcat, SIGNAL(triggered()), this, SLOT(addNewCategory()));
		actions << newcat;
	}
	else if(type == tip::ItemCategory)
	{
		QAction * newcat = new QAction( tr("Add Category"), parent );
		connect(newcat, SIGNAL(triggered()), this, SLOT(addNewCategory()));

		QAction * newgroup = new QAction( tr("Add Group"), parent );
		connect(newgroup, SIGNAL(triggered()), this, SLOT(addNewGroup()));

		QAction * newmatrix = new QAction( tr("Add Matrix"), parent );
		connect(newmatrix, SIGNAL(triggered()), this, SLOT(addNewMatrix()));

		QAction * newprob= new QAction( tr("Add Problem"), parent );
		connect(newprob, SIGNAL(triggered()), this, SLOT(addNewProblem()));

		actions << newcat << newgroup << newmatrix << newprob;
	}
	else if(type == tip::ItemGroup)
	{
		QAction * newprob= new QAction( tr("Add Problem"), parent );
		connect(newprob, SIGNAL(triggered()), this, SLOT(addNewProblem()));

		actions << newprob;

	}
	else if(type == tip::ItemMatrix)
	{
		QAction * newprob= new QAction( tr("Add Problem"), parent );
		connect(newprob, SIGNAL(triggered()), this, SLOT(addNewMatrixProblem()));

		actions << newprob;

	}
	else if(type == tip::ItemUnspecified)
	{
		qDebug("Unspecified Item: Nothing implemented yet!");
	}
	return actions;
}

END_NS

