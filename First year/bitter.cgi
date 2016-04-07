#!/usr/bin/perl -w

# written by andrewt@cse.unsw.edu.au September 2015
# as a starting point for COMP2041/9041 assignment 2
# http://cgi.cse.unsw.edu.au/~cs2041/assignments/bitter/

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;
use CGI::Session;
use DateTime;
use Mail::Sendmail;
use File::Copy;



sendmail(
    From    => 'sender@somewhereelse.com',
    To      => 'recipient@somewhere.com',
    Subject => 'some subject',
    Message => "body of the message",
);


@userdetail=();
@bleats=();
@onebleat=();
@listens=();
@bleatstoprint=();

$username = param('username') || '';
$password = param('password') || '';
$email = param('email') || '';
$loggedIn = param('loggedin') || 0;
%information={};

sub main() {
    # print start of HTML ASAP to assist debugging if there is an error in the script
    print page_header();
    
    # Now tell CGI::Carp to embed any warning in HTML
    warningsToBrowser(1);

    # define some global variables
    $debug = 1;
    $dataset_size = "medium"; 
    $users_dir = "dataset-$dataset_size/users";
    $bleats_dir = "dataset-$dataset_size/bleats";

    
    if ($username && $password) {
        authenticate();
    }
    if (defined param('newaccount')){
        create_acc();
    }
    if (defined param('pwdemail')){
    	mail_pwd();
    }
    if($loggedIn == 1){
        buffer_details();
        #form submissions
     	if(defined param('Bleating')){process_bleats();}
        if (defined param('listen')){listenusr();}
        if (defined param('unlisten')){unlisten();}
        if(defined param('imptsettings')){process_edits();} 
        if (defined param('normalsettings')){process_userinfo();}
        #determine page to show
	    print nav_panel();
        if (defined param('search')){
            search (); 
        } elsif (defined param('userlist')){
            list_users();
        } elsif(defined param('bleattoshow')){
            bleat_page();
        } elsif(defined param('settings') || defined param('normalsettings') || defined param('imptsettings')){
            settings();
	    } elsif (defined param('userprofile')){
            print user_page();
            print user_bleats();
        }else {
            print main_user_page();
            bleat_box();
            print main_user_bleats();
        }
    } elsif (defined param('resetPass')){
        print changepwd();
    }elsif (defined param('recoverpwd')){

	    print pwdrecovery();

    } else {
    
        login();
    }
    print page_trailer();
}


#---------------------------------------------------#
# Settings and user info                            #
#---------------------------------------------------#

sub settings(){
    print "<div class=\"center\">";
    print "<h3> Change your details </h3><br><br>\n";
    print start_form, "\n";

    print "New password:\n", password_field(-name=>'newpwd',
                                            -override=>1,
                                            -pattern=>"[A-Za-z0-9_\-]+",
                                            -maxlength=>30), "<br>\n";
    print "New email:\n", textfield(-name=>'email'), "<br>\n";
    print "Enter current password:\n", password_field(-name=>'oldpwd',
                                                      -override=>1,
                                                      -pattern=>"[A-Za-z0-9_\-]+",
                                                      -maxlength=>30), "<br>\n";
    print hidden('username',"$username"),"\n";
    print hidden('loggedin',"$loggedIn"),"\n";
    print submit('imptsettings','Change'), "\n";
    print end_form, "<br>\n";

    print start_form, "\n";
    print "Full Name: \n", textfield(-name=>'name',
				                     -default => $information{'full_name'},
				                     -maxlength=>30), "\n<br>";
    print "Home Latitude:\n", textfield(-name=>'latitude', 
                      	                -pattern=>"[0-9\.\-]+",
				     	                -default => $information{'home_latitude'},
                                        -maxlength=>30), "\n<br>";
    
    print "Home Longitude:\n", textfield( -name=>'longitude', 
                                       	 -default => $information{'home_longitude'},
					                     -pattern=>"[0-9\.\-]+",
                                       	 -maxlength=>30), "\n<br>";
   
    print "Profile description:<br>\n", textarea(-name=>'about',
			                                      -default=>$information{'about'},
			                                      -rows=>3,
                    	 	          		      -columns=>60,
			                                      -maxlength=>500),"\n<br>";
    print "Maximum length 500 characters, HTML formatting supported.<p>\n";
    print hidden('username',"$username"),"\n";
    print hidden('loggedin',"$loggedIn"),"\n";
    print submit('normalsettings','Edit'), "\n";
    print end_form, "<br>\n";

    print start_form, "\n";
    print hidden('username',"$username"),"\n";
    print hidden('loggedin',"$loggedIn"),"\n";
    print submit('suspendacc','Suspend Account'), "\n";
    print end_form, "<br>\n";

    print start_form, "\n";
    print hidden('username',"$username"),"\n";
    print hidden('loggedin',"$loggedIn"),"\n";
    print submit('deleteacc','Delete Account'), "\n";
    print end_form, "<br>\n";
    print "</div>";

}


