// $Id$
#ifndef __J4CALBLOCK__
#define __J4CALBLOCK__
//*************************************************************************
//* --------------------
//* J4CALBlock
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

class J4CALBlock : public J4VCALDetectorComponent {	

public:
  J4CALBlock( const G4String&    firstname,
                   J4CALBlock*   ptrBlock,
          J4VDetectorComponent   *parent   = 0,
                          G4int  nclones   = 1,
                          G4int  nbrothers = 1, 
                          G4int  me        = 0,
                          G4int  copyno    = -1 );
  virtual ~J4CALBlock();

  virtual void	InstallIn( J4VComponent        *mother,
                           G4RotationMatrix    *prot  = 0,
                           const G4ThreeVector &tlate = 0 );
  virtual void	Draw(); 
  virtual void	Print() const ;

  inline const G4String&  GetFirstName()   { return fFirstName;  }  

protected:
  void 	Assemble();    
  void  Cabling ();
  
protected:  
  G4String      fFirstName;
  J4CALBlock*   fBlock;

};

#endif
