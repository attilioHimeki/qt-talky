#include "CSVParser.h"

const QList<QStringList>* CSVParser::parseCSVFile(QString csvText) const
{
    const QStringList lines = csvText.split("\n");
    const int numLines = lines.length();

    QList<QStringList>* result = new QList<QStringList>();

    for(int i = 0; i < numLines; i++)
    {
        QStringList row = splitCsvLine(lines[i]);
        result->append(row);
    }

    return result;
}

const QStringList CSVParser::splitCsvLine(QString line) const
{
    QRegExp regExp("(((?<x>(?=[,\r\n]+))|""(?<x>([^""]|"""")+)""|(?<x>[^,\r\n]+)),?)");
    return line.split(regExp);
}
