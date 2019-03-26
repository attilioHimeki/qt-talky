#ifndef ORIGINNODE_H
#define ORIGINNODE_H

#include "Node.h"


class OriginNode : public Node
{
public:
    OriginNode(NodeData* data);
    ~OriginNode() override = default;

    void setupView(GraphWidget *graphWidget) override;
};

#endif // ORIGINNODE_H
