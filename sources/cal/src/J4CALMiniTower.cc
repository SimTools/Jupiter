// $Id$
//*************************************************************************
//* --------------------
//* J4CALMiniTower
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALMiniTower.hh"
#include "J4CALLayer.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

//#define __NOLAYER__
#ifdef __NOLAYER__
#include "J4VSD.hh"
#include "J4CALHit.hh"
class J4CALMiniTowerSD : public J4VSD<J4CALHit> {
public:
  J4CALMiniTowerSD(J4VDetectorComponent *det) : J4VSD<J4CALHit>(det) {}

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
  {
     SetNewStep(aStep);
     J4CALMiniTower *cp = (J4CALMiniTower *)GetComponent(0);
     if (cp->IsEM()) {
        std::cerr << "MiniTower got an EM hit!----------" << std::endl;
     }
     return true;
  }
  virtual void   Initialize (G4HCofThisEvent* HCTE) {}
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE) {}

  virtual void   DrawAll () {}
  virtual void   PrintAll() {}
 
  virtual void   OutputAll(G4HCofThisEvent* HCTE) {}
};
#endif

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALMiniTower::fFirstName = "MiniTower";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALMiniTower::J4CALMiniTower(J4VDetectorComponent *parent,
                                             G4bool  isem,
                                              G4int  nclones,
                                              G4int  nbrothers, 
                                              G4int  me,
                                              G4int  copyno)
              : J4VCALDetectorComponent(fFirstName, isem, parent, nclones,
                                        nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALMiniTower::~J4CALMiniTower()
{
  G4int nLayers = fLayers.size();
  for (G4int i = 0; i < nLayers; i++) {
    if (Deregister(fLayers[i] )) delete fLayers[i];
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALMiniTower::Assemble() 
{   
   if (!GetLV()) {
 
      J4CALParameterList* ptrList = OpenParameterList();

      G4Sphere *mothercone = (G4Sphere *)( GetMother()->GetSolid() );

      G4double rmin   = mothercone -> GetInsideRadius();
      G4double rmax   = mothercone -> GetOuterRadius();

      G4double dtheta = mothercone -> GetDeltaThetaAngle();
      G4double stheta = mothercone -> GetStartThetaAngle();
     
      G4int nphi    = 0;
      G4int nLayers = 0;

      //  EM and HD tower divisions ----- //
      if (IsEM()) {
	nLayers = ptrList -> GetEMNLayers();
	nphi    = ptrList -> GetEMMiniTowerNClones();
      } else {
	nLayers = ptrList -> GetHDNLayers();
	nphi    = ptrList -> GetHDMiniTowerNClones();
      }

      G4double dphi = (mothercone -> GetDeltaPhiAngle()) / nphi;
#ifndef __REPLICA__
      G4int myID = GetMyID();
      G4double sphi   = mothercone -> GetStartPhiAngle() + myID * dphi;
#else
      //G4double sphi   = mothercone -> GetStartPhiAngle();
      G4double sphi   = -0.5 * dphi;
#endif

#if 0
      G4cerr << __FILE__ << " " << __LINE__ << " : "
	     << "rmin=" << rmin << " "
             << "rmax=" << rmax << " "
             << "nLayers=" << nLayers << " "
             << "nphi=" << nphi << " "
	     << "dphi=" << dphi << " "
	     << "type=" << (IsEM() ? "EM" : "HD")
             << G4endl;
#endif      
      
      // MakeSolid ----------//
      G4Sphere* minitower = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
      Register(minitower);
      SetSolid(minitower);
      
      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(ptrList->GetMiniTowerMaterial()));
      
      // SetVisAttribute ----//
      PaintLV(ptrList->GetMiniTowerVisAtt(), ptrList->GetMiniTowerColor());
      
#ifndef __NOLAYER__
      for (G4int i = 0; i < nLayers; i++) {
 	 J4CALLayer* ptrLayer = new J4CALLayer(this, IsEM(), 1, nLayers, i);
	 fLayers.push_back(ptrLayer);
	 Register(ptrLayer);
	 ptrLayer -> InstallIn(this);
	 SetDaughter(ptrLayer);
      }
#endif
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALMiniTower::Cabling()
{
#ifdef __NOLAYER__
   if (!GetSD()) {
      J4CALMiniTowerSD *sd = new J4CALMiniTowerSD(this);
      Register(sd);
      SetSD(sd);
   }
#endif
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALMiniTower::InstallIn( J4VComponent       *    mother,
                                G4RotationMatrix   * /* prot   */, 
                                const G4ThreeVector& /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   //===================================================================
   // Caution!!
   // If you use SetPVReplica(), then SD has some trouble !!
   //===================================================================
#ifdef __REPLICA__
   if (GetNclones() > 1) {
      G4double step = ((G4Sphere *)GetSolid())->GetDeltaPhiAngle();
#if 0
      SetPVReplica(kPhi, step);
#else
      G4double off  = ((G4Sphere *)mother->GetSolid())->GetStartPhiAngle() + 0.5*step;
      SetPVReplica(kPhi, step, off);
#endif
   } else {
      SetPVPlacement();
   }
#else
   SetPVPlacement();
#endif
#ifdef __NOLAYER__
   Cabling();
#endif
}


//* Draw  --------------------------------------------------------
void J4CALMiniTower::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALMiniTower::Print() const
{
}
