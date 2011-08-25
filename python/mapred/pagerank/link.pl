#!/usr/bin/env perl
# usage: bunzip2 -c jawiki-latest-pages-articles.xml.bz2 | link.pl > link.txt
use strict;
use warnings;
use utf8;
use Encode;
use open ':utf8';
binmode STDIN, ":utf8";
binmode STDOUT, ":utf8";

my $flag_page_inside = 0;
my $page;

while (<>) {
    my $line = $_;
    if ($flag_page_inside == 0 and $line =~ m{<page>}) {
        $flag_page_inside = 1;
    }
    if ($flag_page_inside == 1) {
        $page .= $line;
    }
    if ($flag_page_inside == 1 and $line =~ m{</page>}) {
        my ($title) = $page =~ m{<title>([^<]+)<};
        $title = word_ok($title);

        if ($title ne "") {
            my %relwords;
            while ($page =~ m{\[\[(.+?)\]\]}g) {
                my $w = word_ok($1);
                next if $w eq "";
                next if $w eq $title;
                next if defined $relwords{$w};
                $relwords{$w}++;
                print "$title\t$w\n";
            }
        }
        $flag_page_inside = 0;
        $page = "";
    }
}

sub word_ok {
    my ($w) = @_;
    return "" unless $w;
    return "" if $w =~ m{[:\|\n\t\[\]]};;
    return "" if $w =~ m{^[\#\s]};;
    $w =~ s/\s*\(.+?\)$//;
    return "" if $w =~ /一覧$/;
    return "" if $w =~ /\d+月\d+日$/;
    return "" if $w =~ /^\d{4}年$/;
    return $w;
}

