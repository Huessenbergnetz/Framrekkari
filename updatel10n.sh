#!/bin/bash

#for LANG in de en_GB fr zh_CN
for LANG in en
do
lupdate -no-obsolete . -ts l10n/framrekkari_$LANG.ts
done

