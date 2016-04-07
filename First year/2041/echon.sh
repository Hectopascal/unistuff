#!/bin/sh

num='^[0-9]+$'

if [[ $# != 2 ]]
    then
    echo 'Usage: ./echon.sh <number of lines> <string>'

elif [[ "${1//[0-9]}" != "" ]]  || (( $1 < 0))
    then
    echo './echon.sh: argument 1 must be a non-negative integer'

#elif [[ $1 -lt '0' ]] 
#    then
#    echo './echon.sh: argument 1 must be a non-negative integer'

else
    n=0
    while [[ $n -lt $1 ]]
        do
        echo "$2"
        ((n+=1))
    done
fi