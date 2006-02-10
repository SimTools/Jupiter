#ifndef __J4CLXBLOCK__
#define __J4CLXBLOCK__
#include "J4VCLXDetectorComponent.hh"
#include "J4CLXEM.hh"
#include "J4CLXHD.hh"
#include "G4Trap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXEM;
class J4CLXHD;
class J4CLXBlock : public J4VCLXDetectorComponent {

public:
    J4CLXBlock(J4VDetectorComponent* parent = 0,
	       G4int nclones = 1,
	       G4int nbrothers = 1,
	       G4int me = 0,
	       G4int copyno = -1);
    virtual ~J4CLXBlock();

    virtual void InstallIn(J4VComponent* mother,
			   G4RotationMatrix* prot = 0,
			   const G4ThreeVector& tlate = 0);

    virtual void Draw();
    virtual void Print() const;

private:
    void Assemble();
    void Cabling();

private:
    static const G4String fFirstName;
    G4Trap *ptrTrap;
    J4CLXEM *fEMcal;
    J4CLXHD *fHDcal;
};
#endif
