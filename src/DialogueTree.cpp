#include "DialogueTree.h"

DialogueTree::DialogueTree()
    :nextNodeId(0)
{
    nodes = QList<Node*>();
}

Node* DialogueTree::createOriginNode()
{
    auto node = NodeBuilder::create(NodeType::Origin, nextNodeId++);
    originNode = node;
    nodes.append(node);

    emit contentChanged();

    return originNode;
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

void DialogueTree::addNodeLink(Node* startNode, Node* endNode)
{
    startNode->addLinkedNode(endNode->getNodeId());

    emit contentChanged();
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

Node* DialogueTree::createDialogueNode()
{
    auto node = NodeBuilder::create(NodeType::Dialogue, nextNodeId++);
    nodes.append(node);
    connect(node, &Node::nodeChanged, this, &DialogueTree::contentChanged);

    emit contentChanged();

    return node;
}

Node* DialogueTree::createChoiceNode()
{
    auto node = NodeBuilder::create(NodeType::Choice, nextNodeId++);
    nodes.append(node);
    connect(node, &Node::nodeChanged, this, &DialogueTree::contentChanged);

    emit contentChanged();

    return node;
}

void DialogueTree::deleteNode(Node* node)
{
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
