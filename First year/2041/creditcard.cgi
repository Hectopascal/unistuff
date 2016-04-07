#!/usr/bin/perl -w
# written by andrewt@cse.unsw.edu.au as a COMP2041 programming example
# validate a credit card number by calculating its
# checksum using Luhn's formula (https://en.wikipedia.org/wiki/Luhn_algorithm)


use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

print header, start_html('Login');
warningsToBrowser(1);


print header, start_html("Credit Card Validation"), "\n";
warningsToBrowser(1);
$credit_card = param("credit_card");
if (defined $credit_card) {
    print validate($credit_card);
}
print end_html;
exit 0;


# Written by John Shepherdi July 2008

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
        return "$credit_card is invalid - does not contain exactly 16 digits\n";
    } elsif (checksum($number) % 10 == 0){
        return "$credit_card is valid\n";
    } else {
        return "$credit_card is invalid\n";
    }
}
