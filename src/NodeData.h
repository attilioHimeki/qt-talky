#ifndef NODEDATA_H
#define NODEDATA_H

#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>

#include "NodeLink.h"
#include "NodeType.h"

class NodeData
{
public:
    NodeData(NodeType t, int id);
    ~NodeData();

    void read(const QJsonObject &json, bool readId = false);
    void write(QJsonObject &json) const;

    int getNodeId() const;

    void addLinkedNode(int linkedNodeId);
    void removeLinkedNode(int linkedNodeId);
    bool isLinkedWith(int nodeId) const;

    QVariant getCustomParameter(QString key) const;
    void setCustomParameter(QString key, QVariant val);
    bool hasCustomParameter(QString key) const;

    QPointF getSerialisedGraphPosition() const;
    void refreshSerialisedGraphPosition(QPointF pos);

    QList<NodeLink*> linkedNodes;
    NodeType type;

protected:
    int nodeId;
    QPointF serialisedGraphPosition;

    QVariantMap customParameters;
};

#endif // NODEDATA_H
