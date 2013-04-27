#ifndef SCRIPTENGINEAPILEVEL_1_H
#define SCRIPTENGINEAPILEVEL_1_H

#include "AbstractScriptEngineApi.h"
#include <QString>

namespace k{

class ScriptEngine;
class ModelTree;
class SurveyTree;


/** @ingroup scriptapi
  @defgroup scriptapi_lvl1 Level 1 API
  Implementation of Script API Level 1

 @section callbacks API Callbacks
 The currently supported callbacks are:

 - @c onEnteredItem(item)\n
 Called when @ref treeitem "item" is entered.
 - @c onLeftItem(item)\n
 Called when @ref treeitem "item" is left.
 - @c onStart()\n
 Called before any item is visited. The model is already loaded.
 This method is useful for some initialization
 - @c onEnd()\n
 Called after all items are processed. The survey is not generated yet.

 @section funcs Utility functions
 These are some useful functions provided by kantalupe
 - @c print(text)\n
 prints text to console window
 - @c debug(text)\n
 prints text to console window. text is marked as debug. Currently, nearly identical to print()

 @section props Global properties
 Global properties are variables (or constants) that are provided by kantalupe.

- @c apilevel\n
This is a must have property and defines, which Level API is used. This is the only
global static property, that all APIs will have in common and won't change in the future.
If it's not defined the script won't start.
- @c model\n
This is a must have property and defines, which model shall be used for traversal.
Simply pass the model's file name. If it is not defined the script won't be started.
- @c restart\n
Allows to restart the entire script, eventually with different configuration, e.g. another
model. (Currently, not implemented)

  @param O. Haeger
  */
class ScriptEngineApiLevel_1 : public AbstractScriptEngineApi
{
public:
	ScriptEngineApiLevel_1(ScriptEngine * e);
	int apiLevel() const { return 1; }

	ModelTree * initialize(QScriptEngine * e);
	SurveyTree * runScript(ModelTree * m, QScriptEngine * e);
protected:
	QString tr(const char * text) const;
	SurveyTree * generateSurvey(ModelTree * model);

};

} // eons

#endif // SCRIPTENGINEAPILEVEL_1_H
