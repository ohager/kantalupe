#-------------------------------------------------
#
# Project created by QtCreator 2010-10-18T11:26:55
# and modified by O. Häger
#
#-------------------------------------------------

TEMPLATE = app
QT       += core gui xml script
CONFIG += qt release
CONFIG -= debug
DESTDIR = $$PWD

DEFINES += _VERMIN=1 _VERMAJ=0
LIBS += -L$$PWD/extern/xsde/lib/ -llibxsde

debug{
	message("--- DEBUG Build ---")
    DEFINES += _DEBUG	
	TARGET = ./bin/kantalupe_edit_debug
}

release{
	message("--- RELEASE Build ---")
    DEFINES += _RELEASE
	TARGET = ./bin/kantalupe_edit
}





INCLUDEPATH =     ./include \
    ./include/xrs \
	./include/thirdparty \
    ./extern/xsde/xrs \
    ./extern/xsde/include






SOURCES += main.cpp\
	src/global.cpp \
    src/MessageHandler.cpp \
    src/MainWindow.cpp \
    src/xrs/XrsObjectModel.cpp \
    src/xrs/XrsLoaderQt.cpp \
    src/xrs/XrsLoader2.cpp \
	src/TaskDialogButton.cpp \
	src/TaskDialog.cpp \
	src/Task.cpp \
    extern/xsde/xrs/xrs-pskel.cxx \
    extern/xsde/xrs/xrs-pimpl.cxx \
    extern/xsde/xrs/xrs.cxx \
    src/ImageFxFactory.cpp \
    src/WobblerWidget.cpp \
	src/UserModeEvent.cpp \
	src/DragStartedEvent.cpp \
	src/Drag.cpp \
	src/Application.cpp \
	src/AboutBox.cpp \
    src/WelcomeWidget.cpp \
	src/ItemEditor.cpp \
	src/Overlay.cpp \
	src/PlainTextEdit.cpp \
	src/ImageListWidget.cpp \
    src/WidgetExtension.cpp \
    src/DragStoppedEvent.cpp \
	src/ItemEditorCategoryPage.cpp\
	src/ItemEditorGroupPage.cpp\
	src/LineEdit.cpp \
	src/ItemEditorPropertiesPage.cpp \
	src/ItemEditorProposalPage.cpp \
    src/PropertyEditWidget.cpp \
	src/UidGenerator.cpp \
	src/UidGeneratorImpl.cpp \
	src/ProposalTreeWidget.cpp \
    src/WxListenerImageListWidget.cpp \
	src/ImageItem.cpp \
    src/ModelView.cpp \
	src/ModelEditor.cpp \
	src/ItemEditorMatrixPage.cpp \
	src/ItemEditorProblemPage.cpp \
	src/ItemEditorMatrixProblemPage.cpp \
	src/ItemEditorModelPage.cpp \
	src/VisitorGenerateHashUid.cpp \
	src/WritePolicyXml.cpp \
    src/WritePolicyXmlImpl_V1.cpp \
	src/ReadPolicyXml.cpp \
	src/ReadPolicyXmlImpl_V1.cpp \
	src/ShortMessage.cpp \
	src/ModelViewReadOnly.cpp \
    src/SurveyModelViewer.cpp \
    src/EditorBasePage.cpp \
    src/SurveyEditorScriptPage.cpp \
	src/SurveyEditorGeneratorPage.cpp \
	src/ModalLabel.cpp \
	src/SurveyView.cpp \
	src/DragUtility.cpp \
    src/AbstractTreeModel.cpp \
    src/TreeItem.cpp \
    src/TreeItemProtocol.cpp \
    src/ModelTree.cpp \
    src/ModelTreeDelegate.cpp \
    src/ModelTreeItemFactory.cpp \
    src/SurveyTree.cpp \
    src/SurveyTreeDelegate.cpp \
    src/SurveyEditorMetaInfoPage.cpp \
    src/SurveyTreeItemFactory.cpp \
	src/TreeView.cpp \
    src/VisitorNumberCategories.cpp \
    src/SurveyEditorModelPage.cpp \
    src/SurveyDataEditor.cpp \
	src/SurveyEditor.cpp \
    src/WritePolicyBinaryImpl_V1.cpp \
    src/WritePolicyBinary.cpp \
    src/ReadPolicyBinaryImpl_V1.cpp \
    src/ReadPolicyBinary.cpp \
    src/ScriptHighlighter.cpp \
	src/ScriptEngine.cpp \
	src/ScriptSyntaxChecker.cpp \
	src/thirdparty/qscripthighlighter.cpp \
    src/ScriptHighlighterImpl.cpp \
    src/ScriptTextEdit.cpp \
    src/ScriptObjectTreeItem.cpp \
    src/ScriptConsoleEdit.cpp \
	src/ScriptInfoWidget.cpp \
    src/ScriptReaderWriter.cpp \
    src/ScriptEngineApiLevel_1.cpp \
    src/ScriptReaderImpl_V1.cpp \
    src/ScriptWriterImpl_V1.cpp \
    src/ScriptListLoaderThread.cpp \
    src/ScriptEngineAgent.cpp \
	src/GeneratorScriptView.cpp \
    src/AbstractEditor.cpp \
    src/SurveyExporter.cpp \
    src/SurveyExportSelector.cpp \
    src/PluginPool.cpp \
    src/WritePolicyQueXml.cpp \
    src/WritePolicyQueXmlImpl_V1.cpp


