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


// ====================================================================
// ----------------
// class definition
// ----------------
 
class J4VParameterList
{
 
 public:
   J4VParameterList() {};   
   virtual ~J4VParameterList(){};  
   
   virtual void PrintParameterList(){};
   
   virtual void PrintAllParameters(){};
  
   //
   // get parameters
   //
   
  
 private:
  
};

//=========================================================
//* inline functions


#endif
