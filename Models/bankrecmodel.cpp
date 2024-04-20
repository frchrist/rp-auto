#include "bankrecmodel.h"
#include <QColor>
#include <QBrush>
BankRecModel::BankRecModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int BankRecModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    //return std::max(_bankCorrections.size(), _entrepriseCorrections.size());
    return _entrepriseCorrections.size();
}

int BankRecModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 10;
}

QVariant BankRecModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    auto entrepiseRow = _entrepriseCorrections.at(index.row());
    auto bankRow = _bankCorrections.at(index.row());
    if(role == Qt::DisplayRole){
        switch (index.column()) {
            case 0:
            return entrepiseRow->isSolde() || entrepiseRow->isTotal() ? "-": entrepiseRow->date().toString("dd/MM/yyyy");
                break;
            case 1:
                return entrepiseRow->isSolde() || entrepiseRow->isTotal() ? "-" : entrepiseRow->reference();
                break;
            case 2:
                return entrepiseRow->label();
                break;
            case 3:
                return entrepiseRow->isTotal() ? QString::number(entrepiseRow->gtAmount()) : (entrepiseRow->debit() > 0 ? QString::number(entrepiseRow->debit())  : "");
                break;
            case 4:
                return entrepiseRow->isTotal() ? QString::number(entrepiseRow->gtAmount()) : (entrepiseRow->credit() > 0 ? QString::number(entrepiseRow->credit()) : "");
                break;
            case 5:
                return bankRow->isSolde() || bankRow->isTotal() ? "-": bankRow->date().toString("dd/MM/yyyy");
                break;
            case 6:
                return bankRow->isSolde() || bankRow->isTotal() ? "-" : bankRow->reference();
                break;
            case 7:
                return bankRow->label();
                break;
            case 8:
                return bankRow->isTotal() ? QString::number(bankRow->gtAmount()) : (bankRow->debit() > 0 ? QString::number(bankRow->debit())  : "");
                break;
            case 9:
                return bankRow->isTotal() ? QString::number(bankRow->gtAmount()) : (bankRow->credit() > 0 ? QString::number(bankRow->credit()) : "");
                break;
            default:
                break;
            }
        }

    if(role == Qt::BackgroundRole && entrepiseRow->isSolde() ){
        return QVariant(QBrush(QColor(40,200,150,150)));
    }

    return QVariant();
}

QVariant BankRecModel::headerData(int section, Qt::Orientation orientation, int role) const
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
        case 5:
            return "Date";
            break;
        case 6:
            return "Réf";
            break;
        case 7:
            return "Libellé";
            break;
        case 8:
            return "Débit";
            break;
        case 9:
            return "Crédit";
            break;
        default:
            break;
        }
    }
    return QVariant();
}

op_cor_t BankRecModel::bankCorrections() const
{
    return _bankCorrections;
}

void BankRecModel::setBankCorrections(const op_cor_t &newBankCorrections)
{
    _bankCorrections = newBankCorrections;
}

op_cor_t BankRecModel::entrepriseCorrections() const
{
    return _entrepriseCorrections;
}

void BankRecModel::setEntrepriseCorrections(const op_cor_t &newEntrepriseCorrections)
{
    _entrepriseCorrections = newEntrepriseCorrections;
}

void BankRecModel::setAndResetModel(op_cor_t d1, op_cor_t d2)
{
    beginResetModel();
    setBankCorrections(d2);
    setEntrepriseCorrections(d1);
    endResetModel();
}



