// $Id$
#ifndef __J4VCLXBLOCK__
#define __J4VCLXBLOCK__
//*************************************************************************
//* --------------------
//* J4VCLXBlock
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*      2006/05/01 H.Ono Original version
//*************************************************************************
#include "J4VCLXLayer.hh"
#include "J4CLXParameterList.hh"
#include "J4VCLXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXLayer;
class J4VCLXBlock : public J4VCLXDetectorComponent {

public:

  J4VCLXBlock( const G4String &name,
	       J4VDetectorComponent *parent = 0,
	       G4int  nclones   = 1,
	       G4int  nbrothers = 1,
	       G4int  me        = 0,
	       G4int  copyno    = -1 );

  J4VCLXBlock( const J4VCLXBlock& orig, G4int copyno );
  
  virtual ~J4VCLXBlock();

  virtual void InstallIn( J4VComponent *mother,
			  G4RotationMatrix    *prot  = 0,
			  const G4ThreeVector &tlate = G4ThreeVector(0.) );
  
  virtual void Draw();
  virtual void Print() const ;

  //* Member functions
  G4double GetHalfX     ( G4int i = 0 ) ;
  G4double GetHalfXL    ( G4int i = 0 ) ;
  G4double GetDphi      ( G4int i = 0 ) ;  
  G4double GetSphi      ( G4int i = 0 ) ;
  G4bool   IsBarrel     ();
  G4String GetMaterial  ();
  G4bool   GetVisAtt    ();
  G4Color  GetColor     ();

  //* Pure virtual functions 
  virtual G4String GetFirstName ()         const = 0;
  virtual G4double GetYmin      ( G4int i = 0 )  = 0;  
  virtual G4double GetYmax      ( G4int i = 0 )  = 0;
  virtual G4double GetHalfZ     ( G4int i = 0 )  = 0;
  virtual G4int    GetNLayers   ()               = 0;
    
  // Barrel = 0, Endcap+Z = 1, Endcap-Z = -1
  virtual G4int    IsEndcap     ()        = 0;
  virtual G4bool   IsEM         ()        = 0;

  virtual J4VCLXLayer *Create( J4VDetectorComponent *parent = 0,
			       G4int  nclones   = 1,
			       G4int  nbrothers = 1,
			       G4int  me        = 0,
			       G4int  copyno    = -1 ) = 0;
  
private:
  void Assemble();
  void Cabling();

private:
  std::vector<J4VCLXLayer*> fLayers;
};

//* Inline funcsionts
inline G4bool J4VCLXBlock::IsBarrel()
{
  return ( IsEndcap() == 0 ) ? true : false;
}

inline G4double J4VCLXBlock::GetHalfX( G4int myID )
{
  return GetYmin( myID ) * std::tan( 0.5*GetDphi() );
}

inline G4double J4VCLXBlock::GetHalfXL( G4int myID )
{
  return GetYmax( myID ) * std::tan( 0.5*GetDphi() );
}

inline G4double J4VCLXBlock::GetDphi( G4int )
{
  return OpenParameterList()->GetTrapDeltaPhi(); 
}

inline G4double J4VCLXBlock::GetSphi( G4int )
{
  return 0.;
}

inline G4String J4VCLXBlock::GetMaterial()
{
  return OpenParameterList()->GetBlockMaterial();
}

inline G4bool J4VCLXBlock::GetVisAtt()
{
  return ( IsEM() )
    ? OpenParameterList()->GetEMVisAtt()
    : OpenParameterList()->GetHDVisAtt();
}

inline G4Color J4VCLXBlock::GetColor()
{
  return ( IsEM() )
    ? OpenParameterList()->GetEMColor()
    : OpenParameterList()->GetHDColor();
}

#endif