sub process_userinfo{

    my $changed = 0; 
    #flag to check in case field does not exist
    #im running out of variable names fjalfdlsajfs;j;dflsakj;        
    

    if(defined param('name') && param('name') ne ''){
            @newdetails = ();
            $changed = 0;
            my $name = param('name');
            open my $c, "./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                while (my $line = <$c>){
                    chomp $line;
                    if ($line =~ /^full_name: (.*)/){
                        $changed = 1;
                        push @newdetails, "full_name: $name\n";
                        $changed = 1;
                    } else {
                        push @newdetails, "$line\n";                    
                    }
                }
            close $c;
            if ($changed != 1){
                 push @newdetails, "full_name: $name\n";
            }
            open my $e, '>',"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                foreach my $line (@newdetails){
                    print $e "$line";
                }
            
            close $e;
        }
        
        if(defined param('about') && param('about') ne ''){
            @newdetails = ();
            $changed = 0;
            my $about = param('about');
            open my $d, "./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                while (my $line = <$d>){
                    chomp $line;
                    if ($line =~ /^about: (.*)/){
                        push @newdetails, "about: $about\n";
                        $changed = 1;
                    } else {
                        push @newdetails, "$line\n";                    
                    }
                }
            close $d;
            if ($changed != 1){
                 push @newdetails, "about: $about\n";
            }
            open my $h, '>',"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                foreach my $line (@newdetails){
                    print $h "$line";
                }
            
            close $h;
        }
        if(defined param('latitude') && param('latitude') ne ''){
            @newdetails = ();
            $changed = 0;
            my $latitude = param('latitude');
            open my $b, "./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                while (my $line = <$b>){
                    chomp $line;
                    if ($line =~ /^home_latitude: (.*)/){
                        push @newdetails, "home_latitude: $latitude\n";
                        $changed= 1;
                    } else {
                        push @newdetails, "$line\n";                    
                    }
                }
            close $b;
            if ($changed != 1){
                 push @newdetails, "home_latitude: $latitude\n";
            }
            open my $p, '>',"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                foreach my $line (@newdetails){
                    print $p "$line";
                }
            
            close $p;
        }
        

        if(param('longitude') ne '' && defined param('longitude') ){
            @newdetails = ();
            my $longitude = param('longitude');
            $changed = 0;
         
            open my $a,"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username/details.txt";
                while (my $line = <$a>){
                    chomp $line;
                    if ($line =~ /^home_longitude: (.*)/){
                        push @newdetails, "home_longitude: $longitude\n";
                        $changed = 1;
                    } else {
                        push @newdetails, "$line\n";                    
                    }
                }
            close $a;
            
            if ($changed != 1){
                 push @newdetails, "home_longitude: $longitude\n";
            }            
            open my $k, '>',"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                foreach $blah (@newdetails){
                    print $k "$blah";
                }
            
            close $k;

        }
        print "information saved. \n";

}

sub process_edits{
    if (param('oldpwd') ne $information{'password'}) {
        print "Incorrect current password.";
    } else {

        
        if(defined param('newpwd') && param('newpwd') ne ''){
            @newdetails = ();
            $newpwd = param('newpwd');
            open my $b, "./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                while (my $line = <$b>){
                    chomp $line;
                    if ($line =~ /^password: (.*)/){
                        push @newdetails, "password: $newpwd\n";
                    } else {
                        push @newdetails, "$line\n";                    
                    }
                }
            close $b;
            open my $p, '>',"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                foreach my $line (@newdetails){
                    print $p "$line";
                }
            
            close $p;
            print "password changed.\n";
        }
        
        if(param('email') ne '' && defined param('email') ){
            @newdetails = ();
            $newemail = param('email');
            if ($newemail =~ /^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+[a-zA-Z0-9]$/){
                open my $a,"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username/details.txt";
                    while (my $line = <$a>){
                        chomp $line;
                        if ($line =~ /^email: (.*)/){
                            push @newdetails, "email: $newemail\n";
                        } else {
                            push @newdetails, "$line\n";                    
                        }
                    }
                close $a;
                
                open my $k, '>',"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                    foreach $blah (@newdetails){
                        print $k "$blah";
                    }
                
                close $k;

                print "email changed.\n";
            } else {
                print "incorrect email format\n";
            
            }
        }
    
    
    }
}

