// $Id$
//*************************************************************************
//* --------------------
//* J4MUDMField
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*	2005/05/27  H.Ono	Edited from J4SOLMField.cc
//*************************************************************************

#include "J4MUDMField.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDMField::J4MUDMField(J4MUDParameterList* list)
 : J4VMField(), fParameterList( list )
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDMField::~J4MUDMField() { }

//=====================================================================
void J4MUDMField::GetLocalFieldValue( G4ThreeVector &position,
                                      G4ThreeVector &bfield,
                                      G4bool        &onlyFlag )
{
  onlyFlag = false;
	
  G4double mudR         = fParameterList->GetMUDOuterR();
  G4double innerR       = fParameterList->GetMUDEndcapInnerR();
  G4double frontEndcapR = fParameterList->GetFrontEndcapOuterR();
  G4double barrelR      = fParameterList->GetBarrelInnerR();
  G4double barrelZ      = fParameterList->GetBarrelFrontHalfL();
  G4double mudZ         = fParameterList->GetMUDHalfL();
  G4double magField     = fParameterList->GetBField();
  G4double posZ         = std::abs( position.z() );
  G4double posR         = sqrt( sqr( position.x() ) + sqr( position.y() ) );

  //**** Magentic field direction/magnitude setup

  // Barrel part outer radius position of the SOL, B_z direction < 0 
  if ( posZ < barrelZ && posR > barrelR && posR < mudR ) {
    //**** Opposit direction to the SOL bfield
    bfield.setZ( -magField );
  }
  
  // Endcap part, outer position of SOL, z position > 0, B_y direction > 0  
  if ( position.z() > 0 && posZ > barrelZ && posZ < mudZ && posR > frontEndcapR && posR < mudR ) {
    bfield.setY( magField );
  }
  
  // Endcap part, outer position of SOL, z position < 0, B_y direction < 0  
  if ( position.z() < 0 && posZ > barrelZ && posZ < mudZ && posR > frontEndcapR && posR < mudR ) {
    bfield.setY( -magField );
  }
  
  // Endcap part, inner radius position of the SOL
  if ( posZ > barrelZ && posZ < mudZ && posR > innerR && posR < frontEndcapR ) {
    bfield.setZ( magField );
  }
  
}

//=====================================================================
void J4MUDMField::GetLocalValidBox( G4double* lpos ){

  lpos[0] = fParameterList->GetMUDOuterR();
  lpos[1] = fParameterList->GetMUDOuterR();
  lpos[2] = fParameterList->GetMUDHalfL();  

}
