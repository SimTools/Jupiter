#!/usr/bin/perl -w

$filename = $ARGV[0];
open(INFILE,"<$filename") || die "\nSTEP file ".$filename." not found.";

$isawincflags = 0;
$output = 0;

while (<INFILE>) {
	if (/^ifndef INCFLAGS/) {
		$isawincflags = 1;
 	}
	
	if ($output == 1 && /^\s*-I/) {
		$s = $_;
		$s =~ s/\\$//;
		$s =~ s/\$\(G4BASE\)/$ARGV[1]/;
		print $s;
	} elsif ($output == 1) {
		$output = 0; 
		$isawincflags = 0;
	} 

#	if ($isawincflags == 1 && /^\s*INCFLAGS\s*:=/) {
	if ($isawincflags == 1 && /^\s*INCFLAGS\s*:=\s*\\/) {
		$output = 1;
#		print  "CPPFLAGS += \\\n";
  	}		
} 
 	
close(INFILE);
