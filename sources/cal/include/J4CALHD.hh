// $Id$
#ifndef __J4CALHD__
#define __J4CALHD__
//*************************************************************************
//* --------------------
//* J4CALHD
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
class J4CALMiniCone;

//=====================================================================
//---------------------
// class definition
//---------------------

//class J4CALHD : public J4VCALDetectorComponent {	
class J4CALHD : public J4CALBlock
{

public:
  J4CALHD(J4VDetectorComponent *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALHD();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

//  inline G4int      GetNsectionsInPhi();
//  inline G4int      GetNsectionsInTheta();   

//  static G4String   GetFirstName() { return fFirstName; }  

//private:
  void 	Assemble();    
//  void  Cabling ();
  
private:  
 //static G4String   fFirstName;
 static G4String     firstName;

  // For input array
  std::vector<J4CALMiniCone *>  fMiniCones;
};


// =====================================================
// inline finctions ------------------------------------
//G4int J4CALHD::GetNsectionsInPhi()
//{
   // mother component : Tower
//   return GetMother()->GetNclones();
//}

//G4int J4CALHD::GetNsectionsInTheta()
//{
   // grand mother component : Cone 
 //  return GetMother()->GetMother()->GetNbrothers();
//}
#endif
