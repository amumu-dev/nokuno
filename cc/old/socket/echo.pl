#!/usr/bin/perl
# $Id: echo-server-inetd.pl,v 1.1 2001/04/21 18:56:40 68user Exp $

$|=1;           # �Хåե���󥰤��ʤ�
while (<STDIN>){
    print "my echod: $_";
}
