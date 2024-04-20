#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class RawAccountModel;
class AccountEntity;
class ReconciliationEngine;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum class STEPS{
        INIT = 0,
        LOAD_ENT_OPERATIONS = 1,
        LOAD_BANK_OPERATION = 2,
        POINTED = 3,
        MAKE_RECONCILICATION = 4
    };

    STEPS currentStep() const;
    void setCurrentStep(STEPS newCurrentStep);
    void resetCurrentStep();

signals:
    void currentStepChanged();

private slots:
    void onRecBtnClicked();
    void onBtn1Clicked();
    void onBtn2Clicked();
    void onReconcilationClicked();
    void onPointerClicked();

private:
    Ui::MainWindow *ui;
    RawAccountModel *_model1;
    RawAccountModel *_model2;
    ReconciliationEngine* _reconciliationEngine;
    void initCon();
    QList<QSharedPointer<AccountEntity>> parsedAccountData(const QTextStream& stream, bool bSource);

    STEPS _currentStep;
    Q_PROPERTY(STEPS currentStep READ currentStep WRITE setCurrentStep RESET resetCurrentStep NOTIFY currentStepChanged FINAL)
};
#endif // MAINWINDOW_H
