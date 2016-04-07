#!/usr/bin/perl -w
# Simple program to read the last n line(s) of a file. 
# Reads from the end of the file for effeciency 
# "\n" linux only, 
# usage tailz  filename  numberoflines 
use strict;

my $filename = shift or die "Usage: $0 file numlines\n";
my $numlines  = shift;
my $byte;

# Open the file in read mode 
open FILE, "<$filename" or die "Couldn't open $filename: $!";

# Rewind from the end of the file until count of eol 's
seek FILE,-1, 2;  #get past last eol 
my $count=0;
 while (1){
   seek FILE,-1,1;
   read FILE,$byte,1;
   if(ord($byte) == 10 ){
    $count++;
    if($count == $numlines){last}
    }

   seek FILE,-1,1;
 if (tell FILE == 0){last}
}
$/=undef;
my $tail = <FILE>;
print "$tail\n";
