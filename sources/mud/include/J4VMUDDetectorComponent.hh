// $Id$
#ifndef __J4VMUDDETECTORCOMPONENT__
#define __J4VMUDDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VMUDDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2003/08/13  Akiya Miyamoto	Original version.(copied from J4IT.....)
//*************************************************************************
#include "J4MUDMaterialStore.hh"
#include "J4MUDParameterList.hh"
#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VMUDDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VMUDDetectorComponent( const G4String&       name, 
  			   J4VDetectorComponent* parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );
  // J4VMUDDetectorComponent( J4VMUDDetectorComponent& right );
  //  virtual const J4VMUDDetectorComponent& 
  //  		operator=(const J4VMUDDetectorComponent& right);    
  virtual ~J4VMUDDetectorComponent();
      
protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4MUDParameterList* 	 OpenParameterList() { return J4MUDParameterList::GetInstance(); }
  
private:
  static J4MUDMaterialStore* fMaterialStore;
  static G4String fSubGroup;
};

//=====================================================================
//---------------------
// inline function
//---------------------
//inline J4VMUDDetectorComponent::J4VMUDDetectorComponent( J4VMUDDetectorComponent& right )
//: J4VDetectorComponent( right )
//{ }

//inline const J4VMUDDetectorComponent& 
//J4VMUDDetectorComponent::operator=(const J4VMUDDetectorComponent& right)
//{
//  return *this;
//}

#endif
