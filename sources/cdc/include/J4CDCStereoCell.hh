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

#include "J4VCDCDetectorComponent.hh"
#include "J4CDCLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCStereoDriftRegion;
//class J4CDCDummyDriftRegion;

class J4CDCStereoCell : public J4VCDCDetectorComponent {	

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
  static G4String          fFirstName;
  J4CDCStereoDriftRegion **fDriftRegions;
//  J4CDCDummyDriftRegion **fDummyDriftRegions;
  G4RotationMatrix         fRot;
  
};


//=====================================================================
//---------------------
// inline function
//---------------------

G4int J4CDCStereoCell::GetNcellsPerLayer() const
{ 
   return ((J4CDCLayer *)GetMother())->GetNcellsPerLayer(); 
}

G4double J4CDCStereoCell::GetTwistedAngle() const
{ 
   return ((J4CDCLayer *)GetMother())->GetTwistedAngle(); 
}

G4double J4CDCStereoCell::GetShieldWidth() const
{ 
   return ((J4CDCLayer *)GetMother())->GetShieldWidth(); 
}

G4String J4CDCStereoCell::GetLayerType() const
{ 
   return ((J4CDCLayer *)GetMother())->GetLayerType(); 
}

G4int J4CDCStereoCell::GetGlobalLayerNumber() const
{
   return ((J4CDCLayer *)GetMother())->GetGlobalLayerNumber();
}


#endif


