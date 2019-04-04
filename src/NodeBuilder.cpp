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
        case NodeType::ChoiceOption:
        {
            return createChoiceOptionNode(id);
        }
        default:
        {
            return createOriginNode(id);
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
            return createDialogueNode(json, id);
        }
        case NodeType::Origin:
        {
            return createOriginNode(json, id);
        }
        case NodeType::Choice:
        {
            return createChoiceNode(json, id);
        }
        case NodeType::ChoiceOption:
        {
            return createChoiceOptionNode(json, id);
        }
        default:
        {
            return createOriginNode(json, id);
        }
    }
}

DialogueNode* NodeBuilder::createDialogueNode(int id)
{
    auto nodeData = new DialogueNodeData(id);
    auto node = new DialogueNode(nodeData);
    return node;
}

DialogueNode* NodeBuilder::createDialogueNode(QJsonObject json, int id)
{
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

OriginNode* NodeBuilder::createOriginNode(QJsonObject json, int id)
{
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

ChoiceNode* NodeBuilder::createChoiceNode(QJsonObject json, int id)
{
    NodeData* nodeData = new NodeData(NodeType::Choice, id);
    nodeData->read(json);

    auto node = new ChoiceNode(nodeData);
    return node;
}

ChoiceOptionNode* NodeBuilder::createChoiceOptionNode(int id)
{
    NodeData* nodeData = new NodeData(NodeType::ChoiceOption, id);
    auto node = new ChoiceOptionNode(nodeData);
    return node;
}

ChoiceOptionNode* NodeBuilder::createChoiceOptionNode(QJsonObject json, int id)
{
    NodeData* nodeData = new NodeData(NodeType::ChoiceOption, id);
    nodeData->read(json);

    auto node = new ChoiceOptionNode(nodeData);
    return node;
}
