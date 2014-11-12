 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in ca cs da de fi hu nl_NL pl fr es
do
lrelease framrekkari_$LANG.ts
done
