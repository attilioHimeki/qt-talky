#include "ChoiceNodeView.h"
#include "GraphWidget.h"

ChoiceNodeView::ChoiceNodeView(Node* ownerNode, GraphWidget *graphWidget)
    :NodeView(ownerNode, graphWidget)
{
}

void ChoiceNodeView::populateContextualMenu(QMenu& menu)
{
//    QAction* actionAddChoice = menu.addAction(tr("Add Choice"), dynamic_cast<ChoiceNode*>(owner), &ChoiceNode::addChoiceEntry);
//    actionAddChoice->setStatusTip(tr("Create a new choice entry"));

    menu.addSeparator();

    NodeView::populateContextualMenu(menu);
}

void ChoiceNodeView::setupContextualMenuSignals()
{
    NodeView::setupContextualMenuSignals();
}
