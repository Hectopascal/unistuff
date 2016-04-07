#!/usr/bin/perl -w

use warnings;


$keyword = lc($ARGV[0]);

    
foreach $file (glob "poets/*.txt"){
    open FILE, $file or die;
    $count = 0;
    $num = 0;
    while ($line = <FILE>) {
        chomp $line;
        @words = split /[^a-zA-Z]+/,$line; 
        @words = grep { $_ ne ''} @words; #remove empty string
        $num += scalar(@words); #add to total word count

        foreach $element (@words) { #count word occurrence
            if(lc($element) eq lc($keyword)){$count++;}
        }
        

    }
    $name = $file;
    $name =~ s/poets\// /g;
    $name =~ s/\_/ /g;
    $name =~ s/.txt//;

    $perc = $count/$num;
    printf "%4d/%6d =  %.9f %s\n", $count, $num, $perc, $name;
    close FILE;
}

