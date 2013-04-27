#include "global.h"

#include <QTextCodec>
#include <QApplication>

//QTextCodec * Utf8Codec  = QTextCodec::codecForName("UTF-8");

#define DEFINE_NEW_EVENT(eventname) QEvent::Type eventname = \
				static_cast<QEvent::Type>(QEvent::registerEventType())

START_NS

namespace global{

DEFINE_NEW_EVENT(UserMode);
DEFINE_NEW_EVENT(DragStarted);
DEFINE_NEW_EVENT(DragStopped);



const char * InvalidUid = "#UID";

const QString DateFormat = QApplication::translate("DateFormat", "dd.MM.yyyy");

const QString Version = QString("%1.%2").arg(_VERMAJ).arg(_VERMIN);

XrsLoaderQt R;

bool initR(const char * xrs )
{
    QString err, detail;
    if(!global::R.load(xrs,&err,&detail))
    {
	ERROR("::","initR",
	      QApplication::tr(
		      "There are problems loading the resource file."),
	      err + '\n' +  detail);
	return false;
    }
    return true;
}

/*
QString utf8(const std::string & str)
{
	return Utf8Codec->toUnicode(str.c_str(), str.size());
}
*/

} // end ns global

namespace mime{

const QString DndTreeItemType = "application/x-kantalupe-dndti-type";
const QString DndTreeItem = "application/x-kantalupe-dndti";
const QString TextXml = "text/xml";
const QString TextPlain = "text/plain";
} // end ns mime


namespace file{

const QString SuffixXml = QString("xml");
const QString SuffixScript = QString("kscript");
const QString SuffixModelBinary = QString("kmodel");
const QString SuffixSurveyBinary = QString("ksurvey");
const QString FilterXml = QApplication::translate("Filefilter","Xml Files (*.%1)").arg(SuffixXml);
const QString FilterScript = QApplication::translate("Filefilter","Script Files (*.%1)").arg(SuffixScript);
const QString FilterModelBinary = QApplication::translate("Filefilter","Kantalupe Model Files (*.%1)").arg(SuffixModelBinary);
const QString FilterSurveyBinary = QApplication::translate("Filefilter","Kantalupe Survey Files (*.%1)").arg(SuffixSurveyBinary);

} // end ns files



END_NS
