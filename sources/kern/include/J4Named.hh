// $Id$
#ifndef __J4NAMED__
#define __J4NAMED__
//*************************************************************************
//* -----------------------
//* J4Named
//* -----------------------
//* (Description)
//* 	Base class for all named object .
//*     
//* (Update Record)
//*	2002/12/20  K.Hoshina	Original version.
//*************************************************************************

#include "G4String.hh"
#include "J4Object.hh"
#include "J4Global.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4Named : public J4Object 
{

public:

  J4Named();
  J4Named(const G4String &name);

  virtual ~J4Named()
  {
#ifdef __THEBE__
     J4cerr << "J4Named::destructor called for " << fName << J4endl;
#endif
  }

  inline virtual const G4String &GetName() const { return fName; }

  inline virtual void  SetName(const G4String &n) { fName = n ; }

private:

  G4String  fName;  

};

//=====================================================================
//---------------------
// inline function for J4Named
//---------------------

#endif

