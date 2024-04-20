#ifndef RECONCILIATIONENGINE_H
#define RECONCILIATIONENGINE_H

#include <QObject>
#include "Types/EntityTypes.h"
class ReconciliationEngine : public QObject
{
   Q_OBJECT
public:
    explicit ReconciliationEngine(QObject* parent = nullptr);
    void point();
    // GETTER AND SETTERS
    AccountEntityPtrVector bankAccount() const;
    AccountEntityPtrVector entrepriseAccount() const;
    void setBankAccount(const AccountEntityPtrVector &newBankAccount);
    void setEntrepriseAccount(const AccountEntityPtrVector &newEntrepriseAccount);
    // SEND
    void sendUnIndexAccountLine();
    void processAndCorrectOperation();

signals:
    void raiseError(const QString&);
    void pointageSuccessed();
    void sendAccountUnpointed(AccountEntityPtrVector);
    void precessDone(const AccountEntityPtrVector&, const AccountEntityPtrVector&);

private:
    bool recongnisedOperation(AccountEntityPtr a, AccountEntityPtr b);
    bool recongnisedWrongRecordOperation(AccountEntityPtr a, AccountEntityPtr b);

private:
    AccountEntityPtrVector _bankAccount;
    AccountEntityPtrVector _entrepriseAccount;
    void insertTotalRows(AccountEntityPtrVector& d1);
};

#endif // RECONCILIATIONENGINE_H
