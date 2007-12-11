//
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Title:  Lepton physics for a Linear Collider Detector                  //
//  Date:   17 June 2004                                                   //
//  Author: D.H. Wright (SLAC)                                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
//

#ifndef LCLeptonPhysics_h
#define LCLeptonPhysics_h 1

#include "G4VPhysicsConstructor.hh"


class LCLeptonPhysics : public G4VPhysicsConstructor
{
  public: 
    LCLeptonPhysics(const G4String& name ="lepton");
    virtual ~LCLeptonPhysics();

    // This method will be invoked in the Construct() method. 
    // each particle type will be instantiated
    virtual void ConstructParticle();
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    virtual void ConstructProcess();

};

#endif





