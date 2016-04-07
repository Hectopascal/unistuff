#!/usr/bin/python



keyword = s.lower($ARGV[0]);
count = 0;
while $line = <STDIN> :
    #chomp $line;
    str.split(str=/[^a-zA-Z]+/, num=string.count(str))
    #@words = split /[^a-zA-Z]+/,$line;
    @words = grep { $_ ne ''} @words;
    #$num += scalar(@words);

    foreach $element (@words) {

        if(lc($element) eq lc($keyword)){$count++;}
    }
}

print keyword, " occurred ", count," times\n";
