// $Id$
#ifndef __J4CLXENDCAPEM__
#define __J4CLXENDCAPEM__
//*************************************************************************
//* --------------------
//* J4CLXEndcapEM
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*      2006/05/01 H.Ono Original version
//*************************************************************************

#include "J4VCLXBlock.hh"
#include "J4VCLXDetectorComponent.hh"
#include "J4CLXParameterList.hh"
#include <vector>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXLayer;
class J4CLXEndcapEM : public J4VCLXBlock {  

public:
  J4CLXEndcapEM( J4VDetectorComponent *parent   = 0,
		 G4int  nclones   = 1,
		 G4int  nbrothers = 1,
		 G4int  me        = 0,
		 G4int  copyno    = -1 );

  J4CLXEndcapEM( const J4CLXEndcapEM& orig, G4int copyno );
  
  virtual ~J4CLXEndcapEM();

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
inline G4bool J4CLXEndcapEM::IsEM()
{
  return true;
}

inline G4int J4CLXEndcapEM::GetNLayers()
{
  return OpenParameterList()->GetEMNLayers();
}

inline G4int J4CLXEndcapEM::IsEndcap()
{
  //* Placement case
  //  return ( GetMyID() < OpenParameterList()->GetNTraps() ) ? 1 : -1;
  return ( GetCopyNo() < OpenParameterList()->GetNTraps() ) ? 1 : -1;  
}

inline G4double J4CLXEndcapEM::GetYmin( G4int )
{
  return OpenParameterList()->GetEndcapInnerR();
}

inline G4double J4CLXEndcapEM::GetYmax( G4int )
{
  //return OpenParameterList()->GetEMYmax();
  return OpenParameterList()->GetEMEndcapYmax();  
}

inline G4double J4CLXEndcapEM::GetHalfZ( G4int )
{
  return 0.5*OpenParameterList()->GetEMThickness();
}

#endif
