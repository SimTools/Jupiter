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
//*     2004/10/07  H.Ono       Parametrized
//*************************************************************************

#include "J4CALLayer.hh"
#include "J4CALSubLayer.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"

//#define __NOSUBLAYER__
#ifdef __NOSUBLAYER__
#include "J4VSD.hh"
#include "J4CALHit.hh"
class J4CALLayerSD : public J4VSD<J4CALHit> {
public:
  J4CALLayerSD(J4VDetectorComponent *det) : J4VSD<J4CALHit>(det) {}

  virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
  {
     SetNewStep(aStep);
     J4CALLayer *cp = (J4CALLayer *)GetComponent(0);
     if (cp->IsEM()) {
        std::cerr << "Layer got an EM hit! -----------------" << std::endl;
     } else {
        std::cerr << "Layer got an HD hit! -----------------" << std::endl;
     }
     return true;
  }
  virtual void   Initialize (G4HCofThisEvent* HCTE) {}
  virtual void   EndOfEvent (G4HCofThisEvent* HCTE) {}

  virtual void   DrawAll () {}
  virtual void   PrintAll() {}

  virtual void   OutputAll(G4HCofThisEvent* HCTE) {}
};
#endif

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALLayer::fFirstName = "Layer";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALLayer::J4CALLayer(J4VDetectorComponent *parent,
                                     G4bool  isem,
                                      G4int  nclones,
                                      G4int  nbrothers, 
                                      G4int  me,
                                      G4int  copyno)
          : J4VCALDetectorComponent(fFirstName, isem, parent, nclones,
                                    nbrothers, me, copyno)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALLayer::~J4CALLayer()
{
   G4int nLayers = fSubLayers.size();
   for (G4int i = 0; i < nLayers; i++) {
     if (Deregister(fSubLayers[i])) delete fSubLayers[i];
   }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALLayer::Assemble() 
{   
   if (!GetLV()) {
 
     J4CALParameterList *ptrList = OpenParameterList();
     
     G4Sphere *motherTower = (G4Sphere *)(GetMother()->GetSolid());

     G4double stheta = motherTower->GetStartThetaAngle();
     G4double dtheta = motherTower->GetDeltaThetaAngle();
     G4double sphi   = motherTower->GetStartPhiAngle();
     G4double dphi   = motherTower->GetDeltaPhiAngle();
     G4double rstart = motherTower->GetInsideRadius();

     G4int nSubLayers   = IsEM() ? ptrList->GetEMNSubLayersPerLayer()
                                 : ptrList->GetHDNSubLayersPerLayer();
     G4int myID = GetMyID();
     G4double thickness = IsEM() ? ptrList->GetEMActiveLayerThickness()
                                   * (nSubLayers-1)
                                   + ptrList->GetEMAbsLayerThickness()
                                 : ptrList->GetHDActiveLayerThickness()
                                   * (nSubLayers-1)
                                   + ptrList->GetHDAbsLayerThickness();
     G4double rmin      = rstart + myID * thickness;
     G4double rmax      = rmin + thickness;

     // MakeSolid ----------//
     G4Sphere* layer = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
     Register(layer);
     SetSolid(layer);

     // MakeLogicalVolume --//  
     const G4String& material  = ptrList -> GetLayerMaterial();
     MakeLVWith(OpenMaterialStore()->Order(material));

#if 0
     G4cerr << __FILE__ << " " << __LINE__ << " : "
            << "layer=" << myID << " "
            << "rmin=" << rmin << " "
            << "rmax=" << rmax << " "
            << "material=" << material << " "
            << "type=" << firstName 
            << G4endl;
#endif
   
     // SetVisAttribute ----//
     PaintLV(ptrList->GetLayerVisAtt(), ptrList->GetLayerColor());

     // Make J4CALSubLayer objects --- //

#ifndef __NOSUBLAYER__
     for (G4int i = 0; i < nSubLayers; i++) {
        J4CALSubLayer* ptrSubLayer = new J4CALSubLayer(this, IsEM(), 1, nSubLayers, i);
        fSubLayers.push_back(ptrSubLayer);
        Register(ptrSubLayer);
        ptrSubLayer -> InstallIn(this);
        SetDaughter(ptrSubLayer);
     }
#endif
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALLayer::Cabling()
{
#ifdef __NOSUBLAYER__
   if (!GetSD()) {
      J4CALLayerSD *sd = new J4CALLayerSD(this);
      Register(sd);
      SetSD(sd);
   }
#endif
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALLayer::InstallIn(J4VComponent        * /* mother */,
                           G4RotationMatrix    * /* prot   */, 
                           const G4ThreeVector & /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.

   // Placement function into mother object...
   SetPVPlacement();

   // Cabling function for SD object... 
#ifdef __NOSUBLAYER__
   Cabling(); 
#endif
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
