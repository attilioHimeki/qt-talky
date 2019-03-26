#include "ChoiceNode.h"
#include "ChoiceNodeView.h"

ChoiceNode::ChoiceNode(NodeData* data)
    : Node(data)
{
}

void ChoiceNode::setupView(GraphWidget *graphWidget)
{
    view = std::make_unique<ChoiceNodeView>(this, graphWidget);

    Node::setupView(graphWidget);
}

void ChoiceNode::addChoiceEntry()
{

}

void ChoiceNode::removeChoiceEntry(int index)
{

}
