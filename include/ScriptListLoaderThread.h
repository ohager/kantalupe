#ifndef SCRIPTLISTLOADERTHREAD_H
#define SCRIPTLISTLOADERTHREAD_H

#include <QThread>
#include <QMutex>
#include "Script.h"

namespace k{



/**
  Loads all deployed scripts.
  @author O. Haeger
  */
class ScriptListLoaderThread : public QThread{
Q_OBJECT
	public:
	ScriptListLoaderThread(const QString & scriptsdir);
	types::ScriptList getScriptList() const;
public slots:
	void stop();
protected:
	void run();
	private:
	volatile bool mStopped;
	types::ScriptList mScripts;
	mutable QMutex mScriptCopyMutex;

	QString mScriptsDir;
};

} // eons


#endif // SCRIPTLISTLOADERTHREAD_H
