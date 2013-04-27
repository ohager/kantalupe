#include "ScriptEngineAgent.h"
#include "global.h"

#include <QTimer>
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptContextInfo>

#include "ScriptEngine.h"

START_NS


static const char * SNR = "[SNR]"; // script not responding tag
//static const char * CSO = "[CSO]"; // call stack overflow tag

ScriptEngineAgent::ScriptEngineAgent(ScriptEngine * engine, QScriptEngine * qengine)
	: QScriptEngineAgent(qengine), mEngine(engine), mSnrTimer(-1)
	//mCallStackCount(0),
{

}

void ScriptEngineAgent::functionEntry(qint64 scriptId)
{

	mSnrTimer = startTimer(ScriptNotRespondingTimeout);

}

void ScriptEngineAgent::functionExit(qint64 scriptId, const QScriptValue &returnValue)
{

	//--mCallStackCount;

	if(mSnrTimer!=-1)
		killTimer(mSnrTimer);

}




void ScriptEngineAgent::exceptionThrow(qint64 scriptId, const QScriptValue &exception, bool hasHandler)
{
	QString errmsg;
	int line = -1;
	if(exception.isError())
	{
		errmsg = exception.property("message").toString();
		line = exception.property("lineNumber").toInteger();
	}
	else if(exception.isString())
	{
		errmsg = exception.toString();
	}
	else
	{
		errmsg = tr("Undefined exception");
	}


	if(!errmsg.isNull() && errmsg.startsWith(SNR))
	{
		// errmsg comes with SNR tag and the function name
		errmsg.remove(0,sizeof(SNR)+1);
		engineWrapper()->postSNR(errmsg, line);
	}
	else
	{
		engineWrapper()->postException(errmsg, line);
	}

	/*
	else if(!errmsg.isNull() && errmsg.startsWith(CSO))
	{
		// errmsg comes with SNR tag and the function name
		errmsg.remove(0,sizeof(CSO)+1);
		int line = exception.property("lineNumber").toInteger();
		engineWrapper()->postException(tr("[CSO] Call Stack Overflow"), line);
	}
	*/
}

void ScriptEngineAgent::timerEvent(QTimerEvent * e)
{
	Q_UNUSED(e);
	killTimer(mSnrTimer);
	QScriptContextInfo ctxtinfo(engine()->currentContext());
	engine()->currentContext()->throwError( QString("%1%2").arg(SNR).arg(ctxtinfo.functionName()) );
}

END_NS


