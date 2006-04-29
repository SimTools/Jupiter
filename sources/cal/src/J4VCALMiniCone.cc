// $Id$
//*************************************************************************
//* --------------------
//* J4VCALMiniCone
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALMiniCone.hh"
#include "J4CALEMMiniTower.hh"
#include "J4CALHDMiniTower.hh"
#include "J4VCALMiniTower.hh"
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

J4VCALMiniCone::J4VCALMiniCone( const G4String       &name,
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

J4VCALMiniCone::~J4VCALMiniCone()
{
#ifdef __REPLICA__
  if (fMiniTowers && Deregister(fMiniTowers)) delete fMiniTowers;
#else
  G4int nMiniTowers = fMiniTowers.size();
  for (G4int i = 0; i < nMiniTowers; i++) {
    if (fMiniTowers[i] && Deregister(fMiniTowers[i])) delete fMiniTowers[i];
  }
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VCALMiniCone::Assemble() 
{   
  if ( !GetLV() ) {

    G4Sphere* mother = (G4Sphere *)( GetMother()->GetSolid() );

    G4double rmin   = mother->GetInsideRadius();
    G4double rmax   = mother->GetOuterRadius();
    G4int nphi      = GetNofMiniCones();
    G4int ntheta    = GetNofMiniTowers();
    G4int myID      = GetMyID();
    G4double sphi   = mother->GetStartPhiAngle();
    G4double dphi   = mother->GetDeltaPhiAngle();
    G4double dtheta = ( mother->GetDeltaThetaAngle() ) / ntheta;
    G4double stheta = ( mother->GetStartThetaAngle() ) + myID * dtheta;

    // MakeSolid ----------//
    G4Sphere* minicone = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
    Register( minicone );
    SetSolid( minicone );

    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial()) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );
  	
    // Install daughter PV //
#ifdef __REPLICA__ 
    J4VCALMiniTower* fMiniTowers = Create( this, nphi );
    Register( fMiniTowers );
    fMiniTowers -> InstallIn( this );
    SetDaughter( fMiniTowers );
#else
    for ( G4int i = 0; i < nphi; i++ ) {
      J4VCALMiniTower* minitower = Create( this, 1, nphi, i );
      fMiniTowers.push_back( minitower );
      Register( minitower );
      minitower -> InstallIn( this );
      SetDaughter( minitower );
    }
#endif
  }
}



//=====================================================================
//* Cabling  ----------------------------------------------------------
 void J4VCALMiniCone::Cabling()
 {
 }

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VCALMiniCone::InstallIn( J4VComponent*        /* mother */,
                               G4RotationMatrix*    /* prot   */, 
                               const G4ThreeVector& /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.

   G4UserLimits *myLimits = new G4UserLimits();
   G4double umaxtime= J4ParameterTable::GetValue("J4CAL.UserMaxTime",1000.0)*nanosecond;
   myLimits->SetUserMaxTime(umaxtime);
   GetLV()->SetUserLimits(myLimits);

   //* placement --------
   SetPVPlacement();
}


//* Draw  --------------------------------------------------------
void J4VCALMiniCone::Draw()
{
   // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VCALMiniCone::Print() const
{
}
