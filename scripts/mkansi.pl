#!/usr/bin/perl
# (Function)
# (Usage)
# (Update Record)
#
#--
#  Check # input files.
#--
$n_files = @ARGV;
if ( ! $n_files ) {
   print "$n_files args given\n";
   print "Usage:\n";
   print "   ./mkansi.pl in_file\n";
   exit 0;
}

#--
#  Loop over input files.
#--
$outdir = "out";
mkdir($outdir);
foreach $infile (@ARGV) {
   open(FILE,"<$infile");
   print "opened $outfile as input\n";
   $outfile = $outdir."/".$infile;
   open(OUT,">$outfile");
   print "opened $outfile as output\n";
   while (<FILE>) {
      s/G4std/std/g;
      s/\bcerr\b/std::cerr/g;
      s/\bcout\b/std::cout/g;
      s/(\b)ios::/\1std::ios::/g;
      s/(\b)setiosflags::/\1std::setiosflags::/g;
      s/(\b)setw(\b)/\1std::setw\2/g;
      s/(\b)setfill(\b)/\1std::setfill\2/g;
      s/(\b)setprecision(\b)/\1std::setprecision\2/g;
      s/(\b)setbase(\b)/\1std::setbase\2/g;
      s/(\b)hex(\b)/\1std::hex\2/g;
      s/(\b)dec(\b)/\1std::dec\2/g;
      s/(\b)ifstream(\b)/\1std::ifstream\2/g;
      s/(\b)ofstream(\b)/\1std::ofstream\2/g;
      s/(\b)istrstream(\b)/\1std::istringstream\2/g;
      s/(\b)ostrstream(\b)/\1std::ostringstream\2/g;
      s/(\b)endl(\b)/\1std::endl\2/g;
      s/(\b)ends(\b)/\1std::ends\2/g;
      if (!/#include/) {
         s/(\b)vector(\s*<)/\1std::vector\2/g;
      }

      s/std::std::/std::/g;
      s/std::std::std::/std::/g;

      # s/(\b)std::/\1G4std::/g;
      # s/G4std::endl/G4endl/g;
      # s/G4std::cout/G4cout/g;
      # s/G4std::cerr/G4cerr/g;

      s/G4endl/std::endl/g;
      s/G4cout/std::cout/g;
      s/G4cerr/std::cerr/g;
      s/g4std/./g;

      s/<(\s*)strstream\.h(\s*)>/<\1sstream\2>/;
      s/<(\s*)strstream(\s*)>/<\1sstream\2>/;
      s/<(\s*)iostream\.h(\s*)>/<\1iostream\2>/;
      s/<(\s*)fstream\.h(\s*)>/<\1fstream\2>/;
      s/<(\s*)iomanip\.h(\s*)>/<\1iomanip\2>/;
      s/<(\s*)string\.h(\s*)>/<\1string\2>/;
      if (/<\s*vector\.h\s*>/) {
	 print OUT "#include <algorithm>\n";
	 print "#include <algorithm>\n";
      }
      s/<(\s*)vector\.h(\s*)>/<\1vector\2>/;

      print OUT;
      print;	
   }
   close(FILE) ;
   close(OUT) ;
}
exit 0 ;

