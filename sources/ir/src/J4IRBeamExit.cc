// $Id$
//*************************************************************************
//* --------------------
//* J4IRBeamExit
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRBeamExit.hh"

#include "G4Tubs.hh"
#include <cmath>

#include "J4IRQC1ParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRBeamExit::fName("IRBeamExit");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBeamExit::J4IRBeamExit(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,
		                          G4bool reflect) :
              J4VIRAcceleratorComponent( fName, parent, nclones,
					 nbrothers, me, copyno,reflect  )
{   
}
//=====================================================================
//* destructor --------------------------------------------------------

J4IRBeamExit::~J4IRBeamExit()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBeamExit::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  J4IRQC1ParameterList* qc1List=new J4IRQC1ParameterList(OpenParameterList()); 
  G4double Rin = 0.*mm;
  G4double Rout= 10.*mm;
  G4double ZLength     = qc1List->GetQC1ZLength();
  G4String Material    = "vacuum";
  	
   // MakeSolid ---------------
    G4String name( GetName() );
    name += ".master";
    G4VSolid *tube = new G4Tubs( name,
				 Rin,
    				    Rout,
                                    ZLength/2.+0.1*cm, 0, 2*M_PI);  
                                       
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(Material));
    
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 0, 0));

    // Install daughter PV -----------
  }
}


//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRBeamExit::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBeamExit::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  J4IRParameterList* list = OpenParameterList();
  rotM->rotateY( -1.*(list->GetCrossAngle()));
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBeamExit::GetTranslation(){
  J4IRQC1ParameterList* qc1List=new J4IRQC1ParameterList(OpenParameterList()); 
  G4double qc1ZLength     = qc1List->GetQC1ZLength();
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRParameterList* list = OpenParameterList();
  G4double angle = list->GetCrossAngle();
  G4double zpos  = list->GetLStar()+qc1ZLength/2.;
  position->setX( zpos*std::sin(angle));
  position->setZ( zpos*std::cos(angle));
  return *position;
}


#if 0
//=====================================================================
void J4IRBeamExit::InstallIn(J4VIRAcceleratorComponent *mother,
                             G4RotationMatrix     *prot, 
                             const G4ThreeVector  &tlate )
{ 
  J4VIRAcceleratorComponent::InstallIn(mother,prot,tlate);
}
#endif
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRBeamExit::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRBeamExit::Print() const
{
}

	
	

