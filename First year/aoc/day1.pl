#!/usr/bin/perl -w

use warnings;

while (<>) {
    chomp $_;
     @input = split //, $_;   
}
$level = 0;
$char = 0;
foreach $element (@input){
    $char++;
    if($element eq '('){
        $level++;
    } elsif ($element eq ')'){
        $level--;
    }
    if($level == -1){
        last;
    }
}
print "The character is $char\n";
print "The level is $level\n";