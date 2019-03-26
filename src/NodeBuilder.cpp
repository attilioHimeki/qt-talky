#include "NodeBuilder.h"

Node* NodeBuilder::create(NodeType type, int id)
{
    switch(type)
    {
        case NodeType::Dialogue:
        {
            return createDialogueNode(id);
        }
        case NodeType::Origin:
        {
            return createOriginNode(id);
        }
        case NodeType::Choice:
        {
            return createChoiceNode(id);
        }
        default:
        {
            return createOriginNode(id);
        }
    }
}

Node* NodeBuilder::create(QJsonObject json)
{
    auto nodeTypeString = json["nodeType"].toString();
    auto type = getNodeTypeFromString(nodeTypeString);

    switch(type)
    {
        case NodeType::Dialogue:
        {
            return createDialogueNode(json);
        }
        case NodeType::Origin:
        {
            return createOriginNode(json);
        }
        default:
        {
            return createOriginNode(json);
        }
    }
}

DialogueNode* NodeBuilder::createDialogueNode(int id)
{
    auto nodeData = new DialogueNodeData(id);
    auto node = new DialogueNode(nodeData);
    return node;
}

DialogueNode* NodeBuilder::createDialogueNode(QJsonObject json)
{
    auto id = json["nodeId"].toInt();
    DialogueNodeData* nodeData = new DialogueNodeData(id);
    nodeData->read(json);

    auto node = new DialogueNode(nodeData);
    return node;
}

OriginNode* NodeBuilder::createOriginNode(int id)
{
    NodeData* nodeData = new NodeData(NodeType::Origin, id);
    auto node = new OriginNode(nodeData);
    return node;
}

OriginNode* NodeBuilder::createOriginNode(QJsonObject json)
{
    auto id = json["nodeId"].toInt();
    NodeData* nodeData = new NodeData(NodeType::Origin, id);
    nodeData->read(json);

    auto node = new OriginNode(nodeData);
    return node;
}

ChoiceNode* NodeBuilder::createChoiceNode(int id)
{
    NodeData* nodeData = new NodeData(NodeType::Choice, id);
    auto node = new ChoiceNode(nodeData);
    return node;
}

ChoiceNode* NodeBuilder::createChoiceNode(QJsonObject json)
{
    auto id = json["nodeId"].toInt();
    NodeData* nodeData = new NodeData(NodeType::Choice, id);
    nodeData->read(json);

    auto node = new ChoiceNode(nodeData);
    return node;
}
