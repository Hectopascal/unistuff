#!/usr/bin/perl -w
use warnings;

%log = ();

$object = $ARGV[0];

foreach $line (<STDIN>) {
    chomp $line;
    @type = split / /, $line, 2;
    push(@{ $log{$type[1]} }, $type[0]);
}
#default values
$pods = 0;
$total=0;

if(exists($log{$object})){ 
    #check if search is valid and give values
    $pods = 0+@{$log{$object}};
    $total=0;
    foreach ( @{$log{$object}} ) { $total += $_; }
}
print "$object observations: $pods pods, $total individuals\n";

