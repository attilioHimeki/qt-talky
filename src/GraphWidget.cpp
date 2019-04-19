#include "GraphWidget.h"
#include "NodeLinkView.h"
#include "MouseLinkView.h"
#include "NodeView.h"
#include "Node.h"
#include "DialogueTree.h"
#include "EditorWindow.h"

#include <math.h>
#include <typeinfo>

#include <QKeyEvent>
#include <QMessageBox>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    graphScene = new QGraphicsScene(this);
    graphScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    graphScene->setSceneRect(-300, -300, 600, 600);

    setScene(graphScene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    showMaximized();

    setBackgroundBrush(Qt::white);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QWidget::customContextMenuRequested, this, &GraphWidget::showContextMenu);

    currentTree = std::make_unique<DialogueTree>();
    connectTreeSignals();

    currentTree->createOriginNode();

    initialiseTransitionIndicator();
}

void GraphWidget::connectTreeSignals()
{
    connect(currentTree.get(), &DialogueTree::contentChanged, this, &GraphWidget::contentChanged);
    connect(currentTree.get(), &DialogueTree::linkAdded, this, &GraphWidget::processAddLink);
    connect(currentTree.get(), &DialogueTree::nodeAdded, this, &GraphWidget::processAddNode);
}

void GraphWidget::initialiseTransitionIndicator()
{
    transitionLinkView = new MouseLinkView(this);
    graphScene->addItem(transitionLinkView);
    transitionLinkView->setVisible(false);
}

void GraphWidget::refreshGraph()
{
    graphScene->clear();

    auto nodes = currentTree->nodes;

    for(Node* n : nodes)
    {
        graphScene->addItem(n->getView());
    }

    for(NodeLinkView* n : nodeLinks)
    {
        graphScene->addItem(n);
    }

    initialiseTransitionIndicator();
}

void GraphWidget::onNodeDeleteRequest(Node* node)
{
    for(NodeLinkView* v : nodeLinks)
    {
        if(v->isLinkedWith(*node->getView()))
        {
            graphScene->removeItem(v);
            nodeLinks.removeOne(v);
        }
    }

    graphScene->removeItem(node->getView());

    currentTree->deleteNode(node);
}

void GraphWidget::onNodeCloneRequest(Node* node)
{
    currentTree->cloneNode(*node);
}

void GraphWidget::onNodeAddTransitionRequest(Node* node)
{
    startAddTransition(node);
}

void GraphWidget::startAddTransition(Node* fromNode)
{
    transitionLinkView->setSource(fromNode->getView());

    transitionLinkView->setVisible(true);

    isAddingTransition = true;
    currentTransitionNode = fromNode;
}

void GraphWidget::clearAddTransition()
{
    isAddingTransition = false;
    currentTransitionNode = Q_NULLPTR;

    transitionLinkView->setVisible(false);
    transitionLinkView->setSource(Q_NULLPTR);
}


void GraphWidget::onNodeMoved(Node* node)
{
    for(auto* n : nodeLinks)
    {
        if(n->isLinkedWith(*node->getView()))
        {
            n->adjust();
        }
    }
}

void GraphWidget::applyNewTree()
{
    clearAddTransition();
    currentTree->clearTree();
    nodeLinks.clear();

    refreshGraph();
    connectTreeSignals();

    currentTree->createOriginNode();
}


void GraphWidget::applyLoadedTreeJsonFile(QJsonObject& treeFileJson)
{
    clearAddTransition();
    currentTree->read(treeFileJson);

    nodeLinks.clear();

    auto nodes = currentTree->nodes;
    for(Node* n : nodes)
    {
        n->setupView(this);
        connect(n->getView(), &NodeView::onNodeMoved, this, &GraphWidget::onNodeMoved);
    }

    for(Node* n : nodes)
    {
        auto linkedNodes = n->getLinkedNodes();
        for(NodeLink* l : linkedNodes)
        {
            auto linkedNode = currentTree->getNodeById(l->getLinkedNodeId());
            if(linkedNode != Q_NULLPTR)
            {
                auto nodeLinkView = new NodeLinkView(this, *n->getView(), *linkedNode->getView());
                nodeLinks.push_back(nodeLinkView);
            }
        }
    }

    refreshGraph();
    connectTreeSignals();
}

