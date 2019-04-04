#ifndef NODE_H
#define NODE_H

#include "DialogueNodeData.h"
#include "NodeData.h"
#include "NodeView.h"
#include "DialogueNodeView.h"
#include "OriginNodeView.h"


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

    virtual void setupView(GraphWidget *graphWidget) = 0;
    NodeView* getView();

    QList<NodeLink*> getLinkedNodes() const;
    void addLinkedNode(int linkedNodeId);
    void removeLinkedNode(int linkedNodeId);
    virtual bool validateAddNode(const Node& linkedNode) const;

    const QPoint getStartPosition() const;

protected:
    std::unique_ptr<NodeView> view;
    std::unique_ptr<NodeData> model;

    QList<NodeType> allowedNodeLinkTypes;

signals:
    void nodeChanged();

};

#endif // NODE_H
