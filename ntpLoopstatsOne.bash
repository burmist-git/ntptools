#!/bin/bash

########################################################################
#                                                                      #
# Copyright(C) 2017 - LBS - (Single person developer.)                 #
# Sun Nov 25 21:39:12 JST 2018                                         #
# Autor: Leonid Burmistrov                                             #
#                                                                      #
# File description:                                                    #
#                  this script builds time offset with respect to      #
#                  the ntp server.                                     #
# Input paramete:                                                      #
#                                                                      #
# This software is provided "as is" without any warranty.              #
#                                                                      #
########################################################################

#source /home/hvala/root/bin/thisroot.sh
source /home/usr/hvala/root_v5.34.34/root/bin/thisroot.sh

function ntpLoopstatsOne_bash {

    mkdir -p $3
    root -l -b -q $sourceHome/ntpLoopstatsOne.C\(\"$1\",\"$2\",\"$3\",\"$4\"\)
    
}

function printHelp {

    echo " --> ERROR in input arguments "
    echo " [0] -d     : default"
    echo " [1]        : full path to the file to analyze ex: ($filePath/loopstats.20181125)"
    echo " [0] -email : copy to hvala@arichsc and send email (using -sshpass key)"
    echo " [1]        : name of the file to copy and send"
    echo " [0] -h     : print help"

}

filePath="/var/log/ntpstats/"
fileNamePreff="loopstats."
sourceHome="/home/usr/hvala/ntptools/"
#sourceHome="/home/hvala/ntptools/"
#sourceHome="/home/burmist/home2/KEK/ntptools/"
pdfLogPath=$sourceHome'pdfLog_data/'
#sourceTempSlowControlHome="/home/hvala/temperaturefebmergerslowcontrol/"
#pcname=$(more /etc/hostname)
pcname=$HOSTNAME

if [ $# -eq 0 ] 
then
    
    printHelp
    
else

    if [ "$1" = "-d" ]; then

	if [ $# -eq 2 ]
        then   

	    filePathND=$(dirname $2)'/' 
	    fileNameND=$(basename $2)
            ntpLoopstatsOne_bash $filePathND $fileNameND $pdfLogPath $pcname

        elif [ $# -eq 1 ]; then

	    fileName=$fileNamePreff$(date +20%y%m%d)
	    FILEIN=$filePath/$fileName
	    if [ -f $FILEIN ]; then
		echo "File $FILEIN exists."
		ntpLoopstatsOne_bash $filePath $fileName $pdfLogPath $pcname
		echo "$pcname"
	    else
		echo "File $FILEIN does not exist."
	    fi

        else
            printHelp
        fi
	
    elif [ "$1" = "-email" ]; then
        
	if [ $# -eq 2 ]
        then   

	    filePathND=$(dirname $2)'/' 
	    fileNameND=$(basename $2)
            ntpLoopstatsOne_bash $filePathND $fileNameND $pdfLogPath $pcname
	    #echo "$pdfLogPath$fileName.pdf"
	    cp "$pdfLogPath$fileNameND.pdf" "$pdfLogPath$fileNameND.pdf"$(date +20%y%m%d)".pdf"
            #$sourceTempSlowControlHome/copyToKEKCC_BDAQ_arichsc.bash -email "$pdfLogPath$fileNameND.pdf" 'TimeSynchronisation'
	    #$sourceTempSlowControlHome/copyToKEKCC_BDAQ_arichsc.bash -sshpass "$pdfLogPath$fileNameND.pdf" 'TimeSynchronisation'

        elif [ $# -eq 1 ]; then

	    fileName=$fileNamePreff$(date +20%y%m%d)
	    ntpLoopstatsOne_bash $filePath $fileName $pdfLogPath $pcname
            #$sourceTempSlowControlHome/copyToKEKCC_BDAQ_arichsc.bash -email "$pdfLogPath$fileName.pdf" 'TimeSynchronisation'
	    #$sourceTempSlowControlHome/copyToKEKCC_BDAQ_arichsc.bash -sshpass "$pdfLogPath$fileName.pdf" 'TimeSynchronisation'

        else
            printHelp
        fi
        
    elif [ "$1" = "-h" ]; then
        
        printHelp
        
    else
        
        printHelp
        
    fi
    
fi

#espeak "I have done"