HEADERS  += \
    include/MessageHandler.h \
    include/MainWindow.h \
    include/xrs/XrsObjectModel.h \
    include/xrs/XrsLoaderQt.h \
    include/xrs/XrsLoader2.h \
	include/TaskDialogButton.h \
	include/TaskDialog.h \
    extern/xsde/xrs/xrs-pskel.hxx \
    extern/xsde/xrs/xrs-pimpl.hxx \
    extern/xsde/xrs/xrs.hxx \
    include/global.h \
    include/ImageFxFactory.h \
    include/WobblerWidget.h \
	include/UserModeEvent.h \
    include/Task.h \
    include/DragStartedEvent.h \
    include/Drag.h \
    include/Application.h \
    include/AboutBox.h \
    include/WelcomeWidget.h \
	include/ItemEditor.h \
    include/Overlay.h \
    include/PlainTextEdit.h \
    include/ImageListWidget.h \
    include/WidgetExtension.h \
    include/DragStoppedEvent.h \
    include/InterfaceEditorPage.h \
	include/ItemEditorCategoryPage.h \
	include/ItemEditorGroupPage.h \
	include/ItemEditorPropertiesPage.h \
	include/ItemEditorProposalPage.h \
	include/LineEdit.h \
    include/PropertyEditWidget.h \
    include/UidGenerator.h \
    include/UidGeneratorImpl.h \
    include/ProposalTreeWidget.h \
    include/WxListenerImageListWidget.h \
    include/ImageItem.h \
    include/ModelView.h \
    include/ModelEditor.h \
    include/ItemEditorMatrixPage.h \
    include/SignalBlocker.h \
	include/ItemEditorProblemPage.h \
	include/ItemEditorMatrixProblemPage.h \
    include/ProtocolTypes.h \
    include/ItemEditorModelPage.h \
    include/VisitorGenerateHashUid.h \
    include/WritePolicyXml.h \
    include/WritePolicyXmlImpl_V1.h \
	include/ReadPolicyXml.h \
	include/ReadPolicyXmlImpl_V1.h \
    include/ShortMessage.h \
    include/ModelViewReadOnly.h \
    include/SurveyModelViewer.h \
    include/EditorBasePage.h \
    include/SurveyEditorScriptPage.h \
	include/SurveyEditorGeneratorPage.h \
	include/ModalLabel.h \
    include/SurveyView.h \
    include/DragUtility.h \
    include/ModelInsertionInterface.h \
    include/AbstractTreeModel.h \
    include/TreeItem.h \
    include/AbstractTreeModelVisitor.h \
    include/TreeItemProtocol.h \
    include/ModelTree.h \
    include/ModelTreeDelegate.h \
    include/ModelTreeItemFactory.h \
    include/SurveyTree.h \
    include/SurveyTreeDelegate.h \
    include/SurveyEditorMetaInfoPage.h \
    include/TreeItemFactory.h \
    include/SurveyTreeItemFactory.h \
    include/TreeView.h \
    include/ItemTypeCombination.h \
    include/VisitorNumberCategories.h \
    include/SurveyEditorModelPage.h \
    include/SurveyDataEditor.h \
    include/SurveyEditor.h \
    include/WritePolicyBinaryImpl_V1.h \
    include/WritePolicyBinary.h \
    include/ReadPolicyBinaryImpl_V1.h \
    include/ReadPolicyBinary.h \
    include/ScriptHighlighter.h \
    include/ScriptEngine.h \
    include/ScriptSyntaxChecker.h \
	include/ScriptHighlighterImpl.h \
	include/thirdparty/qscripthighlighter_p.h \
    include/ScriptTextEdit.h \
    include/ScriptObjectSurvey.h \
	include/ScriptObjectTreeItem.h \
	include/ScriptConsoleEdit.h \
    include/ScriptInfoWidget.h \
    include/Script.h \
    include/ScriptReaderWriter.h \
    include/ScriptEngineApiLevel_1.h \
    include/AbstractScriptEngineApi.h \
    include/ScriptReaderImpl_V1.h \
    include/ScriptWriterImpl_V1.h \
    include/ScriptListLoaderThread.h \
    include/ScriptEngineAgent.h \
    include/GeneratorScriptView.h \
    include/AbstractEditor.h \
    include/SurveyExporter.h \
    include/SurveyExportSelector.h \
    include/PluginPool.h \
    include/PluginInterface.h \
    include/WritePolicyQueXml.h \
    include/WritePolicyQueXmlImpl_V1.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    resources/kantalupe.xrs \
    resources/kantalupe.qss \
    models.xml \
    resources/survey.xml
