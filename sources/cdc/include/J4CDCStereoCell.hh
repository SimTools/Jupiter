// $Id$
#ifndef __J4CDCSTEREOCELL__
#define __J4CDCSTEREOCELL__
//*************************************************************************
//* --------------------
//* J4CDCStereoCell
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

class J4CDCStereoDriftRegion;
//class J4CDCDummyDriftRegion;

class J4CDCStereoCell : public J4VCDCCell {	

public:
  J4CDCStereoCell(J4VDetectorComponent *parent    = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );
                           
  J4CDCStereoCell(const J4CDCStereoCell &orig, G4int copyno);
  
  virtual ~J4CDCStereoCell();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void  Assemble();    
  void  Cabling ();
  
private:  
  static G4String          fFirstName;
  J4CDCStereoDriftRegion **fDriftRegions;
//  J4CDCDummyDriftRegion **fDummyDriftRegions;
  G4RotationMatrix         fRot;
  
};


//=====================================================================
//---------------------
// inline function
//---------------------

#endif

