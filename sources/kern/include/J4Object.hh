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

//=====================================================================
//---------------------
// class definition
//---------------------

class J4Object 
{

public:

  J4Object() {}

  virtual ~J4Object(){}

  inline virtual void Register(void * child);

  virtual G4bool Deregister(void * child);

private:

};

//=====================================================================
//---------------------
// inline function for J4Object
//---------------------
void J4Object::Register(void * child)
{
   TBookKeeper::GetBookKeeper()->Register(this, child);
} 

#endif


