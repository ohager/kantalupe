#ifndef READPOLICYBinaryIMPL_V1_H
#define READPOLICYBinaryIMPL_V1_H

#include <QModelIndex>

class QIODevice;
class QModelIndex;

namespace k{

class ModelInsertionInterface;

class ReadPolicyBinaryImpl_V1
{
public:
	static const char * Version;
	ReadPolicyBinaryImpl_V1();
	bool read(QIODevice * out, ModelInsertionInterface * mtd, const QModelIndex & parent);


	void copyImages(const QString & rootpath, QDataStream & instream);
private:
	// todo: make a temporary pool... that cleans up on applications shutdown.
	//static QStringList sTemporaries;
	ModelInsertionInterface * mModel;
	QString mName;
};

}
#endif // READPOLICYBinaryIMPL_V1_H
