// $Id$
#ifndef __J4CALEM__
#define __J4CALEM__
//*************************************************************************
//* --------------------
//* J4CALEM
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALBlock.hh"
#include "J4CALHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALMiniCone;
class J4CALEM : public J4CALBlock
{

public:
  J4CALEM( J4VDetectorComponent *parent   = 0,
                         G4int  nclones   = 1,
                         G4int  nbrothers = 1, 
                         G4int  me        = 0,
                         G4int  copyno    = -1 );
  virtual ~J4CALEM();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot   = 0,
                           const G4ThreeVector  &tlate  = 0 );
  virtual void	Draw();
  virtual void	Print() const ;

  void 	Assemble();    
  
private:  
  static const G4String&    firstName;
  std::vector<J4CALMiniCone *>  fMiniCones;
};

#endif
