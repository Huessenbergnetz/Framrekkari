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

images.path = /usr/share/harbour-framrekkari/images
images.files = icons/*.jpg
INSTALLS += images

contributors.path = /usr/share/harbour-framrekkari/images/contributors
contributors.files = icons/contributors/*.png
INSTALLS += contributors

transifexlangs.path = /usr/share/harbour-framrekkari/data
transifexlangs.files = data/transifex_langs.json
INSTALLS += transifexlangs

SOURCES += \
    src/main.cpp \
    src/configuration.cpp \
    src/models/accountsmodel.cpp \
    src/network.cpp \
    src/api/projectsapi.cpp \
    src/api/apihelper.cpp \
    src/models/projectsmodel.cpp \
    src/dbmanager.cpp \
    src/models/favoredprojectsmodel.cpp \
    src/api/statisticsapi.cpp \
    src/models/projectlangstatsmodel.cpp \
    src/models/projectresourcesmodel.cpp \
    src/api/translationstringsapi.cpp \
    src/models/projecttranslationsmodel.cpp \
    src/md5generator.cpp \
    src/languagenamehelper.cpp \
    src/notifications.cpp

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
    qml/dialogs/AccountDialog.qml \
    qml/delegates/AccountsDelegate.qml \
    qml/pages/AccountPage.qml \
    qml/pages/ProjectsListPage.qml \
    qml/delegates/ProjectsDelegate.qml \
    qml/common/FancyScroller.qml \
    qml/pages/ProjectPage.qml \
    qml/delegates/ProjectLangDelegate.qml \
    qml/pages/ResourcesPage.qml \
    qml/delegates/ResourcesDelegate.qml \
    qml/pages/TranslationStringsPage.qml \
    qml/delegates/TranslationsDelegate.qml \
    qml/pages/StringPage.qml \
    qml/delegates/PluralDelegate.qml \
    qml/js/helper.js \
    qml/common/OpenSlugField.qml \
    qml/common/MessageContainer.qml \
    qml/pages/PrivacyPolicy.qml \
    qml/dialogs/ListFilterDialog.qml \
    qml/dialogs/OneClickDialogItem.qml \
    qml/pages/Help.qml \
    qml/pages/StringMetaPage.qml \
    qml/BTComponents/ComboBoxList.qml \
    qml/BTComponents/PaypalChooser.qml \
    qml/BTComponents/Changelog.qml \
    qml/BTComponents/ChangelogModel.qml \
    qml/BTComponents/FirstStartInfo.qml \
    qml/BTComponents/ContributorsModel.qml \
    qml/BTComponents/ContributorsDelegate.qml \
    qml/BTComponents/Contributors.qml

HEADERS += \
    src/globals.h \
    src/configuration.h \
    src/models/accountsmodel.h \
    src/models/accountobject.h \
    src/network.h \
    src/api/projectsapi.h \
    src/api/apihelper.h \
    src/models/projectsmodel.h \
    src/models/projectobject.h \
    src/dbmanager.h \
    src/models/favoredprojectsmodel.h \
    src/models/favoredprojectobject.h \
    src/api/statisticsapi.h \
    src/models/langstatobject.h \
    src/models/projectlangstatsmodel.h \
    src/models/projectresourceobject.h \
    src/models/projectresourcesmodel.h \
    src/api/translationstringsapi.h \
    src/models/projecttranslationsmodel.h \
    src/models/translationsobject.h \
    src/md5generator.h \
    src/languagenamehelper.h \
    src/notifications.h

RESOURCES +=



