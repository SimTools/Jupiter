// $Id$

//*************************************************************************
//* --------------------
//* J4CDCDriftRegionSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCDriftRegionSD.hh"
#include "J4CDCDriftRegion.hh"
#include "J4CDCSenseWire.hh"
#include <math.h>

 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCDriftRegionSD::J4CDCDriftRegionSD(J4VDetectorComponent* detector)
		   //:J4VSD<J4CDCDriftRegionHit>(detector)
		   :J4VCDCDriftRegionSD<J4CDCDriftRegionHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCDriftRegionSD::~J4CDCDriftRegionSD()
{
}



