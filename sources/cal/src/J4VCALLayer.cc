// $Id$
//*************************************************************************
//* --------------------
//* J4VCALLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2004/10/07  H.Ono       Parametrized
//*************************************************************************

#include "J4VCALMiniTower.hh"
#include "J4VCALLayer.hh"
#include "J4CALEMLayer.hh"
#include "J4CALHDLayer.hh"
#include "J4VCALSubLayer.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

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

J4VCALLayer::J4VCALLayer( const G4String       &name,
                          J4VDetectorComponent *parent,
                                         G4int  nclones,
                                         G4int  nbrothers, 
                                         G4int  me,
                                         G4int  copyno )
: J4VCALDetectorComponent( name, parent, nclones, nbrothers, me, copyno ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------

J4VCALLayer::~J4VCALLayer()
{
#if 0
  if ( Deregister(fAbsLayer) ) delete fAbsLayer;
  if ( Deregister(fActiveLayer) ) delete fActiveLayer;
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VCALLayer::Assemble() 
{   
   if ( !GetLV() ) {
 
     G4Sphere *motherTower = (G4Sphere *)( GetMother()->GetSolid() );

     G4double stheta = motherTower->GetStartThetaAngle();
     G4double dtheta = motherTower->GetDeltaThetaAngle();
     G4double sphi   = motherTower->GetStartPhiAngle();
     G4double dphi   = motherTower->GetDeltaPhiAngle();
     G4double rstart = motherTower->GetInsideRadius();

     G4int myID         = GetMyID();
     G4double thickness = GetLayerThickness();
     G4double rmin      = rstart + myID * thickness;
     G4double rmax      = rmin + thickness;

     // MakeSolid ----------//
     G4Sphere* layer = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
     Register( layer );
     SetSolid( layer );

     // MakeLogicalVolume --//  
     MakeLVWith( OpenMaterialStore()->Order(GetMaterial()) );
   
     // SetVisAttribute ----//
     PaintLV( GetVisAtt(), GetColor() );

     // Make AbsLayer and ActiveLayer objects --- //
     fAbsLayer = CreateAbs( this );
     Register( fAbsLayer );
     fAbsLayer -> InstallIn( this );
     SetDaughter( fAbsLayer );

     fActiveLayer = CreateActive( this );
     Register( fActiveLayer );
     fActiveLayer -> InstallIn( this );
     SetDaughter( fActiveLayer );
  }
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VCALLayer::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VCALLayer::InstallIn(J4VComponent*         /* mother */,
                            G4RotationMatrix*    /* prot   */, 
                            const G4ThreeVector& /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.

   // Placement function into mother object...
   SetPVPlacement();

   // Cabling function for SD object... 
   //Cabling(); 
}


//* Draw  --------------------------------------------------------
void J4VCALLayer::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4VCALLayer::Print() const
{
}
