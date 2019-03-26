#ifndef CHOICENODEVIEW_H
#define CHOICENODEVIEW_H

#include "NodeView.h"

class ChoiceNodeView : public NodeView
{
public:
    ChoiceNodeView(Node* ownerNode, GraphWidget *graphWidget);

    enum { Type = UserType + 5 };
    int type() const override { return Type; }

    void populateContextualMenu(QMenu& menu) override;
    void setupContextualMenuSignals() override;

signals:
    void onAddChoiceEntryPressed(Node* owner);

private slots:
    void addChoiceEntry();

};


#endif // CHOICENODEVIEW_H
