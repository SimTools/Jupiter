#include "J4CLXHit.hh"
#include "J4VCLXActiveSD.hh"
#include "J4VCLXCell.hh"
#include "J4VCLXBoard.hh"
#include "J4VCLXSubLayer.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXBlock.hh"
#include "J4CLXSD.hh"
#include "J4CLXAddress.hh"
#include "J4VSD.hh"
#include "J4CLXPreHitKeeper.hh"
#include "G4Track.hh"

//=====================================================================
// static datamember's initialize
G4int J4VCLXActiveSD::fgLastHCID = -1;
G4int J4VCLXActiveSD::tmpLayerID[3] = {-1, -1, -1};
G4int J4VCLXActiveSD::tmpCellID[3] = {-1, -1, -1};
G4int J4VCLXActiveSD::loopNo = 0;

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXActiveSD::J4VCLXActiveSD( J4VDetectorComponent* ptrDetector)
    : J4VSD<J4CLXHit>(ptrDetector)
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXActiveSD::~J4VCLXActiveSD() { }

//=====================================================================
//* Initialize --------------------------------------------------------
void J4VCLXActiveSD::Initialize( G4HCofThisEvent* HCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"
#if 0
    MakeHitBuf(HCTE);
#else
    G4THitsCollection<J4CLXHit>* hitbuf;
    hitbuf = new G4THitsCollection<J4CLXHit>(SensitiveDetectorName, collectionName[0]);
    SetHitBuf((G4VHitsCollection*)hitbuf);
    if(fgLastHCID < 0) {
	fgLastHCID = GetCollectionID(0);
    } else {
	fgLastHCID++;
    }
    HCTE -> AddHitsCollection(fgLastHCID, GetHitBuf());
#endif

    if(fCLXHits) fCLXHits = 0;
}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4VCLXActiveSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{
  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);

//don't process e/mu/pi/p with no edep
  if(GetEnergyDeposit() <= 0) return FALSE;
#if 0
  G4String pname = GetParticleName();
  G4bool checkable = (pname == "e-") || (pname == "e+") || (pname == "gamma") ||
      (pname == "mu-") || (pname == "mu+") || (pname == "pi0") || (pname == "pi-") ||
      (pname == "pi+") || (pname == "proton") || (pname == "anti_proton");
  if(checkable && GetEnergyDeposit() <= 0) return FALSE; // don't process this hit if Edep=0
#endif
///////////////////////////////////////////////////////////////////////
// Calorimeter sub structure and depth
// Cell -> Board -> SubLayer -> Layer -> MiniBlock -> Block -> CLX
///////////////////////////////////////////////////////////////////////
//  G4int LargeBoxCellDepth;
  G4int BoardDepth = 1;
//  G4int SubLayerDepth = 2;
  G4int LayerDepth = 3;
//  G4int MiniBlockDepth = 4;
  G4int BlockDepth = 5;

// pointer for components ---------------------------------------------
  J4VCLXCell* ptrCellComponent = (J4VCLXCell *)GetComponent();
//  J4VComponent* ptrLargeBoxCelComponent;
  if(!(ptrCellComponent -> IsTrap())) {
//      LargeBoxCeelDepth = 1;
//      ptrLargeBoxCellComponent = GetComponent(LargeBoxCellDepth);
      BoardDepth++;
//      SubLayerDepth++;
      LayerDepth++;
//      MiniBlockDepth++;
      BlockDepth++;
  }
  J4VComponent* ptrBoardComponent = GetComponent(BoardDepth);
//  J4VComponent* ptrSubLayerComponent = GetComponent(SubLayerDepth);
  J4VComponent* ptrLayerComponent = GetComponent(LayerDepth);
//  J4Component* ptrMiniBlockComponent = GetComponent(MiniBlockDepth);
  J4VComponent* ptrBlockComponent = GetComponent(BlockDepth);

  G4int cellCloneID = -1;
  if(!(ptrCellComponent -> IsTrap())) {
     cellCloneID = GetCloneID(ptrCellComponent);
  }
  G4int boardID = GetCloneID(ptrBoardComponent);
  G4int layerID = ptrLayerComponent -> GetMyID();
  G4bool isEM = IsEM();
  G4int blockID = ptrBlockComponent -> GetCopyNo();

  J4CLXAddress *cellAddress = new J4CLXAddress(blockID, isEM, layerID, boardID, cellCloneID, ptrCellComponent);
  G4int fLayerID = cellAddress -> GetLayerID();
  G4int fCellID = cellAddress -> GetCellID();
  const G4ThreeVector& fCellPosition = cellAddress -> GetCellPosition();
  delete cellAddress;

