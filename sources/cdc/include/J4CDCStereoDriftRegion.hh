// $Id$
#ifndef __J4CDCSTEREODRIFTREGION__
#define __J4CDCSTEREODRIFTREGION__
//*************************************************************************
//* --------------------
//* J4CDCDRIFTREGION
//* --------------------
//* (Description)
//* 	Derivation class for CDC DriftRegion.
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
class J4CDCStereoDriftRegion : public J4VCDCDetectorComponent {	

public:
  J4CDCStereoDriftRegion( J4VDetectorComponent *parent    = 0,
                                   G4int  nclones   = 1,
                                   G4int  nbrothers = 1, 
                                   G4int  me        = 0,
                                   G4int  copyno    = -1 );
  virtual ~J4CDCStereoDriftRegion();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	SwitchOn (G4String opt = "me")  ;
  virtual void	SwitchOff(G4String opt = "me") ;
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
  inline virtual G4double        GetTwistedAngle()      const;
  inline virtual G4String        GetLayerType()         const;
  inline virtual G4int           GetGlobalLayerNumber() const;
  inline virtual G4int           GetCellNumber()        const;
  inline virtual J4CDCSenseWire* GetSenseWire() const 
                                 { return fSenseWire; }
  
private:
  void 	Assemble(); 
  void   Cabling ();  
   
private:  
  static G4String fFirstName;
  J4CDCSenseWire* fSenseWire;
  
};

//=====================================================================
//---------------------
// inline function
//---------------------

G4double J4CDCStereoDriftRegion::GetTwistedAngle() const
{ 
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetTwistedAngle(); 
}
G4String J4CDCStereoDriftRegion::GetLayerType() const
{ 
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetLayerType(); 
}

G4int J4CDCStereoDriftRegion::GetGlobalLayerNumber() const
{
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetGlobalLayerNumber();
}

G4int J4CDCStereoDriftRegion::GetCellNumber() const
{
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetCopyNo();
}

#endif

