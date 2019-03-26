#include "OriginNodeView.h"

OriginNodeView::OriginNodeView(Node* ownerNode, GraphWidget *graphWidget)
    :NodeView(ownerNode, graphWidget)
{
}

void OriginNodeView::populateContextualMenu(QMenu& menu)
{
    NodeView::populateContextualMenu(menu);
}
