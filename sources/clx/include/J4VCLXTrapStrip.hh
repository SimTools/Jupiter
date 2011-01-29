// $Id$
#ifndef __J4VCLXTRAPSTRIP__
#define __J4VCLXTRAPSTRIP__
//*************************************************************************
//* --------------------
//* J4VCLXTrapStrip
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXDetectorComponent.hh"
#include "J4CLXParameterList.hh"
#include "J4VCLXStrip.hh"
#include "J4VCLXCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXTrapStrip : public J4VCLXDetectorComponent {

public:
  J4VCLXTrapStrip( G4bool isBarrel,
                   const G4String &name,
                   J4VDetectorComponent *parent = 0,
	           G4int  nclones   = 1,
	           G4int  nbrothers = 1,
	           G4int  me        = 0,
	           G4int  copyno    = -1 );
  
  virtual ~J4VCLXTrapStrip();

  virtual void InstallIn( J4VComponent        *mother,
			  G4RotationMatrix    *prot  = 0,
			  const G4ThreeVector &tlate = G4ThreeVector(0.) );

  virtual void Draw();
  virtual void Print() const;
  
  //* IsEndcap() == 0(Barrel), 1(Endcap+Z), -1(Endcap-Z)
  //  G4int    IsEndcap() const { return fIsEndcap ; }
  G4bool   IsBarrel() const { return fIsBarrel; }
  
  //* Virtual Functions Deliverd from J4VCLXTrap
  virtual  G4bool   IsEM         () const = 0;
  virtual  G4String GetFirstName () const = 0;    

  //* Member functions
  G4String GetMaterial  ();
  G4bool   GetVisAtt    ();
  G4Color  GetColor     ();

private:
  void Assemble();
  void Cabling();

protected:
  virtual J4VCLXStrip *Create( J4VDetectorComponent *parent = 0,
			       G4int  nclones   = 1,
			       G4int  nbrothers = 1,
			       G4int  me        = 0,
			       G4int  copyno    = -1 ) = 0;

  virtual J4VCLXStrip *CreateBound( J4VDetectorComponent *parent = 0,
				    G4int  nclones   = 1,
				    G4int  nbrothers = 1,
				    G4int  me        = 0,
				    G4int  copyno    = -1 ) = 0;  

  /*
  virtual J4VCLXCell *CreateBound( J4VDetectorComponent *parent = 0,
				   G4int  nclones   = 1,
				   G4int  nbrothers = 1,
				   G4int  me        = 0,
				   G4int  copyno    = -1 ) = 0;
  */
  
  std::vector<J4VCLXStrip*> fStrips;
  //std::vector<J4VCLXCell*> fCells;

private:
  //  G4int fIsEndcap;
  G4int fIsBarrel;
   
};

//* Inilne Functions deliverd from base class
inline G4String J4VCLXTrapStrip::GetMaterial()
{
  return OpenParameterList()->GetTrapStripMaterial();
}

inline G4bool J4VCLXTrapStrip::GetVisAtt()
{
  return OpenParameterList()->GetTrapStripVisAtt();
}

inline G4Color J4VCLXTrapStrip::GetColor()
{
  return OpenParameterList()->GetTrapStripColor();
}

#endif
