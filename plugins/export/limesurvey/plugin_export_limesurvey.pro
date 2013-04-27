#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T13:11:57
#
#-------------------------------------------------

QT       += xml

TARGET = plugin_export_limesurvey
TEMPLATE = lib
TARGET        = $$qtLibraryTarget(plugin_export_limesurvey)
DESTDIR       = ../../../bin/plugins/export

DEFINES += PLUGIN_EXPORT_LIMESURVEY_LIBRARY

SOURCES += SurveyExportLimeSurvey.cpp

INCLUDEPATH += ../../../include

HEADERS += SurveyExportLimeSurvey.h\
		plugin_export_limesurvey_global.h
	#../../../include/AbstractTreeModelVisitor.h \
	#../../../include/AbstractTreeModelVisitor.h \

symbian {
    #Symbian specific definitions
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE377CC87
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = plugin_export_limesurvey.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
