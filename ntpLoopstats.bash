#!/bin/bash

ntpFolderNme1='/home/gred/corto_ntp/data/pc-corto1/'
ntpFolderNme2='/home/gred/corto_ntp/data/pc-corto2/'
ntpFolderNme3='/home/gred/corto_ntp/data/pc-serdi6/'
./makeFileList.bash $ntpFolderNme1
./makeFileList.bash $ntpFolderNme2
./makeFileList.bash $ntpFolderNme3
root -l ntpLoopstats.C\(\"$ntpFolderNme1\",\"$ntpFolderNme2\",\"$ntpFolderNme3\"\)

######/bin/bash

fileList='fileList'
#fileListFolder='/home/gred/corto_ntp/data/pc-corto1/'
fileListFolder=$1

cd $fileListFolder
rm $fileList
rm *~
for entry in `ls $search_dir`; do
    if [ "makeFileList.bash" != $entry ]; then
        if [ "makeFileList.bash~" != $entry ]; then
            echo $entry >> $fileList
        fi
    fi
done
cd -
