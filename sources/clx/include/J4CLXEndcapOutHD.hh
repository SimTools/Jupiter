// $Id$
#ifndef __J4CLXEndcapOutHD__
#define __J4CLXEndcapOutHD__
//*************************************************************************
//* --------------------
//* J4CLXEndcapOutHD
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*      2006/05/01 H.Ono Original version
//*************************************************************************
#include "J4VCLXBlock.hh"
#include "J4CLXParameterList.hh"
#include "J4VCLXDetectorComponent.hh"
#include <vector>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXLayer;
class J4CLXEndcapOutHD : public J4VCLXBlock {  

public:
  J4CLXEndcapOutHD( J4VDetectorComponent *parent   = 0,
		 G4int  nclones   = 1,
		 G4int  nbrothers = 1,
		 G4int  me        = 0,
		 G4int  copyno    = -1 );
  
  virtual ~J4CLXEndcapOutHD();

  virtual G4String GetFirstName () const { return fgFirstName; }
  virtual G4double GetYmin      ( G4int i = 0 ) ;  
  virtual G4double GetYmax      ( G4int i = 0 ) ;
  virtual G4double GetHalfZ     ( G4int i = 0 ) ;
  virtual G4int    GetNLayers   ();
  virtual G4int    IsEndcap     ();
  virtual G4bool   IsEM         ();

//  virtual G4String GetMaterial  ();
//  virtual G4bool   GetVisAtt    ();
//  virtual G4Color  GetColor     ();

protected:
  virtual J4VCLXLayer *Create( J4VDetectorComponent *parent = 0,
			       G4int nclones   = 1,
			       G4int nbrothers = 1,
			       G4int me        = 0,
			       G4int copyno    = -1 );

private:
  static const G4String fgFirstName;
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4bool J4CLXEndcapOutHD::IsEM()
{
  return false;
}

inline G4int J4CLXEndcapOutHD::GetNLayers()
{
  return OpenParameterList()->GetHDNLayers();
}

inline G4int J4CLXEndcapOutHD::IsEndcap()
{
  //  return ( GetMyID() < OpenParameterList()->GetNTraps() ) ? 1 : -1;
  return ( GetCopyNo() < OpenParameterList()->GetNTraps() ) ? 1 : -1;  
}

inline G4double J4CLXEndcapOutHD::GetYmin( G4int )
{
  //return OpenParameterList()->GetEndcapInnerR();
  return OpenParameterList()->GetEMYmax();
}

inline G4double J4CLXEndcapOutHD::GetYmax( G4int )
{
  return OpenParameterList()->GetHDYmax();
}

inline G4double J4CLXEndcapOutHD::GetHalfZ( G4int )
{
  return 0.5*( OpenParameterList()->GetHDThickness() + OpenParameterList()->GetEMThickness() );
}

//inline G4String J4CLXEndcapOutHD::GetMaterial()
//{
//  return OpenParameterList()->GetHDMaterial();
//}
//
//inline G4bool J4CLXEndcapOutHD::GetVisAtt()
//{
//  return OpenParameterList()->GetHDVisAtt();
//}
//
//inline G4Color J4CLXEndcapOutHD::GetColor()
//{
//  return OpenParameterList()->GetHDColor();
//}

#endif
