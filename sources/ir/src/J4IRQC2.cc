// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC2
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC2.hh"
#include "J4IRQC1ParameterList.hh"


#include "G4Box.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC2::fName("IRQC2");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC2::J4IRQC2(J4VAcceleratorComponent *parent,
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

J4IRQC2::~J4IRQC2()
{
  int i;
  for ( i = 0; i < _QC2NIRON1_ ; i++){
    if ( Deregister(firon1[i])) delete firon1[i];
  }
  if (Deregister(firon1)) delete[] firon1;
  for ( i = 0; i < _QC2NIRON2_ ; i++){
    if ( Deregister(firon2[i])) delete firon2[i];
  }
  if (Deregister(firon2)) delete[] firon2;
  for ( i = 0; i < _QC2NIRON3_ ; i++){
    if ( Deregister(firon3[i])) delete firon3[i];
  }
  if (Deregister(firon3)) delete[] firon3;

  for ( i = 0; i < _QC2NCOIL_ ; i++){
    if (Deregister(fcoil[i])) delete fcoil[i];
  }
  if (Deregister(fcoil)) delete[] fcoil;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC2::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String qc2name( GetName() );
    qc2name += ".master";
    G4VSolid *qc2box = new G4Box( qc2name, _QC2HBOX_/2.,
				   _QC2VBOX_/2.,
                                   _QC2ZLEN_/2.+0.1*cm);  

    Register(qc2box);
    SetSolid(qc2box);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_QC2MAT_));
    
    // SetVisAttribute ---------------
//    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(1, 0, 1));
    J4IRQC1ParameterList *qc1List=J4IRQC1ParameterList::GetInstance();
    PaintLV(qc1List->GetQC1VisAtt(), G4Color(1,0,1));
  	
    // Install daughter PV -----------
    firon1 = new J4IRQC2Iron1*[_QC2NIRON1_];
    Register(firon1);
    for ( int i = 0; i < _QC2NIRON1_; i++){
      firon1[i] = new J4IRQC2Iron1(this,1,2,i,-1);
    Register(firon1[i]);
      firon1[i]->InstallIn(this);
      SetDaughter(firon1[i]);
    }
    firon2 = new J4IRQC2Iron2*[_QC2NIRON2_];
    Register(firon2);
    for ( int j = 0; j < _QC2NIRON2_; j++){
      firon2[j] = new J4IRQC2Iron2(this,1,4,j,-1);
      Register(firon2[j]);
      firon2[j]->InstallIn(this);
      SetDaughter(firon2[j]);
    }

    firon3 = new J4IRQC2Iron3*[_QC2NIRON3_];
    Register(firon3);
    for ( int k = 0; k < _QC2NIRON3_; k++ ){
      firon3[k] = new J4IRQC2Iron3(this,1,4,k,-1);
      Register(firon3[k]);
      firon3[k]->InstallIn(this);
      SetDaughter(firon3[k]);
    }

    fcoil = new J4IRQC2Coil*[_QC2NCOIL_];
    Register(fcoil);
    for ( int icoil = 0; icoil < _QC2NCOIL_ ; icoil++){
      fcoil[icoil] = new J4IRQC2Coil(this,1,8,icoil,-1);
      Register(fcoil[icoil]);
      fcoil[icoil]->InstallIn(this);
      SetDaughter(fcoil[icoil]);
    }
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRQC2::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRQC2::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  rotM->rotateY(OpenParameterList()->GetCrossAngle());
  //rotM->rotateY(_IRCROS_);
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRQC2::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  G4double angle = OpenParameterList()->GetCrossAngle();
  position->setX(-(_QC2ZPOS_+_QC2ZLEN_/2.)*std::sin(angle));
  position->setZ( (_QC2ZPOS_+_QC2ZLEN_/2.)*std::cos(angle));
  //position->setX(-(_QC2ZPOS_+_QC2ZLEN_/2.)*std::sin(_IRCROS_));
  //position->setZ( (_QC2ZPOS_+_QC2ZLEN_/2.)*std::cos(_IRCROS_));
  return *position;
}
//* Draw  --------------------------------------------------------
void J4IRQC2::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRQC2::Print() const
{
}

	
	

