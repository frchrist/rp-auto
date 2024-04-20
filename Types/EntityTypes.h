#ifndef ENTITYTYPES_H
#define ENTITYTYPES_H
#include <QSharedPointer>
#include <QVector>

class AccountEntity;
class BaseEntity;

typedef QVector<QSharedPointer<AccountEntity>> AccountEntityPtrVector;
typedef QSharedPointer<AccountEntity> AccountEntityPtr;
typedef QVector<QSharedPointer<BaseEntity>> BaseEntityPtrVector;
typedef QSharedPointer<BaseEntity> BaseEntityPtr;


#endif // ENTITYTYPES_H
