// $Id$
#ifndef __J4CLXBARRELEM__
#define __J4CLXBARRELEM__
//*************************************************************************
//* --------------------
//* J4CLXBarrelEM
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
class J4CLXBarrelEM : public J4VCLXBlock {  

public:
  J4CLXBarrelEM( J4VDetectorComponent *parent   = 0,
		 G4int  nclones   = 1,
		 G4int  nbrothers = 1,
		 G4int  me        = 0,
		 G4int  copyno    = -1 );
  
  virtual ~J4CLXBarrelEM();

  virtual G4String GetFirstName () const { return fgFirstName; }
  virtual G4double GetYmin      ( G4int i = 0 ) ;  
  virtual G4double GetYmax      ( G4int i = 0 ) ;
  virtual G4double GetHalfZ     ( G4int i = 0 ) ;
  virtual G4int    GetNLayers   () ;
  //* Barrel = 0, Endcap+Z = 1, Endcap-Z = -1
  virtual G4int    IsEndcap     ();
  virtual G4bool   IsEM         ();  
  
public:
  J4VCLXLayer *Create( J4VDetectorComponent *parent = 0,
		       G4int nclones   = 1,
		       G4int nbrothers = 1,
		       G4int me        = 0,
		       G4int copyno    = -1 );  

private:
  static const G4String fgFirstName;
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------

inline G4bool J4CLXBarrelEM::IsEM()
{
  return true;
}

inline G4int J4CLXBarrelEM::GetNLayers()
{
  return OpenParameterList()->GetEMNLayers();
}

inline G4int J4CLXBarrelEM::IsEndcap()
{
  //* Barrel = 0, Endcap+Z = 1, Endcap-Z = -1
  return 0;
}

inline G4double J4CLXBarrelEM::GetYmin( G4int )
{
  return OpenParameterList()->GetCLXInnerR();
}

inline G4double J4CLXBarrelEM::GetYmax( G4int )
{
  return OpenParameterList()->GetEMYmax();
}

inline G4double J4CLXBarrelEM::GetHalfZ( G4int )
{
  return OpenParameterList()->GetEMHalfZ();
}

#endif
