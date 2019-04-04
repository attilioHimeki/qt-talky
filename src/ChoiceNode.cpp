#include "ChoiceNode.h"
#include "ChoiceNodeView.h"

ChoiceNode::ChoiceNode(NodeData* data)
    : Node(data)
{
    allowedNodeLinkTypes.append(NodeType::ChoiceOption);
}

void ChoiceNode::setupView(GraphWidget *graphWidget)
{
    view = std::make_unique<ChoiceNodeView>(this, graphWidget);

    Node::setupView(graphWidget);
}
