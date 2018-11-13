 #!/bin/bash
 
STARTDIR=$PWD

cd sailfishos/l10n
for LANG in ar ca cs da de en_US en_GB fi gl hu it nl_BE nl_NL pl fr es sv nb_NO tr ru zh_CN
do
lrelease-qt5 framrekkari_$LANG.ts
done

cd $STARTDIR
