// $Id$
#ifndef __J4VCALBLOCK__
#define __J4VCALBLOCK__
//*************************************************************************
//* --------------------
//* J4VCALBlock
//* --------------------
//* (Description)
//* 	Base for CAL blocks like EM or HD.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2004/11/14  K.Fujii     Derived from J4CALEM by S.Ono
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4VCALMiniCone.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCALMiniCone;
class J4VCALBlock : public J4VCALDetectorComponent {
public:
  J4VCALBlock( const G4String       &name,
               J4VDetectorComponent *parent    =  0,
                              G4int  nclones   =  1,
                              G4int  nbrothers =  1, 
                              G4int  me        =  0,
                              G4int  copyno    = -1);
  virtual ~J4VCALBlock();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot   = 0,
                          const G4ThreeVector  &tlate  = G4ThreeVector(0.));

  virtual void	Draw();
  virtual void	Print() const;

  virtual G4String GetFirstName   () const = 0;
  virtual G4int    GetNofMiniCones()       = 0;
  virtual G4double GetInsideRadius()       = 0;
  virtual G4double GetThickness   ()       = 0;
  virtual G4String GetMaterial    ()       = 0;
  virtual G4bool   GetVisAtt      ()       = 0;
  virtual G4Color  GetColor       ()       = 0;

protected:
  virtual J4VCALMiniCone *Create( J4VDetectorComponent *parent    = 0,
                                                 G4int  nclones   = 1,
				                 G4int  nbrothers = 1, 
                                                 G4int  me        = 0,
                                                 G4int  copyno    = -1 ) = 0;

private:
  void 	Assemble();    
  void  Cabling();

protected:
  std::vector<J4VCALMiniCone *>  fMiniCones;
  
};

#endif
