// $Id$
#ifndef __J4ATTPV__
#define __J4ATTPV__
//*************************************************************************
//* --------------------
//* J4AttPV
//* --------------------
//*     
//* (Update Record)
//*	2002/09/03  R.Kuboshima    Original Ver.
//*************************************************************************

class J4VComponent;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4AttPV 
{
public:

  //====== constructor
  J4AttPV(J4VComponent *component)
            :fComponent(component) 
  {
  } 

  virtual ~J4AttPV() {}

  inline virtual J4VComponent *GetComponent() const { return fComponent; } 
     
private:
  //===== data members
  J4VComponent   *fComponent;             // pointer to J4VComponent

};


#endif


