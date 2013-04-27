#ifndef SCRIPTENGINEAPIINTERFACE_H
#define SCRIPTENGINEAPIINTERFACE_H

class QScriptEngine;

namespace k{

class ScriptEngine;
class ModelTree;
class SurveyTree;

/**
@ingroup scriptapi
The base class for script API implementations.
This implementation is used by ScriptEngine.

@author O. Haeger
  */
class AbstractScriptEngineApi
{
public:
	/**
	  @param engine The engine that uses this API implementation.
	  */
	AbstractScriptEngineApi(ScriptEngine * engine) : _engine(engine), mAbortRequested(false) {}
	virtual ~AbstractScriptEngineApi() { _engine = 0x0; }

	/**
	  @return A number identifying the API level of this implementation
	  */
	virtual int apiLevel() const = 0;

	/**
	  Initializer routine for script engine. This is to declare any object for the script.
		This is usually called @a after the script was evaluated and @e before runScript() is called.
	  @param e The QScriptEngine instance, that shall be initialized
	   @return Must return a loaded ModelTree, or null if failed. The model will be owned by k::ScriptEngine.
	  */
	virtual ModelTree * initialize(QScriptEngine * e)=0;

	/**
	  The script logic. Its intention is to create a survey instance, using a script
	  that is applied on a model.
		@param model The model used for survey generation.
		@param e The QScriptEngine instance, that is used for execution.
	  @return The generated survey, or null if failed. Survey must not be deleted!
	  */
	virtual SurveyTree * runScript(ModelTree * model, QScriptEngine * e)=0;

	/**
	  Requests the script to stop.
	@note This function can be called from engine() on timeout or other exceptions.
	So, you should check for aborted in your implementation parts, e.g. loops and similars.
	  @see isStopped()
	  */
	void abortScript() { mAbortRequested=true; }

	/**
	  Use this to check if a abort of running script is requested.
	  */
	bool isAborted() const { return mAbortRequested; }
protected:
	/**
	  The calling engine.
	  */
	inline ScriptEngine * engine() { return _engine; }
private:
	ScriptEngine * _engine;
	volatile bool mAbortRequested;
};

} // eons


#endif // SCRIPTENGINEAPIINTERFACE_H
