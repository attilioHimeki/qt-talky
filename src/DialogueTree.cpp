#include "DialogueTree.h"

DialogueTree::DialogueTree()
    :nextNodeId(0)
{
    allowedConnectionsScheme.insert(NodeType::Origin, NodeType::Dialogue);
    allowedConnectionsScheme.insert(NodeType::Dialogue, NodeType::Dialogue);
    allowedConnectionsScheme.insert(NodeType::Dialogue, NodeType::Choice);
    allowedConnectionsScheme.insert(NodeType::Choice, NodeType::ChoiceOption);
    allowedConnectionsScheme.insert(NodeType::ChoiceOption, NodeType::Dialogue);
}

Node* DialogueTree::createNode(NodeType type, QPointF pos)
{
    auto node = NodeBuilder::create(type, nextNodeId++, pos);
    nodes.append(node);

    emit nodeAdded(node);
    emit contentChanged();

    return originNode;
}

Node* DialogueTree::createOriginNode(QPointF pos)
{
    auto node = createNode(NodeType::Origin, pos);
    originNode = node;
    return originNode;
}

Node* DialogueTree::cloneNode(const Node &node)
{
    QJsonObject nodeObject;
    node.write(nodeObject);
    auto clone = NodeBuilder::create(nodeObject, nextNodeId++);

    nodes.append(clone);

    emit nodeAdded(clone);
    emit contentChanged();

    return clone;
}

Node* DialogueTree::getNodeById(int nodeId) const
{
    for(Node* n : nodes)
    {
        if(n->getNodeId() == nodeId)
        {
            return n;
        }
    }

    return Q_NULLPTR;
}

bool DialogueTree::addNodeLink(Node* startNode, Node* endNode)
{
    if(isNodeLinkLegal(startNode->getNodeType(), endNode->getNodeType()) &&
        startNode->validateAddNode(*endNode))
    {
        startNode->addLinkedNode(endNode->getNodeId());

        emit linkAdded(startNode, endNode);
        emit contentChanged();

        return true;
    }
    return false;
}

bool DialogueTree::isNodeLinkLegal(const NodeType startNodeType, const NodeType endNodeType) const
{
    return allowedConnectionsScheme.contains(startNodeType, endNodeType) ||
            allowedConnectionsScheme.contains(startNodeType, NodeType::Any);
}

void DialogueTree::write(QJsonObject &json) const
{
    QJsonArray nodesArray;
    for(Node* node : nodes)
    {
        QJsonObject nodeObject;
        node->write(nodeObject);
        nodesArray.append(nodeObject);
    }
    json["nodes"] = nodesArray;
}

void DialogueTree::read(const QJsonObject &json)
{
    clearTree();

    if(json.contains("nodes") && json["nodes"].isArray())
    {
        QJsonArray nodesArray = json["nodes"].toArray();

        auto nodesAmount = nodesArray.size();

        for (int nodeIndex = 0; nodeIndex < nodesAmount; ++nodeIndex)
        {

            QJsonObject nodeObject = nodesArray[nodeIndex].toObject();

            auto node = NodeBuilder::create(nodeObject);
            connect(node, &Node::nodeChanged, this, &DialogueTree::contentChanged);

            nodes.append(node);

            if(node->getNodeId() >= nextNodeId)
            {
                nextNodeId = node->getNodeId() + 1;
            }
        }
    }

    treeName = json.value("name").toString();
}

Node* DialogueTree::createDialogueNode(QPointF pos)
{
    return createNode(NodeType::Dialogue, pos);
}

Node* DialogueTree::createChoiceNode(QPointF pos)
{
    return createNode(NodeType::Choice, pos);
}

Node* DialogueTree::createChoiceOptionNode(QPointF pos)
{
    return createNode(NodeType::ChoiceOption, pos);
}

void DialogueTree::deleteNode(Node* node)
{
    for(auto n : nodes)
    {
        if(n->isLinkedWith(node->getNodeId()))
        {
            n->removeLinkedNode(node->getNodeId());
        }
    }

    nodes.removeOne(node);

    node->disconnect();
    node->getView()->disconnect();

    emit contentChanged();

    delete node;
}

void DialogueTree::clearTree()
{
    for(auto node : nodes)
    {
        node->disconnect();
        node->getView()->disconnect();
        delete node;
    }
    nodes.clear();

    emit contentChanged();

    nextNodeId = 0;
}
