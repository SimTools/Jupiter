#ifndef __J4VCLXLARGEBOXCELL__
#define __J4VCLXLARGEBOXCELL__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXBoxCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXBoxCell;
class J4VCLXLargeBoxCell : public J4VCLXDetectorComponent {
public:
    J4VCLXLargeBoxCell(const G4String        &name,
		       J4VDetectorComponent  *parent   = 0,
		       G4int  nclones   = 1,
		       G4int  nbrothers = 1,
		       G4int  me        = 0,
		       G4int  copyno    = -1 );
    virtual ~J4VCLXLargeBoxCell();

    virtual void  InstallIn( J4VComponent         *mother,
			     G4RotationMatrix     *prot  = 0,
			     const G4ThreeVector  &tlate = 0 );
    virtual void	Draw() ;
    virtual void Print() const;

  virtual G4String GetFirstName      () const = 0;

protected:
    virtual J4VCLXBoxCell *CreateBox(J4VDetectorComponent *parent = 0,
					 G4int nclones = 1,
					 G4int nbrothers = 1,
					 G4int me = 0,
					 G4int copyno = -1) = 0;

private:
    void Assemble();
    void Cabling();

private:
    J4VCLXBoxCell* fBoxCell;
};

#endif
