#include "ScriptEngineApiLevel_1.h"
#include "ScriptEngine.h"
#include "global.h"


#include "ModelTree.h"
#include "SurveyTree.h"
#include "ScriptObjectTreeItem.h"
#include "ScriptEngineApiLevel_1.h"


#include "WritePolicyXml.h"
#include "ReadPolicyXml.h"
#include "ReadPolicyBinary.h"

#include "AbstractTreeModelVisitor.h"

#include <QtScript>


START_NS
ScriptEngineApiLevel_1::ScriptEngineApiLevel_1(ScriptEngine * e) :
	AbstractScriptEngineApi(e) {

}


// ---------------------------- VISITORS -----------------------------------------------

class ScriptTreeModelVisitor : public AbstractTreeModelVisitor
{
	public:
		ScriptTreeModelVisitor(ScriptEngineApiLevel_1 * apiimpl, QScriptEngine * engine) :
			_qengine(engine),_apiimpl(apiimpl)	{}


		TraversalType visit(TreeItem * item){
			Q_ASSERT(_qengine);
			QObject * scriptitem = new ScriptObjectTreeItem(item);
			QScriptValue itemvalue = _qengine->newQObject(scriptitem, QScriptEngine::ScriptOwnership);

			QScriptValue funcEnd = _qengine->globalObject().property("onEnteredItem");
			funcEnd.call(QScriptValue(),QScriptValueList() << itemvalue);

			return _apiimpl->isAborted() || _qengine->hasUncaughtException() ?
							AbstractTreeModelVisitor::TraversalEnd :
							AbstractTreeModelVisitor::TraversalContinue;
		}

		void leave(TreeItem * item){
			Q_ASSERT(_qengine);
			QObject * scriptitem = new ScriptObjectTreeItem(item);
			QScriptValue itemvalue = _qengine->newQObject(scriptitem, QScriptEngine::ScriptOwnership);
			QScriptValue funcEnd = _qengine->globalObject().property("onLeftItem");
			funcEnd.call(QScriptValue(),QScriptValueList() << itemvalue);
		}
private:
		QScriptEngine * _qengine;
		ScriptEngineApiLevel_1 * _apiimpl;

};

/*
  Small helper selecting items
  */
class ScriptItemSelector : public AbstractTreeModelVisitor{
public:
	TraversalType visit(TreeItem *item)
	{
		item->setData(true, tip::ScriptRoleSelected);
		return AbstractTreeModelVisitor::TraversalContinue;
	}
	void leave(TreeItem *item){};
};


/*
  Collects all selected items.
  */
class ScriptSelectedItemCollector: public AbstractTreeModelVisitor
{
public:

	TraversalType visit(TreeItem * item){
		if(item->data(tip::ScriptRoleSelected).toBool())
		{
			mSelectedItems.push_back(item);
		}
		return AbstractTreeModelVisitor::TraversalContinue;
	}

	void leave(TreeItem * item){ }

	const QList<TreeItem*> getSelectedItems() const { return mSelectedItems; }

private:
	QList<TreeItem*> mSelectedItems;
};


/*
  Removes all unselected items, which I call "BonsaiCut"-Method
  Background: On script side the items for a survey receive the state 'selected' (ScriptRoleSelected == true)
  When I need to generate a survey I simply remove all non-selected items.
  And replace the root item by the survey root item. This works, as survey and model data structure
  is nearly identical. So we have a very efficient way to generate a survey from a model.
  Note: As a precondition it is necessary that the entire path of a selected item is selected
  and also its children and grandchildren. --> generateSurvey()
  */
class ScriptModelTreeBonsaiCutter : public AbstractTreeModelVisitor
{
public:
	~ScriptModelTreeBonsaiCutter(){ removeItems();}

	TraversalType visit(TreeItem * item){

		Q_ASSERT(item);
		if(!item->data(tip::ScriptRoleSelected).toBool())
		{
			qDebug() << item->text() << " to be removed" ;
			mItemsToBeRemoved.push_back(item);
			return TraversalIgnoreSubtree;
		}
		return TraversalContinue;
	}

	void leave(TreeItem * item){ }

	void removeItems(){
		foreach(QStandardItem * item, mItemsToBeRemoved)
		{
			QStandardItem *  pitem = item->parent();
			Q_ASSERT(pitem);
			pitem->removeRow(item->index().row());
		}
		mItemsToBeRemoved.clear();
	}

private:
	QList<TreeItem*> mItemsToBeRemoved;
};

/*
  We are BORG.
  I use this to apply the survey style to all items we got from model tree!
  */
class ScriptSurveyTreeAssimilator: public AbstractTreeModelVisitor
{
public:
	TraversalType visit(TreeItem * item){
		mFactory.applyStyle(item);
		return AbstractTreeModelVisitor::TraversalContinue;
	}
	void leave(TreeItem *){ /* noop */	}
private:
	SurveyTreeItemFactory mFactory;
};


//-------------------------------------END OF VISITORS ---------------------------------------------------------





// -------------------------------- API Level 1 Functions ----------------------------

// print redefinition
QScriptValue printFunction(QScriptContext *context, QScriptEngine *engine)
{
	QString result;
	for (int i = 0; i < context->argumentCount(); ++i) {
		if (i > 0)
			result.append(" ");
		result.append(context->argument(i).toString());
	}

	QScriptValue calleeData = context->callee().data();
	ScriptEngine * se = qobject_cast<ScriptEngine*>(calleeData.toQObject());
	se->postMessage(result.prepend("[Script] "));

	return engine->undefinedValue();
}