const QJsonObject GraphWidget:: serialiseLoadedTree()
{
    QJsonObject result;
    currentTree->write(result);

    return result;
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        translateView(0, -50);
        break;
    case Qt::Key_Down:
        translateView(0, 50);
        break;
    case Qt::Key_Right:
        translateView(50, 0);
        break;
    case Qt::Key_Left:
        translateView(-50, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::spawnChoiceNode()
{
    auto mousePos = mapToScene(mapFromGlobal(QCursor::pos()));
    currentTree->createChoiceNode(mousePos);
}

void GraphWidget::spawnChoiceOptionNode()
{
    auto mousePos = mapToScene(mapFromGlobal(QCursor::pos()));
    currentTree->createChoiceOptionNode(mousePos);
}

void GraphWidget::spawnDialogueNode()
{
    auto mousePos = mapToScene(mapFromGlobal(QCursor::pos()));
    currentTree->createDialogueNode(mousePos);
}

void GraphWidget::processAddNode(Node* node)
{
    node->setupView(this);
    graphScene->addItem(node->getView());

    connect(node->getView(), &NodeView::onNodeMoved, this, &GraphWidget::onNodeMoved);
}

void GraphWidget::processAddLink(Node* outputNode, Node* inputNode)
{
    auto nodeLinkView = new NodeLinkView(this, *outputNode->getView(), *inputNode->getView());
    nodeLinks.push_back(nodeLinkView);

    graphScene->addItem(nodeLinkView);
}


void GraphWidget::showDefaultContextMenu(const QPoint& pos)
{
    auto clickPos = mapToGlobal(pos);
    QMenu menu(this);
    auto submenu = menu.addMenu(tr("New Node"));

    QAction* addDialogueNodeAction = submenu->addAction(tr("Dialogue Node"), this, &GraphWidget::spawnDialogueNode);
    addDialogueNodeAction->setStatusTip(tr("Create a new dialogue node"));

    QAction* addChoiceNodeAction = submenu->addAction(tr("Choice Node"), this, &GraphWidget::spawnChoiceNode);
    addChoiceNodeAction->setStatusTip(tr("Create a new choice node"));

    QAction* addChoiceOptionNodeAction = submenu->addAction(tr("Choice Option Node"), this, &GraphWidget::spawnChoiceOptionNode);
    addChoiceOptionNodeAction->setStatusTip(tr("Create a new choice option node"));

    menu.exec(clickPos);

}

void GraphWidget::showContextMenu(const QPoint& pos)
{
     QList<QGraphicsItem*> itemsClicked = items(pos);

     for(auto item : itemsClicked)
     {
         auto nodeView = dynamic_cast<NodeView*>(item);
         if(nodeView != Q_NULLPTR)
         {
             auto clickPos = mapToGlobal(pos);
             QMenu menu(this);
             nodeView->populateContextualMenu(menu);
             menu.exec(clickPos);

             return;
         }
     }

     showDefaultContextMenu(pos);
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::translateView(qreal x, qreal y)
{
    QTransform old_transform = transform();

    QRectF scene_rect = scene()->sceneRect();
    QRectF new_scene_rect(scene_rect.x()-x,
                          scene_rect.y()-y,
                          scene_rect.width(),scene_rect.height());
    scene()->setSceneRect(new_scene_rect);

    setTransform(old_transform);
}

void GraphWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
}

void GraphWidget::showEvent(QShowEvent *)
{
}

void GraphWidget::mousePressEvent(QMouseEvent * event)
{
    if(isAddingTransition)
    {
        auto pos = event->pos();
        QList<QGraphicsItem*> itemsClicked = items(pos);
        for(auto item : itemsClicked)
        {
            if(item != Q_NULLPTR)
            {
               auto nodeView = dynamic_cast<NodeView*>(item);
               if(nodeView != Q_NULLPTR)
               {
                   bool success = currentTree->addNodeLink(currentTransitionNode, nodeView->getOwner());
                   if(!success)
                   {
                       QMessageBox::warning(this, tr("Error linking nodes"), tr("This link is not allowed"));
                   }

                   break;
               }
            }
        }

        clearAddTransition();
    }

    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(isAddingTransition)
    {
        transitionLinkView->adjust();
    }

    QGraphicsView::mouseMoveEvent(event);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
