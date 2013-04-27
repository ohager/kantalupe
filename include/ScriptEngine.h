#ifndef SCRIPTENGINE_H
#define SCRIPTENGINE_H


#include <QObject>
#include <QScriptValue>


/** @defgroup scriptapi Script API
	kantalupe offers an easy-to-use script API (ECMA-262 aka JavaScript)
	to generate survey instances programmatically.
	@section intro Introduction
	The main purpose of the Script API is the computer-aided generation of surveys. Because a survey
	is a subset of one or more models, it could be generated automatically when certain parameters are
	given. Such parameters are provided by the model's (key,value)-Properties for nearly each model element.
	So, basically for a auto-generation a model is 'scanned' for parameters. An element that fits the parameter
	can be selected to be added to the survey. Therefore, the API comes with a set of functions that will be
	called from @e kantalupe, so called @e callbacks. These functions are described in the API sections.
	Additionally, to the callbacks some global properties and utility functions are provided.
	@section quickstart Quickstart (API Level 1)
	The minimum requirements for a script is the selection of an @ref api "API Level",a model file and
	the implementation of the @ref callbacks "callback" function @e onEnteredItem(item)
	To create a survey at least one item must be selected.
	@code
	apilevel = 1;
	model = "mymodel.kmodel";
	function onEnteredItem(item){
		// this will select all items of type problem
		item.selected = (item.type=="problem");
	}
	@endcode
	The example loads the modelfile @e mymodel.kmodel and selects each item, that is of type 'problem'.
	All selected items will appear in the survey instance then.
	Internally, kantalupe loads the model tree and traverses the entire tree. On each visited item callback
	is triggered when entering and when leaving the item. Furthermore, some code can be executed @e before
	the traversal begins and @e after the traversal has finished.

	@section treeitem Items
	A model consists of hierarchically structured items. Each item has exactly one parent and none or many children.
	That is, they are structured as a tree.\n
	For script execution a model is	traversed, using depth-first search strategy, and on each visited item two @ref callbacks "callbacks"
	are triggered. An item provides properties, which are described in k::ScriptObjectTreeItem. The property set
	consist of API-defined properties, and of user defined properties. The latter kind cannot be described within this
	documentation as they are completely unknown. There meaning remains to the user or the model creator. Nevertheless,
	the usage of both property types is identical.\n
	@subsection treeitemselection Item Selection
	To generate a survey instance items from the models must be selected. This can easily be done using the item's property @e selected.
	When set @e true, the item is considered selected and will be added to the survey instance. Initially, no
	item is selected at all, i.e. its selected state is set to @e false.\n
	There are some rules that must be considered when selecting items. It is possible to select any type, be it
	model, category, problem or anything else. Once an item is selected @e all its descendants are going to be selected either.
	That means for example, that selecting a group will also select all matrices, matrixproblems and problem (if exist).
	@subsection treeitemexample Example
	suppose we have a model like the following:
	@code
<?xml version="1.0" encoding="UTF-8"?>
<KModel name="Test Model" version="1">
	<Functional>
		<UidGeneration mode="manual"/>
	</Functional>
	<Content>
	   <Category name="Main Category">
		   <Description>Any description</Description>
		   <PropertyList/>
		   <Problem uid="p1" multiple="true">
			  <PropertyList>
				  <Property key="difficulty" value="easy"></Property>
				  <Property key="maxduration" value="25"></Property>
			  </PropertyList>
			   <Text>What's the name of Homer youngest child?</Text>
			   <Hint/>
			   <ImageList/>
				<ProposalList>
					<Proposal id="1">Marge</Proposal>
					<Proposal id="2">Maggy</Proposal>
					<Proposal id="3">Bart</Proposal>
					<Proposal id="4">Santa Claus</Proposal>
					<Proposal id="5">Lisa</Proposal>
				</ProposalList>
				<SolutionList>
					<Solution idref="2"/>
				</SolutionList>
		   </Problem>
		</Category>
	</Content>
</KModel>
	@endcode

	The model provides for the problem item two user-defined properties, namely @e difficulty and @e maxduration.
	Inside a script we can access them easily.
	@code
// API Level 1
 apilevel = 1;
 model = "testmodel.kmodel";
 var overallduration = 0;
 function onEnteredItem(item){

	item.selected = false;
	if(item.difficulty == "easy")
	{
		// all easy items are selected
		item.selected = true;
	}
	if(item.maxduration != undefined)
	{
		// summing up the duration
		overallduration = overallduration + item.maxduration;
	}
 }

 function onEnd() {
	var mins = overallduration / 60;
	var seconds = overallduration % 60;
	print("The overall duration of this survey is: " + mins + " Minutes and " + seconds + " seconds.");
 }
	@endcode

 @section api Programming Interface
 The Application Programming Interface (in short: API) may change in future versions. To be prepared for minor and
 major changes the API will be versioned using incrementing level count, starting at @ref scriptapi_lvl1.
 All future API Level shall be compatible with its predecessor. Hopefully, this can be guaranteed for quite a while.
Currently, following API levels exist:\n
 - @ref scriptapi_lvl1
  */


