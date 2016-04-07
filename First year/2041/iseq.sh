#!/bin/sh

start=1
inc=1
if [ $# -lt 1] || [$# -gt 4 ]
then echo "Usage: $0 [start [inc] <num>"

elif [ $# -eq 1 ]
then
    end=$1
elif [ $# -eq 2 ]
then
    start=$1
    end=$2
else
        start=$1
        inc=$2
        end=$3
fi

curr=$start
while [ $curr -le $end ]
do
    echo $curr
    curr=$(($curr + $inc))
done