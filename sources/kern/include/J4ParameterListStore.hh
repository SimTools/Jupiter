// $Id$
#ifndef __J4VPARAMETERLISTSTORE__
#define __J4VPARAMETERLISTSTORE__
//********************************************************************
//* ---------------------
//* J4ParameterListStore.hh
//* ---------------------
//* (Description)
//* 	Management class for ParameterLists.
//* 	The instance of this class must be a singleton. 
//*     Use the static method
//*     J4ParameterListStore::GetInstance()
//*     to access this instance. 
//*     
//* (Update Record)
//*	2000/12/20  K.Hoshina	Original version.
//********************************************************************

#include "J4TypeDef.hh"

// ====================================================================
// ----------------
// class definition
// ----------------

 
class J4ParameterListStore
{
 
 public:

   J4ParameterListStore();

   virtual ~J4ParameterListStore();  
   
   virtual void PrintAllParameters();
  
   // getter

   inline static J4ParameterListStore  *GetInstance()
                                        { return fgParameterListStore; }
   inline static J4ObjArray             GetParameterLists()  
                                        { return fgParameterLists; }

 private:

   static J4ParameterListStore *fgParameterListStore;  
   static J4ObjArray            fgParameterLists;  
  
};

//=========================================================
//* inline functions

#endif
