// $Id$
//*************************************************************************
//* --------------------
//* J4CDCStereoDriftRegionSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCStereoDriftRegionSD.hh"
#include "J4CDCStereoDriftRegion.hh"
#include "J4CDCSenseWire.hh"
#include <cmath>
 
//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCStereoDriftRegionSD::J4CDCStereoDriftRegionSD(J4VDetectorComponent* detector)
		                  // :J4VSD<J4CDCStereoDriftRegionHit>(detector)
		                   :J4VCDCDriftRegionSD<J4CDCStereoDriftRegionHit>(detector)
{  
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCStereoDriftRegionSD::~J4CDCStereoDriftRegionSD()
{
}


