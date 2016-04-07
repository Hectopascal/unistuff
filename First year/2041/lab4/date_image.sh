#!/bin/sh


for file in $@
    do
    oDate=`date -r $file "+%m%d%H%M"`

    datime=`ls -l $file | sed -re 's/ +/ /g' | cut -d ' ' -f6-8`
    convert -gravity south -pointsize 36 -draw "text 0,10 '$datime'" $file $file
    
    

    touch -t $oDate $file
    
    
done
