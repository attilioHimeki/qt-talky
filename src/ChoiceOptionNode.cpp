#include "ChoiceOptionNode.h"

const QString ChoiceOptionNode::CHOICE_KEY_PARAM = "choiceKey";

ChoiceOptionNode::ChoiceOptionNode(NodeData* data)
    : Node(data)
{
}

void ChoiceOptionNode::setupView(GraphWidget *graphWidget)
{
    Node::setupView(graphWidget);

    view->setupPropertyTextField(CHOICE_KEY_PARAM, CHOICE_KEY_PARAM, "Insert choice key",
                                 QPointF(10, 15), model->getCustomParameter(CHOICE_KEY_PARAM, "").toString());

    QObject::connect(view->getPropertyTextHandle(CHOICE_KEY_PARAM), &QLineEdit::textChanged, this, &ChoiceOptionNode::onOptionTextKeyChanged);
}

void ChoiceOptionNode::onOptionTextKeyChanged(const QString& key)
{
    model->setCustomParameter(CHOICE_KEY_PARAM, key);

    emit nodeChanged();
}
