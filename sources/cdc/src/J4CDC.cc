// $Id$
//*************************************************************************
//* --------------------
//* J4CDC
//* --------------------
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDC.hh"
#include "J4CDCSuperLayer.hh"


//====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CDC::fFirstName("CDC");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDC::J4CDC(J4VDetectorComponent *parent,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno )
      :J4VCDCDetectorComponent( fFirstName, parent, nclones,
                                nbrothers, me, copyno ),
       fOuterSupportTub(0), fInnerSupportTub(0),
       fEndcaps(0), fLayers(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDC::~J4CDC()
{
   if (Deregister(fInnerSupportTub)) delete fInnerSupportTub;
   if (Deregister(fOuterSupportTub)) delete fOuterSupportTub;
  
   if (fEndcaps) {	
      for (G4int i = 0; i < 2 ; i++) {
         if(Deregister(fEndcaps[i])) delete fEndcaps [i];
      } 
      if (Deregister(fEndcaps)) delete [] fEndcaps;
   }
  	
   if (fLayers) {	
      for (G4int i = 0; i < OpenParameterList()->GetNsuperLayers(); i++) {
         if (Deregister(fLayers[i])) delete fLayers [i];
      } 
      if (Deregister(fLayers)) delete [] fLayers;
   }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDC::Assemble() 
{   
   if (!GetLV()) {
  
      J4CDCParameterList *list = OpenParameterList();
      
      G4double rmin = list->GetCDCInnerR();
      G4double rmax = list->GetCDCOuterR();
      G4double len  = list->GetCDCHalfZ();
      G4double dphi = list->GetCDCDeltaPhi();
      //G4double endcapthick = list->GetEndcapHalfThick();
  	
      // MakeSolid ----------//
      OrderNewTubs (rmin, rmax, len, dphi);
    
      // MakeLogicalVolume --//
      G4String material = list->GetCDCMaterial();  
      MakeLVWith(OpenMaterialStore()->Order(material));
      GetLV()->SetOptimisation(FALSE);
    
      // SetVisAttribute ----//
      PaintLV(list->GetCDCVisAtt(), list->GetCDCColor());
  	
      // Install daughter PV //
      // Install SupportTub       //

      G4double otubInnerR  = list->GetOuterSupportTubInnerR();
      G4double otubOuterR  = list->GetOuterSupportTubOuterR();
      G4double itubInnerR  = list->GetInnerSupportTubInnerR();
      G4double itubOuterR  = list->GetInnerSupportTubOuterR();
      G4double tublen      = list->GetSupportTubHalfZ();
      G4double tubdphi     = list->GetSupportTubDeltaPhi();
    
      fOuterSupportTub = new J4CDCSupportTub(otubInnerR, otubOuterR, tublen,
                                                     tubdphi, this);
      Register(fOuterSupportTub);
      fOuterSupportTub->InstallIn(this);
      SetDaughter(fOuterSupportTub);
    
      fInnerSupportTub = new J4CDCSupportTub(itubInnerR, itubOuterR, tublen, 
                                                     tubdphi, this);
      Register(fInnerSupportTub);
      fInnerSupportTub->InstallIn(this);
      SetDaughter(fInnerSupportTub);
    
      // Install daughters
      // Install Endcap       
    
      fEndcaps = new J4CDCEndcap* [2];
      Register(fEndcaps);
      for (G4int i = 0; i < 2 ; i++) {
         fEndcaps [i] = new J4CDCEndcap(this, 1 , 2 , i );
         Register(fEndcaps[i]);
         fEndcaps [i]->InstallIn(this);  
         SetDaughter(fEndcaps[i]);
      }  
        
      // Install SuperLayers
      G4int nsuperlayers = list->GetNsuperLayers();  
      fLayers = new J4CDCSuperLayer* [nsuperlayers];
      Register(fLayers);
      for (G4int i = 0; i < nsuperlayers ; i++) {
         fLayers [i] = new J4CDCSuperLayer(this, 1, nsuperlayers, i);
         Register(fLayers[i]);
         fLayers [i]->InstallIn(this);  
      
         SetDaughter(fLayers[i]);
      }
      // Install daughters end   
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CDC::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDC::InstallIn(J4VComponent        *,
                      G4RotationMatrix    *,
                      const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}

//* Draw  --------------------------------------------------------
void J4CDC::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDC::Print() const
{
}
