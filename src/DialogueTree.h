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

    void addNodeLink(Node* startNode, Node* endNode);
    void deleteNode(Node* node);
    void clearTree();
    QList<Node*> nodes;

signals:
    void contentChanged();

private:
    QString treeName;

    Node* originNode;
    int nextNodeId;
};

#endif // DIALOGUETREE_H
