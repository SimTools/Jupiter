// $Id$
#ifndef __J4VCLXLAYER__
#define __J4VCLXLAYER__
//*************************************************************************
//* --------------------
//* J4VCLXLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXParameterList.hh"
#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXSubLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXSubLayer;
class J4VCLXLayer : public J4VCLXDetectorComponent {

public:
  J4VCLXLayer( G4bool isBarrel,
	       const G4String &name,
               J4VDetectorComponent *parent    = 0,
	       G4int  nclones   = 1,
	       G4int  nbrothers = 1,
	       G4int  me        = 0,
	       G4int  copyno    = -1 );
  
  virtual ~J4VCLXLayer();

  virtual void InstallIn( J4VComponent        *mother,
			  G4RotationMatrix    *prot  = 0,
			  const G4ThreeVector &tlate = G4ThreeVector(0.) );

  virtual void Draw();
  virtual void Print() const;
  
  //* IsEndcap() == 0(Barrel), 1(Endcap+Z), -1(Endcap-Z)
  //  inline G4int    IsEndcap() const { return fIsEndcap ; }
  inline G4bool   IsBarrel() const { return fIsBarrel ; }
  
  //* Virtual Functions Deliverd from J4VCLXTrap
  virtual G4bool   IsEM         () const        = 0;
  virtual G4String GetFirstName () const        = 0;    
  virtual G4double GetYmin      ( G4int i = 0 ) = 0;  
  virtual G4double GetYmax      ( G4int i = 0 ) = 0;
  virtual G4double GetHalfZ     ( G4int i = 0 ) = 0;
  virtual G4double GetHalfX     ( G4int i = 0 ) = 0;
  virtual G4double GetHalfXL    ( G4int i = 0 ) = 0;

  //* Member functions
  //  G4double GetHalfX     ( G4int i = 0 ) ;
  //  G4double GetHalfXL    ( G4int i = 0 ) ;
  G4double GetDphi      ( G4int i = 0 ) ;  
  G4double GetSphi      ( G4int i = 0 ) ;
  G4String GetMaterial  ();
  G4bool   GetVisAtt    ();
  G4Color  GetColor     ();

private:
  void Assemble();
  void Cabling();
  
protected:
  virtual J4VCLXSubLayer *CreateAbs( J4VDetectorComponent *parent    = 0,
                                                    G4int  nclones   = 1,
                                                    G4int  nbrothers = 1,
                                                    G4int  me        = 0,
                                                    G4int  copyno    = -1 ) = 0;

  virtual J4VCLXSubLayer *CreateActive( J4VDetectorComponent *parent    = 0,
                                                       G4int  nclones   = 1,
                                                       G4int  nbrothers = 1,
                                                       G4int  me        = 0,
                                                       G4int  copyno    = -1 ) = 0;

  virtual J4VCLXSubLayer *CreateFlex( J4VDetectorComponent *parent    = 0,
                                                     G4int  nclones   = 1,
                                                     G4int  nbrothers = 1,
                                                     G4int  me        = 0,
                                                     G4int  copyno    = -1 ) = 0;

protected:
  std::vector<J4VCLXSubLayer*> fSubLayers;

  //  J4VCLXSubLayer *fAbsLayer;
  //  J4VCLXSubLayer *fActiveLayer;
  //  J4VCLXSubLayer *fFlexLayer;
  
private:
  //  G4int fIsEndcap;
  G4bool fIsBarrel;
   
};

////* Inilne Functions deliverd from base class
//inline G4double J4VCLXLayer::GetHalfX( G4int myID )
//{
//  //return GetYmin( myID ) * std::tan( 0.5*GetDphi() );
//  return ( IsEM() ) 
//    ? ((G4Trap*)GetMother())->GetXHalfLength1()+GetMyID()*OpenParameterList()->GetEMLayerThickness()*std::tan( 0.5*GetDphi() )
//    : ((G4Trap*)GetMother())->GetXHalfLength1()+GetMyID()*OpenParameterList()->GetHDLayerThickness()*std::tan( 0.5*GetDphi() );
//}
//
//inline G4double J4VCLXLayer::GetHalfXL( G4int myID )
//{
//  //return GetYmax( myID ) * std::tan( 0.5*GetDphi() );
//  return ( IsEM() ) ? GetHalfX( myID )+OpenParameterList()->GetEMLayerThickness()*std::tan( 0.5*GetDphi() )
//                    : GetHalfX( myID )+OpenParameterList()->GetHDLayerThickness()*std::tan( 0.5*GetDphi() );
//}

inline G4double J4VCLXLayer::GetDphi( G4int )
{
  return OpenParameterList()->GetTrapDeltaPhi(); 
}

inline G4double J4VCLXLayer::GetSphi( G4int )
{
  return 0.;
}

inline G4String J4VCLXLayer::GetMaterial()
{
  return OpenParameterList()->GetLayerMaterial();
}

inline G4bool J4VCLXLayer::GetVisAtt()
{
  return OpenParameterList()->GetLayerVisAtt();
}

inline G4Color J4VCLXLayer::GetColor()
{
  return OpenParameterList()->GetLayerColor();
}

#endif
