#include "reconciliationengine.h"
#include "Entities/accountentity.h"
#include "Entities/indexerentity.h"
#include "accountutil.h"
#include "appalgorithms.h"
ReconciliationEngine::ReconciliationEngine(QObject* parent) : QObject{parent} {}


void ReconciliationEngine::point()
{
    if(_bankAccount.isEmpty() || _entrepriseAccount.isEmpty()){
        emit raiseError("Moteur de rapprochement bancaire, n'as pas tout le information pour proceder au traitement...");
    }
    int n = 0;
    for(auto &acc : _entrepriseAccount){
        n += 1;
        for(auto &acc_2 : _bankAccount){
            if(acc_2->indexer()->isIndexed()){
                continue;
            }
            if(this->recongnisedOperation(acc, acc_2)){
                QSharedPointer<IndexerEntity> indexer = QSharedPointer<IndexerEntity>::create(n, IndexerEntity::STATE::INDEXED, IndexerEntity::WHY::NO_REASON);
                acc->setIndexer(indexer);
                acc_2->setIndexer(indexer);
                qDebug() << acc->label();
            }
        }
    }

    for(auto &acc : _entrepriseAccount){
        if(acc->indexer()->isIndexed() || acc->isTotal() || acc->isSolde()){
            continue;
        }
        n += 1;
        for(auto &acc_2 : _bankAccount){
            if(acc_2->indexer()->isIndexed() || acc_2->isTotal() || acc_2->isSolde()){
                continue;
            }

            if(this->recongnisedWrongRecordOperation(acc,acc_2)){
                QSharedPointer<IndexerEntity> indexer = QSharedPointer<IndexerEntity>::create(n, IndexerEntity::STATE::UNINDEXED, IndexerEntity::WHY::ENTREPRISE_RECORED_IT_WRONG);
                acc->setIndexer(indexer);
                acc_2->setIndexer(indexer);
                 qDebug() << acc->label();
            }
        }
    }
    emit pointageSuccessed();
}

AccountEntityPtrVector ReconciliationEngine::bankAccount() const
{
    return _bankAccount;
}

void ReconciliationEngine::setBankAccount(const AccountEntityPtrVector &newBankAccount)
{
    _bankAccount = newBankAccount;
}

AccountEntityPtrVector ReconciliationEngine::entrepriseAccount() const
{
    return _entrepriseAccount;
}

void ReconciliationEngine::setEntrepriseAccount(const AccountEntityPtrVector &newEntrepriseAccount)
{
    _entrepriseAccount = newEntrepriseAccount;
}

void ReconciliationEngine::sendUnIndexAccountLine()
{
    AccountEntityPtrVector unindexs;
    for(auto &_bank : _bankAccount){
        if(!_bank->isIndexed()){
            unindexs.push_back(_bank);
        }
    }
    for(auto &_ent : _entrepriseAccount){
        if(!_ent->isIndexed()){
            unindexs.push_back(_ent);
        }
    }
    emit sendAccountUnpointed(unindexs);
}

void ReconciliationEngine::insertTotalRows(AccountEntityPtrVector& op_vector)
{
    QSharedPointer<AccountEntity> total = AccountEntity::createTotalLine();
    QSharedPointer<AccountEntity> solde = AccountEntity::createSoldeLine();

    QPair<double, double> t_value =AccountUtil::Total(op_vector);
    QPair<BaseEntity::AmountType, double> s_value = AccountUtil::Solde(t_value);
    total->setAmount(t_value.first,AccountEntity::AmountType::DEBIT);
    total->setAmount(t_value.second,AccountEntity::AmountType::CREDIT);

    solde->setAmount(s_value.second, s_value.first);
    op_vector.push_back(solde);
    op_vector.push_back(total);
}

