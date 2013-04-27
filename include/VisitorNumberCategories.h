#ifndef VISITORNUMBERCATEGORIES_H
#define VISITORNUMBERCATEGORIES_H

#include <QStack>

#include "AbstractTreeModelVisitor.h"

namespace k{

/**
  Visitor that numbers category items according to their depths.
  @author O. Haeger
  */
class VisitorNumberCategories : public AbstractTreeModelVisitor
{
public:
	VisitorNumberCategories();
	 TraversalType visit(TreeItem * item);
	void leave(TreeItem * item);

private:
	QString numberAsString() const;
	QStack<int> mNumberStack;
};

} // eons

#endif // VISITORNUMBERCATEGORIES_H
