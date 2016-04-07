#!/bin/sh



echo "Small files: `find . -type f -size -50c | sed -e 's/.\///g' | sort |tr "\\n" " "|sed "s/ $//"`"
echo "Medium-sized files: `find . -type f -size +49c -a -size -500c | sed -e 's/.\///g'| sort |tr "\\n" " "|sed "s/ $//"`"

echo "Large files: `find . -type f -size +499c | sed -e 's/.\///g'| sort| tr "\\n" " "|sed "s/ $//"`"
