// $Id$
//*************************************************************************
//* --------------------
//* J4CDCLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2004/08/26  K.Fujii	Fixed rotation direction.
//*************************************************************************

#include "J4CDCLayer.hh"
#include "J4CDCCell.hh"
#include "J4CDCStereoCell.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4CDCLayer::fFirstName("Layer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCLayer::J4CDCLayer(J4VDetectorComponent *parent,
                                      G4int  nclones,
                                      G4int  nbrothers, 
                                      G4int  me,
                                      G4int  copyno ) 
           :J4VCDCDetectorComponent(fFirstName, parent, nclones,
                                    nbrothers, me, copyno),
            fCell(0), fStereoCells(0), fOffset(0), fTwistedAngle(0), 
            fStereoAngle(0), 
            fShieldWidth(0), fRmin(0), fRmax(0), fLayerType("W")
{
   J4CDCParameterList *list = OpenParameterList();
   G4int globallayerno = GetGlobalLayerNumber();
   fOffset             = list->GetLayerPhiOffset(globallayerno);
   fTwistedAngle       = list->GetLayerPhiTwist(globallayerno);
std::cerr << "J4CDCLayer::LayerPhiOffset = " << fOffset << std::endl;
   fRot.rotateZ(-fOffset);

#if 0   
   G4int superlayerno = GetMother()->GetMyID();
   std::cerr << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<std::endl;
   std::cerr << "J4CDCLayer::superlayerNo = " << superlayerno << std::endl;
   std::cerr << "            myid = " << me << std::endl;
   std::cerr << "            global layerNo = " << globallayerno << std::endl;
   std::cerr << "            fOffset = " << fOffset << std::endl;
   std::cerr << "            fTwistedAngle = " << fTwistedAngle << std::endl;
#endif

   G4double motherRmin = GetInnerRadius(parent);
   G4double motherRmax = GetOuterRadius(parent);
   G4double cellthick  = list->GetCellThick();
   if (list->IsOddSuperLyrOutermost() || nbrothers == 1) {
      switch (me) {
         case 0 : // axial
            fLayerType = "A";
            fShieldWidth = 0;
            fRmin = motherRmin;
            fRmax = fRmin + cellthick;
            break;
         case 1 : // inner stereo
            fLayerType = "U";
            fShieldWidth = list->GetAxialToStereoGap();
            fRmin = motherRmin + cellthick;
            fRmax = fRmin + cellthick + fShieldWidth;
            break;
         case 2 : // outer stereo
            fLayerType = "V";
            fShieldWidth = list->GetStereoToStereoGap();
            fRmin = motherRmin + 2 * cellthick 
                    + list->GetAxialToStereoGap();
            fRmax = fRmin + cellthick + fShieldWidth;
            break;
         default :
            std::cerr << "J4CDCLayer:: wrong ID! abort" << std::endl;
            abort();
      }
   } else {         
      switch (me) {
         case 0 : // inner stereo
            fLayerType = "U";
            fShieldWidth = list->GetAxialToStereoGap();
            fRmin = motherRmin;
            fRmax = fRmin + cellthick + fShieldWidth;
            break;
         case 1 : // outer stereo
            fLayerType = "V";
            fShieldWidth = list->GetStereoToStereoGap();
            fRmin = motherRmin + cellthick
                    + list->GetAxialToStereoGap();
            fRmax = fRmin + cellthick + fShieldWidth;
            break;
         case 2 : // Axial
            fLayerType = "A";
            fShieldWidth = 0;
            fRmin = motherRmax - cellthick;
            fRmax = motherRmax;
            break;
         default :
            std::cerr << "J4CDCLayer:: wrong ID! abort" << std::endl;
            abort();
      }
   }

   if (list->IsAxialOnly()) {
      // reset layertype "Axial"
      fLayerType = "A";
   }
   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCLayer::~J4CDCLayer()
{
  if (Deregister(fCell)) delete fCell;
  if (fStereoCells){
     for (G4int i = 0; i < GetNcellsPerLayer() ; i++) {
        if (Deregister(fStereoCells[i])) delete fStereoCells[i];
     }
     if (Deregister(fStereoCells)) delete [] fStereoCells;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCLayer::Assemble() 
{   
   if (!GetLV()) {	  
      // define geometry
      J4CDCParameterList *list = OpenParameterList();  
      
      // MakeSolid ----------//
      OrderNewTubs (fRmin, fRmax, GetZHalfLength(GetMother()), 
                                  GetDeltaPhi(GetMother()));
    
      // MakeLogicalVolume --//
      G4String material = list->GetLayerMaterial();
      MakeLVWith(OpenMaterialStore()-> Order(material));
    
      // SetVisAttribute ----//
      PaintLV(list->GetLayerVisAtt() , list->GetLayerColor());    
        
      // Install daughter PV //
      // Install Cell        //

      if (fLayerType == "A") {
         fCell = new J4CDCCell(this, GetNcellsPerLayer());
         Register(fCell);
         fCell->InstallIn(this);
         SetDaughter(fCell);
      } else {
         G4int ncells = GetNcellsPerLayer();
         
         // make pointer array for stereo cell...
         fStereoCells = new J4CDCStereoCell* [ncells];
         Register(fStereoCells);
         
         // make first stereo cell object (MUST define copyNo as 0)
         fStereoCells[0] = new J4CDCStereoCell(this, ncells, 1, 0, 0);
         Register(fStereoCells[0]);
         fStereoCells[0]->InstallIn(this);
         
         // copy stereo cell objects (copyNo must start from 1)
         for (G4int i=1; i<ncells; i++ ) {
            fStereoCells[i] = new J4CDCStereoCell(*fStereoCells[0], i);
            Register(fStereoCells[i]);
         }
         
         // install ladder objects...
         for (G4int i=1; i<ncells; i++ ) {
            fStereoCells[i]->InstallIn(this);
            SetDaughter(fStereoCells[i]);
         }
      }
      // Install daughter end
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CDCLayer::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCLayer::InstallIn(J4VComponent        *,
                           G4RotationMatrix    *,
                           const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement(&fRot);
  
}

//=====================================================================
//* GetGlobalLayerNumber ----------------------------------------------
G4int J4CDCLayer::GetGlobalLayerNumber() 
{
   J4CDCParameterList *list = OpenParameterList();  
   G4int superlayerno       = GetMother()->GetMyID();
   G4int nsuperlayers       = list->GetNlayersPerSuperLayer(superlayerno);
   if (list->IsOddSuperLyrOutermost()) {
      return superlayerno * nsuperlayers + GetMyID();
   } else {
      if (superlayerno == 0) return 0; // innermost layer is odd superlayer
      return (superlayerno - 1) * nsuperlayers + GetMyID() + 1;
   }
}

//* Draw  --------------------------------------------------------
void J4CDCLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDCLayer::Print() const
{
}


	
