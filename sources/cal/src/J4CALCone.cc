// $Id$
//*************************************************************************
//* --------------------
//* J4CALCone
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALCone.hh"
#include "J4CALTower.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CALCone::fFirstName("Cone");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALCone::J4CALCone(J4VDetectorComponent *parent,
                                        G4int  nclones,
                                        G4int  nbrothers, 
                                        G4int  me,
                                        G4int  copyno )
 : J4VCALDetectorComponent( fFirstName, parent, nclones,
                            nbrothers, me, copyno ), fTower(0) 
{   
   J4CALParameterList                  *list     = OpenParameterList();  	
   J4CALParameterList::J4CALTowerParam *curparam = list->GetTowerParam(me); 
   fIsBarrel = curparam->IsBarrel(); 
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALCone::~J4CALCone()
{
   if (Deregister(fTower)) delete fTower;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALCone::Assemble() 
{   
   if(!GetLV()){
 
      J4CALParameterList* ptrList = OpenParameterList();  	
      J4CALParameterList::J4CALTowerParam *curparam = ptrList->GetTowerParam(GetMyID());
      
      J4CALSubLayerParameterList* subList = ptrList->GetSubLayerParam();  	
      G4double EMThickness = (ptrList->GetEMNLayers()) * (subList->GetTotalLayerSize("EM"));
      G4double HDThickness = (ptrList->GetHDNLayers()) * (subList->GetTotalLayerSize("HD"));
      
      G4double rmin   = curparam->GetR();
      G4double rmax   = rmin + EMThickness + HDThickness; 
      G4double theta  = curparam->GetTheta();
      G4double dtheta = curparam->GetDtheta();
      G4int    nphi   = curparam->GetNphi();
      G4double dphi   = 360. *deg; 
      G4double sphi   = - 0.5 * dphi;
      G4double stheta = theta - 0.5 * dtheta;
  	
      // MakeSolid ----------//
      G4Sphere* cone = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
      Register(cone);
      SetSolid(cone);

      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(ptrList->GetConeMaterial()));
    
      // SetVisAttribute ----//
      PaintLV(ptrList->GetConeVisAtt(), ptrList->GetConeColor());
  	
      // Install daughter PV //
      fTower = new J4CALTower(this, nphi);  
      Register(fTower);
      fTower->InstallIn(this);
      SetDaughter(fTower);

   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALCone::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALCone::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  				// 
  
   // Placement function into mother object...
   SetPVPlacement();
  
}

//* Draw  --------------------------------------------------------
void J4CALCone::Draw()
{
   // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CALCone::Print() const
{
}
