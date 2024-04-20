#ifndef ACCOUNTENTITY_H
#define ACCOUNTENTITY_H

#include <QObject>
#include "baseentity.h"
#include <QSharedPointer>
class AccountEntity;
class IndexerEntity;
class AccountEntity : public BaseEntity
{
    Q_OBJECT
public:
    explicit AccountEntity(QSharedPointer<IndexerEntity> indexer,QObject *parent = nullptr);
    explicit AccountEntity(const AccountEntity& b);
    virtual ~AccountEntity();
    static QSharedPointer<AccountEntity> createTotalLine();
    static QSharedPointer<AccountEntity> createSoldeLine();
    static QSharedPointer<AccountEntity> createEmptyLine();
};

#endif // ACCOUNTENTITY_H
