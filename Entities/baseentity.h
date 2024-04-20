#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <QObject>
#include <QDate>
#include "indexerentity.h"
class BaseEntity : public QObject
{
    Q_OBJECT
public:
    BaseEntity(QSharedPointer<IndexerEntity> indexer, QObject *parent = nullptr);
    BaseEntity(const QString &label, const QString &reference, double debit, double credit, const QDate &date, QSharedPointer<IndexerEntity> indexer, QObject *parent = nullptr);
    BaseEntity(const QString &label, const QString &reference, double debit, double credit, const QDate &date, bool isSolde, bool isTotal, QSharedPointer<IndexerEntity> indexer);
    explicit BaseEntity(const BaseEntity& b);
    enum class AmountType{
        DEBIT,
        CREDIT,
        BOTH
    };
    enum class Type{
        FROM_BANK,
        ACCOUNT
    };

    void setAmount(double value, AmountType sens = AmountType::DEBIT);
    double gtAmount() const;
    void inverse();
    double debit() const;
    double credit() const;

    QString label() const;
    void setLabel(const QString &newLabel);

    QString reference() const;
    void setReference(const QString &newReference);

    QDate date() const;
    void setDate(const QDate &newDate);

    bool isSolde() const;
    void setIsSolde(bool newIsSolde);

    bool isTotal() const;
    void setIsTotal(bool newIsTotal);




    Type source() const;
    void setSource(Type newSource);

    bool isIndexed() const;


    QSharedPointer<IndexerEntity> indexer() const;
    void setIndexer(QSharedPointer<IndexerEntity> newIndexer);

    BaseEntity::AmountType type() const;
    void setType(BaseEntity::AmountType newType);

signals:
private:
    QString _label;
    QString _reference;
    double _debit = 0.0;
    double _credit = 0.0;
    QDate _date;
    bool _isSolde = false;
    bool _isTotal = false;
    BaseEntity::Type _source = BaseEntity::Type::FROM_BANK;
    QSharedPointer<IndexerEntity> _indexer;
    BaseEntity::AmountType _type;
};

#endif // BASEENTITY_H
