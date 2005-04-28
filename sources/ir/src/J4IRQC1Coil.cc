// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1Coil
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*************************************************************************

#include "J4IRQC1Coil.hh"


#include "G4Tubs.hh"
#include <cmath>

#include "J4IRQC1ParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRQC1Coil::fName("IRQC1Coil");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1Coil::J4IRQC1Coil(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
			       G4int  copyno):
            J4VIRAcceleratorComponent( fName, parent, nclones,
				       nbrothers, me, copyno  ) 
{   
}
//=====================================================================
//* destructor --------------------------------------------------------

J4IRQC1Coil::~J4IRQC1Coil()
{
  J4IRQC1ParameterList* qc1List=J4IRQC1ParameterList::GetInstance();
  G4int    qc1NCollar         = qc1List->GetQC1NCollar();
  //for ( int i = 0; i < _QC1NCOLLAR_ ; i++){
  for ( int i = 0; i < qc1NCollar ; i++){
      if (Deregister(fcollar[i]) ) delete fcollar[i];
    }
    if (Deregister(fcollar) ) delete[] fcollar;

}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRQC1Coil::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  J4IRQC1ParameterList* qc1List=J4IRQC1ParameterList::GetInstance();
  G4double qc1COILInnerRadius = qc1List->GetQC1CollarRadius();
  G4double qc1COILThickness   = qc1List->GetQC1CollarThick();
  G4double qc1COILZLength     = qc1List->GetQC1ZLength();
  G4String qc1COILMaterial    = qc1List->GetQC1CoilMaterial();
  G4int    qc1NCollar         = qc1List->GetQC1NCollar();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Coil";
    // define geometry
    //     G4VSolid *qc1coil = new G4Tubs( name, 
    //    		_QC1INRADIUS_COIL_,
    //    		_QC1INRADIUS_COIL_+_QC1THICK_COIL_,
    //                _QC1ZLEN_/2., 
    //	        0.,2.*pi );  
    G4VSolid *qc1coil = new G4Tubs( name, 
        		qc1COILInnerRadius,
        		qc1COILInnerRadius+qc1COILThickness,
                   qc1COILZLength/2., 
    	        0.,2.*pi );  

     Register(qc1coil);
     SetSolid(qc1coil);	// Don't forgat call it!

    // MakeLogicalVolume -------------
     MakeLVWith(OpenMaterialStore()->Order(qc1COILMaterial));
    // SetVisAttribute ---------------
     PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 1, 1));

    // Install daughter PV -----------
     //fcollar = new J4IRQC1Collar*[_QC1NCOLLAR_];
     fcollar = new J4IRQC1Collar*[qc1NCollar];
     Register(fcollar);

     //for(int i = 0; i < _QC1NCOLLAR_ ; i++){
     for(int i = 0; i < qc1NCollar ; i++){
       fcollar[i] = new J4IRQC1Collar(this,1,4,i,-1);
       Register(fcollar[i]);
       fcollar[i]->InstallIn(this);
       SetDaughter(fcollar[i]);
     }

#if 0    
    fqlayer = new J4IRQC1QLayer*[_QC1NLAYER_COIL_];
    Register(fqlayer);
    for ( int i = 0; i < _QC1NLAYER_COIL_ ; i++){
      fqlayer[i] = new J4IRQC1QLayer(this,1,4,i,-1);
      Register(fqlayer[i]);
      fqlayer[i]->InstallIn(this);
      SetDaughter(fqlayer[i]);
    }
#endif
  }     
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRQC1Coil::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  J4IRQC1ParameterList* qc1List=J4IRQC1ParameterList::GetInstance(); 
  G4double phi = qc1List->GetQC1CollarPhi();
  G4double dphi = qc1List->GetQC1CollarDPhi();
    //rotM->rotateZ((_QC1PHI_COIL_+_QC1DPHI_COIL_)+90.*degree*GetMyID());
  rotM->rotateZ((phi+dphi)+90.*degree*GetMyID());
  return rotM;
}
//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4IRQC1Coil::Cabling()
{
}
//=====================================================================
//* Draw  --------------------------------------------------------
void J4IRQC1Coil::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4IRQC1Coil::Print() const
{
}

	
	

