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
#include "G4Cons.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "J4UnionSolid.hh"
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
#if 0
  if (fLayers) {  
    G4int i; 
    for (i = 0; i < OpenParameterList()->GetNLayers() ; i++) {
     if(Deregister(fLayers[i])) delete fLayers [i];
    }
    if (Deregister(fLayers)) delete [] fLayers;
  }
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTX::Assemble() 
{   

  J4VTXParameterList* list = OpenParameterList();

  if(!GetLV()){

    //--- Assemble Master volume for VTX ----
    G4String vtxname(GetName());
    G4VSolid* lastsolid;
    G4String tmpname = vtxname+".master";

#if 1
    // New Master
     G4int nlayer = list->GetNLayers();
    G4double rin,rout;
    for ( G4int i = 0 ; i < nlayer; i++ ){
      if ( i == 0 ){
	rin  = list->GetVTXInnerRadius();
	if ( (i+1) == nlayer ) rout = list->GetVTXOuterRadius();
	else rout = list->GetLayerInnerRadius(i+1)-3*mm;	
      }else if ( i < nlayer-1 ){
	rin  = list->GetLayerInnerRadius(i)-5*mm;
	rout = list->GetLayerInnerRadius(i+1)-3*mm;
      }else {
	rin  = list->GetLayerInnerRadius(i)-5*mm;
	rout = list->GetVTXOuterRadius();
      }
      G4double z   = list->GetLayerZLength(i);
      G4String tmptube = vtxname+".tube";

      G4VSolid* tube = new G4Tubs(tmptube,rin,rout,z/2.,0.,twopi);
      if ( i == 0 ) {
	lastsolid = tube;
      }else {
	lastsolid = new J4UnionSolid(vtxname,lastsolid,tube);
      }
    }
#endif

    Register(lastsolid);
    SetSolid(lastsolid);

    // MakeLogicalVolume --//
    MakeLVWith(OpenMaterialStore()->Order(list->GetVTXMaterial()));
    // SetVisAttribute ----//
    PaintLV(list->GetVTXVisAtt(), list->GetVTXColor());

#if 1
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

#endif
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

	
	

