// $Id$
//*************************************************************************
//* --------------------
//* J4IT
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IT.hh"
#include "J4ITParameterList.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IT::fFirstName("IT");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IT::J4IT(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VITDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IT::~J4IT()
{
  J4ITParameterList *list = OpenParameterList(); 
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

void J4IT::Assemble() 
{   
  if(!GetLV()){
  	

    static G4double kEpsilon = 0.1*mm;

    J4ITParameterList *list = OpenParameterList(); 
    G4double rmin   = list->GetITInnerR(); 
    G4double rmax   = list->GetITOuterR() + kEpsilon;
    G4double lenmax = list->GetITHalfZ();
    G4double lenmin = list->GetLayerHalfZ(0);
    G4double dphi   = list->GetITDeltaPhi();
    G4double ethick = (lenmax-lenmin)/2;
    G4double lrmin  = rmax - kEpsilon;
    G4double rrmin  = rmax - kEpsilon;
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, lenmax, dphi, 
                  ethick, rmin, DBL_MAX, lrmin, rrmin);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetITMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetITVisAtt(), list->GetITColor());
  	
    // Install daughter PV //
    // Install Layer       //
  		  
    G4int  nlayers = list->GetNlayers();
    fLayers = new J4ITLayer* [nlayers];
    Register(fLayers);
    G4int i;  
    for (i = 0; i < nlayers ; i++) {
      fLayers [i] = new J4ITLayer(this, 1 , nlayers , i );
      Register(fLayers[i]);
      fLayers [i]->InstallIn(this);  
      
      SetDaughter(fLayers[i]);
    }  
      
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IT::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4IT::InstallIn(J4VComponent         * /* mother */,
                     G4RotationMatrix     * /* prot */  , 
                     const G4ThreeVector  & /* tlate */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}



//* Draw  --------------------------------------------------------
void J4IT::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IT::Print() const
{
}
