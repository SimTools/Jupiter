//
// ********************************************************************
// J4CainEvtInterface 
//
// class description:
// 
// This is a concrete class of G4VPrimaryGenerator.
// This is to read CAIN events and simulate background events by 
// Jupiter.  Thw web site of CAIN is http://www-acc-theory.kek.jp/members/cain .
// Input file is a ASCII file created by CAIN using a CAIN command,
// "WRITE BEAM, FILE='....'"  A sample input file for CAIN will be found at
// http://acfahep.kek.jp/subg/sim/bdsim
//
// An example of the  input file should like as follows.
/*
!K   GEN NAME       Weight               T(m)                X(m)                Y(m)                S(m)                E(eV)              Px(eV/c)            Py(eV/c)            Ps(eV/c)               Sx                  Sy                  Ss
 2     3       2.142670877591D+05  1.776114941129D-08  2.128321576554D-07  5.434993883800D-09  0.000000000000D+00  1.907660729636D+11  7.247634044518D+08  2.440258890020D+06  1.907646961724D+11  0.000000000000D+00  0.000000000000D+00  0.000000000000D+00
 2     3       2.142670877591D+05  8.669693020780D-05  3.234483489981D-07 -3.425321248865D-09  0.000000000000D+00  2.405093781470D+11  9.710429905904D+08  7.610168490995D+06  2.405074177525D+11  0.000000000000D+00  0.000000000000D+00  0.000000000000D+00
....... 
*/
//
// Since particle information in the CAIN output file is not randamized,
// user must read all events in the CAIN file, otherwise result is biased.
//
//
//(Author) 
//   Akiya Miyamoto, KEK (akiya.miyamoto@kek.jp)
//
//$Id$
//
// ********************************************************************
//


#ifndef G4CAINEvtInterface_h
#define G4CAINEvtInterface_h 1

#include "./fstream"
#include "./vector"
#include "globals.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4ParticleDefinition.hh"
#include "J4PrimaryGeneratorAction.hh"

class G4PrimaryVertex;
class G4Event;
class J4CAINEvtMessenger;

class J4CAINEvtInterface:public G4VPrimaryGenerator
{

public: 

    J4CAINEvtInterface(G4String file="");
    ~J4CAINEvtInterface();

    void         GeneratePrimaryVertex(G4Event* evt);
    void         OpenCainFile(G4String file="");

    void         SetGenDirection(G4double flag);
    void         SetGenElectron(G4bool flag);
    void         SetGenPositron(G4bool flag);
    void         SetGenGamma(G4bool flag);
    inline void  SetFileName(const char *file);
    inline void  SetVerboseLevel(G4int level) { fVerboseLevel=level; }

    inline G4bool   GetGenGamma()     { return fGenGamma; }
    inline G4bool   GetGenElectron()  { return fGenElectron; }
    inline G4bool   GetGenPositron()  { return fGenPositron; }
    inline G4double GetGenDirection() { return fGenDirection; }
    inline G4String GetFileName()     { return fFileName; }
    inline G4int    GetVerboseLevel() { return fVerboseLevel; }

private:

    G4String              fFileName;
    std::ifstream       fInputStream;
    G4int                 fNread;
    G4ParticleDefinition *fGamma;
    G4ParticleDefinition *fElectron;
    G4ParticleDefinition *fPositron;
  
    G4bool                fGenGamma;
    G4bool                fGenElectron;
    G4bool                fGenPositron;
    G4double              fGenDirection;
    G4int                 fVerboseLevel;

    J4CAINEvtMessenger   *fMessenger;
  
};

//=====================================================================
//---------------------
// inline function
//---------------------

void J4CAINEvtInterface::SetFileName(const char *file)                             
{                    
   fFileName = file;
   if (fInputStream.is_open()) fInputStream.close();
}                    


#endif

