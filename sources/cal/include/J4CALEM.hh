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
#include "J4CALHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALEM : public J4VCALDetectorComponent {	

public:
  J4CALEM(J4VDetectorComponent *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALEM();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  inline G4int      GetNsectionsInPhi();
  inline G4int      GetNsectionsInTheta();   

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String   fFirstName;
  
};

#endif

// =====================================================
// inline finctions ------------------------------------
G4int J4CALEM::GetNsectionsInPhi()
{
   // mother component : Tower
   return GetMother()->GetNclones();
}

G4int J4CALEM::GetNsectionsInTheta()
{
   // grand mother component : Cone 
   return GetMother()->GetMother()->GetNbrothers();
}


