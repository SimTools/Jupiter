#ifndef __J4TPCPADPLANE__
#define __J4TPCPADPLANE__
//*************************************************************************
//* --------------------
//* J4TPCPadPlane
//* --------------------
//* (Description)
//* 	Derivation class for TPC.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4VTPCDetectorComponent.hh"
#include "J4TPCPadRow.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4TPCPadPlane : public J4VTPCDetectorComponent {	

public:
  J4TPCPadPlane(J4VDetectorComponent *parent    = 0,
                               G4int  nclones   = 1,
                               G4int  nbrothers = 1, 
                               G4int  me        = 0,
                               G4int  copyno    = -1 );
  virtual ~J4TPCPadPlane();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw();
  virtual void	Print() const;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String   fFirstName;
  J4TPCPadRow     **fPadRows;

};

#endif

