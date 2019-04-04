#include "OriginNode.h"

OriginNode::OriginNode(NodeData* data)
    : Node(data)
{
    allowedNodeLinkTypes.append(NodeType::Dialogue);
}

void OriginNode::setupView(GraphWidget *graphWidget)
{
    view = std::make_unique<OriginNodeView>(this, graphWidget);

    Node::setupView(graphWidget);
}

bool OriginNode::validateAddNode(const Node& linkedNode) const
{
    auto linksAmount = model->linkedNodes.count();
    return linksAmount < 1 && Node::validateAddNode(linkedNode);
}
