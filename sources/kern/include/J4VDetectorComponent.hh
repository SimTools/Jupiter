// $Id$
#ifndef __J4VDETECTORCOMPONENT__
#define __J4VDETECTORCOMPONENT__
//*************************************************************************
//* --------------------
//* J4VDetectorComponent
//* --------------------
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/05/15  K.Hoshina	Almost all functions and datamembers are
//*                             moved into J4Component class and this class 
//*                             inherits from J4Component. 
//*************************************************************************

//_________________________________________________________________________
//
// Class description 
//
// This class is the abstract base class for all detectors.
// Use this class by inheriting from it and overriding the
// members, Assemble() and InstallIn(), etc.
//------------------------------------------------------------------------


#include "J4VComponent.hh"

//for OrderSolid
#include "G4Tubs.hh"
#include "J4TypeDef.hh"

class J4VComponent;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VDetectorComponent : public J4VComponent
{

public:

  //====== constructor
  J4VDetectorComponent(const G4String       &groupname,
                       const G4String       &name, 
                       J4VComponent         *parent    = 0,
                       G4int                 nclones   = 1,
                       G4int                 nbrothers = 1, 
                       G4int                 me        = 0,
                       G4int                 copyno    = -1);

  J4VDetectorComponent(const G4String       &groupname,
                       const G4String       &name, 
                       J4VDetectorComponent *parent    = 0,
                       G4int                 nclones   = 1,
                       G4int                 nbrothers = 1, 
                       G4int                 me        = 0,
                       G4int                 copyno    = -1);

  //===== copy constructor
     // If you want some copied objects, you should use this constructor
     // in order to save memoly. This constructor copies fLV pointer 
     // from original object, then original one and copied objects share
     // same LogicalVolume object. 
  inline J4VDetectorComponent(const J4VComponent &orig, G4int copyno);
  inline J4VDetectorComponent(const J4VDetectorComponent &orig, G4int copyno);
  			
  //===== destructor
  virtual ~J4VDetectorComponent();

  //===== operators
  inline const J4VDetectorComponent &operator=(const J4VDetectorComponent &right);    

  //----- user tools
  static J4VDetectorComponent *GetDCPtrByName(const G4String& name);              

};

//=====================================================================
//---------------------
// inline function
//---------------------

J4VDetectorComponent::J4VDetectorComponent(const J4VComponent& orig, G4int copyno)
                     :J4VComponent(orig, copyno) 
{
}

J4VDetectorComponent::J4VDetectorComponent(const J4VDetectorComponent& orig, G4int copyno)
                     :J4VComponent(orig, copyno) 
{
}

const J4VDetectorComponent& 
J4VDetectorComponent::operator= (const J4VDetectorComponent& right)
{
  this->J4VComponent::operator=(right);
  return *this;
}


#endif


