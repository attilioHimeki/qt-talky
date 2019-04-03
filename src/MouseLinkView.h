#ifndef MOUSELINKVIEW_H
#define MOUSELINKVIEW_H

#include "LinkView.h"

class NodeView;

class MouseLinkView : public LinkView
{
public:
    MouseLinkView(GraphWidget *graphWidget);

    enum { Type = UserType + 6 };
    int type() const override { return Type; }

    void setSource(NodeView* s);

    void adjust() override;

private:
    NodeView* source;
};

#endif // MOUSELINKVIEW_H
