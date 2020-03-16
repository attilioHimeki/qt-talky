#include "NodeBuilder.h"

Node* NodeBuilder::create(NodeType type, int id, QPointF pos)
{
    switch(type)
    {
        case NodeType::Dialogue:
        {
            return createGenericNode<DialogueNode>(type, id, pos);
        }
        case NodeType::ChoiceOption:
        {
            return createGenericNode<ChoiceOptionNode>(type, id, pos);
        }
        default:
        {
            return createGenericNode<Node>(type, id, pos);
        }
    }
}

Node* NodeBuilder::create(QJsonObject json, int id)
{
    auto nodeTypeString = json["nodeType"].toString();
    auto type = getNodeTypeFromString(nodeTypeString);

    if(id == -1)
    {
        id = json["nodeId"].toInt();
    }

    switch(type)
    {
        case NodeType::Dialogue:
        {
            return createGenericNode<DialogueNode>(json, id);
        }
        case NodeType::ChoiceOption:
        {
            return createGenericNode<ChoiceOptionNode>(json, id);
        }
        default:
        {
            return createGenericNode<Node>(json, id);
        }
    }
}

template<typename T>
T* NodeBuilder::createGenericNode(NodeType type, int id, QPointF pos)
{
    NodeData* nodeData = new NodeData(type, id);
    nodeData->refreshSerialisedGraphPosition(pos);
    auto node = new T(nodeData);
    return node;
}

template<typename T>
T* NodeBuilder::createGenericNode(QJsonObject json, int id)
{
    NodeData* nodeData = new NodeData(NodeType::None, id);
    nodeData->read(json);

    auto node = new T(nodeData);
    return node;
}
