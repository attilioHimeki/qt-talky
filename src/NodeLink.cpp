#include "NodeLink.h"

#include <QJsonObject>

NodeLink::NodeLink()
{

}

NodeLink::NodeLink(int linkedId)
    :linkedNodeId(linkedId)
{

}

void NodeLink::write(QJsonObject &json) const
{
    json["nodeId"] = linkedNodeId;
}

void NodeLink::read(const QJsonObject &json)
{
    if(json.contains("nodeId"))
    {
        linkedNodeId = json["nodeId"].toInt();
    }
}

int NodeLink::getLinkedNodeId() const
{
    return linkedNodeId;
}
