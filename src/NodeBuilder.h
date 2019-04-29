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
    template<typename T>
    static T* createGenericNode(NodeType type, int id, QPointF pos = {});

    template<typename T>
    static T* createGenericNode(QJsonObject json, int id = -1);


};

#endif // NODEBUILDER_H
