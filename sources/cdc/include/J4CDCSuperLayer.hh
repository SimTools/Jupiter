// $Id$
#ifndef __J4CDCSUPERLAYER__
#define __J4CDCSUPERLAYER__
//*************************************************************************
//* --------------------
//* J4CDCSuperLayer
//* --------------------
//* (Description)
//* 	Derivation class for CDC Layer.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCLayer;
class J4CDCSuperLayer : public J4VCDCDetectorComponent {	

public:

  J4CDCSuperLayer(J4VDetectorComponent* parent    = 0,
                  G4int                 nclones   = 1,
                  G4int                 nbrothers = 1, 
                  G4int                 me        = 0,
                  G4int                 copyno    = -1 );
  	       	     
  virtual ~J4CDCSuperLayer();

  virtual void   InstallIn(J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	  Draw() ;
  virtual void	  Print() const ;
  
  inline virtual G4int GetNcellsPerLayer() const 
                           { return fNcellsPerLayer; }
  
private:
  void  Assemble();    
  void  Cabling ();
  
private:
  
  static G4String   fFirstName;

  J4CDCLayer      **fLayers;
  
  G4double          fOffset;
  G4int             fNcellsPerLayer;
  G4RotationMatrix  fRot;
  
};

#endif


