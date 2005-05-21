#ifndef __J4TPCHALF__
#define __J4TPCHALF__
//*************************************************************************
//* --------------------
//* J4TPCHalf
//* --------------------
//* (Description)
//* 	Derivation class for TPCHalf.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4VTPCDetectorComponent.hh"
#include "J4TPCSupportTub.hh"
#include "J4TPCEndcap.hh"
#include "J4TPCCentralMembrane.hh"
#include "J4TPCPadPlane.hh"
#include "J4TPCDriftRegion.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4TPCHalf : public J4VTPCDetectorComponent {	

public:
  J4TPCHalf(J4VDetectorComponent *parent    = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );
  J4TPCHalf(const J4TPCHalf &orig, G4int copyno);
  virtual ~J4TPCHalf();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw();
  virtual void	Print() const;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String        fFirstName;
  J4TPCDriftRegion      *fDriftRegion;
  J4TPCSupportTub       *fOuterSupportTub;
  J4TPCSupportTub       *fInnerSupportTub;
  J4TPCEndcap           *fEndcaps;
  J4TPCCentralMembrane  *fCentralMembrane;
  J4TPCPadPlane         *fPadPlanes; 
 
};

#endif

