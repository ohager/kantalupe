#ifndef SCRIPTENGINEAGENT_H
#define SCRIPTENGINEAGENT_H

#include <QScriptEngineAgent>

namespace k{

class ScriptEngine;

/**
  Script Engine Agent to control low-level script events
  Currently, the agent checks runtime for called functions, and eventually throw execption if
  call takes too much time.
  @todo Infinite Recursion currently not handled. (dunno how :-( )
  @author O. Haeger
  */
class ScriptEngineAgent : public QObject, public QScriptEngineAgent
{
	Q_OBJECT
public:
	static const int CallStackLimit=500;
	static const int ScriptNotRespondingTimeout=3000;

	ScriptEngineAgent(ScriptEngine * enginewrapper, QScriptEngine * qengine);

	void functionEntry(qint64 scriptId);
	void functionExit(qint64 scriptId, const QScriptValue &returnValue);

	void exceptionThrow(qint64 scriptId, const QScriptValue &exception, bool hasHandler);
protected:
	inline ScriptEngine * engineWrapper() { return mEngine; }

protected slots:

	void timerEvent(QTimerEvent *);


private:
	ScriptEngine * mEngine;
	int mSnrTimer;
	//int mCallStackCount;
};

} // eons

#endif // SCRIPTENGINEAGENT_H
