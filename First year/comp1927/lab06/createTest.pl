#!/usr/bin/perl
use 5.010;
@num =1..5000;
while($#num+1){
say shift@num;
}
