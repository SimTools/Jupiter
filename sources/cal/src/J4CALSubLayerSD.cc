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

//=====================================================================
// static datamember's initialize
G4int J4CALSubLayerSD::fgLastHCID=-1;
G4int J4CALSubLayerSD::currentPreHitID = -1;
std::vector<J4CALHit*> J4CALSubLayerSD::fgCalHits;

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
{
  // Make new hit object
  fNTowers = ( (J4CALSubLayer *)ptrDetector ) -> GetNTowers();
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALSubLayerSD::~J4CALSubLayerSD()
{
//#ifndef __GEANT452__
//  for ( G4int i = 0; i < fgCalHits.size(); i++  ) {
//    if ( fgCalHits[i] )  delete fCalHits[i];
//   }
//  
//#endif
}

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
  
  for ( G4int i = 0; i < fNTowers; i++ ) {
    fgCalHits.push_back( 0 );
  }
  //InitCellID();
  //fCellID = -1;
  
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

#if 1
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
  //G4int  miniTowerID = GetCloneID( ptrMiniTowerComponent );
  G4int  layerID     = ptrLayerComponent     -> GetMyID();
  G4int  subLayerID  = ptrSubLayerComponent  -> GetMyID();

  // flag for checking Barrel or Endcap -------------------------
  G4bool isBarrel    = ( (J4CALCone *)ptrConeComponent ) -> IsBarrel();
  // flag for checking EM or HD ---------------------------------
  const G4String& firstName = ( (J4CALBlock *)ptrBlockComponent ) -> GetFirstName();
  G4bool isEM;
  if ( firstName == "EM" ) isEM = TRUE;
  else isEM = FALSE;
#endif

  //  Get perticle information
  G4int  preHitID = J4CALSD::GetCurrentPreHitID();
  
  if ( currentPreHitID < 0 ) {
    currentPreHitID = J4CALSD::GetCurrentPreHitID();
  }
  
  G4double  tof   = GetTof();
  G4double  edep  = GetEnergyDeposit();
  const G4ThreeVector&  Xcm   = GetPrePosition() * GetEnergyDeposit();

  TVAddress* ptrAddress = new TVAddress( coneID, towerID, miniConeID, miniTowerID, layerID, subLayerID, isBarrel, isEM );
  G4int cellID = GetCellID( ptrAddress );
  
  if ( fgCalHits[cellID] == 0 ) {
    //    ptrAddress -> Print();
    fgCalHits[cellID] = new J4CALHit( ptrSubLayerComponent, ptrAddress, edep, tof, Xcm );
    ((J4CALHitBuf*)GetHitBuf()) -> insert( fgCalHits[cellID] );
    fgCalHits[cellID] -> AddHitlet( currentPreHitID, ptrAddress, edep, tof, Xcm );
  } else { // fCalHits[checkID] has been created.
    if ( currentPreHitID  == preHitID ) {
      //G4cerr << "Should be accumulated energy!" << G4endl;
      fgCalHits[cellID] -> AddEdep( edep );
      fgCalHits[cellID] -> AddXcm( Xcm );
      fgCalHits[cellID] -> SetHitletTof( tof );
    } else { // currentPreHitID != preHitID
      currentPreHitID = preHitID;
      fgCalHits[cellID] -> AddHitlet( currentPreHitID, ptrAddress, edep, tof, Xcm );
      G4cerr << "***** currentPreHitID != preHitID && Address has already created." << G4endl;
      ptrAddress -> Print();
    }
  }

  if ( cellID >= (G4int)fgCalHits.size() ) G4cerr << "checkID has leaked out! checkID = " << cellID << G4endl;

  timer.Stop();
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4CALSubLayerSD::EndOfEvent( G4HCofThisEvent* /* HCTE */ )
{
  currentPreHitID = -1;
  SetHCID(-1);
  fgCalHits.clear();
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------

void J4CALSubLayerSD::DrawAll()
{
}

//=====================================================================
//* PrintAll ----------------------------------------------------------

void J4CALSubLayerSD::PrintAll()
{
  G4int nHit= ( (J4CALHitBuf*)GetHitBuf() ) -> entries();
  G4cout << "------------------------------------------" << G4endl; 
  G4cout << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4CALHitBuf*)GetHitBuf() )-> PrintAllHits();
}
