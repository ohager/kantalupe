#include "ModelTree.h"
#include "TreeItem.h"

#include "VisitorNumberCategories.h"

#include "global.h"
#include "ProtocolTypes.h"

#include "WritePolicyXml.h"

#include <QStandardItem>
#include <QBuffer>
#include <QMimeData>

START_NS

ModelTree::ModelTree(QObject *parent) :
	AbstractTreeModel(parent)
{
//	connect(this, SIGNAL(itemChanged(QStandardItem*)), this , SLOT(__itemChanged(QStandardItem*)));

	Model m;
	m.name=tr("New model");
	m.uidMode= Model::UidManual;
	insertNewModel(m);

}

ModelTree::~ModelTree()
{
}


// ------------------ interface implementation ----------------------

QStandardItem * ModelTree::insertNewModel(const Model & m)
{

	QStandardItem * parent= invisibleRootItem();

	TreeItem * item = mItemFactory.createItem(m);
	parent->appendRow(item);
	return item;

}


QStandardItem * ModelTree::insertNewCategory(const Category & c, const QModelIndex & index)
{

	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(c);
	parent->appendRow(item);

	VisitorNumberCategories v;
	traverse(&v);

	return item;

}

QStandardItem * ModelTree::insertNewGroup(const Group & g, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert( index); // assert'd

	TreeItem * item = mItemFactory.createItem(g);
	parent->appendRow(item);
	return item;
}

QStandardItem * ModelTree::insertNewMatrix(const Matrix & m, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(m);
	parent->appendRow(item);
	return item;
}


QStandardItem * ModelTree::insertNewMatrixProblem(const MatrixProblem & m, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(m);
	parent->appendRow(item);
	return item;
}

QStandardItem * ModelTree::insertNewProblem(const Problem & p, const QModelIndex & index)
{
	QStandardItem * parent= getParentForInsert(index); // assert'd

	TreeItem * item = mItemFactory.createItem(p);
	parent->appendRow(item);

	return item;
}


QStandardItem * ModelTree::insertNewSurvey(const Survey &s)
{
	Q_ASSERT_X(false,"ModelTree::insertNewSurvey", "Method not supported by this class");
	return 0x0;
}

// ----------------------------------- drag drop support --------------------------------



QStringList ModelTree::mimeTypes() const
{
	// for dropping only
	// todo support file types, that may be xml
	return QStringList() << mime::DndTreeItem;
	qDebug("ModelTreeData: mimeTypes?");
}


QMimeData * ModelTree::mimeData(const QModelIndexList &indexes) const
{
	// single selection mode only
	QModelIndex index = indexes.at(0);
	Q_ASSERT(index.isValid());

	QMimeData *mimeData = new QMimeData();
	TreeItem * item = itemFromIndexAsTreeItem(index);

	// item type part
	QByteArray btype;
	QDataStream bstr(&btype, QIODevice::WriteOnly);
	bstr << (int)item->getItemType();
	mimeData->setData(mime::DndTreeItemType, btype );


	// serialization part --- QT framework already makes it lazy loaded!
	QBuffer buf;
	WritePolicyXml wp;
	wp.write( item, &buf);

#ifdef _DEBUG
	QByteArray data = qCompress(buf.buffer());
	qDebug("ModelTreeData::mimeData: compressed data has %u b and uncompressed %u b", data.size(), buf.buffer().size());
	mimeData->setData(mime::DndTreeItem, data );
//	mimeData->setData(mime::TextPlain, buf.buffer() ); // do not use
#else
	mimeData->setData(mime::DndTreeItem, qCompress(buf.buffer()) );
#endif

	return mimeData;
}

bool ModelTree::dropMimeData(const QMimeData *data,
								 Qt::DropAction action,
								 int row, int column, const QModelIndex &parent)
{
	qDebug("ModelTreeData: Drop not implemented yet");
	return false;
}



END_NS


