#include "NodeLinkView.h"
#include "NodeView.h"

#include <qmath.h>
#include <QPainter>

NodeLinkView::NodeLinkView(GraphWidget *graphWidget, const NodeView& sourceNode, const NodeView& destNode)
    : LinkView(graphWidget), source(sourceNode), destination(destNode)
{
    adjust();
}

void NodeLinkView::adjust()
{
    QLineF line(source.getEdgesOutputPoint(), destination.getEdgesInputPoint());
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.))
    {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    }
    else
    {
        sourcePoint = destPoint = line.p1();
    }
}

bool NodeLinkView::isLinkedWith(NodeView& node) const
{
    return &source == &node ||
            &destination == &node;
}
