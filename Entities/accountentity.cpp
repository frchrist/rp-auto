#include "accountentity.h"
#include "indexerentity.h"
AccountEntity::AccountEntity(QSharedPointer<IndexerEntity> indexer,QObject *parent)
    : BaseEntity{indexer,parent}
{}

AccountEntity::AccountEntity(const AccountEntity &b) : BaseEntity{b}
{}

AccountEntity::~AccountEntity()
{

}

QSharedPointer<AccountEntity> AccountEntity::createTotalLine()
{
    QSharedPointer<IndexerEntity> newIndexer = QSharedPointer<IndexerEntity>::create(-100,IndexerEntity::STATE::UNINDEXED,IndexerEntity::WHY::NOT_INDEXABLE);
    QSharedPointer<AccountEntity> totalLine = QSharedPointer<AccountEntity>::create(newIndexer);
    totalLine->setLabel("TOTAL");
    totalLine->setReference("TOTAL");
    totalLine->setIsTotal(true);
    return totalLine;
}

QSharedPointer<AccountEntity> AccountEntity::createSoldeLine()
{
    QSharedPointer<IndexerEntity> newIndexer = QSharedPointer<IndexerEntity>::create(-100,IndexerEntity::STATE::UNINDEXED,IndexerEntity::WHY::NOT_INDEXABLE);
    QSharedPointer<AccountEntity> totalLine = QSharedPointer<AccountEntity>::create(newIndexer);
    totalLine->setLabel("SOLDE");
    totalLine->setReference("TOTAL");
    totalLine->setIsSolde(true);
    return totalLine;
}

QSharedPointer<AccountEntity> AccountEntity::createEmptyLine()
{
    QSharedPointer<IndexerEntity> newIndexer = QSharedPointer<IndexerEntity>::create(-100,IndexerEntity::STATE::UNINDEXED,IndexerEntity::WHY::NOT_INDEXABLE);
    QSharedPointer<AccountEntity> totalLine = QSharedPointer<AccountEntity>::create(newIndexer);
    totalLine->setLabel("-");
    totalLine->setReference("EMPTY");
    totalLine->setAmount(0, AccountEntity::AmountType::DEBIT);
    totalLine->setAmount(0, AccountEntity::AmountType::CREDIT);
    totalLine->setIsSolde(true);
    return totalLine;
}

