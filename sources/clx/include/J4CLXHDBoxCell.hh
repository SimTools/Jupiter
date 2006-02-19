#ifndef __J4CLXHDBoxCell__
#define __J4CLXHDBoxCell__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXBoxCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXHDBoxCell : public J4VCLXBoxCell {

public:
    J4CLXHDBoxCell(J4VDetectorComponent* parent = 0,
		   G4int  nclones = 1,
		   G4int  nbrothers = 1,
		   G4int  me = 0,
		   G4int  copyno = -1);
    virtual ~J4CLXHDBoxCell();

    virtual G4String GetFirstName   () const { return fFirstName; }
    virtual G4String GetMaterial    ();
    virtual G4bool   GetVisAtt      ();
    virtual G4Color  GetColor       ();

private:
    void Cabling();

private:
    static const G4String fFirstName;
};

//* Inline Implementation of Pure Virtuals of Base Class --------------
inline G4String J4CLXHDBoxCell::GetMaterial()
{
  return OpenParameterList()->GetHDCellMaterial();
}

inline G4bool J4CLXHDBoxCell::GetVisAtt()
{
  return OpenParameterList()->GetHDCellVisAtt();
}

inline G4Color J4CLXHDBoxCell::GetColor()
{
  return OpenParameterList()->GetHDCellColor();
}

#endif