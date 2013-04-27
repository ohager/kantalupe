#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T13:11:57
#
#-------------------------------------------------

QT       += xml

TARGET = plugin_export_smssurvey
TEMPLATE = lib
TARGET        = $$qtLibraryTarget(plugin_export_smssurvey)
DESTDIR       = ../../../bin/plugins/export

DEFINES += PLUGIN_EXPORT_QUEXML_LIBRARY

SOURCES += SurveyExportSmsSurvey.cpp \
    ../../../src/TreeItemProtocol.cpp \
	../../../src/AbstractTreeModel.cpp \
    ../../../src/TreeItem.cpp

INCLUDEPATH += ../../../include

HEADERS += SurveyExportSmsSurvey.h\
		plugin_export_smssurvey_global.h \
    ../../../include/AbstractTreeModel.h
	#../../../include/AbstractTreeModelVisitor.h \
	#../../../include/AbstractTreeModelVisitor.h \

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
