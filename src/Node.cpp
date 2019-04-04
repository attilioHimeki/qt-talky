#include "Node.h"

Node::Node(NodeData* data)
    :model(data)
{
}

void Node::setupView(GraphWidget *graphWidget)
{
     auto startPos = model->startPos;
     view->setPos(startPos.x(), startPos.y());

     view->setupTypeLabel(model->type);
     view->setupIdLabel(model->getNodeId());

     view->setupContextualMenuSignals();
}

NodeView* Node::getView()
{
    return view.get();
}

QList<NodeLink*> Node::getLinkedNodes() const
{
    return model->linkedNodes;
}

void Node::write(QJsonObject &json) const
{
    model->write(json);
}

void Node::read(const QJsonObject &json)
{
    model->read(json);
}

void Node::addLinkedNode(int linkedNodeId)
{
    model->addLinkedNode(linkedNodeId);
}

void Node::removeLinkedNode(int linkedNodeId)
{
    model->removeLinkedNode(linkedNodeId);
}

int Node::getNodeId() const
{
    return model->getNodeId();
}

NodeType Node::getNodeType() const
{
    return model->type;
}

const QPoint Node::getStartPosition() const
{
    return model->startPos;
}

bool Node::validateAddNode(const Node& linkedNode) const
{
    return !model->isLinkedWith(linkedNode.getNodeId()) && allowedNodeLinkTypes.contains(linkedNode.getNodeType());
}
