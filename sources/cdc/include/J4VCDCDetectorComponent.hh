// $Id$
#ifndef __J4VCDCDETECTORCOMPONENT__
#define __J4VCDCDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VCDCDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4CDCMaterialStore.hh"
#include "J4CDCParameterList.hh"
#include "J4TwistedTubs.hh"
#include "G4String.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCDCDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  			   
  J4VCDCDetectorComponent( const G4String       &name, 
  			                  J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  J4VCDCDetectorComponent( const J4VCDCDetectorComponent &orig,
                                 G4int                    copyno);
  virtual ~J4VCDCDetectorComponent();

  virtual G4double GetInnerRadius(J4VComponent * cdctubs) const;
                          // returns inner radius at "Endcap".
  virtual G4double GetOuterRadius(J4VComponent * cdctubs) const;
                          // returns outer radius at "Endcap".
  virtual G4double GetInnerWeist (J4VComponent * cdctubs) const;
                          // returns inner radius at z = 0.
  virtual G4double GetOuterWeist (J4VComponent * cdctubs) const;
                          // returns outer radius at z = 0.
  virtual G4double GetZHalfLength(J4VComponent * cdctubs) const;
  virtual G4double GetDeltaPhi   (J4VComponent * cdctubs) const;
  virtual G4double GetPhiOffset  (J4VComponent * cdctubs) const;
  
  static  G4double CalcTanStereo(G4double phitwist,
                                   G4double radius, 
                                   G4double halflength);
  static  G4double CalcWaist(G4double tanstereo,
                             G4double radius, 
                             G4double halflength);

protected:    
  J4VMaterialStore*          OpenMaterialStore();
  J4CDCParameterList*        OpenParameterList() { return J4CDCParameterList::GetInstance();}
  
private:
  static J4CDCMaterialStore *fMaterialStore;
  static G4String            fSubGroup;
       
};

//=====================================================================
//---------------------
// inline function
//---------------------


#endif


