#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

#include "DialogueTree.h"

class NodeView;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = Q_NULLPTR);

    void itemMoved();
    void applyLoadedTreeJsonFile(QJsonObject& treeFileJson);
    const QJsonObject serialiseLoadedTree();
    void processAddNode(Node* node);
    void processAddLink(Node* inputNode, Node* outputNode);

    void spawnDialogueNode();
    void spawnChoiceNode();

    void refreshGraph() const;

signals:
    void contentChanged();

public slots:
    void zoomIn();
    void zoomOut();
    void showContextMenu(const QPoint& pos);
    void onNodeDeleteRequest(Node* node);
    void onNodeCloneRequest(Node* node);
    void onNodeAddTransitionRequest(Node* node);
    void onNodeMoved(Node* node);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void showDefaultContextMenu(const QPoint& pos);
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *) override;
    void mousePressEvent(QMouseEvent * e) override;
    void scaleView(qreal scaleFactor);
    void translateView(qreal x, qreal y);
private:
    QGraphicsScene* graphScene;

    std::unique_ptr<DialogueTree> currentTree;

    bool isAddingTransition = false;
    Node* currentTransitionNode;

    QList<NodeLinkView*> nodeLinks;
};


#endif // GRAPHWIDGET_H