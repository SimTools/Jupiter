// $Id$
#ifndef __J4IRPAIRMONITORCOMPACTBPOUT__
#define __J4IRPAIRMONITORCOMPACTBPOUT__
//*************************************************************************
//* --------------------
//* J4IRPairMonitorCompactBPout
//* --------------------
//* (Description)
//*     Derivation class for PaorMonitor
//*     Mother class : J4VDetectorComponent
//*
//* (Update Record)
//*     2001/06/06  T.Aso       Original version.
//*     2002/11/20  T.Aso       Remove RO
//*************************************************************************
                                                                                              
#include "J4VIRDetectorComponent.hh"
                                                                                              
//=====================================================================
//---------------------
// class definition
//---------------------
                                                                                              
class J4IRPairMonitorCompactBPout : public J4VIRDetectorComponent {
                                                                                              
public:
                                                                                              
  J4IRPairMonitorCompactBPout(J4VComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
                           G4int  copyno    = -1 ,
	                    G4bool reflect=false);
                                                                                              
  virtual ~J4IRPairMonitorCompactBPout();
                                                                                            
  virtual G4RotationMatrix* GetRotation();
  virtual G4ThreeVector&  GetTranslation();

  virtual void  SwitchOn (G4String opt = "me")  ;
  virtual void  SwitchOff(G4String opt = "me") ;
  virtual void  Draw()      ;
  virtual void  Print() const ;
                                                                                              
private:
  void  Assemble();
  void  Cabling ();
                                                                                              
private:
                                                                                              
  static G4String fName;
  G4double rmin;
  G4double r1max;
  G4double zlen;

};
                                                                                              
#endif
