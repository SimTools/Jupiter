
#include "pythia6205/pythia.inc"


      nev=10
      msel=1
       
      call pyinit('cms','e-','e+',91.180d0)
      open(10,file="qqbar.dat",form="formatted",status="unknown")
       
      do 100 i=1, nev
         call pyevnt
         call pyedit(11)
         call pyedit(12)
         call pyedit(15)

         call pyhepc(1)
c         call pylist(1)
         call writehepevt(10)
100   continue
      close(10)
      stop
      end

***********************************************************

      subroutine writehepevt(lu)
c...hepevt commonblock.
      parameter (nmxhep=4000)
      common/hepevt/nevhep,nhep,isthep(nmxhep),idhep(nmxhep),
     &jmohep(2,nmxhep),jdahep(2,nmxhep),phep(5,nmxhep),vhep(4,nmxhep)
      double precision phep,vhep

      write(lu,*) nhep
      do ihep=1, nhep
        write(lu,10) 
     >  isthep(ihep),idhep(ihep),jdahep(1,ihep),jdahep(2,ihep),
     >  phep(1,ihep),phep(2,ihep),phep(3,ihep),phep(5,ihep)
10    format(4i5,4(1x,d15.8))
      enddo
       
      return
      end
