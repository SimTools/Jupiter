// $Id$
#ifndef __J4VCLXSTRIP__
#define __J4VCLXSTRIP__
//*************************************************************************
//* --------------------
//* J4VCLXStrip
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
#include "J4VCLXCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXStrip : public J4VCLXDetectorComponent {

public:
  J4VCLXStrip( G4bool isBarrel,
	       const G4String &name,
	       J4VDetectorComponent *parent    = 0,
	       G4int  nclones   = 1,
	       G4int  nbrothers = 1,
	       G4int  me        = 0,
	       G4int  copyno    = -1 );
  
  virtual ~J4VCLXStrip();

  virtual void InstallIn( J4VComponent        *mother,
			  G4RotationMatrix    *prot  = 0,
			  const G4ThreeVector &tlate = 0 );

  virtual void Draw();
  virtual void Print() const;
  
  //* IsEndcap() == 0(Barrel), 1(Endcap+Z), -1(Endcap-Z)
  //  G4int    IsEndcap() const { return fIsEndcap ; }
  G4bool   IsBarrel() const { return fIsBarrel ; }
  
  //* Virtual Functions Deliverd from J4VCLXTrap
  virtual G4bool   IsBoundary   () const   = 0;
  virtual G4bool   IsEM         () const   = 0;
  virtual G4String GetFirstName () const   = 0;

//  G4bool   IsXPlus     () const;
  G4String GetMaterial ();
  G4bool   GetVisAtt   ();
  G4Color  GetColor    ();

private:
  void Assemble();
  void Cabling();

protected:
  virtual J4VCLXCell *Create( J4VDetectorComponent *parent = 0,
			      G4int  nclones   = 1,
			      G4int  nbrothers = 1,
			      G4int  me        = 0,
			      G4int  copyno    = -1 ) = 0;

  J4VCLXCell *fCell;
  
private:
  //  G4int fIsEndcap;
  G4bool fIsBarrel;
};

inline G4String J4VCLXStrip::GetMaterial()
{
  return OpenParameterList()->GetStripMaterial();
}

inline G4bool J4VCLXStrip::GetVisAtt()
{
  return OpenParameterList()->GetStripVisAtt();
}

inline G4Color J4VCLXStrip::GetColor()
{
  return OpenParameterList()->GetStripColor();
}

#endif
