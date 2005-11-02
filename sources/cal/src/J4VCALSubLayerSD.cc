// $Id$
//*************************************************************************
//* --------------------
//* J4VCALSubLayerSD
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
#include "J4VCALMiniCone.hh"
#include "J4VCALMiniTower.hh"
#include "J4VCALLayer.hh"
#include "J4VCALSubLayer.hh"
#include "J4VCALSubLayerSD.hh"
#include "J4CALHit.hh"
#include "J4CALSD.hh"
#include "G4Sphere.hh"
#include "J4Timer.hh"
#include "J4CALAddress.hh"
#include "J4CALParameterList.hh"
#include <utility>

//=====================================================================
// static datamember's initialize
G4int J4VCALSubLayerSD::fgLastHCID=-1;
std::multimap<G4int,J4CALHit*> J4VCALSubLayerSD::fgCalHits;

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4VCALSubLayerSD::J4VCALSubLayerSD( J4VDetectorComponent* ptrDetector )
  : J4VSD<J4CALHit>( ptrDetector ),
    fConeID(-1), fTowerID(-1), fMiniConeID(-1), fMiniTowerID(-1), fLayerID(-1), 
   fSubLayerID(-1), fIsBarrel(-1)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCALSubLayerSD::~J4VCALSubLayerSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------

