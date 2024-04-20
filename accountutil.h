#ifndef ACCOUNTUTIL_H
#define ACCOUNTUTIL_H
#include "Entities/baseentity.h"
#include "Entities/accountentity.h"
class AccountUtil
{
public:
    static QPair<BaseEntity::AmountType, double> Solde( QPair<double, double> );
    static QPair<double, double> Total(QVector<QSharedPointer<AccountEntity>> );
    static QVector<QSharedPointer<AccountEntity>> Diff(QVector<QSharedPointer<AccountEntity>>, QVector<QSharedPointer<AccountEntity>> );
};

#endif // ACCOUNTUTIL_H
