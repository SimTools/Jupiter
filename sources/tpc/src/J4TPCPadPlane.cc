//*************************************************************************
//* --------------------
//* J4TPCPadPlane
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCPadPlane.hh"
#include "J4TPCPadRow.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4TPCPadPlane::fFirstName("PadPlane");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TPCPadPlane::J4TPCPadPlane(J4VDetectorComponent *parent,
                                            G4int  nclones,
                                            G4int  nbrothers, 
                                            G4int  me,
                                            G4int  copyno ) :
               J4VTPCDetectorComponent( fFirstName, parent, nclones,
                                        nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4TPCPadPlane::~J4TPCPadPlane()
{
  J4TPCParameterList *list = OpenParameterList();
  if (fPadRows){
    G4int i;
    for (i = 0; i < list->GetNlayers(); i++) {
     if(Deregister(fPadRows[i])) delete fPadRows [i];
    }
    if (Deregister(fPadRows)) delete [] fPadRows;
  }

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4TPCPadPlane::Assemble() 
{   
  if(!GetLV()){
     J4TPCParameterList *list = OpenParameterList();
     
     G4double rmin = list->GetPadPlaneInnerR();
     G4double rmax = list->GetPadPlaneOuterR();
     G4double len  = list->GetPadPlaneHalfThick();
     G4double dphi = list->GetPadPlaneDeltaPhi();
  	
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi);
    
    // MakeLogicalVolume --//
    G4String material = list->GetPadPlaneMaterial();  
    MakeLVWith(OpenMaterialStore()->Order(material));
        
    // SetVisAttribute ----//
    PaintLV(list->GetPadPlaneVisAtt(), list->GetPadPlaneColor());

  	
    // Install daughter PV //
    // Install PadRow       //
                                                                                
    G4int  npadRows = list->GetNpadRows();
    fPadRows = new J4TPCPadRow* [npadRows];
    Register(fPadRows);

    for (G4int i = 0; i < npadRows; i++) {
      fPadRows [i] = new J4TPCPadRow(this, 1, npadRows, i);
      Register(fPadRows [i]);
      fPadRows [i]->InstallIn(this);
                                                                                
      SetDaughter(fPadRows[i]);
    }
  }       
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4TPCPadPlane::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4TPCPadPlane::InstallIn(J4VComponent         *,
                              G4RotationMatrix     *,
                              const G4ThreeVector  &)
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  G4double z = OpenParameterList()->GetEndcapFrontZ() -
               OpenParameterList()->GetPadPlaneHalfThick();  
               
  G4ThreeVector tlate(0., 0., z );
  SetPVPlacement(0, tlate); 
  
}

//* Draw  --------------------------------------------------------
void J4TPCPadPlane::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4TPCPadPlane::Print() const
{
}

