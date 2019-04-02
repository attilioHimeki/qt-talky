#ifndef NODEBUILDER_H
#define NODEBUILDER_H

#include "Node.h"
#include "DialogueNode.h"
#include "OriginNode.h"
#include "ChoiceNode.h"

class NodeBuilder
{
public:
    static Node* create(NodeType type, int id);
    static Node* create(QJsonObject json, int id = -1);
private:
    static DialogueNode* createDialogueNode(int id);
    static DialogueNode* createDialogueNode(QJsonObject json, int id = -1);

    static OriginNode* createOriginNode(int id);
    static OriginNode* createOriginNode(QJsonObject json, int id = -1);

    static ChoiceNode* createChoiceNode(int id);
    static ChoiceNode* createChoiceNode(QJsonObject json, int id = -1);
};

#endif // NODEBUILDER_H
