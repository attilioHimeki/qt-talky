#ifndef NODETYPE_H
#define NODETYPE_H

#include <QString>

enum class NodeType {None, Any, Origin, Dialogue, Pause, Action, Choice, ChoiceOption, RandomLink};

inline NodeType getNodeTypeFromString(const QString& typeString)
{
    if(typeString == "none")
    {
        return NodeType::None;
    }
    else if(typeString == "any")
    {
        return NodeType::Any;
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
    else if(typeString == "choiceOption")
    {
        return NodeType::ChoiceOption;
    }

    return NodeType::None;
}

inline QString getStringFromNodeType(NodeType type)
{
    if(type == NodeType::None)
    {
        return "none";
    }
    else if(type == NodeType::Any)
    {
        return "any";
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
    else if(type == NodeType::ChoiceOption)
    {
        return "choiceOption";
    }

    return "none";
}

#endif // NODETYPE_H
