// $Id$
//*************************************************************************
//* --------------------
//* J4CALHDActiveLayerSD
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

#include "J4CALHDActiveLayer.hh"
#include "J4VCALSubLayerSD.hh"
#include "J4CALHDActiveLayerSD.hh"
#include <utility>

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CALHDActiveLayerSD::J4CALHDActiveLayerSD( J4VDetectorComponent* ptrDetector )
  : J4VCALSubLayerSD( ptrDetector )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHDActiveLayerSD::~J4CALHDActiveLayerSD()
{
}

