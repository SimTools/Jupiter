// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1.hh"

#include "G4Tubs.hh"
#include <math.h>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1::fName("IRQC1");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1::J4IRQC1(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,
		                          G4bool reflect) :
              J4VIRAcceleratorComponent( fName, parent, nclones,
					 nbrothers, me, copyno,reflect  ),
	      J4AttMFieldMap()
{   
}
//=====================================================================
//* destructor --------------------------------------------------------

J4IRQC1::~J4IRQC1()
{
  if (Deregister(fsus)) delete fsus;
  if (Deregister(fcoil)) delete fcoil;
  if (Deregister(fcool) ) delete fcool;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
   // MakeSolid ---------------
    G4String qc1name( GetName() );
    qc1name += ".master";
    G4VSolid *qc1tube = new G4Tubs( qc1name,
				    0.,
				   _QC1INRADIUS_+_QC1THICK_,
                                     _QC1ZLEN_/2.+0.1*cm, 0, 2*M_PI);  
                                       
    Register(qc1tube);
    SetSolid(qc1tube);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_));
    
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(1, 0, 0));

    // Install daughter PV -----------
    fsus = new J4IRQC1SUS(this,1,1,0,-1);
    Register (fsus);
    fsus->InstallIn(this);
    SetDaughter(fsus);
#if 1
    fcoil = new J4IRQC1Coil(this,1,1,0,-1);
    Register(fcoil);
    fcoil->InstallIn(this);
    SetDaughter(fcoil);
#endif
#if 1
    fcool = new J4IRQC1Cooling(this,1,1,0,-1);
    Register(fcool);
    fcool->InstallIn(this);
    SetDaughter(fcool);
#endif
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRQC1::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  J4IRParameterList* list = OpenParameterList();
  rotM->rotateY(list->GetCrossAngle());
  //rotM->rotateY(_IRCROS_);
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRQC1::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  J4IRParameterList* list = OpenParameterList();
  G4double angle = list->GetCrossAngle();
  G4double zpos  = list->GetLStar()+_QC1ZLEN_/2.;
  position->setX(-zpos*sin(angle));
  position->setZ( zpos*cos(angle));
  //position->setX(-(_QC1ZPOS_+_QC1ZLEN_/2.)*sin(_IRCROS_));
  //position->setZ( (_QC1ZPOS_+_QC1ZLEN_/2.)*cos(_IRCROS_));
  return *position;
}


//=====================================================================
void J4IRQC1::InstallIn(J4VIRAcceleratorComponent *mother,
                             G4RotationMatrix     *prot, 
                             const G4ThreeVector  &tlate )
{ 
  J4VIRAcceleratorComponent::InstallIn(mother,prot,tlate);
  InstallMField(this);
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1::Print() const
{
}

	
	

