#include "ScriptListLoaderThread.h"
#include "global.h"

#include <QDir>
#include <QFile>
#include <QDebug>

#include "ScriptReaderWriter.h"

START_NS

ScriptListLoaderThread::ScriptListLoaderThread(const QString & scriptsdir) :
	mStopped(false), mScriptsDir(scriptsdir){}

types::ScriptList ScriptListLoaderThread::getScriptList() const {
	QMutexLocker b(&mScriptCopyMutex);
	Q_UNUSED(b);
	return mScripts;
}

void ScriptListLoaderThread::stop(){ mStopped=true; }


void ScriptListLoaderThread::run()
{
	mStopped=false;
	types::ScriptList scripts;
	QDir scriptdir(mScriptsDir);
	scriptdir.setNameFilters(QStringList() << QString("*.").append(file::SuffixScript));
	QStringList scriptfiles = scriptdir.entryList();
	if(scriptfiles.isEmpty())
	{
		qDebug() << "ScriptLoaderThread: " << mScriptsDir << " is unreadable";
		this->exit(-1);
		return;
	}

	ScriptReaderWriter reader;
	foreach(const QString & scriptfile, scriptfiles)
	{
		Script script;
		QFile infile( scriptdir.absoluteFilePath(scriptfile) );
		if(reader.read(script, &infile))
		{
			// for less mem consumption we might think of removal
			// of the scriptcode.
			scripts.push_back(script);
		}
		else
		{
			qDebug() << "ScriptLoaderThread: " << scriptfile << " is unreadable";
		}
#ifdef _DEBUG
		//sleep(1);
#endif
		if(mStopped)
		{
			this->exit(-2);
			return;
		}
	}

	QMutexLocker b(&mScriptCopyMutex);
	Q_UNUSED(b);
	mScripts.clear();
	mScripts = scripts;
	exit(0);
}


END_NS

