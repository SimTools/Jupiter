// $Id$
#ifndef __J4IR__
#define __J4IR__
//*************************************************************************
//* --------------------
//* J4IR
//* --------------------
//* (Description)
//* 	Derivation class for IR region
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

// Sub-Component
#include "J4IRBPPipe.hh"
#include "J4IRBPCone.hh"
#include "J4IRBPAlDrum.hh"
#include "J4IRBPAlTube.hh"

#include "J4IRQC1.hh"
#include "J4IRSD0.hh"
#include "J4IRQC2.hh"
#include "J4IRCH2Mask.hh"

#include "J4IRWSiCAL1.hh"
#include "J4IRWSiCAL2.hh"
#include "J4IRWMask1.hh"
#include "J4IRWMask2.hh"
//#include "J4IRPairMonitor.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IR : public J4VIRAcceleratorComponent {	

public:
  J4IR(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );

  virtual ~J4IR();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;

  J4IRBPPipe* fBeampipe;
  J4IRBPCone* fBeamConeR;
  J4IRBPCone* fBeamConeL;
  J4IRBPAlDrum* fAlDrumR; 
  J4IRBPAlDrum* fAlDrumL; 
  J4IRBPAlTube* fAlBeamPipeR;
  J4IRBPAlTube* fAlBeamPipeL;
  J4IRQC1* fQC1R;
  J4IRQC1* fQC1L;
  J4IRSD0* fSD0R;
  J4IRSD0* fSD0L;
  J4IRQC2* fQC2R;
  J4IRQC2* fQC2L;
  J4IRCH2Mask* fCH2MR;
  J4IRCH2Mask* fCH2ML;
  J4IRWMask1* fWM1R;
  J4IRWMask1* fWM1L;
  J4IRWMask2* fWM2R;
  J4IRWMask2* fWM2L;
  J4IRWSiCAL1* fWSC1R;
  J4IRWSiCAL1* fWSC1L;
  J4IRWSiCAL2* fWSC2R;
  J4IRWSiCAL2* fWSC2L;
  //  J4IRPairMonitor* fPMNR;
  //  J4IRPairMonitor* fPMNL;
};

#endif




