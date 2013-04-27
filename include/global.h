#ifndef _GLOBAL_H 
#define _GLOBAL_H

#include "xrs/XrsLoaderQt.h"
#include "MessageHandler.h"


#include <string>
#include <QEvent>

class QMainWindow;

//------------------- Macros -------------------------

/* we cannot use definition with moc !!!
	So all moc'ed classes, i.e. their headers, 
	need the full qualified namespace thing:
	namespace k{ ... }
*/

#define NS k
#define START_NS namespace NS{
#define END_NS }
#define USE_NS using namespace NS

#define DECLARE_NEW_EVENT(eventname) extern QEvent::Type eventname;

#define ERROR(c,f,m,d) MessageHandler::error(c,f,m,d)
#define WARNING(c,f,m,d) MessageHandler::warning(c,f,m,d)
#ifdef _DEBUG
	#define DEBUG(c,f,m) MessageHandler::debug(c,f,m)
#else
	#define DEBUG(c,f,m) /* no debug */
#endif




#define kApp static_cast<k::Application*>(k::Application::instance())


// ------------- End Macros ----------------------------

START_NS

namespace types{
	typedef QList<QAction*> Actions;

}

namespace global{

DECLARE_NEW_EVENT(UserMode);
DECLARE_NEW_EVENT(DragStarted);
DECLARE_NEW_EVENT(DragStopped);



/**
Types of available views
enum TaskType{
	TaskSelector= 100, ///< Selector
	TaskNewProject,
	TaskLoadProject,
	TaskNewSurvey,
	TaskOpenSurvey,
	TaskNewModel,
	TaskEditModel
};
*/

/**
  User mode types
  */
enum UserModeType{
	UserModeNovice = 100,
	UserModeExpert
};


/**
Types of item models
*/
enum ItemModelType{
	ItemModelKmx=300, ///< The Kantalupe Model
	ItemModelKil ///< The Kantalupe Instance
};

/**
  Insert modes for models,etc.
  */
enum InsertMode{
	AsChild = 0x12,
	AsSibling,
	AsTopLevel
};



/**
This is a opacity value used for transparent widgets
*/
//extern float WindowOpacity;

/**
  The invalid Unique Identifier
  */
extern const char * InvalidUid;

/**
  The application wide used date format
  */
extern const QString DateFormat;

extern const QString Version;

/**
The resource holder
@see initR()
*/
extern XrsLoaderQt R;

/**
  Initializes the resources available under 'R'
  @param xrs The xrs file
  @return @e true, if successfully initialized, otherwise @e false.
 */
extern bool initR(const char * xrs);


/**
Converts a utf8 string in QString unicode.
@param utf8 The utf8 string
@return The unicode string

extern QString utf8(const std::string & utf8);
*/
} // end global namespace



namespace file{

/**
The file suffix for xml files (without dot)
*/
extern const QString SuffixXml;

/**
The file suffix for script files (without dot)
*/
extern const QString SuffixScript;

/**
The file suffix for model binaries (without dot)
*/
extern const QString SuffixModelBinary;

/**
The file suffix for survey binaries (without dot)
*/
extern const QString SuffixSurveyBinary;

/**
The file filter for xml files
*/
extern const QString FilterXml;


/**
The file filter for script files
*/
extern const QString FilterScript;

/**
The file filter for Model binaries
*/
extern const QString FilterModelBinary;

/**
The file filter for Survey binaries
*/
extern const QString FilterSurveyBinary;



} // end ns files

namespace mime{

/**
The Mime Type for drag and drop of TreeItem objects.
In the current implementation it is realized as a compressed
xml description of the items entire subtree. Use qUncompress()
to get its xml data, which than can be processed easily.
*/
extern const QString DndTreeItem;
/**
  The Mime Type for drag and drop of TreeItem objects.
  This information is simply the ItemType identifier (tip::ItemType).
	It is provided for fast item type identification on DnD.
  */
extern const QString DndTreeItemType;
extern const QString TextPlain;
extern const QString TextXml;

}

END_NS


#endif // _kGLOBAL_H

