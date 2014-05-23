#!/bin/bash

for LANG in en
do
lupdate -no-obsolete . -ts l10n/framrekkari_$LANG.ts
done

