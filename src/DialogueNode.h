#ifndef DIALOGUENODE_H
#define DIALOGUENODE_H

#include "Node.h"

class DialogueNode : public Node
{
public:
    DialogueNode(NodeData* data);
    ~DialogueNode() override = default;

    void setupView(GraphWidget *graphWidget) override;

public slots:
    void onDialogueTextKeyChanged(const QString& key);
    void onSpeakerTextKeyChanged(const QString& key);

private:
    static const QString DIALOGUE_KEY_PARAM;
    static const QString SPEAKER_KEY_PARAM;
};

#endif // DIALOGUENODE_H
