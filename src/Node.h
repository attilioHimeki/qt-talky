#ifndef NODE_H
#define NODE_H

#include "NodeData.h"
#include "NodeView.h"


class Node : public QObject
{
    Q_OBJECT

public:
    Node(NodeData* data);
    virtual ~Node() = default;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    int getNodeId() const;
    NodeType getNodeType() const;

    virtual void setupView(GraphWidget *graphWidget);
    NodeView* getView();

    QList<NodeLink*> getLinkedNodes() const;
    void addLinkedNode(int linkedNodeId);
    void removeLinkedNode(int linkedNodeId);
    bool isLinkedWith(int linkedNodeId) const;
    int getLinkedNodesCount() const;

    const QPointF getCurrentGraphPosition() const;
    const QPointF getSerialisedGraphPosition() const;

protected:
    std::unique_ptr<NodeView> view;
    std::unique_ptr<NodeData> model;

signals:
    void nodeChanged();

};

#endif // NODE_H
