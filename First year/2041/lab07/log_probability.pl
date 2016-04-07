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

    $log = log(($count+1)/$num);
    printf "log((%d+1)/%6d) =  %8.4f %s\n", $count, $num, $log, $name;
    close FILE;
}

