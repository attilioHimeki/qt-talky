#include "Node.h"

Node::Node(NodeData* data)
    :model(data)
{
}

void Node::setupView(GraphWidget *graphWidget)
{
     auto startPos = model->getSerialisedGraphPosition();
     view->setPos(startPos);

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
    model->refreshSerialisedGraphPosition(view->pos());
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

bool Node::isLinkedWith(int linkedNodeId) const
{
    return model->isLinkedWith(linkedNodeId);
}

int Node::getLinkedNodesCount() const
{
    return model->linkedNodes.count();
}

int Node::getNodeId() const
{
    return model->getNodeId();
}

NodeType Node::getNodeType() const
{
    return model->type;
}

const QPointF Node::getCurrentGraphPosition() const
{
    return view->pos();
}

const QPointF Node::getSerialisedGraphPosition() const
{
    return model->getSerialisedGraphPosition();
}
