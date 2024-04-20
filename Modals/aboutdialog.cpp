#include "aboutdialog.h"
#include <QCoreApplication>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPushButton>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
        setWindowTitle("A Propos");
        setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
        setMinimumSize(400, 300);
        setMaximumSize(450,300);

        QLabel *iconLabel = new QLabel(this);
        QPixmap icon(":/images/images/mainxl.png");
        iconLabel->setPixmap(icon.scaled(128, 128, Qt::KeepAspectRatio));
        QString name = QCoreApplication::applicationName();
        QLabel *titleLabel = new QLabel(name, this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

        QLabel *versionLabel = new QLabel("Version "+QCoreApplication::applicationVersion(), this);
        versionLabel->setAlignment(Qt::AlignCenter);

        QLabel *descriptionLabel = new QLabel("Outil simple et éfficace pour vos problèmes de rapprochement bancaire "
                                              "<hr>"+
                                              name+" a été conçu pour aider les utilisateurs à résoudre facilement et efficacement leurs problèmes de rapprochement bancaire.<br/>"+
                                              name+" permet de comparer les données bancaires avec les données comptables et d'identifier rapidement les écarts éventuels.", this);
        descriptionLabel->setTextFormat(Qt::RichText);
        descriptionLabel->setWordWrap(true);


        QPushButton *okButton = new QPushButton("Fermer", this);
        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(iconLabel, 0, Qt::AlignCenter);
        layout->addWidget(titleLabel, 0, Qt::AlignCenter);
        layout->addWidget(versionLabel, 0, Qt::AlignCenter);
        layout->addWidget(descriptionLabel, 1);
        layout->addWidget(okButton, 0, Qt::AlignCenter);
 }


