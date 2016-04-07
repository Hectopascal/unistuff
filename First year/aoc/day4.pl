#!/usr/bin/env perl

use strict;
use warnings;

use Digest::MD5 qw/md5_hex/;

my $prefix = 'iwrupvqb';

my $hash = '99';
my $x = 0;

while ($hash !~ m/^00000/) {
        $x++;
        $hash = md5_hex($prefix.$x);
}

print "Part one: $x\n"; #346386

$x = 0;
while ($hash !~ m/^000000/) {
        $x++;
        $hash = md5_hex($prefix.$x);
}

print "Part two: $x\n"; #9958218