QScriptValue debugFunction(QScriptContext *context, QScriptEngine *engine)
{
	QString result;
	for (int i = 0; i < context->argumentCount(); ++i) {
		if (i > 0)
			result.append(" ");
		result.append(context->argument(i).toString());
	}

	QScriptValue calleeData = context->callee().data();
	ScriptEngine * se = qobject_cast<ScriptEngine*>(calleeData.toQObject());
	se->postDebug(result.prepend("[Script Debug] "));

	return engine->undefinedValue();
}

// -------------------------------- End API functions --------------------------------------


ModelTree * ScriptEngineApiLevel_1::initialize(QScriptEngine * qe)
{
	Q_ASSERT(qe);
	// optional property
	qe->globalObject().setProperty("restart",false);

	// redefine print functions
	QScriptValue printfunc = qe->newFunction(printFunction);
	printfunc.setData(qe->newQObject(engine()));
	qe->globalObject().setProperty("print", printfunc);

	QScriptValue debugfunc = qe->newFunction(debugFunction);
	debugfunc.setData(qe->newQObject(engine()));
	qe->globalObject().setProperty("debug", debugfunc);

	ScriptEngine * e = engine();

	QString modelfile = qe->globalObject().property("model").toString();
	if(QFile::exists(modelfile))
	{

		QFile infile(modelfile);
		if(!infile.open(QIODevice::ReadOnly))
		{
			e->postException( tr("Could not open model file <").append(modelfile).append(">\nOperation aborted.") );
			return false;
		}

		ModelTree * model = new ModelTree();
		bool ok = false;
		if(modelfile.endsWith( file::SuffixModelBinary ))
		{
			ReadPolicyBinary policy;
			ok = model->load(&infile, policy);
		}
		else if(modelfile.endsWith( file::SuffixXml ))
		{
			ReadPolicyXml policy;
			ok = model->load(&infile, policy);
		}

		if(!ok)
		{
			e->postException( tr("Could read model file <").append(modelfile).append(">\nOperation aborted.") );
			qDebug() << "Could not read file: " << modelfile;
			delete model;
			return 0x0;
		}
		return model;
	}
	else // exists
	{
		e->postException( tr("Model file <").append(modelfile).append("> does not exist. Operation aborted.") );
	}
	return 0x0;
}

SurveyTree * ScriptEngineApiLevel_1::runScript(ModelTree * model, QScriptEngine * qe)
{

	QScriptValue funcStart = qe->globalObject().property("onStart");
	funcStart.call(QScriptValue(),QScriptValueList());
	if(isAborted() || qe->hasUncaughtException())
		return 0x0;

	ScriptTreeModelVisitor v(this, qe);
	model->traverse(&v);

	QScriptValue funcEnd = qe->globalObject().property("onEnd");
	funcEnd.call(QScriptValue(),QScriptValueList());
	if(isAborted() || qe->hasUncaughtException())
		return 0x0;

	return generateSurvey(model);

	/*
	if(qe.globalObject().property("restart").toBool())
	{
		postDebug( "Restart not implemented yet" );
	}
	*/
}



SurveyTree * ScriptEngineApiLevel_1::generateSurvey(ModelTree * model)
{
	Q_ASSERT(model);

	/*
	  How does it work:
	  Precondition: The user has selected SINGLE (isolated) items using the script.
	  We traverse the model collecting all 'single-selected' items. Then we create
	  their structural context, i.e. selecting all ascendants and descendants (selection mask).
	  Afterwards, all remaining unselected items are collected, as they are going to be
	  removed then- this is a kind of lopping/trimming, which we call bonsai cut.
	  Note: We cannot cut the items during traversal, as we might run into iteration leaks.
	  Thats why the collection-scheme is used.
	  */

	ScriptSelectedItemCollector collector;
	model->traverse(&collector);

	// create complete selection mask
	// i.e. select path to root, select children, and grandchildren
	const QList<TreeItem*> selectedItems = collector.getSelectedItems();

	if(selectedItems.empty())
	{
		engine()->postWarning(tr("Survey cannot be generated. No items in model selected."));
		return 0x0;
	}

	foreach(TreeItem * item, selectedItems)
	{
		TreeItem * pitem = (TreeItem *)item->parent();
		// path to root selection
		while(pitem)
		{
			pitem->setData(true, tip::ScriptRoleSelected);
			pitem = (TreeItem*)pitem->parent();
		}

		// subtree selection
		if(item->hasChildren())
		{
			ScriptItemSelector selector;
			item->treeModel()->traverse(&selector, item);
		}
	}

	ScriptModelTreeBonsaiCutter bonsaicutter;
	model->traverse(&bonsaicutter);
	// cannot remove during traversal!
	bonsaicutter.removeItems();

	TreeItem * modelroot=model->rootItem();
	SurveyTree * survey = new SurveyTree();

	// now put model items into survey
	while(modelroot->hasChildren())
	{
		survey->rootItem()->appendRow( modelroot->takeRow(0) );
	}

	// At last, we apply the survey style!
	ScriptSurveyTreeAssimilator assimilator;
	survey->traverse(&assimilator);

	engine()->postMessage( tr("Survey successfully generated"), true );

	return survey;
}

#include <QApplication>
QString ScriptEngineApiLevel_1::tr(const char * text) const
{
	return QApplication::translate("ScriptEngineApiLevel_1", text );
}


END_NS
