#ifndef RAWACCOUNTMODEL_H
#define RAWACCOUNTMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "Entities/accountentity.h"
#include <QSharedPointer>


class RawAccountModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit RawAccountModel(QObject *parent = nullptr);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVector<QSharedPointer<AccountEntity> > accounts() const;
    void setAccounts(const QVector<QSharedPointer<AccountEntity> > &newAccounts);

private:
    QVector<QSharedPointer<AccountEntity>> _accounts;

};

#endif // RAWACCOUNTMODEL_H
