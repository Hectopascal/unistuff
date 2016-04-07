#!/bin/sh

#generate result file
echo $#
echo $1
echo $2
var=$1
while [ "$var" -ge "0" ]
do
	(time ./sortA < "$2") 2>> $2.txt
	var=`expr $var - 1`
done

egrep user < $2.txt| tr -d 'a-z'>$2.txt
