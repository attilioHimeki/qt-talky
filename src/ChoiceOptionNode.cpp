#include "ChoiceOptionNode.h"

ChoiceOptionNode::ChoiceOptionNode(NodeData* data)
    : Node(data)
{
}

void ChoiceOptionNode::setupView(GraphWidget *graphWidget)
{
    view = std::make_unique<NodeView>(this, graphWidget);

    Node::setupView(graphWidget);
}
