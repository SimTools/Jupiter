// $Id$
//*************************************************************************
//* --------------------
//* J4CALSubLayerSD
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
#include "J4CALCone.hh"
#include "J4CALTower.hh"
#include "J4CALBlock.hh"
#include "J4CALMiniCone.hh"
#include "J4CALMiniTower.hh"
#include "J4CALLayer.hh"
#include "J4CALSubLayer.hh"
#include "J4CALSubLayerSD.hh"
#include "J4CALHit.hh"
#include "J4CALSD.hh"
#include "G4Sphere.hh"
#include "J4Timer.hh"
#include "TVAddress.hh"
#include "J4CALParameterList.hh"
#include <utility>

//=====================================================================
// static datamember's initialize
G4int J4CALSubLayerSD::fgLastHCID=-1;
G4int J4CALSubLayerSD::fgCurrentPreHitID = -1;
std::multimap<G4int,J4CALHit*> J4CALSubLayerSD::fgCalHits;

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CALSubLayerSD::J4CALSubLayerSD( J4VDetectorComponent* ptrDetector )
  : J4VSD<J4CALHit>( ptrDetector ),
    fConeID(-1), fTowerID(-1), fMiniConeID(-1), fMiniTowerID(-1), fLayerID(-1), fSubLayerID(-1),
    fIsBarrel(-1), fIsEM(-1)
{ }

//=====================================================================
//* destructor --------------------------------------------------------

J4CALSubLayerSD::~J4CALSubLayerSD()
{ }

//=====================================================================
//* Initialize --------------------------------------------------------

