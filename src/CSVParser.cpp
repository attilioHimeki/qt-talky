#include "CSVParser.h"

const QMap<int, QStringList>* CSVParser::parseCSVFile(QString csvText) const
{
    const QStringList lines = csvText.split("\n");
    const int numLines = lines.length();

    QMap<int, QStringList>* result = new QMap<int, QStringList>();

    for(int i = 0; i < numLines; i++)
    {
        QStringList row = splitCsvLine(lines[i]);
        result->insert(i, row);
    }

    return result;
}

const QStringList CSVParser::splitCsvLine(QString line) const
{
    QRegExp regExp("(((?<x>(?=[,\r\n]+))|""(?<x>([^""]|"""")+)""|(?<x>[^,\r\n]+)),?)");
    return line.split(regExp);
}
