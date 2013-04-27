#include "ScriptEngine.h"
#include "global.h"

#include <QApplication>
#include <QtScript>
//#include <QScriptEngineAgent>

#include "ModelTree.h"
#include "SurveyTree.h"
#include "ScriptObjectTreeItem.h"
#include "ScriptEngineApiLevel_1.h"
#include "ScriptEngineAgent.h"

#include "WritePolicyXml.h"
#include "ReadPolicyXml.h"
#include "ReadPolicyBinary.h"

#include "AbstractTreeModelVisitor.h"


START_NS



ScriptEngine::ScriptEngine(QObject * parent)
	: QObject(parent), _engineRef(0x0), mScriptApiImpl(0x0), mSnrEvalTimerId(-1)
{

}

ScriptEngine::~ScriptEngine()
{}



class ScriptExecutionTimer
{
public:
	ScriptExecutionTimer(ScriptEngine * engine) : _engine(engine)
	{
		mTimer.start();
	}

	~ScriptExecutionTimer(){
		qint64 ms = mTimer.elapsed();
		_engine->postMessage( QApplication::translate("ScriptEngine", "Script execution time: %1 ms").arg(ms) );
	}

private:
	ScriptEngine * _engine;
	QElapsedTimer mTimer;
};



SurveyTree * ScriptEngine::runScript(const QString & script, int * apilevel)
{
	postMessage( tr("Script started.") );
	ScriptExecutionTimer timer(this); // raii
	Q_UNUSED(timer)
	QScriptSyntaxCheckResult result = QScriptEngine::checkSyntax(script);
	if(result.state() != QScriptSyntaxCheckResult::Valid)
	{
		QString msg= tr("Syntax error: ").append(result.errorMessage());
		postException( msg, result.errorLineNumber() );
		emit scriptFinished(false);
		return 0x0;
	}

	QScriptEngine engine;
	_engineRef = &engine;
	engine.setProcessEventsInterval(100);
	engine.setAgent( new ScriptEngineAgent(this, &engine) );
	mSnrEvalTimerId = startTimer(7500); // evaluation timeout
	engine.evaluate(script);

	int apilvl = engine.globalObject().property("apilevel").toInteger();
	if(!apilvl)
	{
		postException( tr("Property 'apilevel' is not defined") );
		return 0x0;
	}

	if(mScriptApiImpl){
		delete mScriptApiImpl; mScriptApiImpl = 0x0;
	}

	switch(apilvl)
	{
	default:
		postWarning( tr("Given API Level %1 does not exist.").arg(apilvl) );
	case 1:
		mScriptApiImpl = new ScriptEngineApiLevel_1(this);
		break;
	}

	Q_ASSERT(mScriptApiImpl);

	if(apilevel)
		*apilevel = mScriptApiImpl->apiLevel();

	postMessage( tr("Using API Level %1.").arg(mScriptApiImpl->apiLevel()) );
	ModelTree * model = mScriptApiImpl->initialize(&engine);
	if(!model)
	{
		emit scriptFinished(false);
		delete mScriptApiImpl; mScriptApiImpl =0x0;
		return 0x0;
	}


	SurveyTree *  survey = mScriptApiImpl->runScript(model,&engine);
	emit scriptFinished(survey!=0x0);
	if(survey)
		emit surveyGenerated(survey);
	if(model)
		model->deleteLater();

	killTimer(mSnrEvalTimerId);
	delete mScriptApiImpl; mScriptApiImpl =0x0;
	return survey;
}


void ScriptEngine::postMessage(const QString & message, bool success)
{
	if(success)
	{
		emit msgSuccess(message);
	}
	else
	{
		emit msgInformation(message);
	}
}

void ScriptEngine::postDebug(const QString & message)
{
	emit msgDebug(message);
}

void ScriptEngine::postWarning(const QString & message, int line)
{
	emit msgWarning(message,line);
}

void ScriptEngine::postException(const QString & message, int line)
{
	if(mScriptApiImpl)
	{
		mScriptApiImpl->abortScript();
	}
	if(_engineRef->isEvaluating())
		_engineRef->abortEvaluation();

	emit msgException(message,line);
}

void ScriptEngine::postSNR(const QString & functionname, int line)
{
	QString message;
	if(!functionname.isEmpty())
	{
		message = tr("[SNR] Script Not Responding in function '%1'").arg(functionname);
	}
	else
	{
		message = tr("[SNR] Script Not Responding");
	}


	if(mScriptApiImpl)
	{
		mScriptApiImpl->abortScript();
	}

	if(_engineRef->isEvaluating())
		_engineRef->abortEvaluation();

	emit msgException(message, line);
}

/*
QScriptValue ScriptEngine::callScriptFunction(const QString & functionname, const QScriptValueList & arguments)
{
	killTimer(mSnrTimerId);
	mSnrTimerId = startTimer(ScriptNotRespondingTimeout);
	mRecentlyCalledFunction = functionname;
	QScriptValue func = _engineRef->globalObject().property(functionname);
	QScriptValue ret = func.call(QScriptValue(),arguments);
	if(_engineRef->hasUncaughtException())
	{
		QString errmsg = _engineRef->uncaughtException().property("message").toString();
		int line = _engineRef->uncaughtException().property("lineNumber").toInteger();
		postException(errmsg, line);
		//_engineRef->abortEvaluation();
	}
	return ret;
}
*/

// --------------------------------- events --------------------------
void ScriptEngine::timerEvent(QTimerEvent * e)
{
	// the only timeout is 'script not responding'
	if(e->timerId()==mSnrEvalTimerId)
	{
		killTimer(mSnrEvalTimerId);
		postSNR(); // generic SNR
	}
}


END_NS

