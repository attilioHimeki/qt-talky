#include "MouseLinkView.h"
#include "NodeView.h"

MouseLinkView::MouseLinkView(GraphWidget *graphWidget)
    :LinkView (graphWidget)
{
}


void MouseLinkView::setSource(NodeView* s)
{
    source = s;
}

void MouseLinkView::adjust()
{
    if(source != Q_NULLPTR)
    {
        auto mousePos = graph->mapToScene(graph->mapFromGlobal(QCursor::pos()));
        destPoint = mousePos;

        sourcePoint = source->getEdgesOutputPoint();

        prepareGeometryChange();
    }
}
