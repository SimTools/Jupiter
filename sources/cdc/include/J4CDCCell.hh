// $Id$
#ifndef __J4CDCCELL__
#define __J4CDCCELL__
//*************************************************************************
//* --------------------
//* J4CDCCell
//* --------------------
//* (Description)
//* 	Derivation class for CDC Cell.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCCell.hh"
#include "J4CDCLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCDriftRegion;
#if 0
class J4CDCDummyDriftRegion;
#endif

class J4CDCCell : public J4VCDCCell {	

public:
  J4CDCCell(J4VDetectorComponent *parent    = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );

  J4CDCCell(const J4CDCCell &orig, G4int copyno);

  virtual ~J4CDCCell();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void  Assemble();    
  void  Cabling ();
  
private:  
  static G4String         fFirstName;
  J4CDCDriftRegion**      fDriftRegions;
#if 0
  J4CDCDummyDriftRegion** fDummyDriftRegions;
#endif
  
  G4double                fRmin;
  G4double                fRmax;
};


//=====================================================================
//---------------------
// inline function
//---------------------

#endif


