#ifndef __J4VCLXBoxCell__
#define __J4VCLXBoxCell__

#include "J4VCLXCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXBoxCell : public J4VCLXCell {

public:
    J4VCLXBoxCell(const G4String &name,
		  J4VDetectorComponent *parent = 0,
		  G4int nclones = 1,
		  G4int nbrothers = 1,
		  G4int me = 0,
		  G4int copyno = -1);
    virtual ~J4VCLXBoxCell();

    virtual void InstallIn(J4VComponent *mother,
			   G4RotationMatrix *prot = 0,
			   const G4ThreeVector &tlate = 0);
    virtual void Draw();
    virtual void Print() const ;

    virtual G4String GetFirstName() const = 0;
    virtual G4String GetMaterial       ()       = 0;
    virtual G4bool   GetVisAtt         ()       = 0;
    virtual G4Color  GetColor          ()       = 0;

    inline G4bool IsTrap() {return false;};
    inline G4bool IsXPlus() {return false;};

private:
    void Assemble();
    virtual void Cabling();
};


#endif
