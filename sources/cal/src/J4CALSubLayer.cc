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

#include "J4CALSubLayer.hh"
#include "J4CALSubLayerSD.hh"
#include "J4CALHit.hh"
#include "J4CALLayer.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "J4Timer.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CALSubLayer::fFirstName = "SubLayer";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALSubLayer::J4CALSubLayer(J4VDetectorComponent *parent,
                                           G4bool  isem,
                                            G4int  nclones,
                                            G4int  nbrothers, 
                                            G4int  me,
                                            G4int  copyno )
             : J4VCALDetectorComponent(fFirstName, isem, parent, 
                                       nclones,nbrothers,me,copyno)
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
 if (!GetLV()) {
 
   J4CALParameterList* ptrList = OpenParameterList();

   G4Sphere* motherLayer = (G4Sphere *)(GetMother()->GetSolid());

   G4double stheta = motherLayer->GetStartThetaAngle();
   G4double dtheta = motherLayer->GetDeltaThetaAngle();
   G4double sphi   = motherLayer->GetStartPhiAngle();
   G4double dphi   = motherLayer->GetDeltaPhiAngle();
      
   const G4int myID        = GetMyID();
   const G4double rstart   = motherLayer -> GetInsideRadius();
   const G4double absthick = IsEM() ? ptrList->GetEMAbsLayerThickness()
                                    : ptrList->GetHDAbsLayerThickness();
   const G4double actthick = IsEM() ? ptrList->GetEMActiveLayerThickness()
                                    : ptrList->GetHDActiveLayerThickness();
   const G4double rmin     = myID ? rstart + absthick + (myID-1)*actthick
                                  : rstart;
   const G4double rmax     = myID ? rstart + absthick + myID*actthick
                                  : rstart + absthick;

   const G4String material = IsEM() ? (myID ? ptrList->GetEMActiveLayerMaterial()
                                            : ptrList->GetEMAbsLayerMaterial())
                                    : (myID ? ptrList->GetHDActiveLayerMaterial()
                                            : ptrList->GetHDAbsLayerMaterial());

#if 0
   G4cerr << __FILE__ << " " << __LINE__ << " : "
          << "rstart=" << rstart << " "
          << "rmin=" << rmin << " "
          << "rmax=" << rmax << " "
          << "material=" << material << " "
	  << "type=" << (IsEM() ? "EM" : "HD")
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
  if (!GetSD()) {
    if (GetMyID()) {
      J4CALSubLayerSD* sd = new J4CALSubLayerSD(this);
      Register(sd);
      SetSD(sd);
    }
  }
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALSubLayer::InstallIn(J4VComponent        * /* mother */,
                              G4RotationMatrix    * /* prot   */, 
                              const G4ThreeVector & /* tlate  */)
{ 
   static G4int timerID = -1;
   J4Timer timer(timerID, "J4CALSubLayer", "InstallIn()");
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
{
}
