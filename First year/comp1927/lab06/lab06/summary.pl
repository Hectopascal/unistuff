#!/usr/bin/perl -w
use 5.010;
$sum = 0;
foreach (@ARGV){
	open (F,"+<$_") or die "cannot open file $_\n";
	@time = <F>;
	$line = $#time;
	while ($#time){
		$sum+=shift(@time);
	}
	$average = $sum/$line;
	print F "$average for $line tests\n";
	close F;
}
