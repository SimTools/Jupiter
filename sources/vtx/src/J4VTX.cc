// $Id$
//*************************************************************************
//* --------------------
//* J4VTX
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/11/19  T.Aso       Modify to use ParameterList.
//*************************************************************************

#include "J4VTX.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4VTX::fFirstName("VTX");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VTX::J4VTX(J4VDetectorComponent *parent ,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno ) :
       J4VVTXDetectorComponent( fFirstName, parent, 1,1,0,copyno)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTX::~J4VTX()
{
  if (fLayers) {  
    G4int i; 
    for (i = 0; i < OpenParameterList()->GetNLayers() ; i++) {
     if(Deregister(fLayers[i])) delete fLayers [i];
    }
    if (Deregister(fLayers)) delete [] fLayers;
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTX::Assemble() 
{   

  J4VTXParameterList* list = OpenParameterList();

  if(!GetLV()){

    //--- Assemble Master volume for VTX ----
    G4double rmin = list->GetVTXInnerRadius();
    G4double rmax = list->GetVTXOuterRadius();
    G4double len  = list->GetVTXZLength()/2.;
    G4double dphi = twopi;
 	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    // MakeLogicalVolume --//
    MakeLVWith(OpenMaterialStore()->Order(list->GetVTXMaterial()));
    // SetVisAttribute ----//
    PaintLV(list->GetVTXVisAtt(), list->GetVTXColor());

    // Install daughter PV //
    // Install Layer       //
    G4int nlayers = list->GetNLayers();
    fLayers = new J4VTXLayer* [nlayers];
    Register(fLayers);
    for (G4int i = 0; i < nlayers; i++) {
      fLayers[i] = new J4VTXLayer(this,nlayers , i );
      Register(fLayers[i]);
      fLayers[i]->InstallIn(this);  
      SetDaughter(fLayers[i]);
      fLayers[i]->Print();
    }  
    Print();
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTX::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTX::InstallIn(J4VComponent         *mother,
                      G4RotationMatrix     *prot, 
                      const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4VTX::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTX::Print() const
{
}

	
	

