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
#include "J4CALLayer.hh"
#include "J4CALMiniTower.hh"
#include "J4CALMiniCone.hh"
#include "J4CALBlock.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CALSubLayer::fFirstName("SubLayer");

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
         //J4VCALDetectorComponent( fFirstName, parent, nclones,
 : J4CALLayer( parent, nclones, nbrothers, me, copyno  ) 
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

      G4Sphere* motherlayer = (G4Sphere *)(GetMother()->GetSolid());

      G4double stheta = motherlayer->GetStartThetaAngle();
      G4double dtheta = motherlayer->GetDeltaThetaAngle();
      G4double sphi   = motherlayer->GetStartPhiAngle();
      G4double dphi   = motherlayer->GetDeltaPhiAngle();
      
      J4CALLayer* ptrLayer = dynamic_cast<J4CALLayer*>(GetMother());
      J4CALMiniTower* ptrMiniTower = dynamic_cast<J4CALMiniTower*>(ptrLayer->GetMother());
      J4CALMiniCone*  ptrMiniCone = dynamic_cast<J4CALMiniCone*>(ptrMiniTower->GetMother());
      J4CALBlock* ptrBlock = dynamic_cast<J4CALBlock*>(ptrMiniCone->GetMother());
      G4String firstName = ptrBlock -> GetFirstName();
      G4int myID = GetMyID();

      //G4double previousRmax  = rmin;
      const G4double rmin = motherlayer->GetInsideRadius();
      G4double layerFrontPosition = rmin + subList->GetLayerFront(firstName,myID);
      G4double rmax = layerFrontPosition + subList->GetLayerSize(firstName,myID);
      G4String material  = subList -> GetLayerMaterial(firstName,myID);

      // MakeSolid ----------//
      G4Sphere* layer = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
      Register(layer);
      SetSolid(layer);
      
      // MakeLogicalVolume --//  
      //MakeLVWith(OpenMaterialStore()->Order(list->GetEMLayerMaterial()));
      MakeLVWith(OpenMaterialStore()->Order(material));
      
      // SetVisAttribute ----//
      //PaintLV(list->GetEMLayerVisAtt(), list->GetEMLayerColor());
      //PaintLV(subList->GetSubLayerVisAtt(), subList->GetSubLayerColor());
      PaintLV(ptrList->GetSubLayerVisAtt(), ptrList->GetSubLayerColor());
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALSubLayer::Cabling()
{
  if( !GetSD() ) {
   
    J4CALSubLayerParameterList *subList = OpenParameterList()->GetSubLayerParam();
    J4CALLayer* ptrLayer = dynamic_cast<J4CALLayer*>(GetMother());
    J4CALMiniTower* ptrMiniTower = dynamic_cast<J4CALMiniTower*>(ptrLayer->GetMother());
    J4CALMiniCone*  ptrMiniCone = dynamic_cast<J4CALMiniCone*>(ptrMiniTower->GetMother());
    J4CALBlock*     ptrBlock = dynamic_cast<J4CALBlock*>(ptrMiniCone->GetMother());
    const G4String& firstName = ptrBlock -> GetFirstName();
    
    const G4int nSubLayers = subList -> GetNLayers(firstName);
    
    //    for(G4int i = 0; i < nSubLayers; i++){
    G4int myID = GetMyID();
      
    if( subList->isSD(firstName ,myID) ) {
      J4CALSubLayerSD* sd = new J4CALSubLayerSD(this);
      Register(sd);
      SetSD(sd);
      // }
    }
  }
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALSubLayer::InstallIn(J4VComponent       *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   SetPVPlacement();

   // Cablig for SD
   //Cabling();
}

//* Draw  --------------------------------------------------------
void J4CALSubLayer::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALSubLayer::Print() const
{
}
