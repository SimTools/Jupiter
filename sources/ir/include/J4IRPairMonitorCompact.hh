// $Id$
#ifndef __J4IRPAIRMONITORCOMPACT_
#define __J4IRPAIRMONITORCOMPACT__
//*************************************************************************
//* --------------------
//* J4IRPairMonitorCompact
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

#include "J4IRPairMonitorCompactBPin.hh"
#include "J4IRPairMonitorCompactBPout.hh"
//=====================================================================
//---------------------
// class definition
//---------------------
                                                                                              
class J4IRPairMonitorCompact : public J4VIRDetectorComponent {
                                                                                              
public:
                                                                                              
  J4IRPairMonitorCompact(J4VComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
                           G4int  copyno    = -1 ,
	                    G4bool reflect=false);
                                                                                              
  virtual ~J4IRPairMonitorCompact();
                                                                                            
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

  J4IRPairMonitorCompactBPin*  fbpIn;
  J4IRPairMonitorCompactBPout* fbpOut;

};
                                                                                              
#endif