void ReconciliationEngine::processAndCorrectOperation()
{
    AccountEntityPtrVector ent_op_vector;
    AccountEntityPtrVector bank_op_vector;
    for(auto &_etprise : entrepriseAccount()){
        if(_etprise->isTotal()){
            continue;
        }
        if(_etprise->isSolde()){
            AccountEntityPtr new_ent_Op = QSharedPointer<AccountEntity>(new AccountEntity(*_etprise.data()));
            new_ent_Op->inverse();
            ent_op_vector.insert(0, new_ent_Op);
            continue;
        }
        if(!_etprise->isIndexed()){
            AccountEntityPtr new_ent_Op = QSharedPointer<AccountEntity>(new AccountEntity(*_etprise.data()));
            new_ent_Op->inverse();
            if(new_ent_Op->indexer()->getReason() ==  IndexerEntity::WHY::ENTREPRISE_RECORED_IT_WRONG){
                // fine the correct amount from the bank
                //new_ent_Op->inverse();
                for(auto &bk : _bankAccount){
                    if(bk->indexer()->id() == _etprise->indexer()->id()){
                        double correct = bk->gtAmount() - _etprise->gtAmount();
                        new_ent_Op->setAmount(0, AccountEntity::AmountType::DEBIT);
                        new_ent_Op->setAmount(0, AccountEntity::AmountType::CREDIT);
                        switch (bk->type()) {
                            case AccountEntity::AmountType::DEBIT:
                                if(correct > 0){
                                    new_ent_Op->setAmount(correct, AccountEntity::AmountType::CREDIT);
                                }else{
                                    new_ent_Op->setAmount(std::abs(correct), AccountEntity::AmountType::DEBIT);
                                }
                                break;
                            case AccountEntity::AmountType::CREDIT:
                                if(correct > 0){
                                    new_ent_Op->setAmount(correct, AccountEntity::AmountType::DEBIT);
                                }else{
                                    new_ent_Op->setAmount(std::abs(correct), AccountEntity::AmountType::CREDIT);
                                }
                                break;
                            default:
                                break;
                        }
                    }
                }
                new_ent_Op->setLabel("Correction Erreur "+new_ent_Op->label());
                ent_op_vector.push_back(new_ent_Op);
                continue;
            }
            bank_op_vector.push_back(new_ent_Op);

        }
    }
    for(auto &bak : bankAccount()){
        if(bak->isTotal()){
            continue;
        }
        if(bak->isSolde()){
            AccountEntityPtr new_bak_Op = QSharedPointer<AccountEntity>(new AccountEntity(*bak.data()));
            new_bak_Op->inverse();
            bank_op_vector.insert(0,new_bak_Op);
            continue;
        }
        if(!bak->isIndexed() && bak->indexer()->getReason() !=  IndexerEntity::WHY::ENTREPRISE_RECORED_IT_WRONG){
            AccountEntityPtr new_bak_Op = QSharedPointer<AccountEntity>(new AccountEntity(*bak.data()));
            new_bak_Op->inverse();
            ent_op_vector.push_back(new_bak_Op);
        }
    }

    insertTotalRows(ent_op_vector);
    insertTotalRows(bank_op_vector);

    int size_a  = ent_op_vector.size();
    int size_b = bank_op_vector.size();
    double v1 = ent_op_vector.at(size_a - 2)->gtAmount();
    double v2 = bank_op_vector.at(size_b - 2)->gtAmount();
    qDebug() << v1;
    qDebug() << v2;
    if(size_a > size_b){
        for(int i = 0; i < size_a - size_b; i++){
            bank_op_vector.insert(size_b - 2 + i,AccountEntity::createEmptyLine());
        }
    }
    if(size_a < size_b){
        for(int i = 0; i <  size_b - size_a; i++){
            ent_op_vector.insert(size_a - 2 + i,AccountEntity::createEmptyLine());
        }
    }
    emit precessDone(ent_op_vector, bank_op_vector);

}

bool ReconciliationEngine::recongnisedOperation(AccountEntityPtr a, AccountEntityPtr b)
{
    bool debitCreditCheck = a->credit() == b->debit() && a->debit() == b->credit();
    if(!debitCreditCheck)
        return false;
    bool refCheck = a->reference() == b->reference() && debitCreditCheck;
    bool labelCheck = a->label() == b->label() &&  debitCreditCheck;
    return refCheck || labelCheck;
}

bool ReconciliationEngine::recongnisedWrongRecordOperation(AccountEntityPtr a, AccountEntityPtr b)
{
    if(a->isIndexed() || b->isIndexed())
        return false;
    bool debitCreditCheck = AppAlgorithms::levenshteinDistance(QString::number(a->credit()), QString::number(b->debit())) <= 3
                            && AppAlgorithms::levenshteinDistance(QString::number(a->debit()),QString::number(b->credit())) <= 3;
    if(!debitCreditCheck)
        return false;
    bool labelCheck = AppAlgorithms::levenshteinDistance(a->label(),b->label()) <= 3 &&  debitCreditCheck;
    bool refCheck = a->reference() == b->reference() && debitCreditCheck;
    return labelCheck || refCheck;
}

