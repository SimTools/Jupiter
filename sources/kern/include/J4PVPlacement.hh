// $Id$
#ifndef __J4PVPLACEMENT__
#define __J4PVPLACEMENT__
//*************************************************************************
//* --------------------
//* J4PVPlacement
//* --------------------
//*     
//* (Update Record)
//*	2002/09/03  R.Kuboshima    Original Ver.
//*************************************************************************

#include "G4PVPlacement.hh"
#include "J4AttPV.hh"

class J4VComponent;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4PVPlacement : public G4PVPlacement , public J4AttPV 
{
public:

  //====== constructor
  J4PVPlacement(J4VComponent        *component,
		G4RotationMatrix    *pRot,
                const G4ThreeVector &tlate,
                G4LogicalVolume     *pCurrentLogical,
                const G4String      &pName,
                G4LogicalVolume     *pMotherLogical,
                G4bool               pMany,
                G4int                pCopyNo)
          :G4PVPlacement(pRot, tlate, pCurrentLogical, pName,
			  pMotherLogical, pMany, pCopyNo), 
           J4AttPV(component)
  {
  } 

private:
  //===== data members

};


#endif


