 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in de fi
do
lrelease framrekkari_$LANG.ts
done
