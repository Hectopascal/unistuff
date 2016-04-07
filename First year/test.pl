#!/usr/bin/perl -w

use warnings;

while ($line = <STDIN>) {
    chomp $line;
     @type = split / +/, $line, 2;   
    foreach ( @type ) { print "$_\n" }

}