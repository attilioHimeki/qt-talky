#include "NodeLinkView.h"
#include "NodeView.h"

#include <qmath.h>
#include <QPainter>

NodeLinkView::NodeLinkView(const NodeView& sourceNode, const NodeView& destNode)
    : source(sourceNode), destination(destNode)
{
    setAcceptedMouseButtons(Q_NULLPTR);

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

QRectF NodeLinkView::boundingRect() const
{
    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void NodeLinkView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
    {
        return;
    }

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    double angle = std::atan2(-line.dy(), line.dx());

    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
