#!/usr/bin/perl -w

#$urlu = "http://www.handbook.unsw.edu.au/undergraduate/courses/2015/COMP9041.html";

$course =0;
$course = $ARGV[0];
$url = "http://www.handbook.unsw.edu.au/undergraduate/courses/2015/$course.html";


open F, "wget -q -O- $url|" or die;
while ($line = <F>) {
    #chomp $line;
    if(index($line, "Prerequisite") != -1){
        $line =~ s/([A-Z][A-Z][A-Z][A-Z])|.+/$1/ ;
    print $line;
    }
}