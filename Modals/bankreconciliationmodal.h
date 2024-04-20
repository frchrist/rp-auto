#ifndef BANKRECONCILIATIONMODAL_H
#define BANKRECONCILIATIONMODAL_H

#include <QDialog>
#include "Entities/accountentity.h"
#include "Models/bankrecmodel.h"
namespace Ui {
class BankReconciliationModal;
}

class BankReconciliationModal : public QDialog
{
    Q_OBJECT

public:
    explicit BankReconciliationModal(QWidget *parent = nullptr);
    ~BankReconciliationModal();
    void setModalData(QVector<QSharedPointer<AccountEntity>> d1, QVector<QSharedPointer<AccountEntity>> d2);

private:
    Ui::BankReconciliationModal *ui;
    BankRecModel* _model;

};

#endif // BANKRECONCILIATIONMODAL_H
