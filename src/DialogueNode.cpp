#include "DialogueNode.h"

const QString DialogueNode::DIALOGUE_KEY_PARAM = "dialogueKey";

DialogueNode::DialogueNode(NodeData* data)
    : Node(data)
{
}

void DialogueNode::setupView(GraphWidget *graphWidget)
{
    DialogueNodeView* dialogueView = new DialogueNodeView(this, graphWidget);
    view = std::unique_ptr<DialogueNodeView>(dialogueView);

    dialogueView->setKeyText(model->getCustomParameter(DIALOGUE_KEY_PARAM).toString());

    QObject::connect(dialogueView->keyTextField, &QLineEdit::textChanged, this, &DialogueNode::onNodeTextKeyChanged);

    Node::setupView(graphWidget);
}

void DialogueNode::onNodeTextKeyChanged(const QString& key)
{
    model->setCustomParameter(DIALOGUE_KEY_PARAM, key);

    emit nodeChanged();
}
