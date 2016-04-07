#!/bin/sh

for file in $@ 
do
    display "$file"

    echo "Address to email this image to?" 
    read email
    echo "Message to accompany image?" 
    read message
    echo $message |mutt -s 'image' -a "$file" -- $email
    echo "$file sent to $email"
done
