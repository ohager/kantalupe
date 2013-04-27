#include "VisitorNumberCategories.h"
#include "global.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include "UidGenerator.h"

START_NS


VisitorNumberCategories::VisitorNumberCategories()
{
	mNumberStack.push(0);
}

AbstractTreeModelVisitor::TraversalType VisitorNumberCategories::visit(TreeItem * item)
{
	tip::ItemType t=item->getItemType();
	if(t==tip::ItemCategory)
	{
		++mNumberStack.top();
		item->setText( numberAsString() + " " + item->data(tip::RoleTexts).toString() ) ;
		mNumberStack.push(0);

	}
	return AbstractTreeModelVisitor::TraversalContinue;
}


void VisitorNumberCategories::leave(TreeItem * item)
{
	tip::ItemType t=item->getItemType();
	if(t==tip::ItemCategory)
	{
		mNumberStack.pop();
	}
}


QString VisitorNumberCategories::numberAsString() const
{
	QString s;
	foreach(int n, mNumberStack)
	{
		s += QString::number(n) + '.';
	}
	s.chop(1); // cut last point
	return s;
}



END_NS;

