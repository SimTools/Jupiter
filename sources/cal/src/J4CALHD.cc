// $Id$
//*************************************************************************
//* --------------------
//* J4CALHD
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHD.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CALHD::fFirstName("HD");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHD::J4CALHD(J4VDetectorComponent *parent,
                                G4int  nclones,
                                G4int  nbrothers, 
                                G4int  me,
                                G4int  copyno ) :
         J4VCALDetectorComponent( fFirstName, parent, nclones,
                                  nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHD::~J4CALHD()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALHD::Assemble() 
{   
   if(!GetLV()){
 
      J4CALParameterList *list = OpenParameterList();

      G4Sphere *mothertower = (G4Sphere *)(GetMother()->GetSolid());

      G4double rmin   = mothertower->GetInsideRadius()
                        + list->GetEMThickness(); 
      G4double rmax   = rmin + list->GetHDThickness(); 
      G4double stheta = mothertower->GetStartThetaAngle();
      G4double dtheta = mothertower->GetDeltaThetaAngle();
      G4double sphi   = mothertower->GetStartPhiAngle();
      G4double dphi   = mothertower->GetDeltaPhiAngle();
  	
      // MakeSolid ----------//

      SetSolid(new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta));
    
      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(list->GetHDMaterial()));
    
      // SetVisAttribute ----//
      PaintLV(list->GetHDVisAtt(), list->GetHDColor());
  	
      // Install daughter PV //
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALHD::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALHD::InstallIn(J4VComponent         *mother,
                        G4RotationMatrix     *prot, 
                        const G4ThreeVector  &tlate ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  				// 
  
   // Placement function into mother object...

   SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4CALHD::Draw()
{
   // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CALHD::Print() const
{
}

	
	



