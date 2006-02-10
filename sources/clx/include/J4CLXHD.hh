#ifndef __J4CLXHD__
#define __J4CLXHD__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXMiniBlock.hh"
#include "J4CLXHDLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXHDLayer;
class J4CLXHD : public J4VCLXMiniBlock {

public:
  J4CLXHD( J4VDetectorComponent *parent   = 0,
                          G4int  nclones   = 1,
                          G4int  nbrothers = 1,
                          G4int  me        = 0,
                          G4int  copyno    = -1 );
  virtual ~J4CLXHD();

  virtual G4String GetFirstName   () const { return fFirstName; }
    virtual G4int GetNofLayers();
  virtual G4double    GetPx();
  virtual G4double GetPlx();
    virtual G4double GetPy();
    virtual G4double GetTrapPy();
  virtual G4String GetMaterial    ();
  virtual G4bool   GetVisAtt      ();
  virtual G4Color  GetColor       ();

protected:
    virtual J4VCLXLayer *Create(J4VDetectorComponent *parent = 0,
					 G4int nclones = 1,
					 G4int nbrothers = 1,
					 G4int me = 0,
					 G4int copyno = -1);

private:
    void SetParameter();

private:
    static const G4String fFirstName;
    G4double rmin;
    G4double rmax;
    G4double thick;
    G4double dphi;
};


//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4int J4CLXHD::GetNofLayers()
{
    return OpenParameterList() -> GetHDNLayers();
}

inline G4double J4CLXHD::GetPx()
{
    return (rmax * std::cos(.5 * dphi) - thick) * std::tan(.5 * dphi);
}

inline G4double J4CLXHD::GetPlx()
{
    return rmax * std::sin(.5 * dphi);
}

inline G4double J4CLXHD::GetPy()
{
    return .5 * thick;
}

inline G4double J4CLXHD::GetTrapPy()
{
    return .5 * (rmax * std::cos(.5 * dphi) -rmin) - GetPy();
}

inline G4String J4CLXHD::GetMaterial()
{
  return OpenParameterList()->GetHDMaterial();
}

inline G4bool J4CLXHD::GetVisAtt()
{
  return OpenParameterList()->GetHDVisAtt();
}

inline G4Color J4CLXHD::GetColor()
{
  return OpenParameterList()->GetHDColor();
}

#endif
