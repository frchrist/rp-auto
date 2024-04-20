#ifndef PARSER_H
#define PARSER_H
#include <QObject>
#include <QList>
#include <QSharedPointer>
class AccountEntity;

class Parser
{
public:
    static QList<QSharedPointer<AccountEntity>> parseCSV(const QTextStream& s, bool hasHeading,  bool bankSource);
};

#endif // PARSER_H
