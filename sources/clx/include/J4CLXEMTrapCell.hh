#ifndef __J4CLXEMTrapCell__
#define __J4CLXEMTrapCell__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXTrapCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXEMTrapCell : public J4VCLXTrapCell {

public:
    J4CLXEMTrapCell(     J4VDetectorComponent* parent = 0,
			 G4int  nclones = 1,
			 G4int  nbrothers = 1,
			 G4int  me = 0,
			 G4int  copyno = -1,
			 G4bool isXPlus = true);
    virtual ~J4CLXEMTrapCell();

    virtual G4String GetFirstName   () const { return fFirstName; }
    virtual G4String GetMaterial    ();
    virtual G4bool   GetVisAtt      ();
    virtual G4Color  GetColor       ();

private:
    void Cabling();

private:
    static const G4String fFirstName;
};

//=====================================================================
//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4String J4CLXEMTrapCell::GetMaterial()
{
  return OpenParameterList()->GetEMCellMaterial();
}

inline G4bool J4CLXEMTrapCell::GetVisAtt()
{
  return OpenParameterList()->GetEMCellVisAtt();
}

inline G4Color J4CLXEMTrapCell::GetColor()
{
  return OpenParameterList()->GetEMCellColor();
}

#endif
