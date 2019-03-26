#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T23:55:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = talky
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
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
    src/DialogueNodeView.h \
    src/OriginNodeView.h \
    src/NodeLinkView.h \
    src/DialogueNodeData.h \
    src/DialogueNode.h \
    src/OriginNode.h \
    src/NodeBuilder.h \
    src/ChoiceNode.h \
    src/ChoiceNodeEntry.h \
    src/ChoiceNodeView.h \
    src/ChoiceNodeData.h

SOURCES += \
    src/main.cpp \
    src/OriginNodeView.cpp \
    src/NodeLinkView.cpp \
    src/NodeData.cpp \
    src/Node.cpp \
    src/GraphWidget.cpp \
    src/NodeView.cpp \
    src/EditorWindow.cpp \
    src/DialogueTree.cpp \
    src/NodeLink.cpp \
    src/DialogueNodeView.cpp \
    src/DialogueNodeData.cpp \
    src/NodeLinkCondition.cpp \
    src/DialogueNode.cpp \
    src/OriginNode.cpp \
    src/NodeBuilder.cpp \
    src/ChoiceNode.cpp \
    src/ChoiceNodeEntry.cpp \
    src/ChoiceNodeView.cpp \
    src/ChoiceNodeData.cpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
