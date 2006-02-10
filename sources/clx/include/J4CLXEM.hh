#ifndef __J4CLXEM__
#define __J4CLXEM__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXMiniBlock.hh"
#include "J4CLXEMLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXEMLayer;
class J4CLXEM : public J4VCLXMiniBlock {

public:
  J4CLXEM( J4VDetectorComponent *parent   = 0,
                          G4int  nclones   = 1,
                          G4int  nbrothers = 1,
                          G4int  me        = 0,
                          G4int  copyno    = -1 );
  virtual ~J4CLXEM();

  virtual G4String GetFirstName   () const { return fFirstName; }
    virtual G4int GetNofLayers();
  virtual G4double GetPx();
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
inline G4int J4CLXEM::GetNofLayers()
{
    return OpenParameterList() -> GetEMNLayers();
}

inline G4double J4CLXEM::GetPx()
{
    return rmin * std::tan(.5 * dphi);
}

inline G4double J4CLXEM::GetPlx()
{
    return (rmin + thick) * std::tan(.5 * dphi);
}

inline G4double J4CLXEM::GetPy()
{
    return .5 * thick;
}

inline G4double J4CLXEM::GetTrapPy()
{
    return GetPy() - .5 * (rmax * std::cos(.5 * dphi) - rmin);
}

inline G4String J4CLXEM::GetMaterial()
{
  return OpenParameterList()->GetEMMaterial();
}

inline G4bool J4CLXEM::GetVisAtt()
{
  return OpenParameterList()->GetEMVisAtt();
}

inline G4Color J4CLXEM::GetColor()
{
  return OpenParameterList()->GetEMColor();
}

#endif
