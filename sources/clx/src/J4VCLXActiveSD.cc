// $Id$
//*************************************************************************
//* --------------------
//* J4CLXActiveSD
//* --------------------
//* (Description)
//* 	Pure Virtual of ActiveSD class
//*     
//* (Update Record)
//*     2006/05/01  H.Ono Original version
//*************************************************************************
#include "J4CLXHit.hh"
#include "J4VCLXActiveSD.hh"
#include "J4CLXAddress.hh"
#include "J4VCLXCell.hh"
#include "J4VCLXStrip.hh"
#include "J4VCLXTrapStrip.hh"
#include "J4VCLXSubLayer.hh"
#include "J4VCLXLayer.hh"
#include "J4VCLXBlock.hh"
#include "J4CLXSD.hh"
#include "J4VSD.hh"
#include "J4CLXPreHitKeeper.hh"
#include "J4CLXParameterList.hh"
#include "G4Track.hh"

//=====================================================================
// static datamember's initialize
G4int J4VCLXActiveSD::fgLastHCID = -1;
std::multimap<G4int,J4CLXHit*> J4VCLXActiveSD::fgClxHits;

//* constructor -------------------------------------------------------
J4VCLXActiveSD::J4VCLXActiveSD( J4VDetectorComponent* ptrDetector)
  : J4VSD<J4CLXHit>( ptrDetector )
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXActiveSD::~J4VCLXActiveSD()
{}

