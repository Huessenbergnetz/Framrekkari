 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in de
do
lrelease framrekkari_$LANG.ts
done
