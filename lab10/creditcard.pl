#!/usr/bin/perl -w
# written by andrewt@cse.unsw.edu.au as a COMP2041 programming example
# validate a credit card number by calculating its
# checksum using Luhn's formula (https://en.wikipedia.org/wiki/Luhn_algorithm)



foreach $arg (@ARGV){
    $validity = validate($arg);
    if ($validity == 1){
        print $arg, " is invalid  - does not contain exactly 16 digits\n";
    } elsif ($validity == 2){
        print $arg, " is invalid\n";
    } else {
        print $arg, " is valid\n";
    }
}
sub checksum {
    $num = $_[0];
    $checksum = 0;
    
    @digits = reverse split //, $num;
    $index = 0;
    foreach $element (@digits){
        $multiplier = 1 + $index % 2;
        $d = int($element) * $multiplier;
        if ($d > 9){
            $d -= 9;
        }
        $checksum += $d;
        $index++;
    }
    return $checksum;
}
sub validate {
    $credit_card = $_[0];
    $number = $credit_card;
    $number =~ s/[^0-9]//g;
    if (length $number != 16) {
        return 1;
    } elsif (checksum($number) % 10 == 0){
        return 0;
    } else {
        return 2;
    }
}
