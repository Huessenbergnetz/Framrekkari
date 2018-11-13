TEMPLATE = subdirs

sfos {
SUBDIRS += sailfishos

OTHER_FILES += rpm/sailfishos.changes \
    rpm/harbour-framrekkari.spec \
    rpm/sailfishos.yaml
}
