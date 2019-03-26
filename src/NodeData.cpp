#include "NodeData.h"

NodeData::NodeData(NodeType t, int id)
    :type(t), nodeId(id)
{
}

int NodeData::getNodeId() const
{
    return nodeId;
}

void NodeData::write(QJsonObject &json) const
{
    QJsonArray linksArray;
    foreach (const NodeLink* link, linkedNodes) {
          QJsonObject nodeLinkObject;
          link->write(nodeLinkObject);
          linksArray.append(nodeLinkObject);
    }
    json["links"] = linksArray;

    json["nodeId"] = nodeId;
    json["nodeType"] = getStringFromNodeType(type);

}

void NodeData::read(const QJsonObject &json)
{
    auto nodeTypeString = json["nodeType"].toString();
    type = getNodeTypeFromString(nodeTypeString);

    nodeId = json["nodeId"].toInt();

    auto startX = json["x"].toInt();
    auto startY = json["y"].toInt();

    QPoint pos(startX, startY);
    startPos = pos;

    linkedNodes.clear();

    if(json.contains("links") && json["links"].isArray())
    {
        QJsonArray linksArray = json["links"].toArray();

        auto linksAmount = linksArray.size();

        for (int linkIndex = 0; linkIndex < linksAmount; ++linkIndex)
        {
            QJsonObject linkObject = linksArray[linkIndex].toObject();
            NodeLink* link = new NodeLink();
            link->read(linkObject);
            linkedNodes.append(link);
        }
    }

}

void NodeData::addLinkedNode(int linkedNodeId)
{
    NodeLink* link = new NodeLink(linkedNodeId);
    linkedNodes.append(link);
}

void NodeData::removeLinkedNode(int linkedNodeId)
{
    for(auto link : linkedNodes)
    {
        if(link->getLinkedNodeId() == linkedNodeId)
        {
            linkedNodes.removeOne(link);
            break;
        }
    }
}
