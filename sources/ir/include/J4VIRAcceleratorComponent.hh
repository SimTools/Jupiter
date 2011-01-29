// $Id$
#ifndef __J4VIRACCELERATORCOMPONENT__
#define __J4VIRACCELERATORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VIRAcceleratorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRMaterialStore.hh"
#include "J4VAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VIRAcceleratorComponent : public J4VAcceleratorComponent
{	// abstruct class

public:
  //default constructor...
  // (nclones)      number of replication in one component.
  // (nbrothers)    number of same kind of objects with this one.
  J4VIRAcceleratorComponent( const G4String       &name, 
  			  J4VComponent *parent    = 0,
			     G4int                 nclones   = 1,  
                          G4int                 nbrothers = 1, 
                          G4int                 me        = 0,
                          G4int                 copyno    = -1 ,
			     G4bool  reflection=FALSE);

  virtual ~J4VIRAcceleratorComponent();
  virtual void  InstallIn(J4VComponent *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );

  virtual G4RotationMatrix* GetRotation();
  virtual G4ThreeVector&  GetTranslation();
  inline  G4bool  IsReflected(){ return fReflection; }

protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  
private:
  static J4IRMaterialStore* fMaterialStore;
  static G4String fSubGroup;
  G4bool fReflection   ;

private:
  void Assemble()=0;
};

#endif


