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
#include <math.h>

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

   for ( int i = 0; i < _QC1NCOLLAR_ ; i++){
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
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".Coil";
    // define geometry
     G4VSolid *qc1coil = new G4Tubs( name, 
    		_QC1INRADIUS_COIL_,
    		_QC1INRADIUS_COIL_+_QC1THICK_COIL_,
                _QC1ZLEN_/2., 
	        0.,2.*pi );  
     Register(qc1coil);
     SetSolid(qc1coil);	// Don't forgat call it!

    // MakeLogicalVolume -------------
     MakeLVWith(OpenMaterialStore()->Order(_QC1MAT_COIL_));
    // SetVisAttribute ---------------
     PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(0, 1, 1));

    // Install daughter PV -----------
     fcollar = new J4IRQC1Collar*[_QC1NCOLLAR_];
     Register(fcollar);

     for(int i = 0; i < _QC1NCOLLAR_ ; i++){
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
  rotM->rotateZ((_QC1PHI_COIL_+_QC1DPHI_COIL_)+90.*degree*GetMyID());
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

	
	

