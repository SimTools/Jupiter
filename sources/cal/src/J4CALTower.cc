// $Id$
//*************************************************************************
//* --------------------
//* J4CALTower
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALTower.hh"
#include "J4CALEM.hh"
#include "J4CALHD.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

//#define __DRAWONETOWER__

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALTower::fFirstName = "Tower";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALTower::J4CALTower(J4VDetectorComponent *parent,
                                      G4int  nclones,
                                      G4int  nbrothers, 
                                      G4int  me,
                                      G4int  copyno ) 
          : J4VCALDetectorComponent(fFirstName, parent, nclones,
                                          nbrothers, me, copyno) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALTower::~J4CALTower()
{
   if (Deregister(fEMcal)) delete fEMcal;
   if (Deregister(fHDcal)) delete fHDcal;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALTower::Assemble() 
{   
   if (!GetLV()) {

      J4CALParameterList *ptrList = OpenParameterList();

      G4Sphere *mothercone = (G4Sphere *)(GetMother()->GetSolid());

      static const G4double EMThickness = ptrList->GetEMThickness();
      static const G4double HDThickness = ptrList->GetHDThickness();
      
      G4double rmin   = mothercone->GetInsideRadius();
      G4double rmax   = rmin + EMThickness + HDThickness; 
      G4double stheta = mothercone->GetStartThetaAngle();
      G4double dtheta = mothercone->GetDeltaThetaAngle();
      G4double dphi   = 2 * M_PI / GetNclones();
      G4double sphi   = - 0.5 * dphi;
  	
      // MakeSolid ----------//
      G4Sphere* tower = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
      Register(tower);
      SetSolid(tower);
    
      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(ptrList->GetTowerMaterial()));
    
      // SetVisAttribute ----//
      PaintLV(ptrList->GetTowerVisAtt(), ptrList->GetTowerColor());

      // Install daughter PV //

      fEMcal = new J4CALEM(this);  
      Register(fEMcal);
      fEMcal->InstallIn(this);
      SetDaughter(fEMcal);
      
      fHDcal = new J4CALHD(this);  
      Register(fHDcal);
      fHDcal->InstallIn(this);
      SetDaughter(fHDcal);
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALTower::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALTower::InstallIn(J4VComponent*         /* mother */,
                           G4RotationMatrix*     /* prot   */, 
                           const G4ThreeVector&  /* tlate  */ ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   
#ifdef __DRAWONETOWER__
   SetPVPlacement();
#else
   G4double step = ((G4Sphere *)GetSolid())->GetDeltaPhiAngle();
   SetPVReplica(kPhi, step);
#endif
}

//* Draw  --------------------------------------------------------
void J4CALTower::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALTower::Print() const
{
}
