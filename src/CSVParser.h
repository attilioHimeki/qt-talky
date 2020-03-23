#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QString>
#include <QList>

class CSVParser
{
public:
    const QList<QStringList>* parseCSVFile(QString csvText) const;

private:
    const QStringList splitCsvLine(QString line) const;

};

#endif // CSVPARSER_H