class QScriptEngine;


namespace k{

class ModelTree;
class SurveyTree;
class AbstractScriptEngineApi;

/**
  @ingroup scriptapi
  The script engine for executing generator scripts.
  @author O. Haeger
  */
class ScriptEngine : public QObject
{
	Q_OBJECT
signals:
	/**
	  Triggered iff a survey was successfully generated.
	  @param survey The generated survey tree.
	  */
	void surveyGenerated(SurveyTree * survey);

	/**
	  Triggered when script has finished.
	  @param ok The result of run script.
	  */
	void scriptFinished(bool ok);
	/**
	  Messaging signals.
	  */
	void msgInformation(const QString &);
	void msgDebug(const QString &);
	void msgSuccess(const QString &);
	void msgWarning(const QString &, int line);
	void msgException(const QString &, int line);

public:

	explicit ScriptEngine(QObject * obj = 0x0);
	~ScriptEngine();


	/**
	  @param script The program
	  @param apilevel [out] If not null, the used api level is returned.
	  @return The generated survey tree, or NULL if failed
	  @see surveyGenerated()
	  */
	SurveyTree * runScript(const QString & script, int * apilevel=0x0);


	/**
	  Posts a normal message. This will cause to emit msgInformation() or msgSuccess()
	  @param message The text itself
	  @param success [optional] If @e true msgSuccess() is emitted instead of msgInformation()
	  */
	void postMessage(const QString & message, bool success=false);


	/**
	  Posts a debug message. This will cause to emit msgDebug()
	  @param message The text itself
   */
	void postDebug(const QString & message);

	/**
	  Posts a warning message. This will cause to emit a certain message signal, e.g. msgWarning().
	  @param message The text itself
	  @param line [optional] The related line number, iff exist.
	  @see postException()
	  */
	void postWarning(const QString & message, int line =-1);
	void postException(const QString & message, int line =-1);
	/**
	  Post the special Script Not Responding exception
	  @param functionname [optional] The functionname where the hang was detected. If nothing given
	  a generic SNR message is posted.
	  @param line [optional] If given, the line of occurred hang is given.
	  @note postSNR will emit msgException() with unified SNR message and aborts any evaluation
	  */
	void postSNR(const QString & functionname = QString(), int line = -1);

	//QScriptValue callScriptFunction(const QString & functionname, const QScriptValueList & arguments = QScriptValueList());

protected:
	void timerEvent(QTimerEvent *);

private:
	QScriptEngine * _engineRef;
	AbstractScriptEngineApi * mScriptApiImpl;
	//QString mRecentlyCalledFunction;
	int mSnrEvalTimerId;
};

} // eons

#endif // SCRIPTENGINE_H
