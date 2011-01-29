// $Id$
#ifndef __J4CDCSENSEWIRE__
#define __J4CDCSENSEWIRE__
//*************************************************************************
//* --------------------
//* J4CDCSENSEWIRE
//* --------------------
//* (Description)
//* 	Derivation class for CDC SenseWire.
//*     Mother class : J4VCDCDetectorComponent
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

class J4CDCSenseWire : public J4VCDCDetectorComponent {	

public:
  J4CDCSenseWire( J4VDetectorComponent *parent    = 0,
                                 G4int  nclones   = 1,
                                 G4int  nbrothers = 1, 
                                 G4int  me        = 0,
                                 G4int  copyno    = -1 );
  virtual ~J4CDCSenseWire();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
                          
  virtual void          SwitchOn (G4String opt = "me")  ;
  virtual void          SwitchOff(G4String opt = "me") ;
  virtual void          Draw()      ;
  virtual void          Print() const ;
 
  inline virtual G4double      GetTwistedAngle()         const;
  inline virtual G4String      GetLayerType()            const;
  inline virtual G4int         GetGlobalLayerNumber()    const;
  inline virtual G4ThreeVector GetLocalWireEnd(G4int dz) const;
 

private:
  void 	Assemble(); 
  void   Cabling ();
  
private: 
  static G4String   fFirstName;
  G4RotationMatrix *fRot;
  G4ThreeVector     fWireEnd;
   

};

//=====================================================================
//---------------------
// inline function
//---------------------

G4double J4CDCSenseWire::GetTwistedAngle() const
{ 
   J4CDCLayer* greatgrandmother 
       = ((J4CDCLayer *)GetMother()->GetMother()->GetMother());
   return greatgrandmother->GetTwistedAngle(); 
}
G4String J4CDCSenseWire::GetLayerType() const
{ 
   J4CDCLayer* greatgrandmother 
       = ((J4CDCLayer *)GetMother()->GetMother()->GetMother());
   return greatgrandmother->GetLayerType(); 
}

G4int J4CDCSenseWire::GetGlobalLayerNumber() const
{
   J4CDCLayer* greatgrandmother 
       = ((J4CDCLayer *)GetMother()->GetMother()->GetMother());
   return greatgrandmother->GetGlobalLayerNumber(); 
}

G4ThreeVector J4CDCSenseWire::GetLocalWireEnd(G4int dz) const
{
   if (dz > 0) {
      return fWireEnd;
   } else {
      return G4ThreeVector(fWireEnd.x(), -fWireEnd.y(), 
                           -fWireEnd.z());
   }
}

#endif


