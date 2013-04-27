#ifndef WRITEPOLICYBinaryIMPL_V1_H
#define WRITEPOLICYBinaryIMPL_V1_H


#include "AbstractTreeModelVisitor.h"
#include "ProtocolTypes.h"

class QIODevice;
class QDataStream;
class QDir;
class QStringList;

namespace k{

class AbstractTreeModel;
class TreeItem;

/**
  Binary write implementation. Private use only.
  @author O. Haeger
  */
class WritePolicyBinaryImpl_V1 : public AbstractTreeModelVisitor
{
public:
	WritePolicyBinaryImpl_V1();

	static const char * Version;
	static const char * FormatId;

	bool write(AbstractTreeModel * mtd, QIODevice * out);

	AbstractTreeModelVisitor::TraversalType visit(TreeItem *item);
	void leave(TreeItem *item);
	void writeImages(const QStringList & imageurls, QDataStream & outstream);
private:
	QStringList mImageUrlList;
	bool mHasError;
	QString mName;

};

} // eons

#endif // WRITEPOLICYBinaryIMPL_H
