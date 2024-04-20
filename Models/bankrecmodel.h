#ifndef BANKRECMODEL_H
#define BANKRECMODEL_H

#include <QAbstractTableModel>
#include <QObject>
#include "Entities/accountentity.h"
#include <QSharedPointer>
typedef QVector<QSharedPointer<AccountEntity>> op_cor_t;

class BankRecModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BankRecModel(QObject *parent = nullptr);
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


    op_cor_t bankCorrections() const;
    void setBankCorrections(const op_cor_t &newBankCorrections);

    op_cor_t entrepriseCorrections() const;
    void setEntrepriseCorrections(const op_cor_t &newEntrepriseCorrections);
    void setAndResetModel(op_cor_t d1, op_cor_t d2);

private:
    op_cor_t _bankCorrections;
    op_cor_t _entrepriseCorrections;

};

#endif // BANKRECMODEL_H
