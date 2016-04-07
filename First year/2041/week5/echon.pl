#!/usr/bin/perl -w
use warnings;


if (@ARGV != 2) {
print "Usage: ./echon.pl <number of lines> <string> at ./echon.pl line 3.\n";
} else {
    $x = $ARGV[0];

    for ($i = 0; $i < $x; $i++) {
            print "$ARGV[1]\n";   
    }
}