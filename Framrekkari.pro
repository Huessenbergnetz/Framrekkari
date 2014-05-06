TEMPLATE = app

TARGET = harbour-framrekkari

CONFIG += sailfishapp
#CONFIG += link_pkgconfig

QT += core
QT += network
QT += sql

#PKGCONFIG += mlite5

translations.path = /usr/share/harbour-framrekkari/translations
translations.files = l10n/*.qm
INSTALLS += translations

icons.path = /usr/share/harbour-framrekkari/icons
icons.files = icons/*.png
INSTALLS += icons

SOURCES += \
    src/main.cpp \
    src/configuration.cpp \
    src/models/accountsmodel.cpp \
    src/projectapi.cpp \
    src/network.cpp \
    src/api/projectsapi.cpp \
    src/api/apihelper.cpp \
    src/models/projectsmodel.cpp \
    src/dbmanager.cpp \
    src/models/favoredprojectsmodel.cpp

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    rpm/Framrekkari.spec \
    harbour-framrekkari.desktop \
    rpm/harbour-framrekkari.changes \
    rpm/harbour-framrekkari.yaml \
    qml/harbour-framrekkari.qml \
    qml/pages/About.qml \
    qml/pages/MainPage.qml \
    qml/pages/Settings.qml \
    qml/pages/Changelog.qml \
    qml/pages/parts/CLItem.qml \
    qml/dialogs/AccountDialog.qml \
    qml/delegates/AccountsDelegate.qml \
    qml/pages/AccountPage.qml \
    qml/pages/ProjectsListPage.qml \
    qml/delegates/ProjectsDelegate.qml \
    qml/common/FancyScroller.qml \
    qml/pages/ProjectPage.qml

HEADERS += \
    src/globals.h \
    src/configuration.h \
    src/models/accountsmodel.h \
    src/models/accountobject.h \
    src/projectapi.h \
    src/network.h \
    src/api/projectsapi.h \
    src/api/apihelper.h \
    src/models/projectsmodel.h \
    src/models/projectobject.h \
    src/dbmanager.h \
    src/models/favoredprojectsmodel.h \
    src/models/favoredprojectobject.h



