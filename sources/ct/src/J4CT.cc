// $Id$
//*************************************************************************
//* --------------------
//* J4CT
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CT.hh"
#include "J4CTParameterList.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CT::fFirstName("CT");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CT::J4CT(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VCTDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ),
      fSupportTub(0), fOuterCylinder(0), fEndcaps(0), fLayers(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CT::~J4CT()
{

  if (Deregister(fSupportTub)) delete fSupportTub;
  if (Deregister(fOuterCylinder)) delete fOuterCylinder;
   
  if (fEndcaps) {
     for (G4int i = 0; i < 2 ; i++) {
         if(Deregister(fEndcaps[i])) delete fEndcaps [i];
      }
     if (Deregister(fEndcaps)) delete [] fEndcaps;
  }

  J4CTParameterList *list = OpenParameterList(); 
  if (fLayers){	
    G4int i;  
    for (i = 0; i < list->GetNlayers(); i++) {
     if(Deregister(fLayers[i])) delete fLayers [i];
    } 
    if (Deregister(fLayers)) delete [] fLayers;
  }

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CT::Assemble() 
{   
  if(!GetLV()){
  	
    J4CTParameterList *list = OpenParameterList(); 
    G4double rmin = list->GetCTInnerR(); 
    G4double rmax = list->GetCTOuterR();
    G4double len  = list->GetCTHalfZ();
    G4double dphi = list->GetCTDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetCTMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetCTVisAtt(), list->GetCTColor());
  	
    // Install daughter PV //

    // Install Support Tube //
    G4double supportTubIR=list->GetSupportTubInnerR();
    G4double supportTubOR=list->GetSupportTubOuterR();
    G4double supportTubHZ=list->GetSupportTubHalfZ();
    G4double supportTubDphi=list->GetSupportTubDeltaPhi();

    fSupportTub = new J4CTSupportTub(supportTubIR, supportTubOR,
				     supportTubHZ, supportTubDphi, this);
    Register(fSupportTub);
    fSupportTub->InstallIn(this);
    SetDaughter(fSupportTub);

    // Install Outer Cylinder  //
    G4double outerCylinderIR=list->GetOuterCylinderInnerR();
    G4double outerCylinderOR=list->GetOuterCylinderOuterR();
    G4double outerCylinderHZ=list->GetOuterCylinderHalfZ();
    G4double outerCylinderDphi=list->GetOuterCylinderDeltaPhi();

    fOuterCylinder = new J4CTOuterCylinder(outerCylinderIR, outerCylinderOR,
				     outerCylinderHZ, outerCylinderDphi, this);
    Register(fOuterCylinder);
    fOuterCylinder->InstallIn(this);
    SetDaughter(fOuterCylinder);

    // Install EndCaps  //
    fEndcaps = new J4CTEndcap* [2];
    Register(fEndcaps);
    for(G4int i=0;i<2;i++){
      fEndcaps[i]=new J4CTEndcap(this, 1, 2, i);
      Register(fEndcaps[i]);
      fEndcaps[i]->InstallIn(this);
      SetDaughter(fEndcaps[i]);
    }


    // Install Layer       //
  		  
    G4int  nlayers = list->GetNlayers();
    fLayers = new J4CTLayer* [nlayers];
    Register(fLayers);
    G4int i;  
    for (i = 0; i < nlayers ; i++) {
      fLayers [i] = new J4CTLayer(this, 1 , nlayers , i );
      Register(fLayers[i]);
      fLayers [i]->InstallIn(this);  
      SetDaughter(fLayers[i]);
    } 
      
  }

}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CT::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CT::InstallIn(J4VComponent         * /* mother */,
                     G4RotationMatrix     * /* prot   */, 
                     const G4ThreeVector  & /* tlate  */) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}



//* Draw  --------------------------------------------------------
void J4CT::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CT::Print() const
{
}

	
	
