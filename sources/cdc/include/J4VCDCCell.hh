// $Id$
#ifndef __J4VCDCCELL__
#define __J4VCDCCELL__
//*************************************************************************
//* --------------------
//* J4VCDCCell
//* --------------------
//* (Description)
//* 	Virtual abstract class for CDC Cell.
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

class J4VCDCDriftRegion;

class J4VCDCCell : public J4VCDCDetectorComponent {	

public:
  J4VCDCCell(const G4String       &name         , 
             J4VDetectorComponent *parent    = 0,
                            G4int  nclones   = 1,
                            G4int  nbrothers = 1, 
                            G4int  me        = 0,
                            G4int  copyno    = -1 )
      :J4VCDCDetectorComponent( name, parent, nclones,
                                nbrothers, me, copyno ) {}

  J4VCDCCell(const J4VCDCCell &orig, G4int copyno)
      :J4VCDCDetectorComponent(orig, copyno ) {}
                  
             

  virtual ~J4VCDCCell() {}
  
  inline virtual G4int    GetNcellsPerLayer() const; 
  inline virtual G4double GetTwistedAngle()   const;
  inline virtual G4double GetShieldWidth()    const;
  inline virtual G4String GetLayerType()      const;
  inline virtual G4int    GetGlobalLayerNumber() const;
  
};


//=====================================================================
//---------------------
// inline function
//---------------------

G4int J4VCDCCell::GetNcellsPerLayer() const
{ 
   return ((J4CDCLayer *)GetMother())->GetNcellsPerLayer(); 
}

G4double J4VCDCCell::GetTwistedAngle() const
{ 
   return ((J4CDCLayer *)GetMother())->GetTwistedAngle(); 
}

G4double J4VCDCCell::GetShieldWidth() const
{ 
   return ((J4CDCLayer *)GetMother())->GetShieldWidth(); 
}

G4String J4VCDCCell::GetLayerType() const
{ 
   return ((J4CDCLayer *)GetMother())->GetLayerType(); 
}

G4int J4VCDCCell::GetGlobalLayerNumber() const
{
   return ((J4CDCLayer *)GetMother())->GetGlobalLayerNumber();
}


#endif


