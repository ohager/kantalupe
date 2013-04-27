#ifndef SIGNALBLOCKER_H
#define SIGNALBLOCKER_H

#include <QObject>
#include <QList>

/**
  RAII signal blocker class for QObjects
  @author O. Haeger
  */
class SignalBlocker{
public:
	explicit SignalBlocker(QObject * obj)
	{
		mObjects.push_back(obj);
		obj->blockSignals(true);
	}

	explicit SignalBlocker(QList<QObject*> objs)
	{

		foreach(QObject * obj,objs)
		{
			mObjects.push_back(obj);
			obj->blockSignals(true);
		}
	}

	~SignalBlocker(){
		foreach(QObject * obj,mObjects)
		{
			obj->blockSignals(false);
		}
	}

private:

	QList<QObject*> mObjects;

};

#endif // SIGNALBLOCKER_H
