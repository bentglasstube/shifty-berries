#!/usr/bin/env perl

use strict;
use warnings;

while (<>) {
  last if /<data encoding="csv">/;
}

while (<>) {
  last if /<\/data>/;
  chomp;

  my @values = split /,/;
  foreach (@values) {
    if ($_ == 0) {
      print '.';
    } elsif ($_ > 0 and $_ < 26) {
      print chr(ord('A') + $_ - 1);
    } else {
      print chr(ord('a') + $_ - 1);
    }
  }
  print "\n";
}
