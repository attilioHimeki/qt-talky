#include "OriginNode.h"

OriginNode::OriginNode(NodeData* data)
    : Node(data)
{
}

void OriginNode::setupView(GraphWidget *graphWidget)
{
    view = std::make_unique<NodeView>(this, graphWidget);

    Node::setupView(graphWidget);
}

bool OriginNode::validateAddNode(const Node& linkedNode) const
{
    auto linksAmount = model->linkedNodes.count();
    return linksAmount < 1;
}
