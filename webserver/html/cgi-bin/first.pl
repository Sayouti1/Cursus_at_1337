#!/usr/bin/perl
use strict;
use warnings;
$| = 1;  # autoflush
print "Content-type: text/html\n";
print "Connection: close\n";
print "Hello: Hii\n\n";
print "<html><body><h1>Hello, World! FROM CGI pascal</h1></body></html>\n";
