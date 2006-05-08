// $Id$
#ifndef __J4CLXENDCAPHD__
#define __J4CLXENDCAPHD__
//*************************************************************************
//* --------------------
//* J4CLXEndcapHD
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
class J4CLXEndcapHD : public J4VCLXBlock {  

public:
  J4CLXEndcapHD( J4VDetectorComponent *parent   = 0,
		 G4int  nclones   = 1,
		 G4int  nbrothers = 1,
		 G4int  me        = 0,
		 G4int  copyno    = -1 );

  J4CLXEndcapHD( const J4CLXEndcapHD& orig, G4int copyno );
  
  virtual ~J4CLXEndcapHD();

  virtual G4String GetFirstName () const { return fgFirstName; }
  virtual G4double GetYmin      ( G4int i = 0 ) ;  
  virtual G4double GetYmax      ( G4int i = 0 ) ;
  virtual G4double GetHalfZ     ( G4int i = 0 ) ;
  virtual G4int    GetNLayers   ();
  virtual G4int    IsEndcap     ();
  virtual G4bool   IsEM         ();

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
inline G4bool J4CLXEndcapHD::IsEM()
{
  return false;
}

inline G4int J4CLXEndcapHD::GetNLayers()
{
  return OpenParameterList()->GetHDNLayers();
}

inline G4int J4CLXEndcapHD::IsEndcap()
{
  //* Placement case
  //return ( GetMyID() < OpenParameterList()->GetNTraps() ) ? 1 : -1;
  return ( GetCopyNo() < OpenParameterList()->GetNTraps() ) ? 1 : -1;  
}

inline G4double J4CLXEndcapHD::GetYmin( G4int )
{
  return OpenParameterList()->GetEndcapInnerR();
}

inline G4double J4CLXEndcapHD::GetYmax( G4int )
{
  return OpenParameterList()->GetHDYmax();
}

inline G4double J4CLXEndcapHD::GetHalfZ( G4int )
{
  return 0.5*OpenParameterList()->GetHDThickness();
}

#endif
