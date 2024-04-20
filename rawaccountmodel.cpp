#include "rawaccountmodel.h"
#include "Entities/indexerentity.h"

#include <QDate>
#include <QColor>
#include <QBrush>
RawAccountModel::RawAccountModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int RawAccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _accounts.size();
}

int RawAccountModel::columnCount(const QModelIndex &parent) const
{
     Q_UNUSED(parent);
    return 5;
}

QVariant RawAccountModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    AccountEntity& acc = *_accounts[index.row()];
    bool noReal  = acc.isSolde() || acc.isTotal();
    if(role == Qt::DisplayRole){

        switch (index.column()) {
        case 0:
            return noReal ? "-": acc.date().toString("dd/MM/yyyy");
            break;
        case 1:
            return noReal ? "-" : acc.reference();
            break;
        case 2:
            return acc.label();
            break;
        case 3:
            return acc.isTotal() ? QString::number(acc.gtAmount()) : (acc.debit() > 0 ? QString::number(acc.debit())  : "");
            break;
        case 4:
            return acc.isTotal() ? QString::number(acc.gtAmount()) : (acc.credit() > 0 ? QString::number(acc.credit()) : "");
            break;
        default:
            break;
        }
    }

    if(role == Qt::BackgroundRole && noReal ){
        return QVariant(QBrush(QColor(200,185,231,100)));
    }
    if(role == Qt::BackgroundRole && acc.isIndexed()){
        return QVariant(QBrush(QColor(86,251,131,40)));
    }
    if(role == Qt::BackgroundRole &&
        acc.indexer()->getReason() == IndexerEntity::WHY::ENTREPRISE_RECORED_IT_WRONG){
        return QVariant(QBrush(QColor(200,10,131,40)));
    }
    return QVariant();
}

QVariant RawAccountModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
        switch (section) {
        case 0:
            return "Date";
            break;
        case 1:
            return "Réf";
            break;
        case 2:
            return "Libellé";
            break;
        case 3:
            return "Débit";
            break;
        case 4:
            return "Crédit";
            break;
        default:
            break;
        }
    }
    return QVariant();
}

QVector<QSharedPointer<AccountEntity> > RawAccountModel::accounts() const
{
    return _accounts;
}

void RawAccountModel::setAccounts(const QVector<QSharedPointer<AccountEntity> > &newAccounts)
{
    beginResetModel();
    _accounts = newAccounts;
    endResetModel();
}



