// $Id$
#ifndef __J4CALSUBLAYER__
#define __J4CALSUBLAYER__
//*************************************************************************
//* --------------------
//* J4CALSubLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4VCALDetectorComponent.hh"
#include "J4CALCone.hh"
#if 0
#include "J4CALBlock.hh"
#endif

class J4VDetectorComponent;
class J4CALSubLayerSD;
class J4CALSubLayer;
//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALSubLayer : public J4VCALDetectorComponent {

public:
  J4CALSubLayer( J4VDetectorComponent *parent    = 0,
                               G4bool  isem      = true,
                                G4int  nclones   = 1,
                                G4int  nbrothers = 1, 
                                G4int  me        = 0,
                                G4int  copyno    = -1 );
  virtual ~J4CALSubLayer();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = 0 );
  virtual void	Draw() ;
  virtual void	Print() const ;

  inline G4int  GetNCones();
  inline G4int  GetNTowers();
  inline G4int  GetNMiniTowers();

#if 1
  inline G4int  GetMyConeID();
  inline G4int  GetMyTowerID();
  inline G4int  GetNMiniCones();
  inline G4int  GetMyMiniConeID();
  inline G4int  GetMyMiniTowerID();
  inline G4int  GetNLayers();
  inline G4int  GetMyLayerID();
  inline G4int  GetNSubLayers();
  inline G4int  GetMySubLayerID();
  inline G4bool IsBarrel();
#endif
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static const G4String fFirstName;

};

// ===============================================================
// inline functions ----------------------------------------------
G4int J4CALSubLayer::GetNCones()
{
  return GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetNbrothers();
}

G4int J4CALSubLayer::GetNTowers()
{
  return GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetNclones();
}
G4int J4CALSubLayer::GetNMiniTowers()
{
  return GetMother()->GetMother()->GetNbrothers();
}

#if 1
G4int J4CALSubLayer::GetNMiniCones()
{
  return GetMother()->GetMother()->GetMother()->GetNbrothers();
}
G4int J4CALSubLayer::GetMyTowerID()
{
  return GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetMyID();
}

G4int J4CALSubLayer::GetMyConeID()
{
  return GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetMyID();
}

G4int J4CALSubLayer::GetMyMiniConeID()
{
  return GetMother()->GetMother()->GetMother()->GetMyID();
}

G4int J4CALSubLayer::GetMyMiniTowerID()
{
  return GetMother()->GetMother()->GetMyID();
}

G4int J4CALSubLayer::GetNLayers()
{
  return GetMother()->GetNbrothers();
}

G4int J4CALSubLayer::GetMyLayerID()
{
  return GetMother()->GetMyID();
}

G4int J4CALSubLayer::GetNSubLayers()
{
  return GetNbrothers();
}

G4int J4CALSubLayer::GetMySubLayerID()
{
  return GetMyID();
}

G4bool J4CALSubLayer::IsBarrel()
{
  return ( (J4CALCone*)GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetMother() )->IsBarrel();
}

#if 0
G4bool J4CALSubLayer::IsEM()
{
  const G4String& firstName = ( (J4CALBlock*)GetMother()->GetMother()->GetMother()->GetMother() ) -> GetFirstName();
  if ( firstName == "EM" ) return true;
  else return false;
  //return ( (J4CALBlock*)GetMother()->GetMother()->GetMother()->GetMother() ) -> IsEM();
}
#endif
#endif

#endif
