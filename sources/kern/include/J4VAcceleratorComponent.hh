// $Id$
#ifndef __J4VACCELERATORCOMPONENT__
#define __J4VACCELERATORCOMPONENT__
//*************************************************************************
//* --------------------
//* J4VAcceleratorComponent
//* --------------------
//*     
//* (Update Record)
//*	2002/04/28  K.Hoshina	Original version.
//*	2002/05/15  K.Hoshina	Mother class changed from J4VDetectorComponent
//*	                        to J4Component.
//*************************************************************************

//_________________________________________________________________________
//
// Class description
//
// This class is the abstract base class for all accelerator components.
// Use this class by inheriting from it and overriding the
// members, Assemble() and InstallIn(), etc.
//------------------------------------------------------------------------

#include "J4VComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VAcceleratorComponent : public J4VComponent 
{

public:

  //----- constructor
  J4VAcceleratorComponent(const G4String          &groupname,
                          const G4String          &name, 
                          J4VAcceleratorComponent *parent    = 0,
                          G4int                    nclones   = 1,
                          G4int                    nbrothers = 1, 
                          G4int                    me        = 0,
                          G4int                    copyno    = -1);

  inline J4VAcceleratorComponent(J4VAcceleratorComponent &orig, G4int copyno);
  			
  //----- destructor
  virtual ~J4VAcceleratorComponent();

  //----- operators
  inline const J4VAcceleratorComponent &operator=(const J4VAcceleratorComponent &right);    

  //----- user tools
  					     
};


//=====================================================================
//---------------------
// inline function
//---------------------

J4VAcceleratorComponent::J4VAcceleratorComponent(J4VAcceleratorComponent& orig, G4int copyno)
                        :J4VComponent(orig,copyno) 
{
}

const J4VAcceleratorComponent& 
J4VAcceleratorComponent::operator= (const J4VAcceleratorComponent& right)
{
  this->J4VComponent::operator=(right); 
  return *this; 
}

#endif


