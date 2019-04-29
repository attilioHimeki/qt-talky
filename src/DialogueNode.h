#ifndef DIALOGUENODE_H
#define DIALOGUENODE_H

#include "Node.h"

class DialogueNode : public Node
{
public:
    DialogueNode(NodeData* data);
    ~DialogueNode() override = default;

    void setupView(GraphWidget *graphWidget) override;

    bool validateAddNode(const Node& linkedNode) const override;

public slots:
    void onNodeTextKeyChanged(const QString& key);

private:
    static const QString DIALOGUE_KEY_PARAM;
};

#endif // DIALOGUENODE_H
