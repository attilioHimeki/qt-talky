#ifndef DIALOGUENODE_H
#define DIALOGUENODE_H

#include "Node.h"

class DialogueNode : public Node
{
public:
    DialogueNode(DialogueNodeData* data);
    ~DialogueNode() override = default;

    void setupView(GraphWidget *graphWidget) override;

public slots:
    void onNodeTextKeyChanged(const QString& key);
};

#endif // DIALOGUENODE_H
