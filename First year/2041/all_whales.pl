#!/usr/bin/perl -w

use warnings;

%log = ();
while (<>) {
    chomp $line;
     @type = split / +/, $line, 2;   
    $type[1] =~ s/[ ]{2,}/ /;    
     $type[1] =~ s/^[ ]*//;    
     $type[1] =~ tr/A-Z/a-z/;
     $type[1] =~ s/[s]*[ ]*$//;
    
    push(@{ $log{$type[1]} }, $type[0]);
}

foreach $creature (sort keys %log) {
    $total = 0;
    foreach ( @{$log{$creature}} ) { $total += $_; }
    $pods = 0+@{$log{$creature}};
    printf "$creature observations:  $pods pods, $total individuals\n";
}
