// $Id$
//*************************************************************************
//* --------------------
//* J4CALMiniCone
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALMiniCone.hh"
#include "J4CALMiniTower.hh"
#include "J4CALBlock.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String& J4CALMiniCone::fFirstName( "MiniCone" );

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALMiniCone::J4CALMiniCone( J4VDetectorComponent *parent,
                                             G4int  nclones,
                                             G4int  nbrothers, 
                                             G4int  me,
                                             G4int  copyno )
: J4VCALDetectorComponent( fFirstName, parent, nclones,
                                 nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALMiniCone::~J4CALMiniCone()
{
  J4CALParameterList* ptrList = OpenParameterList();
  const G4String& firstName = dynamic_cast<J4CALBlock *>( GetMother() )->GetFirstName();

  G4int nMiniTowers = 0;

  if ( firstName == "EM" ) {
     nMiniTowers = ptrList -> GetEMMiniTowerNClones();
  } else {
     nMiniTowers = ptrList -> GetHDMiniTowerNClones();
  }
 
  for ( G4int i = 0; i < nMiniTowers; i++ ) {
   if ( Deregister( fMiniTowers[i] ) ) delete fMiniTowers[i];
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALMiniCone::Assemble() 
{   
  if ( !GetLV() ) {
 
    J4CALParameterList *ptrList = OpenParameterList();
    //J4CALSubLayerParameterList* subList = ptrList -> GetSubLayerParam();
      
    G4Sphere* mother = (G4Sphere *)( GetMother()->GetSolid() );

    const G4String& firstName = dynamic_cast<J4CALBlock*>( GetMother() ) -> GetFirstName();
    
    G4double rmin = mother -> GetInsideRadius();
    G4double rmax = mother -> GetOuterRadius();
    G4int nLayers = 0;
    G4int ntheta  = 0;
    G4int nphi    = 0;
      
    if ( firstName == "EM" ) {
      nLayers = ptrList -> GetEMNLayers();
      nphi    = ptrList -> GetEMMiniTowerNClones();
      ntheta  = ptrList -> GetEMMiniConeNClones();
    } else {
      nLayers = ptrList -> GetHDNLayers();
      nphi    = ptrList -> GetHDMiniTowerNClones();
      ntheta  = ptrList -> GetHDMiniConeNClones();
    }

    G4int myID = GetMyID();
    G4double sphi   = mother->GetStartPhiAngle();
    G4double dphi   = mother->GetDeltaPhiAngle();
    G4double dtheta = ( mother->GetDeltaThetaAngle() ) / ntheta;
    G4double stheta = ( mother->GetStartThetaAngle() ) + myID * dtheta;

    // MakeSolid ----------//
    G4Sphere* minicone = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
    Register( minicone );
    SetSolid( minicone );

    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order( ptrList->GetConeMaterial()) );
    
    // SetVisAttribute ----//
    PaintLV( ptrList->GetMiniConeVisAtt(), ptrList->GetMiniConeColor() );
  	
    // Install daughter PV //
    //fMiniTower = new J4CALMiniTower( this, nphi );
    for ( G4int i = 0; i < nphi; i++ ) {
      J4CALMiniTower* minitower = new J4CALMiniTower( this, 1, nphi, i );
      fMiniTowers.push_back( minitower );
      Register( minitower );
      minitower -> InstallIn( this );
      SetDaughter( minitower );
    }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALMiniCone::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALMiniCone::InstallIn( J4VComponent*        /* mother */,
                               G4RotationMatrix*    /* prot   */, 
                               const G4ThreeVector& /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.

   //* placement --------
   SetPVPlacement();
}


//* Draw  --------------------------------------------------------
void J4CALMiniCone::Draw()
{
   // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CALMiniCone::Print() const
{
}
