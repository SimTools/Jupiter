// $Id$
#ifndef __J4VCLXSUBLAYER__
#define __J4VCLXSUBLAYER__
//*************************************************************************
//* --------------------
//* J4VCLXSubLayer
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
#include "J4VCLXTrapStrip.hh"
#include "J4VCLXStrip.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXSubLayer : public J4VCLXDetectorComponent {

public:
  J4VCLXSubLayer( G4bool isBarrel,
		  const G4String &name,
		  J4VDetectorComponent *parent    = 0,
		  G4int  nclones   = 1,
		  G4int  nbrothers = 1,
		  G4int  me        = 0,
		  G4int  copyno    = -1 );
  
  virtual ~J4VCLXSubLayer();

  virtual void InstallIn( J4VComponent        *mother,
			  G4RotationMatrix    *prot  = 0,
			  const G4ThreeVector &tlate = 0 );

  virtual void Draw();
  virtual void Print() const;
  
  //* IsEndcap() == 0(Barrel), 1(Endcap+Z), -1(Endcap-Z)
  //  G4int    IsEndcap() const { return fIsEndcap ; }
  G4bool   IsBarrel() const { return fIsBarrel ; }
  
  //* Virtual Functions Deliverd from J4VCLXTrap
  virtual G4bool   IsActive     () const        = 0;
  virtual G4bool   IsEM         () const        = 0;
  virtual G4String GetFirstName () const        = 0;
  
  virtual G4double GetHalfX     ( G4int i = 0 ) = 0;
  virtual G4double GetHalfXL    ( G4int i = 0 ) = 0;  
  virtual G4double GetYmin      ( G4int i = 0 ) = 0;  
  virtual G4double GetYmax      ( G4int i = 0 ) = 0;
  virtual G4double GetHalfZ     ( G4int i = 0 ) = 0;
  virtual G4String GetMaterial  ()              = 0;

  //* Member functions
  G4double GetDphi      ( G4int i = 0 ) ;  
  G4double GetSphi      ( G4int i = 0 ) ;
  G4bool   GetVisAtt    ();
  G4Color  GetColor     ();

private:
  void Assemble();
  void Cabling();

protected:

  virtual J4VCLXTrapStrip *Create( J4VDetectorComponent *parent = 0,
				   G4int  nclones   = 1,
				   G4int  nbrothers = 1,
				   G4int  me        = 0,
				   G4int  copyno    = -1 ) = 0;

  std::vector< J4VCLXTrapStrip* > fTrapStrips;
  
private:
  //  G4int fIsEndcap;
  G4bool fIsBarrel;
  
};

//* Inilne Functions deliverd from base class
//inline G4double J4VCLXSubLayer::GetHalfX( G4int myID )
//{
//  return GetYmin( myID ) * std::tan( 0.5*GetDphi() );
//}
//
//inline G4double J4VCLXSubLayer::GetHalfXL( G4int myID )
//{
//  return GetYmax( myID ) * std::tan( 0.5*GetDphi() );
//}

inline G4double J4VCLXSubLayer::GetDphi( G4int )
{
  return OpenParameterList()->GetTrapDeltaPhi(); 
}

inline G4double J4VCLXSubLayer::GetSphi( G4int )
{
  return 0.;
}

inline G4bool J4VCLXSubLayer::GetVisAtt()
{
  return OpenParameterList()->GetSubLayerVisAtt();
}

inline G4Color J4VCLXSubLayer::GetColor()
{
  return OpenParameterList()->GetSubLayerColor();
}

#endif
