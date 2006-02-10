#ifndef __J4CLXHDBOARD__
#define __J4CLXHDBOARD__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXBoard.hh"
#include "J4VCLXLargeBoxCell.hh"
#include "J4VCLXTrapCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXLargeBoxCell;
class J4VCLXTrapCell;
class J4CLXHDBoard : public J4VCLXBoard {

public:
    J4CLXHDBoard(J4VDetectorComponent *parent   = 0,
		 G4int  nclones   = 1,
		 G4int  nbrothers = 1,
		 G4int  me        = 0,
		 G4int  copyno    = -1 );
    ~J4CLXHDBoard();

    virtual G4String GetFirstName() const {return fFirstName;}

protected:
    virtual J4VCLXLargeBoxCell *CreateLargeBoxCell(J4VDetectorComponent *parent = 0,
						   G4int nclones = 1,
						   G4int nbrothers = 1,
						   G4int me = 0,
						   G4int copyno = -1);
    virtual J4VCLXTrapCell *CreateTrap(J4VDetectorComponent *parent = 0,
				       G4int nclones = 1,
				       G4int nbrothers = 1,
				       G4int me = 0,
				       G4int copyno = -1,
				       G4bool isXPlus = true);

private:
        static const G4String fFirstName;
};

#endif
