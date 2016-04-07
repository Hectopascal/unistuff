#!/bin/sh


for f in *.jpg
do
      if [ -e "${f%.*}.png" ]
        then echo "${f%.*}.png already exists"
        exit
       fi
    convert "$f" "${f%.*}.png" 
    echo $f
done


for f in *.jpg
do
    rm "$f"
    
done

