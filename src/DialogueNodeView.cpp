#include "DialogueNodeView.h"
#include "GraphWidget.h"

DialogueNodeView::DialogueNodeView(Node* ownerNode, GraphWidget *graphWidget)
    :NodeView(ownerNode, graphWidget)
{
    setupKeyLabel();
}

void DialogueNodeView::setupKeyLabel()
{
    keyTextField = new QLineEdit();
    keyTextField->setAlignment(Qt::AlignLeft);
    keyTextField->setFrame(true);
    keyTextField->setStyleSheet("background: transparent;  border: 0px; color: #111111");
    keyTextField->setPlaceholderText("key");
    keyTextField->show();
    QGraphicsProxyWidget* pMyProxy = new QGraphicsProxyWidget(this);
    pMyProxy->setWidget(keyTextField);
    pMyProxy->setPos(-50, -nodeHeight/2);
}

void DialogueNodeView::setKeyText(QString key)
{
    keyTextField->setText(key);
}


void DialogueNodeView::populateContextualMenu(QMenu& menu)
{
    NodeView::populateContextualMenu(menu);
}
