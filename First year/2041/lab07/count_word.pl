#!/usr/bin/perl -w

use warnings;


$keyword = lc($ARGV[0]);
    $count = 0;
while ($line = <STDIN>) {
    #chomp $line;
    @words = split /[^a-zA-Z]+/,$line;
    @words = grep { $_ ne ''} @words;
    #$num += scalar(@words);

    foreach $element (@words) {

        if(lc($element) eq lc($keyword)){$count++;}
    }
}

print "$keyword occurred $count times\n";
