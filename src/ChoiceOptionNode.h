#ifndef CHOICEOPTIONNODE_H
#define CHOICEOPTIONNODE_H

#include "Node.h"

class ChoiceOptionNode : public Node
{
public:
    ChoiceOptionNode(NodeData* data);
    ~ChoiceOptionNode() override = default;

    void setupView(GraphWidget *graphWidget) override;

public slots:
    void onOptionTextKeyChanged(const QString& key);

private:
    static const QString CHOICE_KEY_PARAM;
};

#endif // CHOICEOPTIONNODE_H
