// $Id$
#ifndef __J4PHYSICSLIST__
#define __J4PHYSICSLIST__

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class J4PhysicsList: public G4VUserPhysicsList
{
public:
  J4PhysicsList();
  virtual ~J4PhysicsList();
  
protected:
  // Construct particle and physics
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  
  // 
  virtual void SetCuts();
  
protected:
  // these methods Construct physics processes and register them
  virtual void ConstructGeneral();
  virtual void ConstructEM();
  virtual void ConstructHad();

  // these methods Construct all particles in each category
  virtual void ConstructAllBosons();
  virtual void ConstructAllLeptons();
  virtual void ConstructAllMesons();
  virtual void ConstructAllBaryons();
  virtual void ConstructAllIons();
  virtual void ConstructAllShortLiveds();
};

#endif