// Get particle information
  G4int  preHitID = J4CLXPreHitKeeper::GetInstance()->GetCurrentPreHitID();
  G4double tof = GetTof();
  G4double edep = GetEnergyDeposit();
  const G4ThreeVector& Xcm = GetPrePosition() * GetEnergyDeposit();

  if(fCLXHits == 0) {
      fCLXHits = new J4CLXHit(ptrCellComponent, preHitID, fLayerID, fCellID, isEM, fCellPosition, edep, tof, GetParticle(), Xcm);
      ((J4CLXHitBuf*)GetHitBuf()) -> insert(fCLXHits);
  } else {
      G4int curPreHitID = fCLXHits->GetPreHitID();
      //Loop Check
      if(curPreHitID == preHitID) {
	  if(LoopChecker(fLayerID, fCellID)) {
	      loopNo++;
	  } else {
	      loopNo = 0;
	  }
	  if(loopNo > 999) {
	      G4Track *atrack=aStep->GetTrack();
	      G4Track * aNonConstTrack = const_cast<G4Track*>(atrack);
	      aNonConstTrack->SetTrackStatus(fStopAndKill);
	      G4cerr << " Track terminated due to too many step " << G4endl;
	      G4cerr << "track ID=" << aStep->GetTrack()->GetTrackID() ;
	      G4cerr << " PDG=" << aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
	      G4cerr << " KE=" << aStep->GetTrack()->GetKineticEnergy() ;
	      G4cerr << " time=" << aStep->GetTrack()->GetGlobalTime()/nanosecond << G4endl;
	      G4cerr << " Volume=" << aStep->GetTrack()->GetVolume()->GetName()
		     << "(" << tmpCellID[0] << "," << fCellID << ")";
	      G4cerr << G4endl;

	      loopNo = 0;

	      return false;
	  }
      }

      if(curPreHitID == preHitID) {
	  fCLXHits -> AddEdep(edep);
	  fCLXHits -> AddXcm(Xcm);
	  if(tof < fCLXHits -> GetTof()) {
	      fCLXHits -> SetTof(tof);
	      fCLXHits->SetParticle(GetParticle());
	  }
      } else {
	  fCLXHits = new J4CLXHit(ptrCellComponent, preHitID, fLayerID, fCellID, isEM, fCellPosition, edep, tof, GetParticle(), Xcm);
	  ((J4CLXHitBuf*)GetHitBuf()) -> insert(fCLXHits);

	  loopNo = 0;
      }
  }

  for(G4int i = 2; i > 0; --i) {
      tmpLayerID[i] = tmpLayerID[i - 1];
      tmpCellID[i] = tmpCellID[i - 1];
  }
  tmpLayerID[0] = fLayerID;
  tmpCellID[0] = fCellID;

  return true;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4VCLXActiveSD::EndOfEvent(G4HCofThisEvent* /*HCTE*/)
{
    SetHCID(-1);
}

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4VCLXActiveSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4VCLXActiveSD::PrintAll()
{
  G4int nHit= ( (J4CLXHitBuf*)GetHitBuf() )-> entries();
  G4cout << "------------------------------------------" << G4endl
         << "*** tracker Hit (#hits=" << nHit << ")" << G4endl;
  ( (J4CLXHitBuf*)GetHitBuf() )-> PrintAllHits();
}

//=====================================================================
//* LoopChecker -------------------------------------------------------
G4bool J4VCLXActiveSD::LoopChecker(G4int layerID, G4int cellID)
{
    G4bool layerCheck, cellCheck;

    if(tmpLayerID[2] == tmpLayerID[0] && tmpLayerID[1] == layerID) {
	layerCheck = TRUE;
    } else {
	layerCheck = FALSE;
    }

    if(tmpCellID[2] == tmpCellID[0] && tmpCellID[1] == cellID) {
	cellCheck = TRUE;
    } else {
	cellCheck = FALSE;
    }

    return layerCheck && cellCheck;
}
