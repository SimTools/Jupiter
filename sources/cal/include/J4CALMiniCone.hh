// $Id$
#ifndef __J4CALMINICONE__
#define __J4CALMINICONE__
//*************************************************************************
//* --------------------
//* J4CALMiniCone
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALMiniTower;
class J4CALMiniCone : public J4VCALDetectorComponent {	

public:
  J4CALMiniCone(J4VDetectorComponent *parent  = 0,
                            G4bool isem       = true,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALMiniCone();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

//  inline virtual G4bool IsBarrel() const { return fIsBarrel; }
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static const G4String  fFirstName;
#ifndef __REPLICA__
  std::vector <J4CALMiniTower *> fMiniTowers;
#else
  J4CALMiniTower *fMiniTower;
#endif
  
};

#endif
