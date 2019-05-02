#include "NodeData.h"

NodeData::NodeData(NodeType t, int id)
    :type(t), nodeId(id)
{
}

NodeData::~NodeData()
{
    qDeleteAll(linkedNodes);
    linkedNodes.clear();
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

    json["x"] = serialisedGraphPosition.x();
    json["y"] = serialisedGraphPosition.y();

    QJsonObject customParams = QJsonObject::fromVariantMap(customParameters);
    json["customParams"] = customParams;
}

void NodeData::read(const QJsonObject &json, bool readId)
{
    auto nodeTypeString = json["nodeType"].toString();
    type = getNodeTypeFromString(nodeTypeString);

    if(readId)
    {
        nodeId = json["nodeId"].toInt();
    }

    auto startX = json["x"].toInt();
    auto startY = json["y"].toInt();

    QPointF pos(startX, startY);
    serialisedGraphPosition = pos;

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

    if(json.contains("customParams"))
    {
        auto customParams = json["customParams"].toObject();
        customParameters = customParams.toVariantMap();
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

bool NodeData::isLinkedWith(int nodeId) const
{
    for(auto link : linkedNodes)
    {
        if(link->getLinkedNodeId() == nodeId)
        {
            return true;
        }
    }
    return false;
}

QVariant NodeData::getCustomParameter(QString key) const
{
    return customParameters.value(key);
}

void NodeData::setCustomParameter(QString key, QVariant val)
{
    customParameters.insert(key, val);
}

bool NodeData::hasCustomParameter(QString key) const
{
    return customParameters.contains(key);
}

QPointF NodeData::getSerialisedGraphPosition() const
{
    return serialisedGraphPosition;
}

void NodeData::refreshSerialisedGraphPosition(QPointF pos)
{
    serialisedGraphPosition = pos;
}
