#ifndef DIALOGUETREE_H
#define DIALOGUETREE_H

#include "Node.h"
#include "DialogueNode.h"
#include "OriginNode.h"
#include "NodeBuilder.h"

#include <QJsonObject>


class DialogueTree : public QObject
{
    Q_OBJECT
public:
    DialogueTree();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    Node* getNodeById(int nodeId) const;
    Node* createDialogueNode();
    Node* createOriginNode();
    Node* createChoiceNode();
    Node* createChoiceOptionNode();
    Node* createNode(NodeType type);
    Node* cloneNode(const Node& node);

    bool addNodeLink(Node* startNode, Node* endNode);
    void deleteNode(Node* node);
    void clearTree();
    QList<Node*> nodes;

signals:
    void contentChanged();
    void linkAdded(Node* startNode, Node* endNode);
    void nodeAdded(Node* node);

private:
    QString treeName;

    Node* originNode;
    int nextNodeId;
};

#endif // DIALOGUETREE_H
