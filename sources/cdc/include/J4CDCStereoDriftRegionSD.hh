// $Id$
#ifndef __J4CDCSTEREODRIFTREGIONSD__
#define __J4CDCSTEREODRIFTREGIONSD__
//*************************************************************************
//* --------------------
//* J4CDCStereoDriftRegionSD
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
#include "J4CDCStereoDriftRegionHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4CDCStereoDriftRegionSD : public J4VCDCDriftRegionSD<J4CDCStereoDriftRegionHit>{
  
public:

  J4CDCStereoDriftRegionSD(J4VDetectorComponent* detector);
  ~J4CDCStereoDriftRegionSD();

   
private:
  
};

#endif

