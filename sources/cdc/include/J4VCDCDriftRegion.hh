// $Id$
#ifndef __J4VCDCDRIFTREGION__
#define __J4VCDCDRIFTREGION__
//*************************************************************************
//* --------------------
//* J4VCDCDRIFTREGION
//* --------------------
//* (Description)
//* 	Abstract base class for CDC DriftRegion.
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

class J4CDCSenseWire;
class J4VCDCDriftRegion : public J4VCDCDetectorComponent {	

public:
  J4VCDCDriftRegion( const G4String &name,
                    J4VDetectorComponent *parent    = 0,
                                   G4int  nclones   = 1,
                                   G4int  nbrothers = 1, 
                                   G4int  me        = 0,
                                   G4int  copyno    = -1 )
      :J4VCDCDetectorComponent( name, parent, nclones,
                                nbrothers, me, copyno),
       fTanStereo(0), fRwaist(0){} 

  J4VCDCDriftRegion(const J4VCDCDriftRegion &orig, G4int copyno)
      :J4VCDCDetectorComponent( orig, copyno ), 
       fTanStereo(orig.fTanStereo), fRwaist(orig.fRwaist) {}

  virtual ~J4VCDCDriftRegion() {};

  inline virtual G4double        GetTwistedAngle()      const;
  inline virtual G4String        GetLayerType()         const;
  inline virtual G4int           GetGlobalLayerNumber() const;
  inline virtual J4CDCSenseWire* GetSenseWire()         const 
                                 { return fSenseWire;   }
  inline virtual G4double        GetTanStereo()       const 
                                 { return fTanStereo; } 
  inline virtual G4double        GetRwaist()            const 
                                 { return fRwaist; } 

protected:  
  J4CDCSenseWire* fSenseWire;
  G4double        fTanStereo;
  G4double        fRwaist;
  
};

//=====================================================================
//---------------------
// inline function
//---------------------

G4double J4VCDCDriftRegion::GetTwistedAngle() const
{ 
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetTwistedAngle(); 
}
G4String J4VCDCDriftRegion::GetLayerType() const
{ 
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetLayerType(); 
}

G4int J4VCDCDriftRegion::GetGlobalLayerNumber() const
{
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetGlobalLayerNumber();
}

#endif

