//
////////////////////////////////////////////////////////////////
//                                                            //
//  Title:  Physics List for a Linear Collider Detector       //
//  Date:   16 June 2004                                      //
//  Author: D.H. Wright (SLAC)                                //
//                                                            //
////////////////////////////////////////////////////////////////
//

#ifndef LCPhysicsList_h
#define LCPhysicsList_h 1

#include "G4VModularPhysicsList.hh"


class LCPhysicsList: public G4VModularPhysicsList
{
public:
  LCPhysicsList();
  virtual ~LCPhysicsList();
  
  virtual void SetCuts();
};

#endif



