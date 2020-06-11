#include "DialogueTree.h"

DialogueTree::DialogueTree()
    :nextNodeId(0)
{
    allowedConnectionsScheme.insert(NodeType::Origin, NodeType::Dialogue);
    allowedConnectionsScheme.insert(NodeType::Origin, NodeType::RandomLink);
    allowedConnectionsScheme.insert(NodeType::Dialogue, NodeType::Dialogue);
    allowedConnectionsScheme.insert(NodeType::Dialogue, NodeType::Choice);
    allowedConnectionsScheme.insert(NodeType::Choice, NodeType::ChoiceOption);
    allowedConnectionsScheme.insert(NodeType::ChoiceOption, NodeType::Dialogue);
    allowedConnectionsScheme.insert(NodeType::RandomLink, NodeType::Dialogue);
    allowedConnectionsScheme.insert(NodeType::RandomLink, NodeType::Choice);

    maximumLinkPerNodeType.insert(NodeType::Origin, 1);
    maximumLinkPerNodeType.insert(NodeType::Dialogue, 1);
    maximumLinkPerNodeType.insert(NodeType::Choice, std::numeric_limits<int>::max());
    maximumLinkPerNodeType.insert(NodeType::ChoiceOption, 1);
    maximumLinkPerNodeType.insert(NodeType::RandomLink, std::numeric_limits<int>::max());
}

Node* DialogueTree::createNode(NodeType type, QPointF pos)
{
    auto node = NodeBuilder::create(type, nextNodeId++, pos);
    connect(node, &Node::nodeChanged, this, &DialogueTree::contentChanged);
    nodes.append(node);

    emit nodeAdded(node);
    emit contentChanged();

    return node;
}

Node* DialogueTree::cloneNode(const Node &node)
{
    QJsonObject nodeObject;
    node.write(nodeObject);
    auto clone = NodeBuilder::create(nodeObject, nextNodeId++);
    connect(clone, &Node::nodeChanged, this, &DialogueTree::contentChanged);

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

NodeLinkResponse DialogueTree::addNodeLink(Node* startNode, Node* endNode)
{
    if(startNode == endNode)
    {
        return NodeLinkResponse::FailLinkItself;
    }
    else if(startNode->isLinkedWith(endNode->getNodeId()))
    {
        return NodeLinkResponse::FailAlreadyLinked;
    }
    else if(!isNodeLinkLegal(startNode->getNodeType(), endNode->getNodeType()))
    {
        return NodeLinkResponse::FailIncompatibleType;
    }
    else if(!canAddMoreLinksToNode(startNode))
    {
        return NodeLinkResponse::FailTooManyLinks;
    }
    else
    {
        startNode->addLinkedNode(endNode->getNodeId());

        emit linkAdded(startNode, endNode);
        emit contentChanged();

        return NodeLinkResponse::Success;
    }
}

bool DialogueTree::isNodeLinkLegal(const NodeType startNodeType, const NodeType endNodeType) const
{
    return allowedConnectionsScheme.contains(startNodeType, endNodeType) ||
            allowedConnectionsScheme.contains(startNodeType, NodeType::Any);
}

bool DialogueTree::canAddMoreLinksToNode(const Node* node) const
{
    return node->getLinkedNodesCount() < maximumLinkPerNodeType.value(node->getNodeType());
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
