#!/usr/bin/perl -w

foreach $line (<STDIN>) {
    chomp $line;
    @words = split(/[^a-zA-Z]+/,$line);
    @words = grep { $_ ne ''} @words;
    $num += scalar(@words);
}
print "$num words\n";
