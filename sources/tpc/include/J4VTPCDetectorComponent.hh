#ifndef __J4VTPCDETECTORCOMPONENT__
#define __J4VTPCDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VTPCDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4TPCMaterialStore.hh"
#include "J4TPCParameterList.hh"
#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTPCDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VTPCDetectorComponent(const G4String       &name, 
                          J4VDetectorComponent *parent    = 0,
                          G4int                 nclones   = 1,
                          G4int                 nbrothers = 1, 
                          G4int                 me        = 0,
                          G4int                 copyno    = -1 );
  J4VTPCDetectorComponent(const J4VTPCDetectorComponent &orig,
                                                  G4int  copyno);
#if 0
  J4VTPCDetectorComponent(J4VTPCDetectorComponent& right);
  virtual const J4VTPCDetectorComponent& 
  		operator=(const J4VTPCDetectorComponent& right);    
#endif

  virtual ~J4VTPCDetectorComponent();
      
protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4TPCParameterList* 	 OpenParameterList() { return J4TPCParameterList::GetInstance(); }
  
private:
  static J4TPCMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

//=====================================================================
//---------------------
// inline function
//---------------------


#if 0
inline J4VTPCDetectorComponent::J4VTPCDetectorComponent(J4VTPCDetectorComponent& right)
                              : J4VDetectorComponent(right)
{
          
}

inline const J4VTPCDetectorComponent& 
J4VTPCDetectorComponent::operator=(const J4VTPCDetectorComponent& right)
{
  return *this;
}
#endif


#endif


