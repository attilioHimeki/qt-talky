#include "ChoiceNode.h"

ChoiceNode::ChoiceNode(NodeData* data)
    : Node(data)
{
}

void ChoiceNode::setupView(GraphWidget *graphWidget)
{
    view = std::make_unique<NodeView>(this, graphWidget);

    Node::setupView(graphWidget);
}
