// $Id$
#ifndef __J4VCALDETECTORCOMPONENT__
#define __J4VCALDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VCALDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALMaterialStore.hh"
#include "J4CALParameterList.hh"
#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCALDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VCALDetectorComponent( const G4String       &name, 
  			   J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  J4VCALDetectorComponent( const G4String       &name, 
                           G4bool                isem      = true,
  			   J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  virtual ~J4VCALDetectorComponent();

#if 0
  J4VCALDetectorComponent(J4VCALDetectorComponent& right);

  virtual const J4VCALDetectorComponent& 
  		operator=(const J4VCALDetectorComponent& right);    
#endif
  G4bool IsEM ()            const { return fIsEM; }

protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4CALParameterList* 	 OpenParameterList() { return J4CALParameterList::GetInstance(); }

  void   SetEM(G4bool val = true) { fIsEM = val; }
  
private:
  G4bool fIsEM;
  static J4CALMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

#if 0
//=====================================================================
//---------------------
// inline function
//---------------------


inline J4VCALDetectorComponent::J4VCALDetectorComponent(J4VCALDetectorComponent& right)
 :J4VDetectorComponent(right)
{

}

inline const J4VCALDetectorComponent& 
J4VCALDetectorComponent::operator=(const J4VCALDetectorComponent& right)
{
  J4VDetectorComponent::operator=(right);
  return *this;
}

#endif

#endif
