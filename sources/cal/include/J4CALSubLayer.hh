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
#include "J4CALLayer.hh"

class J4VDetectorComponent;
class J4CALSubLayerSD;
class J4CALSubLayer;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALSubLayer : public J4VCALDetectorComponent {
//class J4CALSubLayer : public J4CALLayer{

public:
  J4CALSubLayer(J4VDetectorComponent  *parent   = 0,
                               G4int  nclones   = 1,
                               G4int  nbrothers = 1, 
                               G4int  me        = 0,
                               G4int  copyno    = -1 );
  virtual ~J4CALSubLayer();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  inline G4int  GetTowerNClones();
  inline G4int  GetMiniTowerNClones();

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static const G4String& fFirstName;

//  G4int fMiniTowerNClones;
//  G4int fTowerNClones;
  
};
// ===============================================================
// inline functions ----------------------------------------------
G4int J4CALSubLayer::GetTowerNClones()
{
  return GetMother()->GetMother()->GetMother()->GetMother()->GetMother()->GetNclones();
}

G4int J4CALSubLayer::GetMiniTowerNClones()
{
  return GetMother()->GetMother()->GetNclones();
}

#endif
