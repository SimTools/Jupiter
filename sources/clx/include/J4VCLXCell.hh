// $Id$
#ifndef __J4VCLXCELL__
#define __J4VCLXCELL__
//*************************************************************************
//* --------------------
//* J4VCLXCell
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXDetectorComponent.hh"
#include "J4CLXParameterList.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXCell : public J4VCLXDetectorComponent {

public:
  J4VCLXCell( G4bool isBarrel,
	      G4bool isBoundary,
	      const G4String &name,
	      J4VDetectorComponent *parent = 0,
	      G4int  nclones   = 1,
	      G4int  nbrothers = 1,
	      G4int  me        = 0,
	      G4int  copyno    = -1 );
  
  virtual ~J4VCLXCell();

  virtual void InstallIn( J4VComponent        *mother,
			  G4RotationMatrix    *prot  = 0,
			  const G4ThreeVector &tlate = 0 );

  virtual void Draw();
  virtual void Print() const;
  
  //* IsEndcap() == 0(Barrel), 1(Endcap+Z), -1(Endcap-Z)
  //  G4int    IsEndcap() const { return fIsEndcap ; }
  G4bool   IsBarrel()   const { return fIsBarrel   ; }
  G4bool   IsBoundary() const { return fIsBoundary ; }
  //G4bool   IsXPlus()    const { return fIsXPlus    ; }
  G4bool   IsXPlus()    const { return true    ; }
  
  //* Virtual Functions Deliverd from J4VCLXTrap
  virtual G4bool   IsEM         () const        = 0;
  virtual G4String GetFirstName () const        = 0;    

  //* Member functions
  G4String GetMaterial  ();  
  G4bool   GetVisAtt    ();
  G4Color  GetColor     ();

private:
  void Assemble();
  void Cabling() = 0;

private:
  //  G4int fIsEndcap;
  G4bool fIsBarrel;
  G4bool fIsBoundary;
  
};

//* Inilne Functions deliverd from base class
inline G4String J4VCLXCell::GetMaterial()
{
  return ( IsEM() )
    ? OpenParameterList()->GetEMCellMaterial()
    : OpenParameterList()->GetHDCellMaterial();
}

inline G4bool J4VCLXCell::GetVisAtt()
{
  return OpenParameterList()->GetCellVisAtt();
}

inline G4Color J4VCLXCell::GetColor()
{
  return OpenParameterList()->GetCellColor();
}

#endif
