#ifndef __J4VCLXCell__
#define __J4VCLXCell__

#include "J4VCLXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXCell : public J4VCLXDetectorComponent {
public:
    J4VCLXCell( const G4String       &name,
		J4VDetectorComponent *parent    =  0,
		G4int  nclones   =  1,
		G4int  nbrothers =  1,
		G4int  me        =  0,
		G4int  copyno    = -1);
    ~J4VCLXCell();
    virtual void InstallIn(J4VComponent         *mother,
			   G4RotationMatrix     *prot   = 0,
			   const G4ThreeVector  &tlate  = 0) = 0;

    virtual G4bool IsTrap() = 0;
    virtual G4bool IsXPlus() = 0;
    virtual void	Draw();
    virtual void	Print() const;

private:
    virtual void Assemble() = 0;
    virtual void Cabling();
};
#endif
