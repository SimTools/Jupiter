// $Id$
//*************************************************************************
//* --------------------
//* J4IRQMField
//* --------------------
//* (Description)
//* 	Provide magnetic field produced by QC.
//*     
//* (Update Record)
//*	2005/07/24  A.Miyamoto  Original version created from the T.Aso's code.
//*************************************************************************

#include "J4IRQMField.hh"
#include "J4SOLParameterList.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRQMField::J4IRQMField(G4double beamE, G4double k, 
	G4double rmin, G4double rmax, G4double zlength ):J4VMField()
{   

  fRmin = rmin;
  fRmax = rmax;
  fZlength = zlength;

  //G4double fBeamEnergy = 250.*GeV;
  //G4double fK1Value = -0.1295329270206;
  G4double fBeamEnergy = beamE;
  G4double fK1Value = k;
  //G4double Zlen = _QC1ZLEN_;

  G4double ebinGeV = fBeamEnergy/GeV;
  G4double len = fZlength/meter;
  G4double k1 = fK1Value;
  fGradient = k1*ebinGeV/0.3/len * ( tesla/meter );
  G4cout << "DDDDDDDDDDDDDDDDDDDDDD  " << fGradient*meter/tesla << G4endl;
}

//=====================================================================
//* constructor -------------------------------------------------------
/*
J4IRQC1MField::J4IRQC1MField(G4double,       // beamE
                             G4double grad, 
                             G4String tag) 
             : J4VMField()
{   
  fGradient = grad;
//  G4cout << tag << "DDDDDDDDDDDDDDDDDDDDDD  " << fGradient*meter/tesla << G4endl;
}
*/

//=====================================================================
//* destructor --------------------------------------------------------
J4IRQMField::~J4IRQMField()
{
}

//=====================================================================
void J4IRQMField::GetLocalFieldValue(G4ThreeVector& lpos,
				       G4ThreeVector& lb,
				       G4bool& onlyFlag){
  onlyFlag = FALSE;
  lb.set(0.,0.,0.);

  if ( std::abs(lpos.z() )< fZlength/2. ){
    G4double radius2 = sqr(lpos.x())+sqr(lpos.y());
    //    if( radius2 < sqr(_QC1INRADIUS_+_QC1THICK_) ){
    if( radius2 < fRmax ){
      onlyFlag = TRUE;
      //      if( radius2 < sqr(_QC1INRADIUS_) ){
      if( radius2 < fRmin ){
	lb.set(fGradient*lpos.y(),fGradient*lpos.x(),0.);
//
//  Subtract solenoid field to cancel its effect.
//
        J4SOLParameterList *spar=J4SOLParameterList::GetInstance();
        if( std::abs(lpos.z()) < spar->GetSOLHalfZ() ) {
          G4ThreeVector sol(0, 0, - spar->GetBField() );
          lb -= sol;
        }
      }
    }
  }
}

//=====================================================================
void J4IRQMField::GetLocalValidBox(G4double* Lpos)
{
  //Lpos[0] = _QC1INRADIUS_+_QC1THICK_+0.5*cm;
  //Lpos[1] = _QC1INRADIUS_+_QC1THICK_+0.5*cm;
  //Lpos[2] = _QC1ZLEN_/2.+0.5*cm;  
//  Lpos[0] = fqc1InnerRadius+fqc1Thickness+0.5*cm;
//  Lpos[1] = fqc1InnerRadius+fqc1Thickness+0.5*cm;
//  Lpos[2] = fqc1ZLength/2.+0.5*cm;  
  Lpos[0] = fRmax;
  Lpos[1] = fRmax;
  Lpos[2] = fZlength*0.5;  
 return;
}

//=====================================================================




