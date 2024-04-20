#include "accountutil.h"


QPair<BaseEntity::AmountType, double> AccountUtil::Solde(QPair<double, double> to)
{
    if(to.first > to.second){
        return QPair<BaseEntity::AmountType, double>(BaseEntity::AmountType::CREDIT, to.first - to.second);
    }else if(to.first < to.second){
        return QPair<BaseEntity::AmountType, double>(BaseEntity::AmountType::DEBIT, to.second - to.first);
    }else{
        return QPair<BaseEntity::AmountType, double>(BaseEntity::AmountType::DEBIT, 0);
    }
}
QPair<double, double> AccountUtil::Total(QVector<QSharedPointer<AccountEntity>> acc)
{
    double debit = 0;
    double credit = 0;
    for(int i = 0; i < acc.size(); i++){
        debit += acc.at(i)->debit();
        credit += acc.at(i)->credit();
    }
    return QPair<double, double>(debit,credit);
}

QVector<QSharedPointer<AccountEntity>> AccountUtil::Diff(QVector<QSharedPointer<AccountEntity> > arr, QVector<QSharedPointer<AccountEntity> > arr_2)
{
    QVector<QSharedPointer<AccountEntity>> diff;
    /*
    for(auto &acc : arr){
        for(auto &acc_2 : arr_2){
            if(acc->reference() == acc_2->reference() && acc->credit() == acc_2->debit() && acc->debit() == acc_2->credit()){
                acc->setIsIndexed(true);
                acc_2->setIsIndexed(true);
            }
        }

    } */
    for(auto &acc : arr){
        if(!acc->isIndexed()  && !acc->isTotal()){
            if(acc->isSolde()){
                acc->setSource(AccountEntity::Type::FROM_BANK);
                acc->inverse();
                diff.insert(0,std::move(acc));
            }else{
                acc->inverse();
                diff.push_back(std::move(acc));
            }

        }
    }
    for(auto &acc_2 : arr_2){
        if(!acc_2->isIndexed()  && !acc_2->isTotal()){
            if(acc_2->isSolde()){
                acc_2->setSource(AccountEntity::Type::ACCOUNT);
                acc_2->inverse();
                diff.insert(0,std::move(acc_2));
            }else{
                acc_2->inverse();
                diff.push_back(std::move(acc_2));
            }

        }
    }

    return diff;

}
