// $Id$
#ifndef __J4CDCDRIFTREGIONSD__
#define __J4CDCDRIFTREGIONSD__
//*************************************************************************
//* --------------------
//* J4CDCDriftRegionSD
//* --------------------
//* (Description)
//* 	Concrate class for DriftRegion sensitive detector.
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "G4Step.hh"
#include "J4VCDCDriftRegionSD.hh"
#include "J4CDCDriftRegionHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4CDCDriftRegionSD : public J4VCDCDriftRegionSD<J4CDCDriftRegionHit>{
  
public:

  J4CDCDriftRegionSD(J4VDetectorComponent* detector);
  ~J4CDCDriftRegionSD();


private:
  
};

#endif

