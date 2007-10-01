#!/usr/bin/perl
#-------------------------------------------------------------------------------
# ---------
# mkg49.pl
# ---------
# (Function)
#    Migrate from g4.8 to g4.9
# (Usage)
#    Just type
#    	./mkg49.pl <dir>
#    then you get "tmp/" that contains converted source files.
# (Update Record)
#   07/09/30	K.Fujii		Original version
#-------------------------------------------------------------------------------
#--
#  Open input directory.
#--
$indir = $ARGV[0];
print "Processing $indir \n";
opendir(INDIR,$indir);

#--
#  Prepare output directory.
#--
$outdir = "tmp";
umask(0000);
mkdir($outdir,0755);

#--
#  Process files.
#--
chdir($indir);
@flist = readdir(INDIR);
foreach $i (@flist) {
   if (-f $i) {
      count($i,*n);
#--
#  *.hh
#--
      if ($n && $i =~ /.*\.h/) {
         xx_hh($i);
#--
#  *.cc
#--
      } elsif ($n && $i =~ /.*\.cc/) {
         xx_cc($i);
#--
#  Others don't need modifications.
#--
      } else {
         print "Copying      $i\n";
	 #system "cp -a $i ../$outdir/.";
	 system "cp -RPp $i ../$outdir/.";
      }
   } elsif (-d $i) {
#--
#  CVS and other directories.
#--
      if ($i =~ /^\.$/ || $i =~ /^\.\.$/) {
      } else {
         print "Copying    $i\n"; 
         #system "cp -ar $i ../$outdir/.";
         system "cp -RPp $i ../$outdir/.";
      }
   }
}

#--
#  Close directories.
#--
closedir(INDIR);
#--
#  That's it, folks!
#--
exit 0;


#------------------------------------------------------------------------------
#  *.hh Processor
#------------------------------------------------------------------------------
sub xx_hh {
   my($i) = $_[0];
   local($n) = 0;
   print "Processing   $i\n"; 
   open(INFILE,"<$i");
   open(OUTFILE,">../$outdir/$i");
   while (<INFILE>) {
      if (!$n && /^#include /) {
         print OUTFILE "#include \"G4Version.hh\"\n";
         print OUTFILE "#if G4VERSION_NUMBER >= 900\n";
         print OUTFILE "#include \"G4GeometryTolerance.hh\"\n\n";
         print OUTFILE "#endif\n\n";
         print OUTFILE $_;
         $n++;
      } elsif (/\bkCarTolerance\b/) {
         print OUTFILE "#if G4VERSION_NUMBER < 900\n";
         print OUTFILE $_;
         print OUTFILE "#else\n";
         s/(\b)kCarTolerance(\b)/\1G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()\2/g;
         print OUTFILE $_;
         print OUTFILE "#endif\n";
      } elsif (/\bkRadTolerance\b/) {
         print OUTFILE "#if G4VERSION_NUMBER < 900\n";
         print OUTFILE $_;
         print OUTFILE "#else\n";
         s/(\b)kRadTolerance(\b)/\1G4GeometryTolerance::GetInstance()->GetRadialTolerance()\2/g;
         print OUTFILE $_;
         print OUTFILE "#endif\n";
      } elsif (/\bkAngTolerance\b/) {
         print OUTFILE "#if G4VERSION_NUMBER < 900\n";
         print OUTFILE $_;
         print OUTFILE "#else\n";
         s/(\b)kAngTolerance(\b)/\1G4GeometryTolerance::GetInstance()->GetAngularTolerance()\2/g;
         print OUTFILE $_;
         print OUTFILE "#endif\n";
      } else {
         print OUTFILE $_;
      }
   }
   close(INFILE);
   close(OUTFILE);
}

#------------------------------------------------------------------------------
#  *.cc Processor
#------------------------------------------------------------------------------
sub xx_cc {
   my($i) = $_[0];
   xx_hh($i);
}

#------------------------------------------------------------------------------
#  Counter
#------------------------------------------------------------------------------
sub count {
   my($i) = $_[0];
   local(*n) = $_[1];
   $ntarget = 0;
   open(INFILE,"<$i");
   while (<INFILE>) {
      if (/\bkCarTolerance\b/) {
         $ntarget++;
      } elsif (/\bkRadTolerance\b/) {
         $ntarget++;
      } elsif (/\bkAngTolerance\b/) {
         $ntarget++;
      }
   }
   close(INFILE);
   $n = $ntarget;
}
