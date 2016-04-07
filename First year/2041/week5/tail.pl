#!/usr/bin/perl -w

use warnings;

if (@ARGV == 0) {
    $num = 10;
    $arg = <STDIN>;
    if(index($arg, "<")  != -1){$arg =~ s/<//;}

    open(FILE,$arg) or die "tail.pl: can't open $arg";
    while (<FILE>) {
        $lines++; 
    } 
    $toShow = ($lines)-($num);
    while (<FILE>){
        print if ($. > $toShow);
    }
            
}
#read from standard input if no file name arguments are supplied
else{
    
    if(index($ARGV[0], "-")  != -1){   #case where N is specified
        #can adjust the number of lines displayed 
        #via an optional first argument -N
        $num = $ARGV[0];
        $num =~ s/-//;
        foreach $arg (@ARGV) {
            if(index($arg, "<")  != -1){$arg =~ s/<//;}
            unless($arg =~ $ARGV[0]){
                if (@ARGV > 2){print "==> $arg <==\n";}
                open(FILE,$arg) or die "tail.pl: can't open $arg"; 
                $lines++ while <FILE>;
                close FILE;
                $toShow = $lines-$num;
                open(FILE,$arg);
                while (<FILE>){
                    print if ($. > $toShow);
                }                
                #if!(-e $arg){print "tail.pl: can't open $arg";}
                #display the error message  for any unreadable file
                #if there are more than one named files, separate each by ==> FileName <==
                #not second argument/more than 1 file
                }
            }
 
    }else{ #N is by default 10
        $num = 10;
        foreach $arg (@ARGV) {
                        if(index($arg, "<")  != -1){$arg =~ s/<//;}

            if (@ARGV > 1) {print "==> $arg <==\n";}
            open(FILE,$arg) or die "tail.pl: can't open $arg";
            #if there are more than one named files, separate each by ==> FileName <==

            #if!(-e $arg){print "tail.pl: can't open $arg";}
                #display the error message  for any unreadable file
                            $lines++ while <FILE>;

            close FILE;
                $toShow = $lines-$num;
                open(FILE,$arg);
                while (<FILE>){
                    print if ($. > $toShow);
                }            
        }
    }



}

  
    #display the last N lines of each file (default N = 10)



