// $Id$
#ifndef __J4OBJECT__
#define __J4OBJECT__
//*************************************************************************
//* -----------------------
//* J4Object
//* -----------------------
//* (Description)
//* 	Base class for all object .
//*     
//* (Update Record)
//*	2001/03/27  K.Hoshina	Original version.
//*************************************************************************

#include "TBookKeeper.hh"
#include "G4String.hh"

class J4VComponent;
//=====================================================================
//---------------------
// class definition
//---------------------

class J4Object 
{
friend class J4VComponent;

public:

  J4Object() {}
  virtual ~J4Object(){}

  inline virtual void Register(void * child) 
  {
     TBookKeeper::GetBookKeeper()->Register(this, child);
  } 

  inline virtual G4bool Deregister(void * child) 
  {
#ifdef __DEBUG__ 
     G4cerr << " J4Object::Deregister called for " << child 
            << " by " << fName << G4endl;
#endif
     if (child && TBookKeeper::GetBookKeeper()->GetParent(child) == this) {
        if (TBookKeeper::GetBookKeeper()->Deregister(child)) {
            return true;
        } else {
            G4cerr << " J4Object::Deregister of "
                 << fName 
                 << " failed to orphan the child ("
                 << child
                 << "). The child had already been orphaned !!" 
                 << G4endl;
        }
     } 
     return false;
  } 

private:

  G4String               fName;                   // full name

};

#endif


