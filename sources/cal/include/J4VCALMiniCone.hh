// $Id$
#ifndef __J4VCALMINICONE__
#define __J4VCALMINICONE__
//*************************************************************************
//* --------------------
//* J4VCALMiniCone
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4VCALMiniTower.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCALMiniTower;
class J4VCALMiniCone : public J4VCALDetectorComponent {	

public:
  J4VCALMiniCone( const G4String       &name ,
                  J4VDetectorComponent *parent    = 0,
                                 G4int  nclones   = 1,
                                 G4int  nbrothers = 1, 
                                 G4int  me        = 0,
                                 G4int  copyno    = -1 );
  virtual ~J4VCALMiniCone();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw();
  virtual void	Print() const;

  virtual G4String GetFirstName    () const = 0;
  virtual G4int    GetNofMiniCones ()       = 0;
  virtual G4int    GetNofMiniTowers()       = 0;
  virtual G4String GetMaterial     ()       = 0;
  virtual G4bool   GetVisAtt       ()       = 0;
  virtual G4Color  GetColor        ()       = 0;

protected:
  virtual J4VCALMiniTower *Create( J4VDetectorComponent *parent    = 0,
                                                  G4int  nclones   = 1,
				                  G4int  nbrothers = 1, 
                                                  G4int  me        = 0,
                                                  G4int  copyno    = -1 ) = 0;

private:
  void 	Assemble();    
  void  Cabling ();
 
protected:
#ifdef __REPLICA__
  J4VCALMiniTower *fMiniTowers;
#else
  std::vector <J4VCALMiniTower *> fMiniTowers;
#endif
};
#endif
