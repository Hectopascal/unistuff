useful regex


 \+(?=([^"\\]*(\\.|"([^"\\]*\\.)*[^"\\]*"))*[^"]*$)

[^\s"']+|"([^"]*)"|'([^']*)'




----------------
        #this works for double quotes only
        if($line =~ /echo +("(?:[^"\\]|\\.)*"|(?:.*?)) *(>> *"(?:[^"]*?)"|>>(?:[^"]*?))$/){
            #write to output file
            print "print $2, $1\n";
            #TODO:
            #consider backtix piped into files lmao
        }
-----------------



#useful regex: /"(?:[^"\\]|\\.)*"/  anything in quoted string



if($test =~ /(.*?) += +(.*)/){
push @string, "'$1' == '$2':\n"
}       
#######IMPT###### RMB TO TEST
    if($line =~ /\$[0-9]+/){
        if($sys ==0){
            splice @array, 1, 0, "import sys\n";
            $sys =1;
        }
        $line =~ s/\$([0-9]+)/sys.argv[$1]/g
    }

     elsif ($val =~ /^\$([0-9]+)/){
            if($sys ==0){
                splice @array, 1, 0, "import sys\n";
                $sys =1;
                $indentStart++;
            }

            push @array, "$var = sys.argv[$1]\n";

        }