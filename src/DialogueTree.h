#ifndef DIALOGUETREE_H
#define DIALOGUETREE_H

#include "Node.h"
#include "DialogueNode.h"
#include "NodeBuilder.h"

#include <QJsonObject>

enum class NodeLinkResponse {Success, FailAlreadyLinked, FailIncompatibleType, FailTooManyLinks, FailLinkItself};

class DialogueTree : public QObject
{
    Q_OBJECT
public:
    DialogueTree();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    Node* getNodeById(int nodeId) const;
    Node* createNode(NodeType type, QPointF pos = {});
    Node* cloneNode(const Node& node);

    NodeLinkResponse addNodeLink(Node* startNode, Node* endNode);
    void deleteNode(Node* node);
    void clearTree();
    QList<Node*> nodes;

    bool isNodeLinkLegal(const NodeType startNodeType, const NodeType endNodeType) const;
    bool canAddMoreLinksToNode(const Node* node) const;

signals:
    void contentChanged();
    void linkAdded(Node* startNode, Node* endNode);
    void nodeAdded(Node* node);

private:
    QString treeName;

    Node* originNode;
    int nextNodeId;

    QMultiMap<NodeType, NodeType> allowedConnectionsScheme;
    QMap<NodeType, int> maximumLinkPerNodeType;
};

#endif // DIALOGUETREE_H
