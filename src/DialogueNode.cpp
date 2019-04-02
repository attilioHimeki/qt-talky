#include "DialogueNode.h"


DialogueNode::DialogueNode(DialogueNodeData* data)
    : Node(data)
{
}

void DialogueNode::setupView(GraphWidget *graphWidget)
{
    DialogueNodeView* dialogueView = new DialogueNodeView(this, graphWidget);
    view = std::unique_ptr<DialogueNodeView>(dialogueView);

    DialogueNodeData* dialogueData = dynamic_cast<DialogueNodeData*>(model.get());

    dialogueView->setKeyText(dialogueData->getNodeTextKey());

    QObject::connect(dialogueView->keyTextField, &QLineEdit::textChanged, this, &DialogueNode::onNodeTextKeyChanged);

    Node::setupView(graphWidget);
}

void DialogueNode::onNodeTextKeyChanged(const QString& key)
{
    DialogueNodeData* dialogueData = dynamic_cast<DialogueNodeData*>(model.get());
    dialogueData->setNodeTextKey(key);

    emit nodeChanged();
}

bool DialogueNode::validateAddNode(const Node& linkedNode) const
{
    auto linksAmount = model->linkedNodes.count();
    return linksAmount < 1 && linkedNode.getNodeType() != NodeType::Origin;
}
