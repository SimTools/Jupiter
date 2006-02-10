#ifndef __J4CLXHDTrapCell__
#define __J4CLXHDTrapCell__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXTrapCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXHDTrapCell : public J4VCLXTrapCell {

public:
    J4CLXHDTrapCell(     J4VDetectorComponent* parent = 0,
					  G4int  nclones = 1,
					  G4int  nbrothers = 1,
					  G4int  me = 0,
					  G4int  copyno = -1,
					  G4bool isXPlus = true);
    virtual ~J4CLXHDTrapCell();

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
inline G4String J4CLXHDTrapCell::GetMaterial()
{
  return OpenParameterList()->GetHDCellMaterial();
}

inline G4bool J4CLXHDTrapCell::GetVisAtt()
{
  return OpenParameterList()->GetHDCellVisAtt();
}

inline G4Color J4CLXHDTrapCell::GetColor()
{
  return OpenParameterList()->GetHDCellColor();
}

#endif
