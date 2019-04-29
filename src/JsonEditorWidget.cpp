#include "JsonEditorWidget.h"

#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

JsonEditorWidget::JsonEditorWidget(QWidget *parent)
    : QPlainTextEdit(parent)
{
    setReadOnly(true);
}

void JsonEditorWidget::applyLoadedTreeJsonFile(const QJsonObject& treeFileJson)
{
    QJsonDocument doc(treeFileJson);
    QString strJson(doc.toJson(QJsonDocument::Indented));
    setPlainText(strJson);
}
