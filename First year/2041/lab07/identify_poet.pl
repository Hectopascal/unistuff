#!/usr/bin/perl -w

use warnings;

#so many hashes ooooOooo
%sample =();
%index = (); # multidimensional hash
%logvalues = ();
%max=();

#collect data from ALL SAMPLE files
foreach $text (@ARGV){ #DONE
    open FILE, $text or die;
    #reset counters
    $count = 0;
    $num = 0;    
    while ($line = <FILE>) {
        chomp $line;
        @poem = split /[^a-zA-Z]+/,$line; 
        @poem = grep { $_ ne ''} @poem; #remove empty string
        #@poem = grep /\S/, @poem; #remove strings of spaces
        $num += scalar(@poem); #add to total word count
        
        foreach $element (@poem) { #save words to hash
            $element = lc($element);
            $sample{$text}{$element}++; 
            #unnecessary word counting but whatev
        } 

    }

    close FILE;
}

#collect data for  every poet poets
foreach $file (glob "poets/*.txt"){

    open FILE, $file or die;
    #format name of author
    $name = $file;
    $name =~ s/poets\// /g;
    $name =~ s/\_/ /g;
    $name =~ s/.txt//;
    $name =~ s/^ //;
    #reset counters
    $count = 0;
    $num = 0;
    $log = 0;
    $totlog = 0;

    while ($line = <FILE>) { #iterate by LINE
        chomp $line;
        @list = split /[^a-zA-Z]+/,$line; 
        #@poem = grep /\S/, @poem; #remove strings of spaces
        @poem = grep { $_ ne ''} @poem; #remove empty string

        $num += scalar(@list); #add to total word count
        
        foreach $element (@list) { #count word occurrence
            $element = lc($element);
            #$element =~ s/^\s+//;
            #$element =~ s/\s+$//;
            $index{$name}{$element}++;
        } 

    } #all words saved; total words counted


    #compares data of each poet with all three samples
    foreach $file (keys %sample){ #iterate by file
        foreach $word (keys %{$sample{$file}}){ #iterate by words of file
            #log calculation
            if(exists $index{$name}{$word}){
                $log = log(($index{$name}{$word}+1)/$num); 
            } else {
                $log = log(1/$num); 
            }
            $totlog += $log; 

        }
        $logvalues{$file}{$name} = $totlog; #save to log of log values. how punny
    }

    close FILE;
}

foreach $thing (sort keys %logvalues) { #iterate by sample
    #printf "final log probability of %8.4f %s\n", $log{$poet}, $poet;
    $max = (sort { $logvalues{$thing}{$b} <=> $logvalues{$thing}{$a} } keys %{$logvalues{$thing}})[0];
    printf "%s most resembles the work of %s (log-probability=%8.4f)\n", $thing, $max, $logvalues{$thing}{$max};

}


    