#---------------------------------------------------#
# GENERAL FUNCTIONS                                 #
#---------------------------------------------------#
sub list_users(){
    my @users = <./$users_dir/*>;
    my $directory = quotemeta"$users_dir";
    @users = grep(!/temporary/,@users);
    foreach my $user (@users) {
               $user =~ s/\.\/$directory\///;
               print '<form method="POST" action="">';
               print "<input type=\"hidden\" name=\"username\" value=\"$username\">";
               print  "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
               print "<input type=\"submit\" name=\"userprofile\" value=\"$user\" class=\"user_button\">\n";
               print "</form>";
    
    }
    return;

}


sub search(){
    $query = param('query');
    print "<div class=\"search\">";
    print start_form, "\n";
    print "Search \n", textfield('query'), "\n";
    print hidden('username',"$username"),"\n";
    print hidden('loggedin',"$loggedIn"),"\n";
    print submit('search','Search'), "\n";
    print end_form, "\n";
    print "</div>\n";
    $keyword = quotemeta "$query";
    $directory = quotemeta"$users_dir";
    $bleatdir = quotemeta"$bleats_dir";
    if (defined $keyword && $keyword ne ''){

        
        #check users
        print "<h4>Related Users</h4>";
        
        
        #match by username
        my @users = <./$users_dir/*>;
        %userresults = ();
        foreach $user (@users){
            open   (F, "$user/details.txt");
            while (my $detail = <F>){
                if ($detail =~ /^full_name: (.*)/){
                    my $fullname = $1;
                    if (($fullname =~ /$keyword/i || $user =~ /$keyword/i)){
                        $user =~ s/\.\/$directory\///;
                        $userresults{"$user"} = $fullname;
                    }      
                }
               
            }
            close F;
        
        }
       
        print "<div class=\"results\"\n>";

       if (%userresults){
            
            foreach my $key (keys %userresults) {
               print '<form method="POST" action="">';
               print "<input type=\"hidden\" name=\"username\" value=\"$username\">";
               print  "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
               print "<input type=\"submit\" name=\"userprofile\" value=\"$key\" class=\"profile_button\">\n";
               print "</form>";
               print "Full name: $userresults{$key}\n";
                
            }
        } else {
            print "nothing found!\n";
        }
        print "</div><p><br>";
        
        #check bleats
        print "<h4>Related Bleats</h4>";
        my @files = <./$bleats_dir/*>;
        $yes = 0;
        foreach my $file (@files) {

            @onebleat = ();
            open   (FILE, "$file");
            push @onebleat, "<div class=\"bitter_user_bleats\"\n>";
            while(my $line= <FILE> ){
                chomp $line;
                if ($line =~ /^bleat: (.*)/){
                    $tocheck = $1;
                    if ($tocheck =~ /$keyword/i){
                        $yes = 1;
                    } else {
                        $yes = 0;
                    }   
                    push @onebleat, "<b>$tocheck</b>\n";
                } elsif($line =~ /^time: (.*)/){
                    $difference = $1;
                    $dt = DateTime->new( year       => 1970,
                                          month      => 1,
                                          day        => 1,
                                          time_zone  => "Australia/Sydney",
                                         );
                    $dt->add(seconds => $difference);
                    $dt =~ s/T/ /;
                    push @onebleat, "$dt\n";
                } elsif ($line =~ /^username: (.*)/){
                    
                    $bleater = $1;

  
                } elsif ($line =~ /(^longitude: )|(^latitude: )/){
                    #ignore
                } else {
                    push @onebleat, "$line\n";
                }
            }
            close FILE;
            push @onebleat, '<form method="POST" action="">';
            push @onebleat, "<input type=\"hidden\" name=\"username\" value=\"$username\">";
            push @onebleat, "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
            push @onebleat, "<input type=\"submit\" name=\"userprofile\" value=\"$bleater\" class=\"profile_button\">";
            push @onebleat, "</form>";
            $element = $file;
            $element =~ s/\.\/$bleatdir\///;
            push @onebleat, '<form method="POST" action="">';
            push @onebleat, "<input type=\"hidden\" name=\"username\" value=\"$username\">";
            push @onebleat, "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
            push @onebleat, "<input type=\"hidden\" name=\"bleattoshow\" value=\"$element\" >";
            push @onebleat, "<input type=\"submit\" name=\"userprofile\" value=\"reply\" class=\"profile_button\">";
            push @onebleat, "</form>";

            push @onebleat, "</div>\n";
            if ($yes == 1){
                $bleatresult = join '', @onebleat;
                push @bleats, $bleatresult;
            } 
            
        }
        foreach $thingy (@bleats){
            print "$thingy";
        }
    }
    return;

}

sub buffer_details(){
    my $user_to_show  = "./$users_dir/$username";
    my $details_filename = "$user_to_show/details.txt";
    open my $p, "$details_filename" or die "can not open $details_filename: $!";
    while (my $line = <$p>){
        chomp $line;
        if ($line =~ /^listens: (.*)/){
            @listens = split(' ',$1);
            #$information{"listens"}= \@listens;
        }elsif($line =~ /([^:]+): (.*)/){
            $information{"$1"}= "$2";
        }
    }
    close $p;
}
sub nav_panel(){

   
   return <<eof
<div class="menu">
<form method="POST" action="">
<input type="hidden" name="username" value="$username">
<input type="hidden" name="n" value="Home">
<input type="hidden" name="loggedin" value="$loggedIn"><input type="submit" value="Home" class="bitter_button"></form>
<form method="POST" action="">
<input type="hidden" name="username" value="$username">
<input type="hidden" name="n" value="Home">
<input type="hidden" name="loggedin" value="$loggedIn">
<input type="submit" name="userlist" value="User List" class="bitter_button">
</form><form method="POST" action="">
<input type="hidden" name="username" value="$username">
<input type="hidden" name="n" value="Home">
<input type="hidden" name="loggedin" value="$loggedIn">
<input type="submit" name="search" value="Search" class="bitter_button">
</form>
<form method="POST" action="">
<input type="hidden" name="username" value="$username">
<input type="hidden" name="n" value="Home">
<input type="hidden" name="loggedin" value="$loggedIn">
<input type="submit" name="settings" value="Settings" class="bitter_button">
</form>
<form method="POST" action="">
<input type="hidden" name="n" value="Home">
<input type="submit" value="Logout" class="bitter_button">
</form>
</div> <br><p><br>
eof
}

#---------------------------------------------------#
# Login / Authentication                            #
#---------------------------------------------------#

sub userexists{
    if (open(FILE, "$users_dir/$username/details.txt")) {
        return 1;
    } else {
        return 0;
    }


}
sub pwdrecovery(){
    print "<div class=\"center\">";
    if(defined param('username') && param('username') ne ''){
        if(userexists()){
            if(param('checkemail') eq $information{'email'}){
            
	            mail_pwd();
	            print "A link to change your password has been sent to your email.\n";
            } else {
	            print "Incorrect details provided \n";

	        }
	    } else {
	        print "user does not exist\n";
	    } 
	}
    print start_form, "\n";
    print "Username:\n", textfield( -name=>'username',
                                    -pattern=>"[A-Za-z0-9_\-]+",
                                    -maxlength=>30), "\n<br>";
    print "Email:\n", textfield(-name=>'checkemail',-override=>1), "<br>\n";
    print hidden('recoverpwd','recoverpwd');
    print submit('pwdemail','Recover'), "\n";
    print end_form, "\n";

    print "</div><br>\n";

return <<eof
<form method="POST" action="">
<input type="hidden" name="n" value="Home">
<input type="submit" value="Back to Main" class="center">
</form>
</div> <br>
eof

}
sub changepwd{
    $username = param('resetPass');
    print start_form, "\n";
    print "New Password:\n", textfield( -name=>'pwd1',
                                    -pattern=>"[A-Za-z0-9_\-]+",
                                    -maxlength=>30), "\n<br>";
    print "Please re-enter:\n", textfield( -name=>'pwd2',
                                    -pattern=>"[A-Za-z0-9_\-]+",
                                    -maxlength=>30), "\n<br>";
    print hidden('username', "$username");
    print submit('process_pwdchange','Reset'), "\n";
    print end_form, "\n";
return <<eof
<form method="POST" action="">
<input type="hidden" name="n" value="Home">
<input type="submit" value="Back to Main" class="center">
</form>
</div> <br>
eof


}
sub process_pwdchange(){
    if(param('pwd1') ne param('pwd2')){
        print "passwords do not match.\n";
        print start_form, "\n";
        print "New Password:\n", textfield( -name=>'pwd1',
                                        -pattern=>"[A-Za-z0-9_\-]+",
                                        -maxlength=>30), "\n<br>";
        print "Please re-enter:\n", textfield( -name=>'pwd2',
                                        -pattern=>"[A-Za-z0-9_\-]+",
                                        -maxlength=>30), "\n<br>";
        print hidden('username', "$username");
        print submit('process_pwdchange','Reset'), "\n";
        print end_form, "\n";
    
    } else {
        if(param('pw1') ne ''){
            @newdetails = ();
            $newpwd = param('pw1');
            open my $b, "./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                while (my $line = <$b>){
                    chomp $line;
                    if ($line =~ /^password: (.*)/){
                        push @newdetails, "password: $newpwd\n";
                    } else {
                        push @newdetails, "$line\n";                    
                    }
                }
            close $b;
            open my $p, '>',"./$users_dir/$username/details.txt" or die "cannot open ./$users_dir/$username";
                foreach my $line (@newdetails){
                    print $p "$line";
                }

            close $p;
            print "password changed.\n";
        } else {
            print start_form, "\n";
            print "New Password:\n", textfield( -name=>'pwd1',
                                            -pattern=>"[A-Za-z0-9_\-]+",
                                            -maxlength=>30), "\n<br>";
            print "Please re-enter:\n", textfield( -name=>'pwd2',
                                            -pattern=>"[A-Za-z0-9_\-]+",
                                            -maxlength=>30), "\n<br>";
            print hidden('username', "$username");
            print submit('process_pwdchange','Reset'), "\n";
            print end_form, "\n";
        }
    }

}
sub authenticate(){

    if (open(FILE, "$users_dir/$username/details.txt")) {
      while ($row = <FILE>) {
        chomp $row;
	    if($row =~ /^password: (.*)/){
            if($password =~ $1){
                print "Logged in as $username\n";
                $loggedIn = 1;
            } else {
                print "<div class=\"error\">Incorrect password</div>\n";

            }
	    }
      }
    } else {
        print "<div class=\"error\">Unknown username! <p>If you have recently created your account, <p>please check your email and confirm registration.</div>\n";

    }
}
sub login(){
    if (defined param('confirm') && defined param('loggedAs')){
        my $confirmuser = param('loggedAs');
        move("./$users_dir/temporary/$confirmuser","./$users_dir/$confirmuser");
        print "Confirmation successful! Please login.\n";
    }
    print "<div class=\"center\">";
    print "<h3>y so bitter</h3><p>";
    print start_form, "\n";
    print "Username:\n", textfield('username'), "<br>\n";
    print "Password:\n", password_field('password'), "<br>\n";
    print submit('login','Login'), "\n";
    print end_form, "\n";
    print start_form, "\n";
    print submit('recoverpwd','Forgot Password'), "\n";
    print end_form, "\n";
    
    print "<br><br><h3>Create a new account</h3><p>";
    print "<div class=\"subtitle\">Only alphanumeric  characters, underscores and dashes are allowed<p> for username and password, to a maximum of 30 characters.</div><p>";
    print start_form, "\n";
    
    print "Username:\n", textfield( -name=>'newusr',
                                    -override=>1, 
                                    -pattern=>"[A-Za-z0-9_\-]+",
                                    -maxlength=>30), "\n<br>";
    print "Password:\n", password_field(-name=>'newpwd',
                                        -override=>1,
                                        -pattern=>"[A-Za-z0-9_\-]+",
                                        -maxlength=>30), "<br>\n";
    print "Email:\n", textfield(-name=>'email',-override=>1), "<br>\n";

    print submit('newaccount','Create'), "\n";
    print end_form, "\n";

    print "</div>";
}
sub create_acc{

    $newusr = param('newusr');
    $newpwd = param('newpwd');
    if($email =~ /^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+[a-zA-Z0-9]$/){
        if ((-d "./$users_dir/temporary/$newusr") || (-d "./$users_dir/$newusr")){
            print "<div class=\"error\">username exists</div>\n"
        } else {
            if ((-d "./$users_dir/temporary")){
                mkdir("./$users_dir/temporary/$newusr");
            } else {
                mkdir("./$users_dir/temporary");
                mkdir("./$users_dir/temporary/$newusr");
            }
            open my $b, '>',"./$users_dir/temporary/$newusr/details.txt" or die "cannot open ./$users_dir/temporary/$newusr";
            print $b "username: $newusr\n";
            print $b "password: $newpwd\n";
            print $b "email: $email\n";
            close $b;
            open my $a, '>',"./$users_dir/temporary/$newusr/bleats.txt" or die "cannot open ./$users_dir/temporary/$newusr";
            print '';
            close $a;
            mail_new();
        }
        
    } else {
        print "invalid email\n";
    }

}


#---------------------------------------------------#
# Email Related                                     #
#---------------------------------------------------#

sub mail_new(){
    my $url = 'http://cgi.cse.unsw.edu.au/~z5013079/ass2/bitter.cgi';
    print $email;
    $to = "$email";
    $from = 'z5013079@zmail.unsw.edu.au';
    $subject = 'Welcome to Bitter!';
    $message = "Congratulations! You've taken the first step in becoming a terrible person. Copy and paste the following url into your browser to confirm your registration:
    
$url?loggedAs=$newusr&confirm=$to";
     
    open(MAIL, "|/usr/sbin/sendmail -t");
    print MAIL "To: $to\n";
    print MAIL "From: $from\n";
    print MAIL "Subject: $subject\n";
    print MAIL "Content-type:text/html\n";
    print MAIL $message;

    close(MAIL);

    print "<br>Account created! Please check your email to confirm.<br>\n";
}

sub mail_pwd{
    my $url = 'http://cgi.cse.unsw.edu.au/~z5013079/ass2/bitter.cgi';

    $to = "$email";
    $from = 'z5013079@zmail.unsw.edu.au';
    $subject = 'Reset your password';
    $message = "Copy and paste the following url into your browser to change your password:
    
$url?resetPass=$username&confirm=$to";
     
    open(MAIL, "|/usr/sbin/sendmail -t");
    print MAIL "To: $to\n";
    print MAIL "From: $from\n";
    print MAIL "Subject: $subject\n";
    print MAIL "Content-type:text/html\n";
    print MAIL $message;

    close(MAIL);


}


#---------------------------------------------------#
# User Related                                      #
#---------------------------------------------------#

# Show unformatted details for user "n".
# Increment parameter n and store it as a hidden variable
#
sub main_user_page {
    
    my $user_to_show  = "./$users_dir/$username";
    my $details_filename = "$user_to_show/details.txt";
    print "<div class=\"bitter_picture\">";
    print "<img src=\"$user_to_show/profile.jpg\" alt=\"User has not uploaded a picture\" >";
    print "</div>";
    open my $p, "$details_filename" or die "can not open $details_filename: $!";
        while (my $line = <$p>){
	        push @userdetail, $line;
        }
        @userdetail = grep(!/password: /,@userdetail);
        @userdetail = grep(!/email: /,@userdetail);
        $details = join '', @userdetail;
    close $p;
    #print "<div class=\"bitter_user_details\">";
    #print "<b>$information{'username'}</b>\n";
    #print "Longitude: $information{'home_longitude'}\n";
    #print "Latitude: $information{'home_latitude'}\n";
    #print "Listening to:\n";
    #foreach $listened (@listens){
	#print "$listened ";
    #
    #} 
    #print "</div>";

    return<<eof
<div class="bitter_user_details">
$details
</div>
<p>
eof
}


sub user_page {
    my $toshow = param('userprofile');
    my $user_to_show  = "./$users_dir/$toshow";
     
    my $details_filename = "$user_to_show/details.txt";
    print "<div class=\"bitter_picture\">";
    print "<img src=\"$user_to_show/profile.jpg\" alt=\"User has not uploaded a picture\" >";
    print "</div>";
    if($toshow ne $username){
        print '<form method="POST" action="">';
        print "<input type=\"hidden\" name=\"username\" value=\"$username\">";
        print  "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
        print  "<input type=\"hidden\" name=\"listunlistuser\" value=\"$toshow\">";
        if(grep {$_ eq $toshow} @listens){
            print "<input type=\"submit\" name=\"unlisten\" value=\"Unlisten\" class=\"bitter_button\">\n";
        } else {
            print "<input type=\"submit\" name=\"listen\" value=\"Listen\" class=\"bitter_button\">\n";
        }
  
        print "</form><p>\n";
    }
    open my $p, "$details_filename" or die "can not open $details_filename: $!";
    while (my $line = <$p>){
	chomp $line;
	push @userdetail, "$line\n";
    }
    close $p;
    @userdetail = grep(!/^password: /,@userdetail);
    @userdetail = grep(!/^email: /,@userdetail);
    $details = join '', @userdetail;

    return <<eof
<div class="bitter_user_details">
$details
</div>
<p>
eof
}

sub listenusr{
    my @details =();
    my $listen = param('listunlistuser');
    my $details_filename = "./$users_dir/$username/details.txt";
    push @listens, "$listen";
    $updated = join ' ', @listens;
    open my $p, "$details_filename" or die "can not open $details_filename: $!";
   	while(my $line = <$p>){
	    chomp $line;
	    if($line =~ /^listens: (.*)/){
		push @details, "listens: $updated\n"; 
	    } else {
		push @details, "$line\n";
	    }
		

	}
    close $p;

    open my $b,'>', "$details_filename" or die "can not open $details_filename: $!";
	foreach my $element (@details){
	    print $b "$element";
	}

    close $b;

}
sub unlisten{
    my @details = ();
    my $unlisten = param('listunlistuser');
    my $details_filename = "./$users_dir/$username/details.txt";
    
    my $index = 0;
    $index++ until $listens[$index] eq $unlisten;
    splice(@listens, $index, 1); 
    
    $updated = join ' ', @listens;
    $updated =~ s/$unlisten //;
    #print "$updated\n";
    open my $p,"$details_filename" or die "can not open $details_filename: $!";
   	while(my $line = <$p>){
	    if($line =~ /^listens: (.*)/){
		push @details, "listens: $updated\n"; 
	    } else {
		push @details, "$line";
	    }

	}
    close $p;

    open my $b,'>',"$details_filename" or die "can not open $details_filename: $!";
	foreach $something (@details){
	    print $b "$something";
	}

    close $b;

}



#-----------------------------------------------------------------#
# Bleats related code                                             #
#-----------------------------------------------------------------#

sub process_bleats(){
     $edit = param('post');
     $edit =~ s/\n/ /g;
     $newpost = CGI::escapeHTML($edit);

     $dt = DateTime->new( year       => 1970,
                          month      => 1,
                          day        => 1,
                          time_zone  => "Australia/Sydney",
                         );
    $timestamp = DateTime->now(time_zone  => "Australia/Sydney");
    $difference = $timestamp->subtract_datetime_absolute($dt);
    $filename= $difference->seconds();
    $filename =~ s/[^0-9]//g;

    #add to list
    open(my $p, '>>', "$users_dir/$username/bleats.txt") or die "wrong user";
    print $p "n$filename\n";
    close $p;
    
    #make bleat
    open(my $fh, '>', "$bleats_dir/n$filename") or die "Could not open file 'n$filename'";
    print $fh "bleat: $newpost\n";
    print $fh "time: $filename\n";
    print $fh "username: $username\n";
    if (defined param('replyto')){
        $at = param('replyto');
        print $fh "in_reply_to: $at\n";
    }
    close $fh;
    return;
}

#text box for bleating
sub bleat_box{
    
    print "<div class=\"bleatbox\">";
    print start_form, "\n";
   
    if(defined param('bleattoshow')){
        print textarea(-name=>'post',
			  -default=>"\@$bleatowner ",
			  -rows=>3,
			  -columns=>60,
			  -maxlength=>142);
	print hidden('replyto',$masterbleat);
    } else {
        print textarea(-name=>'post',
			  -default=>'Type your complaints',
			  -rows=>3,
			  -columns=>60,
			  -maxlength=>142);
    }
    print hidden('loggedin',"$loggedIn");
    print hidden('username',"$username");
    print submit('Bleating','Bleat!'),"\n";
    print end_form, "\n";
    print "</div>";
   
}
sub bleat_page{
    $masterbleat = param('bleattoshow');
    open my $b, "./$bleats_dir/$masterbleat" or die "cannot open $bleats_dir/$masterbleat: $!";;
        push @onebleat, "<div class=\"bitter_user_bleats\"\n>";
	while(my $line = <$b>){
	    chomp $line;
	    if($line =~ /^username: (.*)/){
	        $bleatowner = $1;
	    }
	    push @onebleat, "$line\n";
	}
	push @onebleat, "</div>\n"; 
    close $b;

    foreach my $line (@onebleat){
	print $line;
    }

    bleat_box();

}
#bleats of requested user
sub user_bleats {
    #print toggle();
    my $toShow = param('userprofile');
    my $bleats_filename = "$users_dir/$toShow/bleats.txt";

    open my $p, "$bleats_filename" or die "can not open $bleats_filename: $!";
        while (my $line = <$p>){
            chomp $line;
            push @bleatstoprint, "$line";
        }
    close $p;
    if(@bleatstoprint){
    }
    else{
        print "Nothing to show\n";
        return;    
    }
    @bleatstoprint = reverse sort @bleatstoprint;
    my $i = 0;
    foreach $element (@bleatstoprint){
        if($i >= 20){
            last;
        }
        @onebleat = (); #reset onebleat holder
        
        open my $b, "$bleats_dir/${element}" or die "cannot open $bleats_dir/${element}: $!";;
            push @onebleat, "<div class=\"bitter_user_bleats\"\n>";
            while (my $bleatdetail = <$b>){
                chomp $bleatdetail;
                if($bleatdetail =~ /^time: (.*)/){
                    $difference = $1;
                    $dt = DateTime->new(  year       => 1970,
                                          month      => 1,
                                          day        => 1,
                                          time_zone  => "Australia/Sydney",
                                         );
                    $dt->add(seconds => $difference);
                    $dt =~ s/T/ /;
                 
		    push @onebleat, "$dt\n";
                } elsif ($bleatdetail =~ /(^longitude: )|(^latitude: )/){
                    #ignore
                } elsif ($bleatdetail =~ /^bleat: (.*)/){
                    my $text = $1;
                    push @onebleat,"<b>$text</b>\n";
                } elsif ($bleatdetail =~ /^username: (.*)/){
                    
                    $bleater = $1;
                    
  
                } else {
                    push @onebleat, "$bleatdetail\n";
                }
            
            }
            push @onebleat, '<form method="POST" action="">';
            push @onebleat, "<input type=\"hidden\" name=\"username\" value=\"$username\">";
            push @onebleat, "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
            push @onebleat, "<input type=\"submit\" name=\"userprofile\" value=\"$bleater\" class=\"profile_button\">";
            push @onebleat, "</form>";
	        push @onebleat, '<form method="POST" action="">';
            push @onebleat, "<input type=\"hidden\" name=\"username\" value=\"$username\">";
            push @onebleat, "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
            push @onebleat, "<input type=\"hidden\" name=\"bleattoshow\" value=\"$element\" >";
            push @onebleat, "<input type=\"submit\" name=\"userprofile\" value=\"reply\" class=\"profile_button\">";
            push @onebleat, "</form>\n";
            push @onebleat, "</div>\n";

        close $b;
        
        $bleat_to_show = join '',@onebleat;
        push @bleats, "$bleat_to_show";
        $i++;
    }


   foreach $post (@bleats){
       print "$post";
   }
   
   
   
   return;

}


#
# show bleats of current user
#
sub main_user_bleats {
    #print toggle();

    my $bleats_filename = "$users_dir/$username/bleats.txt";
    
    
    open my $p, "$bleats_filename" or die "can not open $bleats_filename: $!";
        while (my $line = <$p>){
            chomp $line;
            push @bleatstoprint, "$line";
        }
    close $p;
    followed_bleats();
    if(@bleatstoprint){
    }
    else{
        print "Nothing to show\n";
        return;    
    }
    @bleatstoprint = reverse sort @bleatstoprint;
    my $i = 0;
    foreach $element (@bleatstoprint){
        if($i >= 20){ #no more than 20 per page
            last;
        }
        @onebleat = (); #reset onebleat holder
        
        open my $b, "$bleats_dir/${element}" or die "cannot open $bleats_dir/${element}: $!";;
            push @onebleat, "<div class=\"bitter_user_bleats\"\n>";
            while (my $bleatdetail = <$b>){
                chomp $bleatdetail;
                if($bleatdetail =~ /^time: (.*)/){
                    $difference = $1;
                    $dt = DateTime->new(  year       => 1970,
                                          month      => 1,
                                          day        => 1,
                                          time_zone  => "Australia/Sydney",
                                         );
                    $dt->add(seconds => $difference);
                    $dt =~ s/T/ /;
                    push @onebleat, "$dt\n";
                } elsif ($bleatdetail =~ /(^longitude: )|(^latitude: )/){
                    #ignore
                } elsif ($bleatdetail =~ /^bleat: (.*)/){
                    my $text = $1;
                    push @onebleat,"<b>$text</b>\n";
                } elsif ($bleatdetail =~ /^username: (.*)/){
                    
                    $bleater = $1;
  
                } else {
                    push @onebleat, "$bleatdetail\n";
                }
            
            }
            push @onebleat, '<form method="POST" action="">';
            push @onebleat, "<input type=\"hidden\" name=\"username\" value=\"$username\">";
            push @onebleat, "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
            push @onebleat, "<input type=\"submit\" name=\"userprofile\" value=\"$bleater\" class=\"profile_button\">";
            push @onebleat, "</form>";
            push @onebleat, '<form method="POST" action="">';
            push @onebleat, "<input type=\"hidden\" name=\"username\" value=\"$username\">";
            push @onebleat, "<input type=\"hidden\" name=\"loggedin\" value=\"$loggedIn\">";
            push @onebleat, "<input type=\"hidden\" name=\"bleattoshow\" value=\"$element\" >";
            push @onebleat, "<input type=\"submit\" name=\"userprofile\" value=\"reply\" class=\"profile_button\">";
            push @onebleat, "</form>";
  


	    push @onebleat, "</div>\n";

        close $b;
        
        $bleat_to_show = join '',@onebleat;
        push @bleats, "$bleat_to_show";
        $i++;
    }




   foreach $post (@bleats){
   print "$post";
   }
   
   
   
   return;

}

#show bleats of who you're listening to
sub followed_bleats(){


    foreach $person (@listens){
        my $bleats_filename = "$users_dir/$person/bleats.txt";
        open my $p, "$bleats_filename" or die "can not open $bleats_filename: $!";
            while (my $line = <$p>){
                chomp $line;
                push @bleatstoprint, "$line";
            }
        close $p;
    }


}

#---------------------------------------------------#
# HTML related code                                 #
#---------------------------------------------------#

# HTML placed at the top of every page              
sub page_header {
    return <<eof
Content-Type: text/html

<!DOCTYPE html>
<html lang="en">
<head>
<title>Bitter</title>
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css" integrity="sha512-dTfge/zgoMYpP7QbHy4gWMEGsbsdZeCXz7irItjcC3sPUFtf0kuFbDz/ixG7ArTxmDjLXDmezHubeNikyKGVyQ==" crossorigin="anonymous">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css" integrity="sha384-aUGj/X2zp5rLCbBxumKTCw2Z50WgIr1vs/PFN4praOTvYXWlVyh2UtNUU0KAUhAX" crossorigin="anonymous">
<link href="bitter.css" rel="stylesheet">
</head>
<body>
<div class="bitter_heading">
Bitter
</div>
eof
}


#
# HTML placed at the bottom of every page
# It includes all supplied parameter values as a HTML comment
# if global variable $debug is set
#
sub page_trailer {
    my $html = "";
    $html .= join("", map("<!-- $_=".param($_)." -->\n", param())) if $debug;
    $html .= end_html;
    return $html;
}

main();
