#!/usr/bin/perl -w
@input=<>;
while($#input+1){
	$cut=rand($#input+1);
	print $input[$cut-1];
	splice @input, $cut-1, 1;
}
