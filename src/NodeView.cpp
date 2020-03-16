#include "NodeLinkView.h"
#include "NodeView.h"
#include "GraphWidget.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QLineEdit>
#include <QLabel>
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

void NodeView::moveTo(QPointF pos)
{
    setPos(pos);
}

void NodeView::setupTypeLabel(NodeType type)
{
    typeLabel = new QLabel();
    auto typeText = getStringFromNodeType(type);
    typeLabel->setText(typeText);
    typeLabel->setAlignment(Qt::AlignLeft);
    typeLabel->setStyleSheet("font: 12pt;background: transparent;  border: 0px; color: #111111");
    typeLabel->show();
    QGraphicsProxyWidget* pMyProxy = new QGraphicsProxyWidget(this);
    pMyProxy->setWidget(typeLabel);
    pMyProxy->setPos(baseNodeWidth - typeLabel->width(), -20);
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
    pMyProxy->setPos(0, -20);
}

void NodeView::setupPropertyTextField(const QString id, const QString title, const QString fieldPlaceholder, const QPointF pos, const QString value)
{
    auto titleTextField = new QLabel(title);
    titleTextField->setAlignment(Qt::AlignLeft);
    titleTextField->setStyleSheet("background:transparent; border: 2px; font-size: 10px; color: #990000");
    titleTextField->show();
    titleTextField->setFixedSize(baseNodeWidth - 20, 30);
    QGraphicsProxyWidget* titleProxy = new QGraphicsProxyWidget(this);
    titleProxy->setWidget(titleTextField);
    titleProxy->setPos(pos.x(), pos.y());

    QLineEdit* fieldTextField = new QLineEdit();
    fieldTextField->setAlignment(Qt::AlignLeft);
    fieldTextField->setFrame(true);
    fieldTextField->setStyleSheet("background:transparent; border: 2px; color: #111111");
    fieldTextField->setPlaceholderText(fieldPlaceholder);
    fieldTextField->setText(value);
    fieldTextField->show();
    fieldTextField->setFixedSize(baseNodeWidth - 20, 30);
    QGraphicsProxyWidget* fieldProxy = new QGraphicsProxyWidget(this);
    fieldProxy->setWidget(fieldTextField);
    fieldProxy->setPos(pos.x(), pos.y() + 10);

    textFields.insert(id, fieldTextField);
}

void NodeView::setPropertyText(const QString id, const QString text)
{
    if(textFields.contains(id))
    {
        auto field = textFields.value(id);
        field->setText(text);
    }
}

const QLineEdit* NodeView::getPropertyTextHandle(const QString id) const
{
    if(textFields.contains(id))
    {
        return textFields.value(id);
    }

    return Q_NULLPTR;
}

QRectF NodeView::boundingRect() const
{
    return QRectF(0, 0, baseNodeWidth, getNodeHeight());
}

QPainterPath NodeView::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, baseNodeWidth, getNodeHeight());
    return path;
}

QPointF NodeView::getEdgesInputPoint() const
{
    auto nodePosition = pos();
    return QPointF(nodePosition.x(), nodePosition.y() + getNodeHeight()/2);
}

QPointF NodeView::getEdgesOutputPoint() const
{
    auto nodePosition = pos();
    return QPointF(nodePosition.x() + baseNodeWidth, nodePosition.y() + getNodeHeight()/2);
}

int NodeView::getNodeHeight() const
{
    // Todo: Find a better way to calculate this
    int totalHeight = baseNodeHeight;
    for(auto field : textFields)
    {
        totalHeight += field->height();
    }

    return totalHeight;
}

void NodeView::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget *)
{
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRoundedRect(0, 0, baseNodeWidth, getNodeHeight(), 5, 5);
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
