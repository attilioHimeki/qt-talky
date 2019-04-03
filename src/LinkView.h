#ifndef LINKVIEW_H
#define LINKVIEW_H

#include <QGraphicsItem>
#include "GraphWidget.h"

class LinkView : public QGraphicsItem
{

public:
    LinkView(GraphWidget *graphWidget);

    virtual void adjust() = 0;

protected:
    GraphWidget *graph;

    const qreal arrowSize = 10;
    QPointF sourcePoint;
    QPointF destPoint;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // LINKVIEW_H
