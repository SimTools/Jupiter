// $Id$
//*************************************************************************
//* --------------------
//* J4VCALMiniTower
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALMiniTower.hh"
#include "J4VCALLayer.hh"
#include "J4CALEMLayer.hh"
#include "J4CALHDLayer.hh"
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

J4VCALMiniTower::J4VCALMiniTower( const G4String       &name,
                                  J4VDetectorComponent *parent,
                                                 G4int  nclones,
                                                 G4int  nbrothers, 
                                                 G4int  me,
                                                 G4int  copyno ) 
: J4VCALDetectorComponent( name, parent, nclones, nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCALMiniTower::~J4VCALMiniTower()
{
  for ( G4int i = 0; i < (G4int)fLayers.size(); i++ ){
#if 0
    if ( Deregister( fLayers[i] ) ) delete fLayers[i];
#else
    delete fLayers[i];
#endif
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCALMiniTower::Assemble() 
{   
  if( !GetLV() ) {
    
    G4Sphere *mothercone = (G4Sphere *)( GetMother()->GetSolid() );
    
    G4double rmin   = mothercone -> GetInsideRadius();
    G4double rmax   = mothercone -> GetOuterRadius();
    G4double dtheta = mothercone -> GetDeltaThetaAngle();
    G4double stheta = mothercone -> GetStartThetaAngle();
    G4int nLayers   = GetNofLayers();
    G4int nphi      = GetNofMiniTowers();
    G4double dphi   = ( mothercone -> GetDeltaPhiAngle() ) / nphi;

#ifdef __REPLICA__
    G4double sphi   = -0.5 * dphi;
#else
    G4int myID      = GetMyID();
    G4double sphi   = mothercone -> GetStartPhiAngle() + myID * dphi;
#endif

    // MakeSolid ----------//
    G4Sphere* minitower = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
    Register( minitower );
    SetSolid( minitower );
      
    // MakeLogicalVolume --//  
    MakeLVWith( OpenMaterialStore()->Order(GetMaterial()) );
    
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );
      
    // Make J4CALLayer objects --- //
      for ( G4int i = 0; i < nLayers; i++ ) {
	J4VCALLayer* Layer = Create( this, 1, nLayers, i );
	fLayers.push_back( Layer );
	Register( Layer );
	Layer -> InstallIn( this );
	SetDaughter( Layer );
      }
  }
}
//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VCALMiniTower::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VCALMiniTower::InstallIn( J4VComponent*        /* mother */,
                                G4RotationMatrix*    /* prot   */, 
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
     G4double off  = ((G4Sphere *)GetMother()->GetSolid())->GetStartPhiAngle()\
       + 0.5*step;
     SetPVReplica(kPhi, step, off);
   } else {
     SetPVPlacement();
   }
#else
   SetPVPlacement();
#endif

}


//* Draw  --------------------------------------------------------
void J4VCALMiniTower::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4VCALMiniTower::Print() const
{
}
