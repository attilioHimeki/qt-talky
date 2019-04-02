#ifndef CHOICENODE_H
#define CHOICENODE_H

#include "Node.h"
#include "ChoiceNodeEntry.h"

class ChoiceNode : public Node
{
public:
    ChoiceNode(NodeData* data);
    ~ChoiceNode() override = default;

    void setupView(GraphWidget *graphWidget) override;

    bool validateAddNode(const Node& linkedNode) const override;

private:
    QList<ChoiceNodeEntry*> choices;

public slots:
    void addChoiceEntry();
    void removeChoiceEntry(int index);
};

#endif // CHOICENODE_H
