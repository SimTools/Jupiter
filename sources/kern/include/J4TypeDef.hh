// $Id$
#ifndef __J4TYPEDEF__
#define __J4TYPEDEF__
//*************************************************************************
//* -----------------------
//* TypeDef
//* -----------------------
//* (Description)
//* 
//*     
//* (Update Record)
//*	2001/03/27  K.Hoshina	Original version.
//*************************************************************************

#include "tpordvec.h"

class J4Object;
class J4VComponent;
//=====================================================================
//---------------------
// definition
//---------------------

  typedef G4RWTPtrOrderedVector<J4Object> J4ObjArray;
  typedef G4RWTPtrOrderedVector<J4VComponent> J4ComponentArray; 



  enum EPlacementType { kReplicated,   // placed by G4PVReplica
                        kCopied,       // copied volume placed by G4PVPlacement
                        kSingle     }; // single volume placed by G4PVPlacement


  enum EPrimaryGeneratorType { kHEPEvt,        // use HEPEvt Generator
                               kCAINEvt,       // use CAINEvt Generator 
                               kParticleGun,   // use Particle Gun 
                               kParticleBeam };// use Particle Beam 

#endif

