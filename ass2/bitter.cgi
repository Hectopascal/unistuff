#!/usr/bin/perl -w

# written by andrewt@cse.unsw.edu.au September 2015
# as a starting point for COMP2041/9041 assignment 2
# http://cgi.cse.unsw.edu.au/~cs2041/assignments/bitter/

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

@userdetail=();
@bleats=();
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
    print nav_panel();
    print user_page();
    print user_bleats();
    print page_trailer();
}

#
# show navigation menu
#

sub nav_panel(){


   return <<eof
<div class="menu">
<p>
<form method="POST" action="">
    <input type="hidden" name="n" value="Home">
    <input type="submit" value="Home" class="bitter_button">
</form>
<p>
<form method="POST" action="">
    <input type="hidden" name="n" value="Home">
    <input type="submit" value="Home" class="bitter_button">
</form>
<p>
</div>
eof
}

#
# Show unformatted details for user "n".
# Increment parameter n and store it as a hidden variable
#
sub user_page {
    my $n = param('n') || 0;
    my @users = sort(glob("$users_dir/*"));

    my $user_to_show  = $users[$n % @users];
    my $details_filename = "$user_to_show/details.txt";
    open my $p, "$details_filename" or die "can not open $details_filename: $!";
    while (my $line = <$p>){
	push @userdetail, $line;
    }
    @userdetail = grep(!/password: /,@userdetail);
    @userdetail = grep(!/email: /,@userdetail);
    $details = join '', @userdetail;
    close $p;
    my $next_user = $n + 1;
   
    print start_form, "\n";
    print textarea(-name=>'bleat',
			  -default=>'Type your complaints',
			  -rows=>3,
			  -columns=>60,
			  -maxlength=>142);
    print submit('Bleating','Bleat!'),"\n";
    print end_form, "\n";
   
    return <<eof
<form method="POST" action="">
    <input type="hidden" name="n" value="$next_user">
    <input type="submit" value="Next user" class="bitter_button">
</form>

<div class="bitter_user_details">
$details
</div>
<p>
eof
}


#
# show bleats of user n
#

sub user_bleats {
    my $n = param('n') || 0;
    my @users = sort(glob("$users_dir/*"));
 
    my $user_to_show  = $users[$n % @users];
    my $bleats_filename = "$user_to_show/bleats.txt";
    open my $p, "$bleats_filename" or die "can not open $bleats_filename: $!";
    while (my $line = <$p>){
	open my $b, "$bleats_dir/${line}" or die "cannot open $bleats_dir/${line}: $!";;
	$bleat_to_show = join '',<$b>;
	close $b;
	push @bleats, $bleat_to_show;
	push @bleats, "<br>";  
   }
   my $next_user = $n + 1;
   @bleats = reverse @bleats;
   $bleat = join '',@bleats;
   close $p;
   return <<eof
<div class="bitter_user_bleats">
$bleat
</div>
<p>
<form method="POST" action="">
    <input type="hidden" name="n" value="$next_user">
    <input type="submit" value="Next user" class="bitter_button">
</form>
eof

}

#
# HTML placed at the top of every page
#
sub page_header {
    return <<eof
Content-Type: text/html

<!DOCTYPE html>
<html lang="en">
<head>
<title>Bitter</title>
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
