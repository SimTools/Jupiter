// $Id$
//*************************************************************************
//* --------------------
//* J4VCALSubLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALSubLayer.hh"
#include "J4CALEMActiveLayer.hh"
#include "J4CALHDActiveLayer.hh"
#include "J4VCALSubLayerSD.hh"
#include "J4VCALLayer.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "G4UserLimits.hh"
#include "J4ParameterTable.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VCALSubLayer::J4VCALSubLayer( const G4String       &name,
                                J4VDetectorComponent *parent,
                                               G4int  nclones,
                                               G4int  nbrothers, 
                                               G4int  me,
                                               G4int  copyno )
: J4VCALDetectorComponent( name, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCALSubLayer::~J4VCALSubLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VCALSubLayer::Assemble() 
{   
 if(!GetLV()){
 
   G4Sphere* motherLayer = (G4Sphere *)(GetMother()->GetSolid());

   G4double stheta = motherLayer->GetStartThetaAngle();
   G4double dtheta = motherLayer->GetDeltaThetaAngle();
   G4double sphi   = motherLayer->GetStartPhiAngle();
   G4double dphi   = motherLayer->GetDeltaPhiAngle();
      
   G4double sthickness      = GetStartThickness();
   G4double ethickness      = GetEndThickness();
   G4double rstart          = motherLayer -> GetInsideRadius();
   G4double rmin            = rstart + sthickness;
   G4double rmax            = rmin + ethickness;

   // MakeSolid ----------//
   G4Sphere* sublayer = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
   Register( sublayer );
   SetSolid( sublayer );
      
   // MakeLogicalVolume --//  
   MakeLVWith( OpenMaterialStore()->Order( GetMaterial()));
     
   // SetVisAttribute ----//
   PaintLV( GetVisAtt(), GetColor() );
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VCALSubLayer::Cabling()
{
#if 0
  if( !GetSD() ) {
    J4VCALSubLayerSD* sd = CreateSD(this);
    Register(sd);
    SetSD(sd);
  }
#endif
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VCALSubLayer::InstallIn( J4VComponent*        /* mother */ ,
                                G4RotationMatrix*    /* prot   */ , 
                                const G4ThreeVector& /* tlate  */  ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   G4double ullen= J4ParameterTable::GetValue("J4CAL.UserLimits",0.1)*cm;
   G4UserLimits *myLimits = new G4UserLimits(ullen);
   G4double umaxtime= J4ParameterTable::GetValue("J4CAL.UserMaxTime",1000.0)*nanosecond;
   myLimits->SetUserMaxTime(umaxtime);
   GetLV()->SetUserLimits(myLimits);

   // Placement function into mother object...
   SetPVPlacement();

   // Cablig for SD
   Cabling();
}

//=====================================================================
//* Draw  --------------------------------------------------------
void J4VCALSubLayer::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4VCALSubLayer::Print() const
{ }
