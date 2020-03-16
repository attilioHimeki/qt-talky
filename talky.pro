#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T23:55:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = talky
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14


HEADERS += \
    src/NodeView.h \
    src/NodeType.h \
    src/NodeLinkCondition.h \
    src/NodeLink.h \
    src/NodeData.h \
    src/Node.h \
    src/GraphWidget.h \
    src/EditorWindow.h \
    src/DialogueTree.h \
    src/NodeLinkView.h \
    src/DialogueNode.h \
    src/NodeBuilder.h \
    src/SettingsDialog.h \
    src/SettingsGeneralTab.h \
    src/SettingsLanguageTab.h \
    src/MouseLinkView.h \
    src/LinkView.h \
    src/ChoiceOptionNode.h \
    src/JsonEditorWidget.h

SOURCES += \
    src/main.cpp \
    src/NodeLinkView.cpp \
    src/NodeData.cpp \
    src/Node.cpp \
    src/GraphWidget.cpp \
    src/NodeView.cpp \
    src/EditorWindow.cpp \
    src/DialogueTree.cpp \
    src/NodeLink.cpp \
    src/NodeLinkCondition.cpp \
    src/DialogueNode.cpp \
    src/NodeBuilder.cpp \
    src/SettingsDialog.cpp \
    src/SettingsGeneralTab.cpp \
    src/SettingsLanguageTab.cpp \
    src/MouseLinkView.cpp \
    src/LinkView.cpp \
    src/ChoiceOptionNode.cpp \
    src/JsonEditorWidget.cpp

TRANSLATIONS += res/languages/talky_en.ts \
                res/languages/talky_it.ts \

OTHER_FILES += res/languages/talky_en.ts \
                res/languages/talky_it.ts \

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/resources.qrc
