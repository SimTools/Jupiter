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
#include "J4CALMiniCone.hh"
#include "J4CALLayer.hh"
#include "J4CALBlock.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String& J4CALMiniTower::fFirstName( "MiniTower" );

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALMiniTower::J4CALMiniTower( J4VDetectorComponent *parent,
                                               G4int  nclones,
                                               G4int  nbrothers, 
                                               G4int  me,
                                               G4int  copyno ) 
: J4VCALDetectorComponent( fFirstName, parent, nclones,
                                 nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALMiniTower::~J4CALMiniTower()
{
  J4CALMiniCone*  ptrMiniCone  = dynamic_cast<J4CALMiniCone*>( GetMother() );
  J4CALBlock*     ptrBlock     = dynamic_cast<J4CALBlock*>( ptrMiniCone->GetMother() );
  const G4String& firstName    = ptrBlock -> GetFirstName();
  const G4int nLayers = ( OpenParameterList()->GetSubLayerParam() )->GetNLayers(firstName);

  for ( G4int i = 0; i < nLayers; i++ ){
     if ( Deregister( fLayers[i] ) ) delete fLayers[i];
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALMiniTower::Assemble() 
{   
   if( !GetLV() ) {
 
      J4CALParameterList* ptrList = OpenParameterList();

      J4CALMiniCone* ptrMiniCone = dynamic_cast<J4CALMiniCone*>(GetMother());
      J4CALBlock*    ptrBlock    = dynamic_cast<J4CALBlock*>(ptrMiniCone->GetMother());
      const G4String& firstName  = ptrBlock -> GetFirstName();
      G4Sphere *mothercone = (G4Sphere *)( GetMother()->GetSolid() );

      G4double rmin   = mothercone -> GetInsideRadius();
      G4double rmax   = mothercone -> GetOuterRadius();

      G4double dtheta = mothercone -> GetDeltaThetaAngle();
      G4double stheta = mothercone -> GetStartThetaAngle();
     
      G4int nphi = 0;
      G4int nLayers = 0;

      //  EM and HD tower divisions ----- //
      if ( firstName == "EM" ) {
	nLayers = ptrList -> GetEMNLayers();
	nphi    = ptrList -> GetEMMiniTowerNClones();
      } else {
	nLayers = ptrList -> GetHDNLayers();
	nphi    = ptrList -> GetHDMiniTowerNClones();
      }

      G4int myID = GetMyID();
      G4double dphi = ( mothercone -> GetDeltaPhiAngle() ) / nphi;
      G4double sphi   = mothercone -> GetStartPhiAngle() + myID * dphi;

#if 0
      G4cerr << __FILE__ << " " << __LINE__ << " : "
	     << "rmin=" << rmin << " "
             << "rmax=" << rmax << " "
             << "nLayers=" << nLayers << " "
             << "nphi=" << nphi << " "
	     << "dphi=" << dphi << " "
	     << "type=" << firstName
             << G4endl;
#endif      
      
      // MakeSolid ----------//
      G4Sphere* minitower = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
      Register( minitower );
      SetSolid( minitower );
      
      // MakeLogicalVolume --//  
      MakeLVWith( OpenMaterialStore()->Order(ptrList->GetMiniTowerMaterial()) );
      
      // SetVisAttribute ----//
      PaintLV( ptrList->GetMiniTowerVisAtt(), ptrList->GetMiniTowerColor() );
      
      for ( G4int i = 0; i < nLayers; i++ ) {
	J4CALLayer* ptrLayer = new J4CALLayer( this, 1, nLayers, i );
	fLayers.push_back( ptrLayer );
	Register( ptrLayer );
	ptrLayer -> InstallIn( this );
	SetDaughter( ptrLayer );
      }
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALMiniTower::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALMiniTower::InstallIn( J4VComponent*        /* mother */,
                                G4RotationMatrix*    /* prot   */, 
                                const G4ThreeVector& /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   //===================================================================
   // Caution!!
   // If you use SetPVReplica(), then SD has some trouble !!
   //===================================================================
   //G4double step = ((G4Sphere *)GetSolid())->GetDeltaPhiAngle();
   //SetPVReplica(kPhi, step);
   SetPVPlacement();
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
