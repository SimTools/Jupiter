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

#include "J4VCDCDriftRegion.hh"
#include "J4CDCLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCSenseWire;
class J4CDCStereoDriftRegion : public J4VCDCDriftRegion {	

public:
  J4CDCStereoDriftRegion( J4VDetectorComponent *parent    = 0,
                                   G4int  nclones   = 1,
                                   G4int  nbrothers = 1, 
                                   G4int  me        = 0,
                                   G4int  copyno    = -1 );

  J4CDCStereoDriftRegion(const J4CDCStereoDriftRegion &orig,
                                                G4int  copyno );

  virtual ~J4CDCStereoDriftRegion();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	SwitchOn (G4String opt = "me")  ;
  virtual void	SwitchOff(G4String opt = "me") ;
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
  inline virtual G4int           GetCellNumber()        const;
  
private:
  void 	Assemble(); 
  void   Cabling ();  
   
private:  
  static G4String fFirstName;
  
};

//=====================================================================
//---------------------
// inline function
//---------------------

G4int J4CDCStereoDriftRegion::GetCellNumber() const
{
   J4CDCLayer *grandmother = (J4CDCLayer *)GetMother()->GetMother();
   return grandmother->GetCopyNo();
}

#endif

