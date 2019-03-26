#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QLabel>
#include <QMenu>

#include "NodeType.h"

class Node;
class NodeLinkView;
class GraphWidget;

class NodeView : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    NodeView(Node* ownerNode, GraphWidget *graphWidget);

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    void setupTypeLabel(NodeType type);
    void setupIdLabel(int nodeId);

    QPointF getEdgesInputPoint() const;
    QPointF getEdgesOutputPoint() const;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void populateContextualMenu(QMenu& menu);
    virtual void setupContextualMenuSignals();

    Node* getOwner() const;

signals:
    void onNodeDeletePressed(Node* owner);
    void onNodeClonePressed(Node* owner);
    void onNodeAddTransitionPressed(Node* owner);
    void onNodeMoved(Node* owner);

private slots:
     void deleteNode();
     void cloneNode();
     void addNodeTransition();

protected:
    GraphWidget *graph;

    Node* owner;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    const int nodeWidth = 150;
    const int nodeHeight = 50;

private:
    QLabel* typeLabel;
    QLabel* idLabel;
};


#endif // NODEVIEW_H
