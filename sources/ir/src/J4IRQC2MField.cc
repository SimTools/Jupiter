// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC2MField
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*	2002/12/05  T.Aso	k1 and Beam energy is given via  Constructor
//*************************************************************************

#include "J4IRQC2MField.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC2MField::J4IRQC2MField(G4double beamE, G4double k):J4VMField()
{   
  //G4double fBeamEnergy = 250.*GeV;
  //G4double fK1Value = 0.0537249;
  G4double fBeamEnergy = beamE;
  G4double fK1Value = k;

  G4double Zlen = _QC2ZLEN_;
  G4double ebinGeV = fBeamEnergy/GeV;
  G4double len = Zlen/meter;
  G4double k1 = fK1Value;
  fGradient = k1*ebinGeV/0.3/len * ( tesla/meter );

}

//=====================================================================
//* destructor --------------------------------------------------------
J4IRQC2MField::~J4IRQC2MField()
{
}

//=====================================================================
void J4IRQC2MField::GetLocalFieldValue(G4ThreeVector& lpos,
				       G4ThreeVector& lb,
				       G4bool& onlyFlag){
  onlyFlag = FALSE;
  lb.set(0.,0.,0.);
  if ( std::abs(lpos.z()) < _QC2ZLEN_/2  ){
    if( std::abs(lpos.x())< _QC2HBOX_/2. && std::abs(lpos.y()) < _QC2VBOX_/2. ){
      onlyFlag = true;
      G4double radius2 = lpos.x()*lpos.x()+lpos.y()*lpos.y(); 
      if( radius2 < sqr(_QC2INRADIUS_) ){
	lb.set(fGradient*lpos.y(),fGradient*lpos.x(),0.);
      }
    }
  }
}

//=====================================================================
void J4IRQC2MField::GetLocalValidBox(G4double* Lpos){

  Lpos[0] = _QC2HBOX_/2.+0.5*cm;
  Lpos[1] = _QC2VBOX_/2.+0.5*cm;
  Lpos[2] = _QC2ZLEN_/2.+0.5*cm;  
  return;
}

//=====================================================================




