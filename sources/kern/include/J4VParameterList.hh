// $Id$
#ifndef __J4VPARAMETERLIST__
#define __J4VPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4VParameterList.hh
//* ---------------------
//* (Description)
//* 	Abstract Parameter List Class.
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4Named.hh"

// ====================================================================
// ----------------
// class definition
// ----------------

 
class J4VParameterList : public J4Named
{
 
 public:

   J4VParameterList();
   J4VParameterList(const G4String &name);

   virtual ~J4VParameterList();  
   
   virtual void PrintParameterList() = 0;
  
   // getter
   
 private:
  
};

//=========================================================
//* inline functions


#endif
