#ifndef __J4CLXEMBoxCell__
#define __J4CLXEMBoxCell__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXBoxCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXEMBoxCell : public J4VCLXBoxCell {

public:
    J4CLXEMBoxCell(J4VDetectorComponent* parent = 0,
		   G4int  nclones = 1,
		   G4int  nbrothers = 1,
		   G4int  me = 0,
		   G4int  copyno = -1);
    virtual ~J4CLXEMBoxCell();

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
inline G4String J4CLXEMBoxCell::GetMaterial()
{
  return OpenParameterList()->GetEMCellMaterial();
}

inline G4bool J4CLXEMBoxCell::GetVisAtt()
{
  return OpenParameterList()->GetEMCellVisAtt();
}

inline G4Color J4CLXEMBoxCell::GetColor()
{
  return OpenParameterList()->GetEMCellColor();
}

#endif
