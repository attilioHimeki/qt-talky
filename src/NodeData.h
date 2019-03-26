#ifndef NODEDATA_H
#define NODEDATA_H

#include <QJsonObject>
#include <QJsonArray>

#include "NodeLink.h"
#include "NodeView.h"
#include "NodeType.h"

class NodeData
{
public:
    NodeData(NodeType t, int id);
    virtual ~NodeData() = default;

    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;

    int getNodeId() const;

    void addLinkedNode(int linkedNodeId);
    void removeLinkedNode(int linkedNodeId);

    QPoint startPos;
    QList<NodeLink*> linkedNodes;
    NodeType type;

protected:
    int nodeId;
};

#endif // NODEDATA_H
