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
      
      G4double rmin = list->GetCDCIR();
      G4double rmax = list->GetCDCOR();
      G4double len  = list->GetCDCOR();
      G4double dphi = list->GetCDCDPhi();
      //G4double endcapthick = list->GetEndcapThick();
  	
      // MakeSolid ----------//
      OrderNewTubs (rmin, rmax, len, dphi);
    
      // MakeLogicalVolume --//
      G4String material = list->GetCDCMaterial();  
      MakeLVWith(OpenMaterialStore()->Order(material));
    
      // SetVisAttribute ----//
      PaintLV(list->GetCDCVisAtt(), list->GetCDCColor());
  	
      // Install daughter PV //
      // Install SupportTub       //

      G4double otubIR  = list->GetOuterSupportTubIR();
      G4double otubOR  = list->GetOuterSupportTubOR();
      G4double itubIR  = list->GetInnerSupportTubIR();
      G4double itubOR  = list->GetInnerSupportTubOR();
      G4double tublen  = list->GetSupportTubHalfZ();
      G4double tubdphi = list->GetSupportTubDPhi();
    
      fOuterSupportTub = new J4CDCSupportTub(otubIR, otubOR, tublen,
                                                     tubdphi, this);
      Register(fOuterSupportTub);
      fOuterSupportTub->InstallIn(this);
      SetDaughter(fOuterSupportTub);
    
      fInnerSupportTub = new J4CDCSupportTub(itubIR, itubOR, tublen, 
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

void J4CDC::InstallIn(J4VComponent         *mother,
                      G4RotationMatrix     *prot, 
                      const G4ThreeVector  &tlate ) 
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