//=====================================================================
//* Initialize --------------------------------------------------------
void J4VCLXActiveSD::Initialize( G4HCofThisEvent* HCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
#if 0
  MakeHitBuf( HCTE );
#else
  G4THitsCollection<J4CLXHit>* hitbuf;
  hitbuf = new G4THitsCollection<J4CLXHit>( SensitiveDetectorName, collectionName[0] );
  SetHitBuf( (G4VHitsCollection*)hitbuf );
  if ( fgLastHCID < 0 ) {
    fgLastHCID = GetCollectionID( 0 );
  } else {
    fgLastHCID++;
  }
  HCTE->AddHitsCollection( fgLastHCID, GetHitBuf() );
#endif

  //* Initialize hit pointer
  //if ( fCLXHits ) fCLXHits = 0;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4VCLXActiveSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  //* In order to use Get function, you must call SetNewStep() at first.
  SetNewStep( aStep );

  //* Skip no energy deposit event-------------------------------------
  if ( GetEnergyDeposit() <= 0 ) return FALSE;

  
  //-------------------------------------------------------------------
  // Calorimeter Sub-Structure
  // cell -> strip -> trapStrip -> SubLayer -> Layer -> Block -> CLX
  //-------------------------------------------------------------------
  G4int cellDepth     = 0;
  //  G4int stripDepth    = 1;
  G4int ptrStripDepth = 2;
  //  G4int subLayerDepth = 3;
  G4int layerDepth    = 4;
  G4int blockDepth    = 5;

  //* Get Component
  J4VCLXCell*      ptrCell      = (J4VCLXCell*)GetComponent( cellDepth );
  //  J4VCLXStrip*     ptrStrip     = (J4VCLXStrip*)GetComponent( stripDepth );
  J4VCLXTrapStrip* ptrTrapStrip = (J4VCLXTrapStrip*)GetComponent( ptrStripDepth );  
  //  J4VCLXSubLayer*  ptrSubLayer  = (J4VCLXSubLayer*)GetComponent( subLayerDepth );
  J4VCLXLayer*     ptrLayer     = (J4VCLXLayer*)GetComponent( layerDepth );
  J4VCLXBlock*     ptrBlock     = (J4VCLXBlock*)GetComponent( blockDepth );

  G4bool  isEM        = ptrCell->IsEM();
  //G4int   isEndcap    = ptrBlock->IsEndcap();
  G4bool  isBarrel    = ptrCell->IsBarrel();
  
  G4int   cellID      = GetCloneID( ptrCell );
  G4int   stripID     = ( isBarrel ) ? GetCloneID( ptrTrapStrip ) : ptrTrapStrip->GetMyID();
  G4int   layerID     = ( isBarrel ) ? ptrLayer->GetMyID() : GetCloneID( ptrLayer );
  G4int   blockID     = ( isBarrel ) ? ptrBlock->GetMyID() : ptrBlock->GetCopyNo();
  
  //* Particle information
  G4int    trackID        =  GetTrackID();
  G4int    motherTrackID  =  GetMotherTrackID();
  
  G4int    preHitID =  J4CLXPreHitKeeper::GetInstance()->GetCurrentPreHitID();
  G4double edep     =  GetEnergyDeposit();
  G4double tof      =  GetTof();
  const G4ThreeVector  &Xcm      = GetPrePosition() * GetEnergyDeposit();
  G4ParticleDefinition *particle = GetParticle();
  //G4int    pdg      = particle->GetPDGEncoding();

  //* Get global cell ID from each ID
  G4int globalID = J4CLXAddress::GetGlobalCellID( isEM, isBarrel, blockID, layerID, stripID, cellID );
  const G4ThreeVector  &Xcell = J4CLXAddress::GetCellPosition( globalID, isEM );
  //const G4ThreeVector  &Xcell = GetPrePosition();

#if 0
  const G4ThreeVector  &pos   = GetPrePosition(); 
  //* Open Parameter List
  J4CLXParameterList* ptrList = J4CLXParameterList::GetInstance();
  if ( ( Xcell - pos ).mag() > ptrList->GetCellSize() ) {
    std::cerr << "**** Cell position generator error "
              << "cellPos=" << J4CLXAddress::GetCellPosition( globalID, isEM ) << " "
              << "prepos=" << GetPrePosition() << std::endl;
  }
#endif

  if ( cellID != J4CLXAddress::GetCellID( globalID, isEM ) ) { 
   std::cerr << "cellID=" << cellID << " not equal " 
             << J4CLXAddress::GetCellID( globalID, isEM )
             << std::endl;
  }

  if ( stripID != J4CLXAddress::GetStripID( globalID, isEM ) )  {
   std::cerr << "stripID=" << stripID << " not equal " 
             << J4CLXAddress::GetStripID( globalID, isEM )
             << std::endl;
  }

  if ( layerID != J4CLXAddress::GetLayerID( globalID, isEM ) )  {
   std::cerr << "layerID=" << layerID << " not equal " 
             << J4CLXAddress::GetLayerID( globalID, isEM )
             << std::endl;
  }

  if ( blockID != J4CLXAddress::GetBlockID( globalID ) )  {
   std::cerr << "blockID=" << blockID << " not equal " 
             << J4CLXAddress::GetBlockID( globalID )
             << std::endl;
  }

  //* Check cell has already hit or not --------------------------------
  typedef std::multimap< G4int, J4CLXHit* >::iterator cellHitItr;
  // cellHitRange has lower(first) and upper(last) bound of fgClxHits refered by key "globalID"
  std::pair< cellHitItr, cellHitItr > cellHitRange = fgClxHits.equal_range( globalID );

  if ( cellHitRange.first == fgClxHits.end() ) {
    //* Does not find this key globalID in fgClxHits,
    //  Cell is not yet hit, create new hit and insert to the hit buffer.
    J4CLXHit* cellHit = new J4CLXHit( ptrCell, preHitID, globalID, isEM, isBarrel, edep, tof, particle, Xcm, Xcell, trackID, motherTrackID ) ;
    fgClxHits.insert( std::make_pair( globalID, cellHit ) );
    ((J4CLXHitBuf*)GetHitBuf())->insert( cellHit );
    
  } else {
    //* Found this key cellID in fgClxHits, cell is already hit.
    //  Next check mother particle in same globalID.
    //  If mother particle is same(same preHitID), update hit information
    //  else create new cellHit (althogh cellID is same) and insert to the fgClxHits
    
    G4bool isDiffMother = true;
    for ( cellHitItr itr = cellHitRange.first; itr != cellHitRange.second; ++itr ) {
      //* Loop over the hits in a same cell.
      //  Search same preHitID cellHit in fgClxHits
      //  If such cellHit is found, update existing cellHit information.
      //  Else create new cellHit and insert to the fgClxHits
      
      J4CLXHit* cellHit   = (J4CLXHit*)( itr->second );
      G4int     aPreHitID = cellHit->GetPreHitID();

      if ( aPreHitID == preHitID ) {
	//* preHitID and currentPreHitID are same,
	//  Mother particle might be same, update hit information.
	
	cellHit->AddEdep( edep ) ;
	cellHit->AddXcm( Xcm ) ;
	//* If tof earlier, update tof.
	if ( tof < cellHit->GetTof() ) {
	  cellHit->SetTof( tof );
	  cellHit->SetParticle( GetParticle() );
	}

	//* After updating hit, Tagged to skip making new hit.
	isDiffMother = false;
	break;
      }
    }
    
    //* Same globalID but different mother particle.
    //  Create new hit and insert to the fgClxHits
    if ( isDiffMother ) {
      J4CLXHit* cellHit = new J4CLXHit( ptrCell, preHitID, globalID, isEM, isBarrel, edep, tof, particle, Xcm, Xcell, trackID, motherTrackID );
      fgClxHits.insert( std::make_pair( globalID, cellHit ) );
      ((J4CLXHitBuf*)GetHitBuf())->insert( cellHit );
    }
  }
  return true;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4VCLXActiveSD::EndOfEvent( G4HCofThisEvent* /*HCTE*/ )
{
  SetHCID( -1 );
  fgClxHits.clear();
}

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4VCLXActiveSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4VCLXActiveSD::PrintAll()
{
  G4int nHit = ( (J4CLXHitBuf*)GetHitBuf() )->entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4CLXHitBuf*)GetHitBuf() )->PrintAllHits();
}
