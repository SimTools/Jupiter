// $Id$
//*************************************************************************
//* --------------------
//* J4CDCSuperLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCSuperLayer.hh"
#include "J4CDCLayer.hh"

#include "G4Tubs.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4CDCSuperLayer::fFirstName("SuperLayer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCSuperLayer::J4CDCSuperLayer(J4VDetectorComponent *parent,
                                      G4int  nclones,
                                      G4int  nbrothers, 
                                      G4int  me,
                                      G4int  copyno ) 
  	             :J4VCDCDetectorComponent(fFirstName, parent, nclones,
                                         nbrothers, me, copyno),
                 fLayers(0)
{
   J4CDCParameterList *list = OpenParameterList();
   fOffset         = list->GetSuperLayerSPhi(me);
   fNcellsPerLayer = list->GetNcellsPerLayer(me);
   fRot.rotateZ(list->GetSuperLayerSPhi(me));
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCSuperLayer::~J4CDCSuperLayer()
{
   if (fLayers) { 
      for (G4int i = 0; i < OpenParameterList()->GetNlayersPerSuperLayer(GetMyID()); i++) {
         if (Deregister(fLayers[i])) delete fLayers[i];
      } 
      if (Deregister(fLayers)) delete [] fLayers;
   }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCSuperLayer::Assemble() 
{
   if(!GetLV()){	  
      // define geometry
      J4CDCParameterList *list = OpenParameterList();

      G4double rmin = list->GetSuperLayerIR(GetMyID());
      G4double rmax = list->GetSuperLayerOR(GetMyID());
      G4double len  = list->GetSuperLayerHalfZ();
      G4double motherphi = list->GetCDCDPhi();
         
      // MakeSolid ----------//
      OrderNewTubs (rmin, rmax, len, motherphi);
      
      // MakeLogicalVolume --//
      G4String material = list->GetLayerMaterial();
      MakeLVWith(OpenMaterialStore()->Order(material));
      
      // SetVisAttribute ----//
      PaintLV(list->GetSuperLayerVisAtt(), 
              list->GetSuperLayerColor());
      
      // Install daughter PV //
      // Install Layers       //

      if (!(list->IsAxialInnermost()) && GetMyID() == 0) {
         // isolated superlayer! (innermost)
         fLayers = new J4CDCLayer* [1];
         Register(fLayers);
         fLayers[0] = new J4CDCLayer(this, 1, 1, 0);
         Register(fLayers[0]);
         fLayers [0]->InstallIn(this);
         SetDaughter(fLayers[0]);
      } else if ((list->IsAxialInnermost())
                 && (GetMyID() == list->GetNsuperLayers() - 1)) {
         // isolated superlayer! (outermost)
         fLayers = new J4CDCLayer* [1];
         Register(fLayers);
         fLayers[0] = new J4CDCLayer(this, 1, 1, 0);
         Register(fLayers[0]);
         fLayers[0]->InstallIn(this);
         SetDaughter(fLayers[0]);
         // Instal daughter end
      } else {
         G4int nlayers = list->GetNlayersPerSuperLayer(GetMyID());
         G4cerr << "J4CDCSuperLayer::Assemble: nlayers, MyID = "
            << nlayers << " " << GetMyID() <<  G4endl;
         fLayers = new J4CDCLayer* [nlayers];
         Register(fLayers);
         for (G4int i = 0; i < nlayers; i++) {
            fLayers [i] = new J4CDCLayer(this, 1, nlayers, i);
            Register(fLayers[i]);
            fLayers [i]->InstallIn(this);
            SetDaughter(fLayers[i]);
         }
      }
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CDCSuperLayer::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCSuperLayer::InstallIn(J4VComponent         *mother,
                                G4RotationMatrix     *prot, 
                                const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement(&fRot);
  
}

//* Draw  --------------------------------------------------------
void J4CDCSuperLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDCSuperLayer::Print() const
{
}
