// $Id$
//*************************************************************************
//* --------------------
//* J4CALLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALLayer.hh"
#include "J4CALSubLayer.hh"
#include "J4CALMiniTower.hh"
#include "J4CALMiniCone.hh"
#include "J4CALBlock.hh"
#include "J4CALParameterList.hh"
#include "J4CALSubLayerSD.hh"
#include "G4Sphere.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String& J4CALLayer::fFirstName( "Layer" );

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALLayer::J4CALLayer( J4VDetectorComponent *parent,
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

J4CALLayer::~J4CALLayer()
{
 G4int nLayers = fSubLayers.size();

   for ( G4int i = 0; i < nLayers; i++ ) {
     if ( Deregister(fSubLayers[i]) ) delete fSubLayers[i];
   }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALLayer::Assemble() 
{   
   if ( !GetLV() ) {
 
     J4CALParameterList *ptrList = OpenParameterList();
     J4CALSubLayerParameterList *subList = ptrList -> GetSubLayerParam();

     J4CALMiniTower* ptrMiniTower = dynamic_cast<J4CALMiniTower*>( GetMother() );
     J4CALMiniCone* ptrMiniCone = dynamic_cast<J4CALMiniCone*>( ptrMiniTower->GetMother());
     J4CALBlock* ptrBlock = dynamic_cast<J4CALBlock*>(ptrMiniCone->GetMother());
     const G4String& firstName = ptrBlock->GetFirstName();
     
     G4Sphere *motherTower = (G4Sphere *)( GetMother()->GetSolid() );

     G4double stheta = motherTower->GetStartThetaAngle();
     G4double dtheta = motherTower->GetDeltaThetaAngle();
     G4double sphi   = motherTower->GetStartPhiAngle();
     G4double dphi   = motherTower->GetDeltaPhiAngle();
     G4double rstart = motherTower->GetInsideRadius();

     G4int myID = GetMyID();
     G4double thickness = subList -> GetTotalLayerSize(firstName);
     G4double rmin      = rstart + myID * thickness;
     G4double rmax      = rmin + thickness;
     const G4String& material  = ptrList -> GetLayerMaterial();

#if 0
     G4cerr << __FILE__ << " " << __LINE__ << " : "
            << "layer=" << myID << " "
            << "rmin=" << rmin << " "
            << "rmax=" << rmax << " "
            << "material=" << material << " "
            << "type=" << firstName 
            << G4endl;
#endif

     // MakeSolid ----------//
     G4Sphere* layer = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
     Register( layer );
     SetSolid( layer );

     // MakeLogicalVolume --//  
     MakeLVWith( OpenMaterialStore()->Order(material) );
   
     // SetVisAttribute ----//
     PaintLV( ptrList->GetLayerVisAtt(), ptrList->GetLayerColor() );

     // Make J4CALSubLayer objects --- //
     G4int nSubLayers = subList->GetNLayers(firstName);

     for ( G4int i = 0; i < nSubLayers; i++ ) {
       J4CALSubLayer* ptrSubLayer = new J4CALSubLayer( this, 1, nSubLayers, i );
       fSubLayers.push_back( ptrSubLayer );
       Register( ptrSubLayer );
       ptrSubLayer -> InstallIn( this );
       SetDaughter( ptrSubLayer );
    }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALLayer::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALLayer::InstallIn(J4VComponent*         /* mother */,
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
void J4CALLayer::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALLayer::Print() const
{
}
