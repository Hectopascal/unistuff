fsd
print "@ARGV", "\n"; prints array individually with spaces 

print @ARGV, "\n"; prints array w/o spaces in between


while(sline <STDIN){
    $line =~ s/[aeiou]//g
    print



}
-------------

$opposite = 0;
$match_only_print = 0;

if ($ARGV[0] eq "-v"){
    $opposite = 1;
    shift(@ARGV);
}
if ($ARGV[0] eq "-v"){
    $match_only_print = 1;
    shift(@ARGV);
}

if (@ARGV ==0){
    print "Usage: $0 [-v -o] <regex>";
    exit 1;
}
$regex = shift(@argv);
if(@ARGV == 0){
    doGrep(STDIN);
} else {
    foreach my $file (@ARGV){
        if(!open(HANDLE, "$file")){
            print STDERR "invalid file \n";
            exit 0;
        }
        doGrep(HANDLE);
        close(HANDLE);
    }
}

sub doGrep {
    (my $HANDLE, my $regex) = @_; #
    while (my $line = <STDIN>){
        if($line =~ /$regex/){
            chomp $line;

            if(!$opposite){
                if($match_only_print){
                    print $1 , "\n";
                } else {
                    print $line, "\n";
                }
            }
        }elsif ($opposite) {
            print $line;
        } 
    }
}

--------

regex reads groups in brackets
eg.
((abc)d)(e)

(abc) == $1
((bc)d) == $2
(e) == $3


--------

#can't read and write file at the same time

2 Ways:
1. read the file and write to another file; close, remove old file and replace
2. read file, write to array and write array into another file.

eg.
for $arg (@ARGV){
    open IN , "arg";
    @contents = <IN>;
    close IN;

    open OUT;
    foreach $line (@contents){
        print OUT "$line" if $line !~ /^\s*$/;
    }
    close OUT;
}


-----------

glob() searches directory for files matching the pattern and returns them in an array.
