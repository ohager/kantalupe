#ifndef SCRIPTOBJECTSURVEY_H
#define SCRIPTOBJECTSURVEY_H

#include <QObject>

namespace k{

class ScriptObjectTreeItem;
/**
  Survey object for Qt Script
  */
class ScriptObjectSurvey : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QObject * rootItem READ getRootItem);
public:
	ScriptObjectSurvey(QObject * parent=0x0);

	QObject * getRootItem() const { return 0x0; }

public slots:
	void appendItem() {};
private:
	ScriptObjectTreeItem * mRootItem;
};

} // eons

#endif // SCRIPTOBJECTGENERATOR_H
