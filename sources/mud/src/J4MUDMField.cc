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
J4MUDMField::J4MUDMField( J4MUDParameterList* list )
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

  G4double mudR            = fParameterList->GetMUDOuterR();
  G4double innerR          = fParameterList->GetMUDEndcapInnerR();
  G4double frontEndcapR    = fParameterList->GetFrontEndcapOuterR();
  G4double barrelR         = fParameterList->GetBarrelInnerR();
  G4double barrelZ         = fParameterList->GetBarrelFrontHalfL();
  G4double mudZ            = fParameterList->GetMUDHalfL();
  G4double posZ            = std::abs( position.z() );
  G4double posR            = sqrt( sqr( position.x() ) + sqr( position.y() ) );
  G4double diagonalTan     = mudR / mudZ;
  G4double endcapTan       = frontEndcapR / ( mudZ - barrelZ );

  G4double barrelField     = fParameterList->GetBarrelBField();
  G4double cornerField     = fParameterList->GetCornerBField();  
  G4double endcapField     = fParameterList->GetEndcapBField();
  G4double returnField     = fParameterList->GetReturnBField();

  const G4ThreeVector& endcapPos     = position - position.project(); // pos_xy = pos - pos_z
  const G4ThreeVector& endcapPosUnit = endcapPos.unit();              // Unit vector parellel of pos_xy
  const G4ThreeVector& bEndcap       = endcapField * endcapPosUnit;   // 

  //**** Magentic field direction/magnitude setup

  // Barrel part to diagonal part
  // B_vec = B*( 0, 0, -1 )
  if ( posZ < barrelZ && posR > barrelR && posR < mudR ) {
   bfield.setX( 0. );
   bfield.setY( 0. );
    bfield.setZ( -barrelField );
  }
  
  // Barrel part to diagonal part
  // B_vec = B*( 0, 0, -1 )
  if ( posZ > barrelZ && posR / posZ > diagonalTan && posR > barrelR && posR < mudR ) {
    bfield.setX( 0. );
    bfield.setY( 0. );
    bfield.setZ( -cornerField );
  }
  
  // Diagonal part to endcap part and z position > 0
  // B_vec = B*( sin(phi), cos(phi), 0 )
  if ( position.z() > 0  && posR / posZ < diagonalTan && posR / (mudZ-posZ) > endcapTan && posZ < mudZ && posZ > barrelZ ) {
    bfield.setX( bEndcap.x() );
    bfield.setY( bEndcap.y() );
    bfield.setZ( 0. );
  }

  // Diagonal part to endcap part and z position > 0
  // B_vec = B*( -sin(phi), -cos(phi), 0 )
  if ( position.z() < 0  && posR / posZ < diagonalTan && posR / (mudZ-posZ) > endcapTan && posZ < mudZ && posZ > barrelZ ) {
    bfield.setX( -bEndcap.x() );
    bfield.setY( -bEndcap.y() );
    bfield.setZ( 0. );
  }

  // endcap part to frontEndcap part and z position > 0, B_z direction > 0
  if ( position.z() > 0  && posR / (mudZ-posZ) < endcapTan && posZ > barrelZ && posR > innerR ) {
    bfield.setX(0.);
    bfield.setY(0.);    
    bfield.setZ( returnField );
  }

  // endcap part to frontEndcap part and z position < 0, B_y direction < 0
  if ( position.z() < 0  && posR / (mudZ-posZ) < endcapTan && posZ > barrelZ && posR > innerR ) {
    bfield.setX(0.);
    bfield.setY(0.);        
    bfield.setY( -returnField );
  }
  
}

//=====================================================================
void J4MUDMField::GetLocalValidBox( G4double* lpos ) {

  lpos[0] = fParameterList->GetMUDOuterR();
  lpos[1] = fParameterList->GetMUDOuterR();
  lpos[2] = fParameterList->GetMUDHalfL();  

}
