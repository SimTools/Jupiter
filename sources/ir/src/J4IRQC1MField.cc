// $Id$
//*************************************************************************
//* --------------------
//* J4IRQC1MField
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*	2002/12/05  T.Aso	k1 and Beam energy is given via  Constructor
//*************************************************************************

#include "J4IRQC1MField.hh"
#include "J4IRQC1ParameterList.hh"
#include "J4IRParameterList.hh"
//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQC1MField::J4IRQC1MField(G4double beamE, G4double k):J4VMField()
{   
  J4IRQC1ParameterList* qc1List=
    new J4IRQC1ParameterList(J4IRParameterList::GetInstance()); 
  fqc1ZLength     = qc1List->GetQC1ZLength();
  fqc1InnerRadius     = qc1List->GetQC1Radius();
  fqc1Thickness     = qc1List->GetQC1Thick();

  //G4double fBeamEnergy = 250.*GeV;
  //G4double fK1Value = -0.1295329270206;
  G4double fBeamEnergy = beamE;
  G4double fK1Value = k;
  //G4double Zlen = _QC1ZLEN_;
  G4double Zlen = fqc1ZLength;

  G4double ebinGeV = fBeamEnergy/GeV;
  G4double len = Zlen/meter;
  G4double k1 = fK1Value;
  fGradient = k1*ebinGeV/0.3/len * ( tesla/meter );
  G4cout << "DDDDDDDDDDDDDDDDDDDDDD  " << fGradient*meter/tesla << G4endl;
}

//=====================================================================
//* constructor -------------------------------------------------------
J4IRQC1MField::J4IRQC1MField(G4double beamE, G4double grad, G4String tag):J4VMField()
{   
  fGradient = grad;
  G4cout << tag << "DDDDDDDDDDDDDDDDDDDDDD  " << fGradient*meter/tesla << G4endl;
}

//=====================================================================
//* destructor --------------------------------------------------------
J4IRQC1MField::~J4IRQC1MField()
{
}

//=====================================================================
void J4IRQC1MField::GetLocalFieldValue(G4ThreeVector& lpos,
				       G4ThreeVector& lb,
				       G4bool& onlyFlag){
  onlyFlag = FALSE;
  lb.set(0.,0.,0.);
  //  if ( abs(lpos.z()) < _QC1ZLEN_/2  ){
  if ( abs(lpos.z() )< fqc1ZLength/2. ){
    G4double radius2 = sqr(lpos.x())+sqr(lpos.y());
    //    if( radius2 < sqr(_QC1INRADIUS_+_QC1THICK_) ){
    if( radius2 < sqr(fqc1InnerRadius+fqc1Thickness) ){
      onlyFlag = TRUE;
      //      if( radius2 < sqr(_QC1INRADIUS_) ){
      if( radius2 < sqr(fqc1InnerRadius) ){
	lb.set(fGradient*lpos.y(),fGradient*lpos.x(),0.);
      }
    }
  }
}

//=====================================================================
void J4IRQC1MField::GetLocalValidBox(G4double* Lpos){

  //Lpos[0] = _QC1INRADIUS_+_QC1THICK_+0.5*cm;
  //Lpos[1] = _QC1INRADIUS_+_QC1THICK_+0.5*cm;
  //Lpos[2] = _QC1ZLEN_/2.+0.5*cm;  
  Lpos[0] = fqc1InnerRadius+fqc1Thickness+0.5*cm;
  Lpos[1] = fqc1InnerRadius+fqc1Thickness+0.5*cm;
  Lpos[2] = fqc1ZLength/2.+0.5*cm;  
  return;
}

//=====================================================================




