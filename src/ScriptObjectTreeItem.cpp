#include "ScriptObjectTreeItem.h"
#include "global.h"

#include "TreeItem.h"
#include "AbstractTreeModelVisitor.h"
#include "AbstractTreeModel.h"

#include <QDebug>
START_NS

class ScriptTreeItemSelector : public AbstractTreeModelVisitor
{
public:
	ScriptTreeItemSelector(bool selected) : mSelected(selected) {}

	TraversalType visit(TreeItem * item){
		item->setData(mSelected, tip::ScriptRoleSelected);
		return AbstractTreeModelVisitor::TraversalContinue;
	}

	void leave(TreeItem *){/*noop*/}
private:
	bool mSelected;
};



ScriptObjectTreeItem::ScriptObjectTreeItem(TreeItem * item, QObject * parent) :
	QObject(parent), mItem(item)
{
	initialize();
}


void ScriptObjectTreeItem::initialize(){
	// adding items properties dynamically
	// making them available in QtScript
	types::Properties props = getProperties();
	foreach(const Property & p, props)
	{
		this->setProperty(p.key.toAscii().data(), QVariant(p.value));
	}
}

bool ScriptObjectTreeItem::isSelected() const
{
	return mItem->data( tip::ScriptRoleSelected ).toBool();
}

void ScriptObjectTreeItem::setSelected(bool selected)
{
	mItem->setData( selected, tip::ScriptRoleSelected );

	/*
	if(!selected)
		return;

	// select path to root
	TreeItem * item = (TreeItem*)mItem->parent();
	while(item || item->getItemType()!=tip::ItemModel)
	{
		item->setData(selected, tip::ScriptRoleSelected);
		item = item->parent();
	}

	if(mItem->hasChildren())
	{
		// select entire subtree
		ScriptTreeItemSelector selector(selected);
		mItem->treeModel()->traverse(&selector, mItem);
	}
	*/
}



QString ScriptObjectTreeItem::getItemType()
{
	switch(mItem->getItemType())
	{
	case tip::ItemCategory:
		return "category";
	case tip::ItemGroup:
		return "group";
	case tip::ItemMatrix:
		return "matrix";
	case tip::ItemMatrixProblem:
		return "matrixproblem";
	case tip::ItemProblem:
		return "problem";
	case tip::ItemModel:
		return "model";
	case tip::ItemSurvey:
		return "survey";
	default:
		return QString();
	}
}

QString ScriptObjectTreeItem::getName()
{
	switch(mItem->getItemType())
	{
	case tip::ItemGroup:
	case tip::ItemMatrix:
	case tip::ItemSurvey:
		return mItem->text();
	case tip::ItemCategory:
		return mItem->data(tip::RoleTexts).toString();
	default:
		return QString();

	}
}

types::Properties ScriptObjectTreeItem::getProperties() const
{
	switch(mItem->getItemType())
	{
	case tip::ItemCategory:
	{
		Category obj;
		tip::extract(mItem, obj);
		return obj.properties;
	}
	case tip::ItemGroup:
	{
		Group obj;
		tip::extract(mItem, obj);
		return obj.properties;
	}
	case tip::ItemMatrix:
	{
		Matrix obj;
		tip::extract(mItem, obj);
		return obj.properties;
	}
	case tip::ItemMatrixProblem:
	{
		MatrixProblem obj;
		tip::extract(mItem, obj);
		return obj.properties;
	}
	case tip::ItemProblem:
	{
		Problem obj;
		tip::extract(mItem, obj);
		return obj.properties;
	}
	case tip::ItemSurvey:
	{

		Survey obj;
		tip::extract(mItem, obj);
		return obj.properties;
	}

	case tip::ItemModel:
	default:
		return types::Properties();
	}
}


END_NS

