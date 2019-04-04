#ifndef CHOICENODE_H
#define CHOICENODE_H

#include "Node.h"

class ChoiceNode : public Node
{
public:
    ChoiceNode(NodeData* data);
    ~ChoiceNode() override = default;

    void setupView(GraphWidget *graphWidget) override;
};

#endif // CHOICENODE_H
