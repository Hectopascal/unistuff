#!/usr/bin/perl -w

#use strict;
use warnings;

while ($line = <STDIN>) {
     $line =~ tr/0-9/<<<<<5>>>>/;
    print $line;
}
