#!/usr/bin/perl -w
use warnings;
 


#useful regex: /"(?:[^"\\]|\\.)*"/  anything in quoted string

foreach $line (<STDIN>) {
    chomp $line;
    $line =~ s/^\s+|\s+$//g 
    #trim leading and trailing whitespace

    if ($line =~ /#!\/bin\/sh/) {
        $line = "#!/usr/bin/python2.7 -u\n";
        print $line;
        $line = "import glob, subprocess\n" ;

    } elsif($line =~ /^echo (.*)/){ 
        @toPrint = split $1;
        @toPrint = grep { $_ ne '' } @toPrint;
        print "print ";
        while $i < scalar @toPrint){
            print "'$word', ";
        }
        print 'hello', 'world'
    } elsif (){



    } elsif (){}


    }elsif($line =~ /^exit$/){
        print "exit()";
    }


}
