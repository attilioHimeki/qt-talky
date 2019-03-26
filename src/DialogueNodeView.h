#ifndef DIALOGUENODEVIEW_H
#define DIALOGUENODEVIEW_H

#include "NodeView.h"

class DialogueNodeView : public NodeView
{
public:
    DialogueNodeView(Node* ownerNode, GraphWidget *graphWidget);

    enum { Type = UserType + 4 };
    int type() const override { return Type; }

    void populateContextualMenu(QMenu& menu) override;

    void setKeyText(QString key);

    QLineEdit* keyTextField;

private:
    void setupKeyLabel();
};

#endif // DIALOGUENODEVIEW_H
