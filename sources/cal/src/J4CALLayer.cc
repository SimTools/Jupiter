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

G4String J4CALLayer::fFirstName("Layer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALLayer::J4CALLayer(J4VDetectorComponent *parent,
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

J4CALLayer::~J4CALLayer()
{
#if 0
  J4CALMiniTower* ptrJ4CALMiniTower = dynamic_cast<J4CALMiniTower*>(GetMother());
  J4CALMiniCone*  ptrJ4CALMiniCone  = dynamic_cast<J4CALMiniCone*>(ptrJ4CALMiniTower-> GetMother());
  J4CALBlock*  ptrJ4CALBlock  = dynamic_cast<J4CALBlock*>(ptrJ4CALMiniCone-> GetMother());
   const G4String& firstName = ptrJ4CALBlock->GetFirstName();

   G4int nlayers = ((OpenParameterList() -> GetSubLayerParam()) -> GetNLayers(firstName));
#else
   G4int nlayers = fSubLayers.size();
#endif

   for(G4int i = 0; i < nlayers; i++){
     if (Deregister(fSubLayers[i])) delete fSubLayers[i];
   }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALLayer::Assemble() 
{   
   if(!GetLV()){
 
     J4CALParameterList *ptrList = OpenParameterList();
     J4CALSubLayerParameterList *subList = ptrList -> GetSubLayerParam();

     J4CALMiniTower* ptrMiniTower = dynamic_cast<J4CALMiniTower*>(GetMother());
     J4CALMiniCone* ptrMiniCone = dynamic_cast<J4CALMiniCone*>(ptrMiniTower->GetMother());
     J4CALBlock* ptrBlock = dynamic_cast<J4CALBlock*>(ptrMiniCone->GetMother());
     const G4String& firstName = ptrBlock->GetFirstName();
     
     G4Sphere *mothertower = (G4Sphere *)(GetMother()->GetSolid());

     G4double stheta = mothertower->GetStartThetaAngle();
     G4double dtheta = mothertower->GetDeltaThetaAngle();
     G4double sphi   = mothertower->GetStartPhiAngle();
     G4double dphi   = mothertower->GetDeltaPhiAngle();
     G4double rstart = mothertower->GetInsideRadius();

     G4int myID = GetMyID();
     G4double thickness = subList -> GetTotalLayerSize(firstName);
     G4double rmin      = rstart + myID * thickness;
     G4double rmax      = rmin + thickness;
     G4String material  = ptrList -> GetLayerMaterial();

     // MakeSolid ----------//
     G4Sphere* layer = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
     Register(layer);
     SetSolid(layer);

     // MakeLogicalVolume --//  
     MakeLVWith(OpenMaterialStore()->Order(material));
   
     // SetVisAttribute ----//
     //PaintLV(list->GetEMLayerVisAtt(), list->GetEMLayerColor());
     PaintLV(ptrList->GetLayerVisAtt(), ptrList->GetLayerColor());

     // Make J4CALSubLayer objects --- //
     G4int nSubLayers = subList->GetNLayers(firstName);

     for(G4int i = 0; i < nSubLayers; i++){
      J4CALSubLayer* ptrSubLayer = new J4CALSubLayer(this,1,nSubLayers,i);
       //G4cout << ptrSubLayer ;
       fSubLayers.push_back(ptrSubLayer);
       Register(ptrSubLayer);
       ptrSubLayer->InstallIn(this);
       SetDaughter(ptrSubLayer);
     }
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALLayer::Cabling()
{
//  if( !GetSD() ) {
//
//    J4CALParameterList* ptrList = OpenParameterList();
//    J4CALSubLayerParameterList *subList = ptrList -> GetSubLayerParam();
//    J4CALMiniTower* ptrJ4CALMiniTower = dynamic_cast<J4CALMiniTower*>(GetMother());
//    J4CALMiniCone*  ptrJ4CALMiniCone = dynamic_cast<J4CALMiniCone*>(ptrJ4CALMiniTower-> GetMother());
//    J4CALBlock*  ptrJ4CALBlock = dynamic_cast<J4CALBlock*>(ptrJ4CALMiniCone-> GetMother());
//    const G4String& firstName = ptrJ4CALBlock -> GetFirstName();
//    const G4int nSubLayers = subList -> GetNLayers(firstName);
//    G4String  material;
//
//    for(G4int i = 0; i < nSubLayers; i++){
//      
//      material = subList -> GetLayerMaterial(firstName,i);
//      
//      if( subList -> isSD(material,i) ) {
//	J4CALSubLayerSD* sd = new J4CALSubLayerSD(this);
//	Register(sd);
//	SetSD(sd);
//      }
//      
//    }
//  } 
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALLayer::InstallIn(J4VComponent         *mother,
                            G4RotationMatrix     *prot, 
                            const G4ThreeVector  &tlate ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  				// 
  
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
