#!/bin/bash

if [ ! -d l10n ]; then
    mkdir l10n
fi

lupdate-qt5 -no-obsolete -source-language en -target-language en -locations none . -ts l10n/framrekkari.ts
lupdate-qt5 -no-obsolete -pluralonly -source-language en -target-language en_US -locations none . -ts l10n/framrekkari_en_US.ts
lupdate-qt5 -no-obsolete -pluralonly -source-language en -target-language en_GB -locations none . -ts l10n/framrekkari_en_GB.ts
