#include "baseentity.h"
#include "indexerentity.h"

BaseEntity::BaseEntity(QSharedPointer<IndexerEntity> indexer, QObject *parent) : QObject(parent),
    _indexer(indexer)
{}


BaseEntity::BaseEntity(const QString &label, const QString &reference, double debit, double credit, const QDate &date, QSharedPointer<IndexerEntity> indexer, QObject *parent) : QObject(parent),
    _label(label),
    _reference(reference),
    _debit(debit),
    _credit(credit),
    _date(date),
    _indexer(indexer)
{}

BaseEntity::BaseEntity(const QString &label, const QString &reference, double debit, double credit, const QDate &date, bool isSolde, bool isTotal,QSharedPointer<IndexerEntity> indexer) : _label(label),
    _reference(reference),
    _debit(debit),
    _credit(credit),
    _date(date),
    _isSolde(isSolde),
    _isTotal(isTotal),
    _indexer(indexer)
{}

BaseEntity::BaseEntity(const BaseEntity &b) :
    QObject(b.parent()),
    _label(b.label()),
    _reference(b.reference()),
    _debit(b.debit()),
    _credit(b.credit()),
    _date(b.date()),
    _isSolde(b.isSolde()),
    _isTotal(b.isTotal()),
    _indexer(b.indexer()),
    _type(b.type())
{
}

void BaseEntity::setAmount(double value, AmountType sens)
{
    switch (sens) {
    case AmountType::DEBIT:
        _debit = value;
        _type  = AmountType::DEBIT;
        break;
    case AmountType::CREDIT:
        _credit = value;
        _type  = AmountType::CREDIT;
        break;
    default:
        break;
    }
}

double BaseEntity::gtAmount() const
{
    return _debit > _credit ? _debit : _credit;
}

void BaseEntity::inverse()
{
    if(_type == AmountType::CREDIT){
        _type = AmountType::DEBIT;
        _debit = _credit;
        _credit = 0;
        return;
    }

    if(_type == AmountType::DEBIT){
        _type = AmountType::CREDIT;
        _credit = _debit;
        _debit = 0;
        return;
    }

}

double BaseEntity::debit() const
{
    return _debit;
}

double BaseEntity::credit() const
{
    return _credit;
}

QString BaseEntity::label() const
{
    return _label;
}

void BaseEntity::setLabel(const QString &newLabel)
{
    _label = newLabel;
}

QString BaseEntity::reference() const
{
    return _reference;
}

void BaseEntity::setReference(const QString &newReference)
{
    _reference = newReference;
}

QDate BaseEntity::date() const
{
    return _date;
}

void BaseEntity::setDate(const QDate &newDate)
{
    _date = newDate;
}

bool BaseEntity::isSolde() const
{
    return _isSolde;
}

void BaseEntity::setIsSolde(bool newIsSolde)
{
    _isSolde = newIsSolde;
}

bool BaseEntity::isTotal() const
{
    return _isTotal;
}

void BaseEntity::setIsTotal(bool newIsTotal)
{
    _isTotal = newIsTotal;
}

bool BaseEntity::isIndexed() const
{
    return _indexer->isIndexed();
}

QSharedPointer<IndexerEntity> BaseEntity::indexer() const
{
    return _indexer;
}

void BaseEntity::setIndexer(QSharedPointer<IndexerEntity> newIndexer)
{
    _indexer = newIndexer;
}

BaseEntity::AmountType BaseEntity::type() const
{
    return _type;
}

void BaseEntity::setType(BaseEntity::AmountType newType)
{
    _type = newType;
}

BaseEntity::Type BaseEntity::source() const
{
    return _source;
}

void BaseEntity::setSource(Type newSource)
{
    _source = newSource;
}


