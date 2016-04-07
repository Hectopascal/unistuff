#!/usr/bin/perl -w
$total = 0;
$ribbon = 0;
while ($line = <>){
    chomp $line;
    my @input = split /x/, $line; 

    ####Part 1  
    $a = $input[0]*$input[1];
    $b = $input[1]*$input[2];
    $c = $input[2]*$input[0];
    my @paper = sort { $a <=> $b } ($a,$b,$c);
    $total += 2*($a+$b+$c) + $paper[0];

    ####Part 2
    @sorted = sort {$a <=> $b} @input;
    $ribbon += 2*($sorted[0]+$sorted[1]) + $sorted[0]*$sorted[1]*$sorted[2];
}
print "paper: $total\n";
print "ribbon: $ribbon\n";