// $Id$
#ifndef __J4IRPAIRMONITORCOMPACTSP_
#define __J4IRPAIRMONITORCOMPACTSP__
//*************************************************************************
//* --------------------
//* J4IRPairMonitorCompactSP
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
#include "J4IRPairMonitorCompact.hh"
//=====================================================================
//---------------------
// class definition
//---------------------
                                                                                              
class J4IRPairMonitorCompactSP : public J4VIRDetectorComponent {
                                                                                              
public:
                                                                                              
  J4IRPairMonitorCompactSP(J4VComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
                           G4int  copyno    = -1 ,
	                    G4bool reflect=false);
                                                                                              
  virtual ~J4IRPairMonitorCompactSP();
                                                                                            
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
  J4IRPairMonitorCompact*  fpm;
};
                                                                                              
#endif
