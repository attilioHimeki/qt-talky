#include "JsonEditorWidget.h"

#include <QJsonDocument>

JsonEditorWidget::JsonEditorWidget(QWidget *parent)
    : QPlainTextEdit(parent)
{
    setReadOnly(true);
}

void JsonEditorWidget::refresh(const QJsonDocument& treeFileJson)
{
    QString strJson(treeFileJson.toJson(QJsonDocument::Indented));
    setPlainText(strJson);
}
