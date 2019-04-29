#ifndef JSONEDITORWIDGET_H
#define JSONEDITORWIDGET_H

#include <QPlainTextEdit>

class JsonEditorWidget : public QPlainTextEdit
{
public:
    JsonEditorWidget(QWidget *parent = Q_NULLPTR);

    void refresh(const QJsonDocument& treeFileJson);

};

#endif // JSONEDITORWIDGET_H
