#include "DialogueNodeData.h"

DialogueNodeData::DialogueNodeData(int id)
    :NodeData (NodeType::Dialogue, id)
{
}

const QString DialogueNodeData::getNodeTextKey() const
{
    return textKey;
}

void DialogueNodeData::setNodeTextKey(const QString key)
{
    textKey = key;
}

void DialogueNodeData::write(QJsonObject &json) const
{
    json["textKey"] = textKey;

    NodeData::write(json);
}

void DialogueNodeData::read(const QJsonObject &json)
{
    textKey = json["textKey"].toString();

    NodeData::read(json);
}
