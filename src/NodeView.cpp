#include "NodeLinkView.h"
#include "NodeView.h"
#include "GraphWidget.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QLineEdit>
#include <QGraphicsProxyWidget>

NodeView::NodeView(Node* ownerNode, GraphWidget *graphWidget)
    : graph(graphWidget), owner(ownerNode)
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
}

Node* NodeView::getOwner() const
{
    return owner;
}


void NodeView::setupTypeLabel(NodeType type)
{
    typeLabel = new QLabel();
    auto typeText = getStringFromNodeType(type);
    typeLabel->setText(typeText);
    typeLabel->setAlignment(Qt::AlignVCenter);
    typeLabel->setStyleSheet("font: 12pt;background: transparent;  border: 0px; color: #111111");
    typeLabel->show();
    QGraphicsProxyWidget* pMyProxy = new QGraphicsProxyWidget(this);
    pMyProxy->setWidget(typeLabel);
    pMyProxy->setPos(-70, -40);
}

void NodeView::setupIdLabel(int nodeId)
{
    idLabel = new QLabel();
    QString text = QString("ID:%1").arg(nodeId);
    idLabel->setText(text);
    idLabel->setAlignment(Qt::AlignRight);
    idLabel->setStyleSheet("background: transparent;  border: 0px; color: #111111");
    idLabel->show();
    QGraphicsProxyWidget* pMyProxy = new QGraphicsProxyWidget(this);
    pMyProxy->setWidget(idLabel);
    pMyProxy->setPos(nodeWidth/3, -nodeHeight/2 - idLabel->height());
}

QRectF NodeView::boundingRect() const
{
    return QRectF(-nodeWidth/2, -nodeHeight/2, nodeWidth, nodeHeight);
}

QPainterPath NodeView::shape() const
{
    QPainterPath path;
    path.addRect(-nodeWidth/2, -nodeHeight/2, nodeWidth, nodeHeight);
    return path;
}

QPointF NodeView::getEdgesInputPoint() const
{
    auto nodePosition = pos();
    return QPointF(nodePosition.x() - nodeWidth/2, nodePosition.y());
}

QPointF NodeView::getEdgesOutputPoint() const
{
    auto nodePosition = pos();
    return QPointF(nodePosition.x() + nodeWidth/2, nodePosition.y());
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundRect(-nodeWidth/2, -nodeHeight/2, nodeWidth, nodeHeight, 5, 5);
}

QVariant NodeView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change)
    {
        case ItemPositionHasChanged:
        {
            emit onNodeMoved(getOwner());
            break;
        }
        default:
            break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void NodeView::populateContextualMenu(QMenu& menu)
{   
    QAction* actionDelete = menu.addAction(tr("Delete"), this, &NodeView::deleteNode);
    actionDelete->setStatusTip(tr("Delete this node"));

    QAction* actionClone = menu.addAction(tr("Clone"), this, &NodeView::cloneNode);
    actionClone->setStatusTip(tr("Clone this node"));

    QAction* actionAddTransition = menu.addAction(tr("Add Transition"), this, &NodeView::addNodeTransition);
    actionAddTransition->setStatusTip(tr("Create a new dialogue node"));
}

void NodeView::setupContextualMenuSignals()
{
    connect(this, &NodeView::onNodeDeletePressed, graph, &GraphWidget::onNodeDeleteRequest);
    connect(this, &NodeView::onNodeClonePressed, graph, &GraphWidget::onNodeCloneRequest);
    connect(this, &NodeView::onNodeAddTransitionPressed, graph, &GraphWidget::onNodeAddTransitionRequest);
}

void NodeView::deleteNode()
{
    emit onNodeDeletePressed(owner);
}

void NodeView::cloneNode()
{
    emit onNodeClonePressed(owner);
}

void NodeView::addNodeTransition()
{
    emit onNodeAddTransitionPressed(owner);
}
