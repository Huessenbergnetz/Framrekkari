 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in da de fi hu pl
do
lrelease framrekkari_$LANG.ts
done
