#ifndef __J4CLXHDLARGEBOXCELL__
#define __J4CLXHDLARGEBOXCELL__

#include "J4VCLXLargeBoxCell.hh"
#include "J4VCLXBoxCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXBoxCell;
class J4CLXHDLargeBoxCell : public J4VCLXLargeBoxCell {
public:
    J4CLXHDLargeBoxCell(J4VDetectorComponent  *parent    = 0,
		       G4int  nclones   = 1,
		       G4int  nbrothers = 1,
		       G4int  me        = 0,
		       G4int  copyno    = -1 );
    virtual ~J4CLXHDLargeBoxCell();

  virtual G4String GetFirstName      () const { return fFirstName; }

protected:
    virtual J4VCLXBoxCell *CreateBox(J4VDetectorComponent *parent = 0,
					 G4int nclones = 1,
					 G4int nbrothers = 1,
					 G4int me = 0,
					 G4int copyno = -1);

private:
    void Cabling();

private:
    static const G4String fFirstName;
};

#endif
