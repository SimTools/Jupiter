// $Id$
#ifndef __J4VIRDETECTORCOMPONENT__
#define __J4VIRDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VIRDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4IRMaterialStore.hh"
#include "J4IRParameterList.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VIRDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VIRDetectorComponent( const G4String       &name, 
  			   J4VComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1,
			     G4bool  reflection=FALSE);

  J4VIRDetectorComponent( const J4VIRDetectorComponent &orig, 
                                        G4int                    copyno);

  virtual ~J4VIRDetectorComponent();
  virtual void  InstallIn(J4VComponent *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );

  virtual G4RotationMatrix* GetRotation();
  virtual G4ThreeVector&  GetTranslation();

protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4IRParameterList*     OpenParameterList() { return J4IRParameterList::GetInstance(); }
  
private:
  static J4IRMaterialStore* fMaterialStore;
  static G4String fSubGroup;
  static J4IRParameterList*  fParameterList;
  G4bool fReflection   ;

private:
  virtual void Assemble()=0;
  virtual void Cabling()=0;

};

#endif