void J4VCALSubLayerSD::Initialize( G4HCofThisEvent* HCTE )
{
  
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
#if 0
  MakeHitBuf( HCTE );
#else
  G4THitsCollection<J4CALHit>* hitbuf; 
  hitbuf = new G4THitsCollection<J4CALHit>( SensitiveDetectorName, collectionName[0] ) ;
  SetHitBuf( (G4VHitsCollection*)hitbuf );
  if ( fgLastHCID < 0  ) {
    //G4int hcID = GetCollectionID(0); 
    fgLastHCID=GetCollectionID(0); 
  }
  else {
    fgLastHCID++;
  }
  HCTE->AddHitsCollection( fgLastHCID, GetHitBuf() );
  // Don't "delete" fCalHits[i]!
  // Geant4 deletes hit objects at the end of the run.
#endif
  
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4VCALSubLayerSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{

  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep( aStep );

  //Don't create hit witout energy deposit.
  if ( GetEnergyDeposit() <= 0 ) return FALSE;
  
#if 0  
  // don't process e/mu/gamma/pi/p with no edep
  G4String pname = GetParticleName();
  G4bool checkable = (pname=="e-") || (pname=="e+") || (pname=="gamma") ||
    (pname=="mu-") || (pname=="mu+") || (pname=="pi0") || (pname=="pi-") || (pname=="pi+") ||
    (pname=="proton") || (pname=="anti_proton");
  if( checkable && GetEnergyDeposit() <= 0 ) return FALSE; // don't process this hit if Edep=0
#endif  

  ////////////////////////////////////////////////////////////////
  // Calorimeter sub structure and depth-------------------------
  // SubLayer->Layer->MiniTower->MiniCone->Block->Tower->Cone->CAL
  ////////////////////////////////////////////////////////////////
  const G4int LayerDepth     = 1;
  const G4int MiniTowerDepth = 2;
  const G4int MiniConeDepth  = 3;
#if 0
  const G4int BlockDepth     = 4;
#endif
  const G4int TowerDepth     = 5;
  const G4int ConeDepth      = 6;

  // poiters for components -------------------------------------
  J4VCALSubLayer*    ptrSubLayerComponent  = (J4VCALSubLayer *)GetComponent();
  J4VComponent*      ptrLayerComponent        = GetComponent( LayerDepth );
  J4VComponent*      ptrMiniTowerComponent    = GetComponent( MiniTowerDepth );
  J4VComponent*      ptrMiniConeComponent     = GetComponent( MiniConeDepth );
#if 0
  J4VComponent*  ptrBlockComponent     = GetComponent( BlockDepth );
#endif
  J4VComponent*      ptrTowerComponent        = GetComponent( TowerDepth );
  J4VComponent*      ptrConeComponent         = GetComponent( ConeDepth );

  G4int  coneID      = ptrConeComponent      -> GetMyID();
  G4int  towerID     = GetCloneID( ptrTowerComponent );
  G4int  miniConeID  = ptrMiniConeComponent  -> GetMyID();
#ifdef __REPLICA__
  G4int  miniTowerID = GetCloneID( ptrMiniTowerComponent );  
#else
  G4int  miniTowerID = ptrMiniTowerComponent -> GetMyID();
#endif
  G4int  layerID     = ptrLayerComponent     -> GetMyID();
  G4int  subLayerID  = ptrSubLayerComponent  -> GetMyID();

  // flag for checking Barrel or Endcap -------------------------
  G4bool isBarrel    = ( (J4CALCone *)ptrConeComponent ) -> IsBarrel();
  // flag for checking EM or HD ---------------------------------
  G4bool isEM =IsEM();

  //  Get particle information
  G4int  preHitID = J4CALPreHitKeeper::GetInstance()->GetCurrentPreHitID();
  //G4int  pdgcode = GetParticle()->GetPDGEncoding();

  G4double  tof   = GetTof();
  G4double  edep  = GetEnergyDeposit();
  const G4ThreeVector&  Xcm   = GetPrePosition() * GetEnergyDeposit(); // energy-weighted position vector

  G4int cellID = J4CALAddress::GetCellID( coneID, towerID, miniConeID, miniTowerID, layerID, subLayerID, isEM );
  
  // check if the cell is already hit
  typedef std::multimap< G4int, J4CALHit* >::iterator MI;
  std::pair< MI, MI > itr_range = fgCalHits.equal_range( cellID );

  J4CALParameterList *ptrList= J4CALParameterList::GetInstance();

  if ( itr_range.first == fgCalHits.end() ) {
    // cell is not yet hit.
    // make new hit for that cell and insert to hit buffer.

    //caluclate hit cell position.
    G4double nminitower = isEM ?
                          ptrList->GetEMMiniTowerNClones(): 
                          ptrList->GetHDMiniTowerNClones();
    G4double phitower   = nminitower*towerID  + miniTowerID;

    G4Sphere *cellsphere  = (G4Sphere*)(ptrSubLayerComponent->GetSolid());
    G4Sphere *towersphere = (G4Sphere*)(ptrTowerComponent->GetSolid());
    G4double cellrho   = cellsphere->GetInsideRadius();
    G4double celltheta = cellsphere->GetStartThetaAngle() + 0.5*cellsphere->GetDeltaThetaAngle();
    G4double cellphi   = towersphere->GetStartPhiAngle() + (phitower + 0.5)*cellsphere->GetDeltaPhiAngle();

    G4double cellX = cellrho*std::sin(celltheta)*std::cos(cellphi);
    G4double cellY = cellrho*std::sin(celltheta)*std::sin(cellphi);
    G4double cellZ = cellrho*std::cos(celltheta);

    J4CALHit *aHit = new J4CALHit( ptrSubLayerComponent, preHitID, cellID, isEM, isBarrel, edep, tof, GetParticle(), Xcm, G4ThreeVector(cellX,cellY,cellZ) );
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
	if ( tof < aHit->GetTof() ) {
	  aHit->SetTof( tof );
	  aHit->SetParticle( GetParticle() );
	}
	makeNewHit = FALSE;
	break;
      }
    }
    if ( makeNewHit ) {
      //caluclate hit cell position.
      G4double nminitower = isEM ?
                            ptrList->GetEMMiniTowerNClones(): 
                            ptrList->GetHDMiniTowerNClones();
      G4double phitower   = nminitower*towerID  + miniTowerID;

      G4Sphere *cellsphere  = (G4Sphere*)(ptrSubLayerComponent->GetSolid());
      G4Sphere *towersphere = (G4Sphere*)(ptrTowerComponent->GetSolid());
      G4double cellrho   = cellsphere->GetInsideRadius();
      G4double celltheta = cellsphere->GetStartThetaAngle() + 0.5*cellsphere->GetDeltaThetaAngle();
      G4double cellphi   = towersphere->GetStartPhiAngle() + (phitower + 0.5)*cellsphere->GetDeltaPhiAngle();

      G4double cellX = cellrho*std::sin(celltheta)*std::cos(cellphi);
      G4double cellY = cellrho*std::sin(celltheta)*std::sin(cellphi);
      G4double cellZ = cellrho*std::cos(celltheta);

      J4CALHit *aHit = new J4CALHit( ptrSubLayerComponent, preHitID, cellID, isEM, isBarrel, edep, tof, GetParticle(), Xcm, G4ThreeVector(cellX,cellY,cellZ) );
      fgCalHits.insert( std::make_pair( cellID, aHit ) );
      ((J4CALHitBuf*)GetHitBuf())->insert( aHit );
    }
  }
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------

void J4VCALSubLayerSD::EndOfEvent( G4HCofThisEvent* /* HCTE */ )
{
  SetHCID(-1);
  fgCalHits.clear();
}

//=====================================================================
//* clear -------------------------------------------------------------


//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4VCALSubLayerSD::DrawAll()
{ }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4VCALSubLayerSD::PrintAll()
{
  G4int nHit= ( (J4CALHitBuf*)GetHitBuf() ) -> entries();
  G4cout << "------------------------------------------" << G4endl; 
  G4cout << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4CALHitBuf*)GetHitBuf() )-> PrintAllHits();
}
