#ifndef NODELINKVIEW_H
#define NODELINKVIEW_H

#include "LinkView.h"

class NodeView;

class NodeLinkView : public LinkView
{
public:
    NodeLinkView(GraphWidget *graphWidget, const NodeView& sourceNode, const NodeView& destNode);

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void adjust() override;

    bool isLinkedWith(NodeView& node) const;

private:
    const NodeView& source;
    const NodeView& destination;
};

#endif // NODELINKVIEW_H
