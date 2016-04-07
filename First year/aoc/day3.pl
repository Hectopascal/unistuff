#!/usr/bin/perl -w

use warnings;

while ($line = <>) {
    chomp $line;
    @input = split //, $line;
}

@visited = ();
$curr=0;
push @visited, $curr;
$count = 1;
foreach $element (@input){
    if($element == "^"){ #up
        $curr = $curr + I;
    } elsif ($element == ">") { #right
        $curr = $curr + 1;
    } elsif ($element == "<") { #left
        $curr = $curr - 1;
    } else{ #down
        $curr = $curr - I;
    }

    unless( ){ 
        #unless $curr already exists, add to array and increase counter
        push @visited, $curr;
        $count++;
    }

}

print $count;
