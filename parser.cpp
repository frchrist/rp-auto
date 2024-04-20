#include "parser.h"
#include "Entities/accountentity.h"
#include "Entities/indexerentity.h"

#include <QDate>
QList<QSharedPointer<AccountEntity> > Parser::parseCSV(const QTextStream&  csvContent, bool hasHeading, bool bankSource)
{
     QTextStream csvStream(csvContent.device());
    QList<QSharedPointer<AccountEntity>> entities;

    if (hasHeading && !csvStream.atEnd()) {
        QString headerLine;
          csvStream.readLineInto(&headerLine);
    }
    while(!csvStream.atEnd()){
        QString line;
        csvStream.readLineInto(&line);

        QStringList fields = line.split(';');
        if (fields.size() != 5) {
            qWarning() << "Invalid CSV line:" << line;
            continue;
        }
       QSharedPointer<IndexerEntity> newIndexser = QSharedPointer<IndexerEntity>::create();
       QSharedPointer<AccountEntity> entity = QSharedPointer<AccountEntity>::create(newIndexser);
        entity->setDate(QDate::fromString(fields[0], "dd/MM/yyyy"));
        entity->setReference(fields[1]);
        entity->setLabel(fields[2]);
        if(!bankSource)
            entity->setSource(AccountEntity::Type::ACCOUNT);
        bool ok = false;
        double debit, credit = 0.0;
        debit = fields[3].toDouble(&ok);
        if (!ok) {
            qWarning() << "Invalid debit value:" << fields[3];
            debit = 0.0;
        }
        credit = fields[4].toDouble(&ok);
        if (!ok) {
            qWarning() << "Invalid credit value:" << fields[4];
            credit = 0.0;
        }
        debit > 0.0 ? entity->setAmount(debit, AccountEntity::AmountType::DEBIT) :  entity->setAmount(credit, AccountEntity::AmountType::CREDIT);

        entities.emplace_back(std::move(entity));
    }

    return entities;
}
