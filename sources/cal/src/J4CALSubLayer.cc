// $Id$
//*************************************************************************
//* --------------------
//* J4CALSubLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALSubLayer.hh"
#include "J4CALSubLayerSD.hh"
#include "J4CALHit.hh"
#include "J4CALLayer.hh"
#include "J4CALMiniTower.hh"
#include "J4CALMiniCone.hh"
#include "J4CALBlock.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "J4Timer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String& J4CALSubLayer::fFirstName( "SubLayer" );

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALSubLayer::J4CALSubLayer(J4VDetectorComponent *parent,
                                            G4int  nclones,
                                            G4int  nbrothers, 
                                            G4int  me,
                                            G4int  copyno )
: J4VCALDetectorComponent( fFirstName, parent, nclones,nbrothers,me,copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALSubLayer::~J4CALSubLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALSubLayer::Assemble() 
{   
 if(!GetLV()){
 
   J4CALParameterList* ptrList = OpenParameterList();
   J4CALSubLayerParameterList* subList = ptrList->GetSubLayerParam();

   G4Sphere* motherLayer = (G4Sphere *)(GetMother()->GetSolid());

   G4double stheta = motherLayer->GetStartThetaAngle();
   G4double dtheta = motherLayer->GetDeltaThetaAngle();
   G4double sphi   = motherLayer->GetStartPhiAngle();
   G4double dphi   = motherLayer->GetDeltaPhiAngle();
      
   J4CALLayer*     ptrLayer     = dynamic_cast<J4CALLayer*>(GetMother());
   J4CALMiniTower* ptrMiniTower = dynamic_cast<J4CALMiniTower*>(ptrLayer->GetMother());
   J4CALMiniCone*  ptrMiniCone  = dynamic_cast<J4CALMiniCone*>(ptrMiniTower->GetMother());
   J4CALBlock*     ptrBlock     = dynamic_cast<J4CALBlock*>(ptrMiniCone->GetMother());

   const G4String& firstName = ptrBlock->GetFirstName();
   const G4int myID      = GetMyID();
   const G4double rstart = motherLayer -> GetInsideRadius();
   G4double rmin   = rstart;

   if ( myID != 0 ) {
    for ( G4int i = 0; i < myID; i++ ) {
     rmin += subList -> GetLayerSize( firstName, i ); 
    }
   }

   G4double rmax = rmin + subList -> GetLayerSize(firstName, myID );
   const G4String& material  = subList -> GetLayerMaterial(firstName,myID);

#if 0
   G4cerr << __FILE__ << " " << __LINE__ << " : "
          << "rstart=" << rstart << " "
          << "rmin=" << rmin << " "
          << "rmax=" << rmax << " "
          << "material=" << material << " "
	  << "type=" << firstName
          << G4endl;
#endif
  
   // MakeSolid ----------//
   G4Sphere* sublayer = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
   Register(sublayer);
   SetSolid(sublayer);
      
   // MakeLogicalVolume --//  
   MakeLVWith(OpenMaterialStore()->Order(material));
     
   // SetVisAttribute ----//
   PaintLV(ptrList->GetSubLayerVisAtt(), ptrList->GetSubLayerColor());
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALSubLayer::Cabling()
{
  if( !GetSD() ) {
   
   J4CALSubLayerParameterList *subList = OpenParameterList()->GetSubLayerParam();
   J4CALLayer*     ptrLayer     = dynamic_cast<J4CALLayer*>(GetMother());
   J4CALMiniTower* ptrMiniTower = dynamic_cast<J4CALMiniTower*>(ptrLayer->GetMother());
   J4CALMiniCone*  ptrMiniCone  = dynamic_cast<J4CALMiniCone*>(ptrMiniTower->GetMother());
   J4CALBlock*     ptrBlock     = dynamic_cast<J4CALBlock*>(ptrMiniCone->GetMother());

   const G4String& firstName = ptrBlock -> GetFirstName();
//   const G4int nSubLayers = subList -> GetNLayers(firstName);
    
   G4int myID = GetMyID();

   if( subList->isSD( firstName ,myID ) ) {
     
     J4CALSubLayerSD* sd = new J4CALSubLayerSD(this);
     Register(sd);
     SetSD(sd);

#if 0
     G4cerr //<< __FILE__ <<  " " << __LINE__ << " : "
            << "Cabling : "
	    << "sublayer=" << GetMyID() << " "
	    << "layer=" << ptrLayer -> GetMyID() << " "
	    << "minitower=" << ptrMiniTower->GetCopyNo() << " "
	    << "minicone=" << ptrMiniCone->GetMyID() << " "
	    << "type=" << ptrBlock->GetFirstName() << " "
	    << "tower=" << ptrBlock->GetMother()->GetCopyNo() << " "
	    << "cone=" << ptrBlock->GetMother()->GetMother()->GetMyID()
	    << G4endl; 
#endif
     
    }
  }
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALSubLayer::InstallIn( J4VComponent*        /* mother */ ,
                               G4RotationMatrix*    /* prot   */ , 
                               const G4ThreeVector& /* tlate  */  ) 
{ 
   static G4int timerID = -1;
   J4Timer timer( timerID, "J4CALSubLayer", "InstallIn()" );
   timer.Start();

   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   SetPVPlacement();

   // Cablig for SD
   Cabling();

   timer.Stop();
}

//* Draw  --------------------------------------------------------
void J4CALSubLayer::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALSubLayer::Print() const
{ }
