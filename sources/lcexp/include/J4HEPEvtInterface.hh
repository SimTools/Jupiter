// $Id$
//

#ifndef J4HEPEVTINTERFACE
#define J4HEPEVTINTERFACE

#include "./fstream"
#include "./vector"
#include "globals.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4HEPEvtParticle.hh"
#include "J4PrimaryGeneratorAction.hh"

class G4PrimaryVertex;
class G4Event;
class J4HEPEvtMessenger;

// class description:
//
//  This is a concrete class of G4VPrimaryGenerator.
//  This class object reads an ASCII file which contains particles generated
// by a physics generator which supports /HEPEVT/ common block.
// 
//  The format of ASCII file must be equivalent to the follwing sample fortran
// code.
//***********************************************************
//      SUBROUTINE HEP2G4
//*
//* Output /HEPEVT/ event structure to J4HEPEvtInterface
//*
//***********************************************************
//      PARAMETER (NMXHEP=2000)
//      COMMON/HEPEVT/NEVHEP,NHEP,ISTHEP(NMXHEP),IDHEP(NMXHEP),
//     >JMOHEP(2,NMXHEP),JDAHEP(2,NMXHEP),PHEP(5,NMXHEP),VHEP(4,NMXHEP)
//      DOUBLE PRECISION PHEP,VHEP
//*
//      WRITE(6,*) NHEP
//      DO IHEP=1,NHEP
//       WRITE(6,10) 
//     >  ISTHEP(IHEP),IDHEP(IHEP),JDAHEP(1,IHEP),JDAHEP(2,IHEP),
//     >  PHEP(1,IHEP),PHEP(2,IHEP),PHEP(3,IHEP),PHEP(5,IHEP)
//10    FORMAT(4I5,4(1X,D15.8))
//      ENDDO
//*
//      RETURN
//      END
//
//  The position and time of the primary interaction must be set by the corresponding
// set methods of G4VPrimaryGenerator base class, otherwise zero will be set.
//

class J4HEPEvtInterface:public G4VPrimaryGenerator
{

public: 

    J4HEPEvtInterface(G4String file="");
    ~J4HEPEvtInterface();

    void OpenHEPEvtFile(G4String file="");
    void GeneratePrimaryVertex(G4Event* evt);

    inline void     SetFileName(char *file); 
    inline void     SetNskipEvents(G4int n) { fNskipEvents = n; }
    inline G4String GetFileName() const { return fFileName; } 
    inline G4int    GetNskipEvents()    { return fNskipEvents; }

private:

    G4String                          fFileName;
    std::ifstream                   fInputStream;
    std::vector<G4HEPEvtParticle*>  fHPlist;
    G4int                             fNskipEvents;

    J4HEPEvtMessenger                *fMessenger;

};

//=====================================================================
//---------------------
// inline function
//---------------------

void J4HEPEvtInterface::SetFileName(char *file)
{
   fFileName = file;
   if (fInputStream.is_open()) fInputStream.close();
}

#endif

