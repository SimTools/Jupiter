// $Id$
//*************************************************************************
//* --------------------
//* J4SOLMField
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4SOLMField.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4SOLMField::J4SOLMField(J4SOLParameterList* list)
            :J4VMField(), fParameterList(list)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------
J4SOLMField::~J4SOLMField()
{
}

//=====================================================================
void J4SOLMField::GetLocalFieldValue(G4ThreeVector &position,
                                     G4ThreeVector &bfield,
                                     G4bool        &onlyFlag)
{

  onlyFlag = false;
	
  G4double maxBRad    = fParameterList->GetOR();
  G4double maxBZ      = fParameterList->GetLength();
  G4double zBfield    = fParameterList->GetBField();	
  G4double maxBRad_sq = maxBRad * maxBRad;
  
  if(  abs(position.z()) < maxBZ 
       && (sqr(position.x())+sqr(position.y())) < maxBRad_sq ) {  
     bfield.setZ(zBfield); 
  }
}

//=====================================================================
void J4SOLMField::GetLocalValidBox(G4double* lpos){

  lpos[0] = fParameterList->GetOR();
  lpos[1] = fParameterList->GetOR();
  lpos[2] = fParameterList->GetLength();


  return;
}
//=====================================================================

