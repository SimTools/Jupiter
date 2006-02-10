#ifndef __J4VCLXBoard__
#define __J4VCLXBoard__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXLargeBoxCell.hh"
#include "J4VCLXTrapCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXBoard : public J4VCLXDetectorComponent {
public:
    J4VCLXBoard(const G4String &name,
		    J4VDetectorComponent *parent = 0,
		    G4int nclones = 1,
		    G4int nbrothers = 1,
		    G4int me = 0,
		    G4int cpyno = -1);
    ~J4VCLXBoard();
    virtual void InstallIn(J4VComponent *mother,
			   G4RotationMatrix *prot = 0,
			   const G4ThreeVector &tlate = 0);

    virtual void Draw();
    virtual void Print() const;

    virtual G4String GetFirstName() const = 0;

protected:
    virtual J4VCLXLargeBoxCell *CreateLargeBoxCell(J4VDetectorComponent *parent = 0,
						   G4int nclones = 1,
						   G4int nbrothers = 1,
						   G4int me = 0,
						   G4int copyno = -1) = 0;
    virtual J4VCLXTrapCell *CreateTrap(J4VDetectorComponent *parent = 0,
				       G4int nclones = 1,
				       G4int nbrothers = 1,
				       G4int me = 0,
				       G4int copyno = -1,
				       G4bool isXPlus = true) = 0;

private:
    virtual void Assemble();
    virtual void Cabling();

protected:
    J4VCLXLargeBoxCell* fLargeBoxCell;
    std::vector<J4VCLXTrapCell *> pTraps;
};

#endif
