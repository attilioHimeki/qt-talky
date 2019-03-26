#ifndef NODELINK_H
#define NODELINK_H

#include <QString>
#include <QList>

class NodeLink
{
public:
    NodeLink();
    NodeLink(int linkedId);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    int getLinkedNodeId() const;
private:
    int linkedNodeId;
};

#endif // NODELINK_H
