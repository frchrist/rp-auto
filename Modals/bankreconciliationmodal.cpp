#include "bankreconciliationmodal.h"
#include "ui_bankreconciliationmodal.h"

BankReconciliationModal::BankReconciliationModal(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BankReconciliationModal)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::WindowMaximizeButtonHint);
    this->setMinimumSize(800, 500);

    _model = new BankRecModel(this);
    ui->tableView->setModel(_model);
    for (int i = 0; i < ui->tableView->model()->columnCount(QModelIndex()); ++i) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

BankReconciliationModal::~BankReconciliationModal()
{
    delete ui;
}

void BankReconciliationModal::setModalData(QVector<QSharedPointer<AccountEntity>> d1, QVector<QSharedPointer<AccountEntity>> d2)
{
    _model->setAndResetModel(d1,d2);
}
