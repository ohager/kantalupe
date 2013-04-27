#ifndef VISITORGENERATEHASHUID_H
#define VISITORGENERATEHASHUID_H

#include "AbstractTreeModelVisitor.h"

namespace k{

/**
  Visitor that generates hash-based Unique Identifiers for certain items.
  @author O. Haeger
  */
class VisitorGenerateHashUid : public AbstractTreeModelVisitor
{
public:
	 TraversalType visit(TreeItem * item);
	void leave(TreeItem * item){}
};

} // eons

#endif // VISITORGENERATEHASHUID_H
