#ifndef NODELINKCONDITION_H
#define NODELINKCONDITION_H

#include <QList>

class NodeLinkCondition
{
public:
    NodeLinkCondition();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // NODELINKCONDITION_H
