#include "VisitorGenerateHashUid.h"
#include "global.h"
#include "TreeItem.h"
#include "TreeItemProtocol.h"
#include "UidGenerator.h"

START_NS

AbstractTreeModelVisitor::TraversalType VisitorGenerateHashUid::visit(TreeItem * item)
{
	qDebug("visited item '%s'...", item->text().toAscii().data());

	tip::ItemType t=item->getItemType();
	if(t==tip::ItemMatrixProblem)
	{
		MatrixProblem obj;
		tip::extract(item, obj);
		obj.uid = UidGenerator().generate(obj.text);
		tip::incept(obj, item);
	}
	else if(t==tip::ItemProblem)
	{
		Problem obj;
		tip::extract(item, obj);
		obj.uid = UidGenerator().generate(obj.text);
		tip::incept(obj, item);
	}


	return AbstractTreeModelVisitor::TraversalContinue;
}


END_NS;