void J4CALSubLayerSD::Initialize( G4HCofThisEvent* HCTE )
{
  
  static G4int timerID = -1;
  J4Timer timer( timerID, "J4CALSubLayerSD", "Initialize()" );
  timer.Start();
  
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  //MakeHitBuf( HCTE );

  G4THitsCollection<J4CALHit>* hitbuf; 
  hitbuf = new G4THitsCollection<J4CALHit>( SensitiveDetectorName, collectionName[0] ) ;
  SetHitBuf( (G4VHitsCollection*)hitbuf );
  if ( fgLastHCID < 0  ) {
    //     G4int hcID = GetCollectionID(0); 
    fgLastHCID=GetCollectionID(0); 
  }
  else {
    fgLastHCID++;
  }
  HCTE->AddHitsCollection( fgLastHCID, GetHitBuf() );
  // Don't "delete" fCalHits[i]!
  // Geant4 deletes hit objects at the end of the run.
  
  timer.Stop();
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4CALSubLayerSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  static G4int timerID = -1;
  J4Timer timer( timerID, "J4CAL", "J4CALSubLayerSD:ProcessHits" );
  timer.Start();

  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep( aStep );

  // don't process e/mu/gamma/pi/p with no edep
  G4String pname = GetParticleName();
  G4bool checkable = (pname=="e-") || (pname=="e+") || (pname=="gamma") ||
    (pname=="mu-") || (pname=="mu+") || (pname=="pi0") || (pname=="pi-") || (pname=="pi+") ||
    (pname=="proton") || (pname=="anti_proton");
  if( checkable && GetEnergyDeposit() <= 0 ) return FALSE; // don't process this hit if Edep=0

  ////////////////////////////////////////////////////////////////
  // Calorimeter sub structure and depth-------------------------
  // SubLayer->Layer->MiniTower->MiniCone->Block->Tower->Cone->CAL
  ////////////////////////////////////////////////////////////////
  const G4int LayerDepth     = 1;
  const G4int MiniTowerDepth = 2;
  const G4int MiniConeDepth  = 3;
  const G4int BlockDepth     = 4;
  const G4int TowerDepth     = 5;
  const G4int ConeDepth      = 6;

  // poiters for components -------------------------------------
  J4VComponent*  ptrSubLayerComponent  = GetComponent();
  J4VComponent*  ptrLayerComponent     = GetComponent( LayerDepth );
  J4VComponent*  ptrMiniTowerComponent = GetComponent( MiniTowerDepth );
  J4VComponent*  ptrMiniConeComponent  = GetComponent( MiniConeDepth );
  J4VComponent*  ptrBlockComponent     = GetComponent( BlockDepth );
  J4VComponent*  ptrTowerComponent     = GetComponent( TowerDepth );
  J4VComponent*  ptrConeComponent      = GetComponent( ConeDepth );

  G4int  coneID      = ptrConeComponent      -> GetMyID();
  G4int  towerID     = GetCloneID( ptrTowerComponent );
  G4int  miniConeID  = ptrMiniConeComponent  -> GetMyID();
  G4int  miniTowerID = ptrMiniTowerComponent -> GetMyID();
  //G4int  miniTowerID = GetCloneID( ptrMiniTowerComponent );  // double replica problem
  G4int  layerID     = ptrLayerComponent     -> GetMyID();
  G4int  subLayerID  = ptrSubLayerComponent  -> GetMyID();

  // flag for checking Barrel or Endcap -------------------------
  G4bool isBarrel    = ( (J4CALCone *)ptrConeComponent ) -> IsBarrel();
  // flag for checking EM or HD ---------------------------------
  G4bool isEM = ((J4CALBlock*)ptrBlockComponent) -> IsEM();

  //  Get particle information
  G4int  preHitID = J4CALSD::GetCurrentPreHitID();
  G4int  trackID  = J4CALSD::GetCurrentTrackID();

  if ( fgCurrentPreHitID < 0 ) {
    fgCurrentPreHitID = J4CALSD::GetCurrentPreHitID();
  }
  
  G4double  tof   = GetTof();
  G4double  edep  = GetEnergyDeposit();
  const G4ThreeVector&  Xcm   = GetPrePosition() * GetEnergyDeposit(); // energy-weighted position vector

  G4int cellID = TVAddress::GetCellID( coneID, towerID, miniConeID, miniTowerID, layerID, subLayerID, isEM );
  
  // check if the cell is already hit
  typedef std::multimap< G4int, J4CALHit* >::iterator MI;
  std::pair< MI, MI > itr_range = fgCalHits.equal_range( cellID );

  if ( itr_range.first == fgCalHits.end() ) {
    // cell is not yet hit.
    // make new hit for that cell and insert to hit buffer.
    J4CALHit *aHit = new J4CALHit( ptrSubLayerComponent, preHitID, trackID, cellID, isEM, isBarrel, edep, tof, Xcm );
    fgCalHits.insert( std::make_pair( cellID, aHit ) );
    ((J4CALHitBuf*)GetHitBuf())->insert( aHit );
  }
  else {
    // loop over hits in a cell, look for the same prehitID
    // if found, update existing hit. else, make a new cell hit.
    G4bool makeNewHit = TRUE;
    for ( MI p = itr_range.first; p!=itr_range.second; ++p ) {
      J4CALHit *aHit = (J4CALHit*)( p -> second );
      G4int aPreHitID = aHit->GetPreHitID();
      if ( aPreHitID == preHitID ) {
	aHit->AddEdep( edep );
	aHit->AddXcm( Xcm );
	if ( tof < aHit->GetTof() ) aHit->SetTof( tof );
	makeNewHit = FALSE;
	break;
      }
    }
    if ( makeNewHit ) {
      J4CALHit *aHit = new J4CALHit( ptrSubLayerComponent, preHitID, trackID, cellID, isEM, isBarrel, edep, tof, Xcm ); 
      fgCalHits.insert( std::make_pair( cellID, aHit ) );
      ((J4CALHitBuf*)GetHitBuf())->insert( aHit );
    }
  }
  
  timer.Stop();
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4CALSubLayerSD::EndOfEvent( G4HCofThisEvent* /* HCTE */ )
{
  fgCurrentPreHitID = -1;
  SetHCID(-1);
  fgCalHits.clear();
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4CALSubLayerSD::DrawAll()
{ }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4CALSubLayerSD::PrintAll()
{
  G4int nHit= ( (J4CALHitBuf*)GetHitBuf() ) -> entries();
  G4cout << "------------------------------------------" << G4endl; 
  G4cout << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4CALHitBuf*)GetHitBuf() )-> PrintAllHits();
}
