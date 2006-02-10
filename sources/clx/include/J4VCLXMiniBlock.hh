#ifndef __J4VCLXMiniBlock__
#define __J4VCLXMiniBlock__

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXLayer;
class J4VCLXMiniBlock : public J4VCLXDetectorComponent {
public:
    J4VCLXMiniBlock( const G4String       &name,
		     J4VDetectorComponent *parent    =  0,
		     G4int  nclones   =  1,
		     G4int  nbrothers =  1,
		     G4int  me        =  0,
		     G4int  copyno    = -1);
    ~J4VCLXMiniBlock();
    virtual void InstallIn(J4VComponent         *mother,
			   G4RotationMatrix     *prot   = 0,
			   const G4ThreeVector  &tlate  = 0);

    virtual void	Draw();
    virtual void	Print() const;

    virtual G4String GetFirstName() const = 0;
    virtual G4int GetNofLayers() = 0;
    virtual G4double GetPy() = 0;
    virtual G4double GetPx() = 0;
    virtual G4double GetPlx() = 0;
    virtual G4double GetTrapPy() = 0;
    virtual G4String GetMaterial() = 0;
    virtual G4bool GetVisAtt() = 0;
    virtual G4Color GetColor() =0;

protected:
    virtual J4VCLXLayer *Create(J4VDetectorComponent *parent = 0,
				G4int nclones = 1,
				G4int nbrothers = 1,
				G4int me = 0,
				G4int copyno = -1) = 0;

private:
    virtual void Assemble();
    virtual void Cabling();

protected:
    std::vector<J4VCLXLayer *> fLayers;

};

#endif
