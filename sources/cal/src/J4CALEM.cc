// $Id$
//*************************************************************************
//* --------------------
//* J4CALEM
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEM.hh"
#include "J4CALEMSD.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CALEM::fFirstName("EM");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEM::J4CALEM(J4VDetectorComponent *parent,
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

J4CALEM::~J4CALEM()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALEM::Assemble() 
{   
   if(!GetLV()){
 
      J4CALParameterList *list = OpenParameterList();

      G4Sphere *mothertower = (G4Sphere *)(GetMother()->GetSolid());

      G4double rmin   = mothertower->GetInsideRadius();
      G4double rmax   = rmin + list->GetEMThickness(); 
      G4double stheta = mothertower->GetStartThetaAngle();
      G4double dtheta = mothertower->GetDeltaThetaAngle();
      G4double sphi   = mothertower->GetStartPhiAngle();
      G4double dphi   = mothertower->GetDeltaPhiAngle();
  	
      // MakeSolid ----------//

      SetSolid(new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta));
    
      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(list->GetEMMaterial()));
    
      // SetVisAttribute ----//
      PaintLV(list->GetEMVisAtt(), list->GetEMColor());

      // Install daughter PV //
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALEM::Cabling()
{
   if (!GetSD()) {
      J4CALEMSD* sd = new J4CALEMSD(this);
      Register(sd);
      SetSD(sd);
   }
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALEM::InstallIn(J4VComponent         *mother,
                        G4RotationMatrix     *prot, 
                        const G4ThreeVector  &tlate ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  				// 
  
   // Placement function into mother object...

   SetPVPlacement();
   
   Cabling(); 
  
}


//* Draw  --------------------------------------------------------
void J4CALEM::Draw()
{
   // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CALEM::Print() const
{
}

	
	



