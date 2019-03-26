#ifndef NODELINKVIEW_H
#define NODELINKVIEW_H

#include <QGraphicsItem>

class NodeView;

class NodeLinkView : public QGraphicsItem
{
public:
    NodeLinkView(const NodeView& sourceNode, const NodeView& destNode);

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void adjust();

    bool isLinkedWith(NodeView& node) const;

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    const qreal arrowSize = 10;

    QPointF sourcePoint;
    QPointF destPoint;

    const NodeView& source;
    const NodeView& destination;
};

#endif // NODELINKVIEW_H
