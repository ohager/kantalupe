#include "SurveyTree.h"
#include "global.h"
#include "ItemTypeCombination.h"
#include "ReadPolicyXml.h"

#include <QMimeData>
#include <QBuffer>

START_NS


// --------------------------------------------------------------

SurveyTree::SurveyTree(QObject * parent) :
	AbstractTreeModel(parent)
{
	Survey s;
	s.name = tr("New survey");
	s.texts.welcome = tr("<Enter Welcome Text for this survey here>");
	s.texts.remind = tr("<Enter Reminder Text for this survey here>");
	s.texts.thank = tr("<Enter Note of Thank for this survey here>");
	s.affiliation.email = tr("<Enter Author's email>");
	s.affiliation.firstname= tr("<Enter Author's First Name>");
	s.affiliation.lastname= tr("<Enter Author's Last Name>");
	s.affiliation.telephone= tr("<Enter Author's Phone number>");

	insertNewSurvey(s);
}

SurveyTree::~SurveyTree()
{
	qDebug("SurveyTree deleted...");
}


// ------------------ interface implementation ----------------------

QStandardItem * SurveyTree::insertNewCategory(const Category & c, const QModelIndex & index)
{

	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(c);
	parent->appendRow(item);
	return item;

}

QStandardItem * SurveyTree::insertNewGroup(const Group & g, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert( index); // assert'd

	TreeItem * item = mItemFactory.createItem(g);
	parent->appendRow(item);
	return item;
}

QStandardItem * SurveyTree::insertNewMatrix(const Matrix & m, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(m);
	parent->appendRow(item);
	return item;
}


QStandardItem * SurveyTree::insertNewMatrixProblem(const MatrixProblem & m, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(m);
	parent->appendRow(item);
	return item;
}

QStandardItem * SurveyTree::insertNewProblem(const Problem & p, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(p);
	parent->appendRow(item);

	return item;
}

QStandardItem * SurveyTree::insertNewModel(const Model & m)
{
	Q_ASSERT_X(false,"SurveyTree::insertNewModel", "Method not supported by this class");
	return 0x0;
}

QStandardItem * SurveyTree::insertNewSurvey(const Survey & s)
{
  // todo
	QStandardItem * parent= invisibleRootItem();

	TreeItem * item = mItemFactory.createItem(s);
	parent->appendRow(item);
	return item;
}


// --------------------------- Interface implementation end  -----------------------------------

QStringList SurveyTree::mimeTypes() const
{
	return QStringList() << mime::DndTreeItem << mime::DndTreeItemType;
}

Qt::DropActions SurveyTree::supportedDropActions() const
{
	return Qt::CopyAction;
}

bool SurveyTree::dropMimeData(const QMimeData *mime, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{

	if(action == Qt::CopyAction)
	{
		/*
		  Note: QTreeView supports drops BETWEEN two items.
			In that case the row is set to the future's item, which must be considered.
			Currently, we do not support inbetween drops (for easiness), but append siblings to the end
		  */

		TreeItem * parentitem = itemFromIndexAsTreeItem(parent),
					* targetitem =0x0;
		if(parentitem ) // check inbetween drops
		{

			if(parentitem->rowCount() == row && row!=0)
			{
				qDebug("Inbetween drop");
				--row;
			}

			targetitem = (TreeItem*)parentitem->child(row,0);

		}
		else
		{
			qDebug("Invalid parent...adding to root");
			targetitem = rootItem();
		}

		Q_ASSERT(targetitem!=0x0);
		QDataStream data(mime->data(mime::DndTreeItemType));
		int itype;
		data >> itype;
		/*
		TreeItem * targetitem = itemFromIndexAsTreeItem(target);
		Q_ASSERT_X(targetitem, "SurveyTree::dropMimeData", "Target Item is NULL");
		*/
		tip::ItemType sourcetype = (tip::ItemType)itype;
		tip::ItemType targettype = targetitem->getItemType();

		if(AllowedItemTypeCombinations().accept(sourcetype,targettype))
		{
			ReadPolicyXml reader;
			QByteArray xml(qUncompress(mime->data(mime::DndTreeItem)));
			QBuffer iodev(&xml);
			return reader.read(&iodev, this, targetitem->index());
		}
	}
	return false;
}



END_NS

