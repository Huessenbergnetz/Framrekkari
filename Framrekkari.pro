TARGET = harbour-framrekkari

CONFIG += sailfishapp

translations.path = /usr/share/harbour-framrekkari/translations
translations.files = l10n/*.qm
INSTALLS += translations

SOURCES += \
    src/main.cpp

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
    qml/pages/parts/CLItem.qml

HEADERS += \
    src/globals.h



