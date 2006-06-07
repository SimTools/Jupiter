// $Id$
//*************************************************************************
//* --------------------
//* J4OptDetSD
//* --------------------
//* (Description)
//* 	Class for describing optional detector
//*     
//* (Update Record)
//*	2006/06/04 A.Miyamoto  Original version
//*************************************************************************
#include "J4OptDet.hh"
#include "J4OptDetSD.hh"
#include "J4OptDetHit.hh"
#include "J4ParameterTable.hh"

#include <cmath>
#include <utility>

G4int J4OptDetSD::fNumberOfOptDet=0;
G4int J4OptDetSD::fHitNumber=0;

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4OptDetSD::J4OptDetSD( J4OptDet* detector )
 :J4VSD<J4OptDetHit>( detector )
{
  fOptDetID=detector->GetOptDetID();
  fOptDetSerialID = fNumberOfOptDet;
  std::cerr << detector->GetName() << " MyID" 
	    << detector->GetMyID() 
            << " serial ID=" << GetOptDetSerialID() 
	    << " OptDetID="  << GetOptDetID() << std::endl;

  fNumberOfOptDet++;

}

//=====================================================================
//* destructor --------------------------------------------------------
J4OptDetSD::~J4OptDetSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------
void J4OptDetSD::Initialize( G4HCofThisEvent* PreHCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"

//  std::cerr << " ----------------------------------" << std::endl;
//  std::cerr << " J4OptDetSD .. Initialize called.  " << std::endl;
//  std::cerr << " ----------------------------------" << std::endl;
  
  MakeHitBuf( PreHCTE );

}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4OptDetSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{

  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);

  G4double       edep      = GetEnergyDeposit();

  J4VComponent* ptrDetector = GetComponent(0);

  //Get perticle information

  const G4ThreeVector&  pre       = GetPrePosition();
  const G4ThreeVector&  post      = GetPostPosition();
  const G4ThreeVector&  p         = GetMomentum();

  fHitNumber++;
  //  G4int preHitID = 0 ;
  G4double              totalE    = GetTotalEnergy();
  G4double              tof       = GetTof();
  G4int                 trackID   = GetTrackID();
  G4int                 motherTrackID = GetMotherTrackID();
  G4ParticleDefinition* particle = GetParticle(); 

  J4OptDetHit *aHit=new J4OptDetHit(ptrDetector, fOptDetID, fOptDetSerialID,
				    trackID, motherTrackID, particle,
				    tof, edep, totalE,
				    p, pre, post, fHitNumber);

  ((J4OptDetHitBuf*)GetHitBuf())->insert(aHit);

  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4OptDetSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{	
  fHitNumber=0;
}

//=====================================================================
//* clear -------------------------------------------------------------

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4OptDetSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4OptDetSD::PrintAll()
{
  G4int nHit= ( (J4OptDetHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** OptDet Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4OptDetHitBuf*)GetHitBuf() ) -> PrintAllHits();
}
