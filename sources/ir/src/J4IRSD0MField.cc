// $Id$
//*************************************************************************
//* --------------------
//* J4IRSD0MField
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/12  T.Aso	Original version.
//*	2002/12/05  T.Aso	k1 and Beam energy is given via  Constructor
//*************************************************************************

#include "J4IRSD0MField.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRSD0MField::J4IRSD0MField(G4double beamE, G4double k):J4VMField()
{   
  //G4double fBeamEnergy = 250.*GeV;
  //G4double fK2Value = -2.249174;
  G4double fBeamEnergy = beamE;
  G4double fK2Value = k;

  G4double Zlen = _SD0ZLEN_;
  G4double ebinGeV = fBeamEnergy/GeV;
  G4double len = Zlen/meter;
  G4double k2 = fK2Value;
  fGradient = k2*ebinGeV/0.3/len * ( tesla/meter );

}

//=====================================================================
//* destructor --------------------------------------------------------
J4IRSD0MField::~J4IRSD0MField()
{
}

//=====================================================================
void J4IRSD0MField::GetLocalFieldValue(G4ThreeVector& lpos,
				       G4ThreeVector& lb,
				       G4bool& onlyFlag){
  onlyFlag = FALSE;
  lb.set(0.,0.,0.);
  if ( std::abs(lpos.z()) < _SD0ZLEN_/2  ){
    G4double radius2 = lpos.x()*lpos.x()+lpos.y()*lpos.y(); 
    if( std::sqrt(radius2)<(_SD0INRADIUS_+_SD0THICK_)){
      onlyFlag = true;
      if( radius2 < sqr(_SD0INRADIUS_) ){
	lb.set(fGradient*lpos.x()*lpos.y(),
	       fGradient/2*(lpos.x()*lpos.x()-lpos.y()*lpos.y()),0.);
      }
    }
  }
}

//=====================================================================
void J4IRSD0MField::GetLocalValidBox(G4double* Lpos){

  Lpos[0] = _SD0INRADIUS_+_SD0THICK_+0.5*cm;
  Lpos[1] = _SD0INRADIUS_+_SD0THICK_+0.5*cm;
  Lpos[2] = _SD0ZLEN_/2.+0.5*cm;  

  return;
}

//=====================================================================

