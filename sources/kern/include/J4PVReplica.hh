// $Id$
#ifndef __J4PVREPLICA__
#define __J4PVREPLICA__
//*************************************************************************
//* --------------------
//* J4PVReplica
//* --------------------
//*     
//* (Update Record)
//*	2002/09/03  R.Kuboshima    Original Ver.
//*************************************************************************

#include "G4PVReplica.hh"
#include "J4AttPV.hh"
#include "J4Global.hh"

class J4VComponent;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4PVReplica : public G4PVReplica, public J4AttPV 
{
public:

  //====== constructor
   J4PVReplica(J4VComponent     *component,
	       const G4String   &pName,
               G4LogicalVolume  *pLogical,
               G4LogicalVolume  *pMother,
               const EAxis       pAxis,
               const G4int       nReplicas,
               const G4double    width,
               const G4double    offset=0)
	  : G4PVReplica(pName, pLogical, pMother, pAxis,
			 nReplicas , width, offset),
            J4AttPV(component)
            {} 

   virtual ~J4PVReplica()
   {
#ifdef __THEBE__
      J4cerr << "J4PVReplica:destructor is called for " << GetName() << J4endl; 
#endif
   }
     
private:
  //===== data members

};


#endif


