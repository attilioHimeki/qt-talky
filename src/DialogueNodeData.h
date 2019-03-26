#ifndef DIALOGUENODEDATA_H
#define DIALOGUENODEDATA_H

#include "NodeData.h"

class DialogueNodeData : public NodeData
{
public:
    DialogueNodeData(int id);

    const QString getNodeTextKey() const;
    void setNodeTextKey(const QString key);

    void read(const QJsonObject &json) override;
    void write(QJsonObject &json) const override;

private:
    QString textKey;
};

#endif // DIALOGUENODEDATA_H
