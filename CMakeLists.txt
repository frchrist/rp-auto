cmake_minimum_required(VERSION 3.16)
project(BankApp VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

qt_add_executable(BankApp WIN32 MACOSX_BUNDLE
    Engines/reconciliationengine.cpp Engines/reconciliationengine.h
    Entities/accountentity.cpp Entities/accountentity.h
    Entities/baseentity.cpp Entities/baseentity.h
    Entities/indexerentity.cpp Entities/indexerentity.h
    Modals/aboutdialog.cpp Modals/aboutdialog.h
    Modals/bankreconciliationmodal.cpp Modals/bankreconciliationmodal.h Modals/bankreconciliationmodal.ui
    Models/bankrecmodel.cpp Models/bankrecmodel.h
    Types/EntityTypes.h
    accountutil.cpp accountutil.h
    appalgorithms.cpp appalgorithms.h
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    parser.cpp parser.h
    rawaccountmodel.cpp rawaccountmodel.h
)
target_link_libraries(BankApp PRIVATE
    # Remove: network
    Qt::Core
    Qt::Gui
)


# Resources:
set(ressources_resource_files
    "images/1.png"
    "images/2.png"
    "images/3.png"
    "images/4.png"
    "images/5.png"
    "images/main.png"
    "images/mainxl.png"
)

qt_add_resources(BankApp "ressources"
    PREFIX
        "/images"
    FILES
        ${ressources_resource_files}
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(BankApp PRIVATE
        Qt::Widgets
    )
endif()

install(TARGETS BankApp
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
