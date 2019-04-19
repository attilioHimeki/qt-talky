#ifndef NODEBUILDER_H
#define NODEBUILDER_H

#include "Node.h"
#include "DialogueNode.h"
#include "OriginNode.h"
#include "ChoiceNode.h"
#include "ChoiceOptionNode.h"

class NodeBuilder
{
public:
    static Node* create(NodeType type, int id, QPointF pos = {});
    static Node* create(QJsonObject json, int id = -1);
private:
    static DialogueNode* createDialogueNode(int id, QPointF pos = {});
    static DialogueNode* createDialogueNode(QJsonObject json, int id = -1);

    static OriginNode* createOriginNode(int id, QPointF pos = {});
    static OriginNode* createOriginNode(QJsonObject json, int id = -1);

    static ChoiceNode* createChoiceNode(int id, QPointF pos = {});
    static ChoiceNode* createChoiceNode(QJsonObject json, int id = -1);

    static ChoiceOptionNode* createChoiceOptionNode(int id, QPointF pos = {});
    static ChoiceOptionNode* createChoiceOptionNode(QJsonObject json, int id = -1);


};

#endif // NODEBUILDER_H
