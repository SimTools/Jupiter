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

#include "J4VCDCDetectorComponent.hh"
#include "J4CDCLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCDriftRegion;
#if 0
class J4CDCDummyDriftRegion;
#endif

class J4CDCCell : public J4VCDCDetectorComponent {	

public:
  J4CDCCell(J4VDetectorComponent *parent    = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );
  virtual ~J4CDCCell();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
  inline virtual G4int    GetNcellsPerLayer() const; 
  inline virtual G4double GetTwistedAngle()   const;
  inline virtual G4double GetShieldWidth()    const;
  inline virtual G4String GetLayerType()      const;
  inline virtual G4int    GetGlobalLayerNumber() const;
  
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

G4int J4CDCCell::GetNcellsPerLayer() const
{ 
   return ((J4CDCLayer *)GetMother())->GetNcellsPerLayer(); 
}

G4double J4CDCCell::GetTwistedAngle() const
{ 
   return ((J4CDCLayer *)GetMother())->GetTwistedAngle(); 
}

G4double J4CDCCell::GetShieldWidth() const
{ 
   return ((J4CDCLayer *)GetMother())->GetShieldWidth(); 
}

G4String J4CDCCell::GetLayerType() const
{ 
   return ((J4CDCLayer *)GetMother())->GetLayerType(); 
}

G4int J4CDCCell::GetGlobalLayerNumber() const
{
   return ((J4CDCLayer *)GetMother())->GetGlobalLayerNumber();
}


#endif


