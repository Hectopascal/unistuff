#!/usr/bin/perl -w

use CGI qw/:all/;
use CGI::Carp qw/fatalsToBrowser warningsToBrowser/;

print header, start_html('Login');
warningsToBrowser(1);

$username = param('username') || '';
$password = param('password') || '';

if ($username && $password) {
    if (open(FILE, "../accounts/$username/password")) {
      while ($row = <FILE>) {
        chomp $row;
        if($password =~ $row){
            print "$username authenticated.\n";
        } else {
            print "Incorrect password!\n";
        }
      }
    } else {
            print "Unknown username!\n";
    }

} elsif ($username) {
    print start_form, "\n";
    print hidden('username'), "\n";
    print "Password:\n", textfield('password'), "\n";
    print submit(value => Login), "\n";
    print end_form, "\n";
}elsif ($password) {
    print start_form, "\n";
    print "Username:\n", textfield('username'), "\n";
    print hidden('password'), "\n";
    print submit(value => Login), "\n";
    print end_form, "\n";
} else {

    
    print start_form, "\n";
    print "Username:\n", textfield('username'), "\n";
    print "Password:\n", textfield('password'), "\n";
    print submit(value => Login), "\n";
    print end_form, "\n";
}
print end_html;
exit(0);

