#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QString>
#include <QMap>

class CSVParser
{
public:
    const QMap<int, QStringList>* parseCSVFile(QString csvText) const;

private:
    const QStringList splitCsvLine(QString line) const;

};

#endif // CSVPARSER_H
