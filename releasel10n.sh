 #!/bin/bash
 
STARTDIR=$PWD

cd l10n
for LANG in ca cs da de fi gl hu it nl_NL pl fr es sv nb_NO tr ru zh_CN
do
lrelease framrekkari_$LANG.ts
done
