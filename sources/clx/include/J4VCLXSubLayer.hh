// $Id$
#ifndef __J4VCLXSUBLAYER__
#define __J4VCLXSUBLAYER__
//*************************************************************************
//* --------------------
//* J4VCLXSubLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXBoard.hh"
#include "J4VCLXLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXBoard;
class J4VCLXSubLayer : public J4VCLXDetectorComponent {

public:
  J4VCLXSubLayer( const G4String        &name,
                  J4VDetectorComponent  *parent   = 0,
                                  G4int  nclones   = 1,
                                  G4int  nbrothers = 1,
                                  G4int  me        = 0,
                                  G4int  copyno    = -1 );
  virtual ~J4VCLXSubLayer();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = 0 );
  virtual void	Draw() ;
  virtual void	Print() const ;

  virtual G4String GetFirstName      () const = 0;
    virtual G4double GetPlx() = 0;
    virtual G4double GetPx() = 0;
  virtual G4double GetStartThickness () = 0;
  virtual G4double GetEndThickness   () = 0;
  virtual G4String GetMaterial       ()       = 0;
  virtual G4bool   GetVisAtt         ()       = 0;
  virtual G4Color  GetColor          ()       = 0;

protected:
    virtual J4VCLXBoard *Create(J4VDetectorComponent *parent = 0,
				G4int nclones = 1,
				G4int nbrothers = 1,
				G4int me = 0,
				G4int copyno = -1) = 0;
    virtual G4bool IsActive() = 0;

private:
  void 	Assemble();
  void  Cabling () = 0;

private:
    J4VCLXBoard *fBoard;
};

#endif
