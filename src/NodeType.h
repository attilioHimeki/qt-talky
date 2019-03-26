#ifndef NODETYPE_H
#define NODETYPE_H

#include <QString>

enum class NodeType {None, Origin, Dialogue, Pause, Action, Choice};

inline NodeType getNodeTypeFromString(QString typeString)
{
    if(typeString == "none")
    {
        return NodeType::None;
    }
    else if(typeString == "origin")
    {
        return NodeType::Origin;
    }
    else if(typeString == "dialogue")
    {
        return NodeType::Dialogue;
    }
    else if(typeString == "pause")
    {
        return NodeType::Pause;
    }
    else if(typeString == "action")
    {
        return NodeType::Action;
    }
    else if(typeString == "choice")
    {
        return NodeType::Choice;
    }

    return NodeType::None;
}

inline QString getStringFromNodeType(NodeType type)
{
    if(type == NodeType::None)
    {
        return "none";
    }
    else if(type == NodeType::Origin)
    {
        return "origin";
    }
    else if(type == NodeType::Dialogue)
    {
        return "dialogue";
    }
    else if(type == NodeType::Pause)
    {
        return "pause";
    }
    else if(type == NodeType::Action)
    {
        return "action";
    }
    else if(type == NodeType::Choice)
    {
        return "choice";
    }

    return "none";
}

#endif // NODETYPE_H
