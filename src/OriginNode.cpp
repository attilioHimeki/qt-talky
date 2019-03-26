#include "OriginNode.h"

OriginNode::OriginNode(NodeData* data)
    : Node(data)
{
}

void OriginNode::setupView(GraphWidget *graphWidget)
{
    view = std::make_unique<OriginNodeView>(this, graphWidget);

    Node::setupView(graphWidget);
}
