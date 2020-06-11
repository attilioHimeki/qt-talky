#include "DialogueNode.h"

const QString DialogueNode::DIALOGUE_KEY_PARAM = "dialogueKey";
const QString DialogueNode::SPEAKER_KEY_PARAM = "speakerKey";

DialogueNode::DialogueNode(NodeData* data)
    : Node(data)
{
}

void DialogueNode::setupView(GraphWidget *graphWidget)
{
    Node::setupView(graphWidget);

    view->setupPropertyTextField(SPEAKER_KEY_PARAM, SPEAKER_KEY_PARAM,"Insert speaker key",
                                 QPointF(10, 8), model->getCustomParameter(SPEAKER_KEY_PARAM, "").toString());
    view->setupPropertyTextField(DIALOGUE_KEY_PARAM, DIALOGUE_KEY_PARAM, "Insert dialogue key",
                                 QPointF(10, 50), model->getCustomParameter(DIALOGUE_KEY_PARAM, "").toString());


    QObject::connect(view->getPropertyTextHandle(DIALOGUE_KEY_PARAM), &QLineEdit::textEdited, this, &DialogueNode::onDialogueTextKeyChanged);
    QObject::connect(view->getPropertyTextHandle(SPEAKER_KEY_PARAM), &QLineEdit::textEdited, this, &DialogueNode::onSpeakerTextKeyChanged);
}

void DialogueNode::onDialogueTextKeyChanged(const QString& key)
{
    model->setCustomParameter(DIALOGUE_KEY_PARAM, key);

    emit nodeChanged();
}


void DialogueNode::onSpeakerTextKeyChanged(const QString& key)
{
    model->setCustomParameter(SPEAKER_KEY_PARAM, key);

    emit nodeChanged();
}
