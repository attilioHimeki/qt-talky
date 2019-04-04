#ifndef CHOICEOPTIONNODE_H
#define CHOICEOPTIONNODE_H

#include "Node.h"

class ChoiceOptionNode : public Node
{
public:
    ChoiceOptionNode(NodeData* data);
    ~ChoiceOptionNode() override = default;

    void setupView(GraphWidget *graphWidget) override;
};

#endif // CHOICEOPTIONNODE_H
