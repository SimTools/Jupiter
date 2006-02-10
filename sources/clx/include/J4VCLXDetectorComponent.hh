// $Id$
#ifndef __J4VCLXDETECTORCOMPONENT__
#define __J4VCLXDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VCLXDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CLXMaterialStore.hh"
#include "J4CLXParameterList.hh"
#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VCLXDetectorComponent( const G4String       &name, 
  			   J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  virtual ~J4VCLXDetectorComponent();

#if 0
  J4VCLXDetectorComponent(J4VCLXDetectorComponent& right);

  virtual const J4VCLXDetectorComponent& 
  		operator=(const J4VCLXDetectorComponent& right);    
#endif

protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4CLXParameterList* 	 OpenParameterList() { return J4CLXParameterList::GetInstance(); }

private:
  static J4CLXMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

#if 0
//=====================================================================
//---------------------
// inline function
//---------------------


inline J4VCLXDetectorComponent::J4VCLXDetectorComponent(J4VCLXDetectorComponent& right)
 :J4VDetectorComponent(right)
{

}

inline const J4VCLXDetectorComponent& 
J4VCLXDetectorComponent::operator=(const J4VCLXDetectorComponent& right)
{
  J4VDetectorComponent::operator=(right);
  return *this;
}

#endif

#endif
