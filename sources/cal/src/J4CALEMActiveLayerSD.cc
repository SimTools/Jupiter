// $Id$
//*************************************************************************
//* --------------------
//* J4CALEMActiveLayerSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive ptrDetector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2004/08/30  Ono Hiroaki  Add Pre hit data, hitlet data
//*     2004/10/12  Allister Sanchez  Record J4CALHits as if they are hitlets.
//*                                   J4CALHit::J4CALHitlet is now obsolete.
//*                                   Use std::multimap for monitoring hits.
//*************************************************************************

#include "J4CALEMActiveLayer.hh"
#include "J4VCALSubLayerSD.hh"
#include "J4CALEMActiveLayerSD.hh"
#include "J4CALHit.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CALEMActiveLayerSD::J4CALEMActiveLayerSD( J4VDetectorComponent* ptrDetector )
  : J4VCALSubLayerSD( ptrDetector )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEMActiveLayerSD::~J4CALEMActiveLayerSD()
{
}

