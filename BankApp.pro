QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Engines/reconciliationengine.cpp \
    Entities/accountentity.cpp \
    Entities/baseentity.cpp \
    Entities/indexerentity.cpp \
    Modals/aboutdialog.cpp \
    Modals/bankreconciliationmodal.cpp \
    Models/bankrecmodel.cpp \
    accountutil.cpp \
    appalgorithms.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    rawaccountmodel.cpp

HEADERS += \
    Engines/reconciliationengine.h \
    Entities/accountentity.h \
    Entities/baseentity.h \
    Entities/indexerentity.h \
    Modals/aboutdialog.h \
    Modals/bankreconciliationmodal.h \
    Models/bankrecmodel.h \
    Types/EntityTypes.h \
    accountutil.h \
    appalgorithms.h \
    mainwindow.h \
    parser.h \
    rawaccountmodel.h

FORMS += \
    Modals/bankreconciliationmodal.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
