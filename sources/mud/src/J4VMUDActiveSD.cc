// $Id$
//*************************************************************************
//* --------------------
//* J4VMUDActiveSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include <iomanip>
#include "J4VSD.hh"
#include "J4MUDHit.hh"
#include "J4VMUDActiveSD.hh"
#include "J4VDetectorComponent.hh"
#include "J4VMUDDetectorComponent.hh"
#include "J4VMUDEndcapTrap.hh"
#include "J4MUDBarrelActive.hh"
#include "J4MUDEndcapActive.hh"
#include "J4MUDFrontEndcapActive.hh"
#include "J4MUDPreHitKeeper.hh"
 
//=====================================================================
//---------------------
// class definition
//---------------------
G4int J4VMUDActiveSD::fgLastHCID=-1;

//=====================================================================
//* constructor -------------------------------------------------------
J4VMUDActiveSD::J4VMUDActiveSD( J4VDetectorComponent* detector )
: J4VSD<J4MUDHit>( detector )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VMUDActiveSD::~J4VMUDActiveSD() { }

//=====================================================================
//* Initialize --------------------------------------------------------
void J4VMUDActiveSD::Initialize( G4HCofThisEvent* HCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
  
  //MakeHitBuf( HCTE );  
  G4THitsCollection<J4MUDHit>* hitbuf; 
  hitbuf = new G4THitsCollection<J4MUDHit>( SensitiveDetectorName, collectionName[0] ) ;
  SetHitBuf( (G4VHitsCollection*)hitbuf );
  if ( fgLastHCID < 0  ) {
    //G4int hcID = GetCollectionID(0); 
    fgLastHCID=GetCollectionID(0); 
  }
  else {
    fgLastHCID++;
  }
  HCTE->AddHitsCollection( fgLastHCID, GetHitBuf() ); 

  if ( fMUDHits ) fMUDHits = 0;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4VMUDActiveSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{

  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);
   
  //Only when a charged particle has just come into a sensitive detector,
  //create a new hit
  
  //if ( GetCharge() == 0. ) return false;

  //Get perticle information
  J4VComponent*          location      = GetComponent();
  J4VComponent*          blockPtr      = GetComponent(1);

  G4int                  preHitID      = J4MUDPreHitKeeper::GetInstance()->GetCurrentPreHitID();
  G4int                  trackID       = GetTrackID();
  G4int                  mothertrackID = GetMotherTrackID();
  G4ParticleDefinition * particle      = GetParticle();
  G4double               tof           = GetTof();
  G4double               edep          = GetEnergyDeposit();
  G4double               etot          = GetTotalEnergy();
  G4ThreeVector          p             = GetMomentum();
  const G4ThreeVector&   pre           = GetPrePosition();
  const G4ThreeVector&   post          = GetPostPosition();

  G4int                  blockID       = blockPtr->GetMyID();
  G4int                  layerID       = location->GetMyID();

  fIsBarrel      = IsBarrel();
  fIsFront       = IsFront();

  if ( fMUDHits == 0 ) {
     fMUDHits =  new J4MUDHit( location, blockID, layerID, fIsBarrel, fIsFront, preHitID, 
                               trackID, mothertrackID, particle, tof, edep, etot, p, pre, post );
    ( (J4MUDHitBuf*)GetHitBuf() )->insert( fMUDHits );
  } else  {
    G4int curPreHitID = fMUDHits->GetPreHitID();
    if ( curPreHitID == preHitID ) {
      fMUDHits->AddEdep( edep );
      if ( tof < fMUDHits -> GetTof() ) {
        fMUDHits->SetTof( tof );
      } 
    } else {
     fMUDHits =  new J4MUDHit( location, blockID, layerID, fIsBarrel, fIsFront, preHitID, 
                               trackID, mothertrackID, particle, tof, edep, etot, p, pre, post );
    ( (J4MUDHitBuf*)GetHitBuf() )->insert( fMUDHits );   
   }
  }
  return true;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4VMUDActiveSD::EndOfEvent( G4HCofThisEvent* /* HCTE */ ) 
{ 
  SetHCID(-1);
}

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4VMUDActiveSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4VMUDActiveSD::PrintAll()
{
  G4int nHit= ( (J4MUDHitBuf*)GetHitBuf() )-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4MUDHitBuf*)GetHitBuf() )-> PrintAllHits();
}

//=====================================================================
//* IsSDFront ---------------------------------------------------------
G4bool J4VMUDActiveSD::IsSDFront( const G4ThreeVector& pos, const G4ThreeVector& p ) const
{
  J4MUDParameterList* ptrList = J4MUDParameterList::GetInstance();
  //static G4double tolerance = 5.;
  static G4double tolerance = 10.;
  J4VComponent*   location  = GetComponent();
  G4int    myID             = location->GetMyID();
  G4double frontR           = 0;
  G4double frontZ           = 0;

  // Barrel
  if ( fIsBarrel && !fIsFront ) { 
    frontR = ((J4MUDBarrelActive*)location)->J4MUDBarrelActive::GetFront(myID);
    frontZ = ((J4MUDEndcapActive*)location)->J4MUDEndcapActive::GetFront(myID);
#if 0
    G4double frontX           = 0;
    frontX = frontR * tan( 0.5*ptrList->GetTrapDeltaPhi() ); 
    if (  frontX - abs( pos.x() )  >= 0
      &&  frontR - abs( pos.y() )  <= tolerance*kCarTolerance 
      &&  frontZ - abs( pos.z() )  >= 0 )
      return true;
#else
    if ( abs( pos.perp() - frontR ) <= tolerance*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0. ) 
      return true;
    if ( abs( abs(pos.z()) - frontZ ) <= tolerance*kCarTolerance && p.z() * pos.z() > 0. ) 
      return true;
#endif
  }
  // Front Endcap
  if ( !fIsBarrel && fIsFront ) { 
    frontR = ptrList->GetEndcapInnerR();
    frontZ = ((J4MUDFrontEndcapActive*)location)->J4MUDFrontEndcapActive::GetFront(myID);
    if ( abs( pos.perp() - frontR ) <= tolerance*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0. ) 
      return true;
    if ( abs( abs(pos.z()) - frontZ ) <= tolerance*kCarTolerance && p.z() * pos.z() > 0. ) 
      return true;
  }
  // Endcap
  if ( !fIsBarrel && !fIsFront ) {
    frontR = ptrList -> GetEndcapInnerR(); 
    frontZ = ((J4MUDEndcapActive*)location)->J4MUDEndcapActive::GetFront(myID);
    if ( abs( pos.perp() - frontR ) <= tolerance*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0. ) 
      return true;
    if ( abs( abs(pos.z()) - frontZ ) <= tolerance*kCarTolerance && p.z() * pos.z() > 0. ) 
      return true;
  }
   
  
  return false;
}
