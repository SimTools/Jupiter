#ifndef __J4TPCPADRING__
#define __J4TPCPADRING__
//*************************************************************************
//* --------------------
//* J4TPCPadRow
//* --------------------
//* (Description)
//* 	Derivation class for TPC PadRow.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4VTPCDetectorComponent.hh"
#include "J4TPCPad.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4TPCPadRow : public J4VTPCDetectorComponent {	

public:

  J4TPCPadRow(J4VDetectorComponent* parent    = 0,
  	       G4int                 nclones   = 1,
  	       G4int                 nbrothers = 1, 
  	       G4int                 me        = 0,
               G4int                 copyno    = -1);
  	     
  virtual ~J4TPCPadRow();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw();
  virtual void	Print() const;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
  J4TPCPad   *fPad;
  
};

#endif

