#ifndef ORIGINNODEVIEW_H
#define ORIGINNODEVIEW_H

#include "NodeView.h"

class OriginNodeView : public NodeView
{

public:
    OriginNodeView(Node* ownerNode, GraphWidget *graphWidget);

    enum { Type = UserType + 3 };
    int type() const override { return Type; }

    void populateContextualMenu(QMenu& menu) override;
};

#endif // ORIGINNODEVIEW_H
