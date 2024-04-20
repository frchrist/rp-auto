#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Modals/bankreconciliationmodal.h"
#include "Modals/aboutdialog.h"
#include "Engines/reconciliationengine.h"
#include "rawaccountmodel.h"
#include "accountutil.h"
#include "parser.h"
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _reconciliationEngine(new ReconciliationEngine(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Accueil");
    this->initCon();
    setCurrentStep(STEPS::INIT);
    _model1 = new RawAccountModel(this);
    _model2 = new RawAccountModel(this);
    ui->myBankView->setModel(_model1);
    ui->myBankView_2->setModel(_model2);
    for (int i = 0; i < ui->myBankView->model()->columnCount(QModelIndex()); ++i) {
        ui->myBankView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        ui->myBankView_2->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initCon()
{
    QObject::connect(ui->recBtn, &QPushButton::clicked, this, &MainWindow::onReconcilationClicked);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onBtn1Clicked);
    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onBtn2Clicked);
    QObject::connect(ui->pointerBtn, &QPushButton::clicked, this, &MainWindow::onPointerClicked);
    QObject::connect(_reconciliationEngine, &ReconciliationEngine::pointageSuccessed, this, [&](){
        _model1->setAccounts(_reconciliationEngine->entrepriseAccount());
        _model2->setAccounts(_reconciliationEngine->bankAccount());
    });

    QObject::connect(_reconciliationEngine, &ReconciliationEngine::precessDone, this, [&](const AccountEntityPtrVector& d1,const AccountEntityPtrVector& d2){
        BankReconciliationModal* modal = new BankReconciliationModal(this);
        modal->setModalData(d1, d2);
        modal->exec();
        delete modal;
    });

    QObject::connect(this, &MainWindow::currentStepChanged, this, [&](){
        switch (_currentStep) {
        case STEPS::INIT:
            ui->pushButton->setEnabled(true);
            ui->arrow1->setEnabled(false);
            ui->arrow2->setEnabled(false);
            ui->arrow3->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pointerBtn->setEnabled(false);
            ui->recBtn->setEnabled(false);
            break;
        case STEPS::LOAD_ENT_OPERATIONS:
            ui->arrow1->setEnabled(true);
            ui->arrow2->setEnabled(false);
            ui->arrow3->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pointerBtn->setEnabled(false);
            ui->recBtn->setEnabled(false);
            break;
        case STEPS::LOAD_BANK_OPERATION:
            ui->arrow1->setEnabled(true);
            ui->arrow2->setEnabled(true);
            ui->arrow3->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pointerBtn->setEnabled(true);
            ui->recBtn->setEnabled(false);
            break;
        case STEPS::POINTED:
            ui->arrow1->setEnabled(true);
            ui->arrow2->setEnabled(true);
            ui->arrow3->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pointerBtn->setEnabled(true);
            ui->recBtn->setEnabled(true);
        case STEPS::MAKE_RECONCILICATION:
            break;
        default:
            break;
        }
    });

    QObject::connect(this->ui->actionA_Propos, &QAction::triggered, this, [&](){
        AboutDialog* about = new AboutDialog(this);
        about->exec();
    });
}


void MainWindow::onRecBtnClicked(){
}

QList<QSharedPointer<AccountEntity>> MainWindow::parsedAccountData(const QTextStream& stream, bool bSource )
{
    auto con = Parser::parseCSV(stream, true, bSource);
    QSharedPointer<AccountEntity> total = AccountEntity::createTotalLine();
    QPair<double, double> totalValue =AccountUtil::Total(con);
    QPair<BaseEntity::AmountType, double> soldeValue = AccountUtil::Solde(totalValue);
    total->setAmount(totalValue.first,AccountEntity::AmountType::DEBIT);
    total->setAmount(totalValue.second,AccountEntity::AmountType::CREDIT);

    QSharedPointer<AccountEntity> solde = AccountEntity::createSoldeLine();
    solde->setAmount(soldeValue.second, soldeValue.first);
    con.append(solde);
    con.append(total);

    return con;
}

MainWindow::STEPS MainWindow::currentStep() const
{
    return _currentStep;
}

void MainWindow::setCurrentStep(STEPS newCurrentStep)
{
    if (_currentStep == newCurrentStep)
        return;
    _currentStep = newCurrentStep;
    emit currentStepChanged();
}

void MainWindow::resetCurrentStep()
{
    setCurrentStep(STEPS::INIT);
}

void MainWindow::onBtn1Clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Ouvrir Un fichier"), "", tr("Fichier CSV (*.csv)"));
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            auto con = parsedAccountData(stream, false);
            _model1->setAccounts(con);

            file.close();
            setCurrentStep(STEPS::LOAD_ENT_OPERATIONS);
        } else {
            qDebug() << "Failed to open file: " << file.errorString();
        }
    }

}

void MainWindow::onBtn2Clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Ouvrir Un fichier"), "", tr("Fichier CSV (*.csv)"));
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            auto con = parsedAccountData(stream,true);
            _model2->setAccounts(con);

            file.close();
            setCurrentStep(STEPS::LOAD_BANK_OPERATION);
        } else {
            qDebug() << "Failed to open file: " << file.errorString();
        }
    }

}

void MainWindow::onReconcilationClicked()
{
    if(_reconciliationEngine->entrepriseAccount().isEmpty())
        return;
    if(_reconciliationEngine->bankAccount().isEmpty())
        return;
       setCurrentStep(STEPS::MAKE_RECONCILICATION);
    _reconciliationEngine->processAndCorrectOperation();

}

void MainWindow::onPointerClicked(){
    _reconciliationEngine->setEntrepriseAccount(_model1->accounts());
    _reconciliationEngine->setBankAccount(_model2->accounts());
    _reconciliationEngine->point();
    setCurrentStep(STEPS::POINTED);
}
