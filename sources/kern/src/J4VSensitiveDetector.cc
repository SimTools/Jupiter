// $Id$
//*************************************************************************
//* --------------------
//* J4VSensitiveDetector
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/05/16  K.Hoshina	Changed argument of constructor.
//*************************************************************************

//=====================================================================
//---------------------
// class implementation
//---------------------

#include "J4VSensitiveDetector.hh"
#include "J4Global.hh"

G4int J4VSensitiveDetector::fHitNumber = 0; 

//* constructor -------------------------------------------------------
	
J4VSensitiveDetector::J4VSensitiveDetector(J4VComponent* detector)
			: G4VSensitiveDetector(detector->GetName()), 
			  fLV(detector->GetLV()), fHitBuf(0),
			  fNewStep(0), fROHist(0),
                          fIsOutputLocked(FALSE)
{  
  collectionName.insert(detector->GetName());  
}

//* destructor --------------------------------------------------------
	
J4VSensitiveDetector::~J4VSensitiveDetector()
{
#ifdef __THEBE__
  J4cerr << "J4VSensitiveDetector::destructor is called for " << GetName() << J4endl;
#endif
}
	
	
	
	


