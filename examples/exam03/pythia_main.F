
#include "pythia6205/pythia.inc"


      nev=10
      msel=1

#if 0
C ... For Z --> uds only at Z pole.
      iz = pycomp(23)
      mdcy(iz,1) = 1
      do 100 idc = mdcy(iz,2), mdcy(iz,2)+mdcy(iz,3)-1
         mdme(idc,1)=0
 100  continue
      mdme(174,1) = 1
      mdme(175,1) = 1
      mdme(176,1) = 1

C Suppress ISR
      call pygive('mstp(11)=0')
#endif

C Suppress decay of relatively long lived particles
      call pygive('mstj(22)=2')
       
      call pyinit('cms','e-','e+',91.180d0)
      open(10,file="qqbar.dat",form="formatted",status="unknown")
       
      do 200 i=1, nev
         call pyevnt

C pyedit(11), (12), (15) are to remove history records.
         call pyedit(11)
         call pyedit(12)
         call pyedit(15)

         call pyhepc(1)
c         call pylist(1)
         call writehepevt(10)
200   continue
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
