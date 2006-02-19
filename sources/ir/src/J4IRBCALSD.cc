// $Id$
//*************************************************************************
//* --------------------
//* J4IRBCALSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2006/01/27 A.Miyamoto  Original version
//*************************************************************************
//#include "J4TPCPostHit.hh"
//#include "J4TPCPostHitKeeper.hh"
#include "J4IRBCAL.hh"
#include "J4IRBCALSD.hh"
#include "J4IRBCALLayer.hh"
#include "G4Tubs.hh"
#include "J4ParameterTable.hh"
//#include "J4CALPreHit.hh"
//#include "J4CALPreHitKeeper.hh"
//#include "J4CALPostHit.hh"
//#include "J4CALPostHitKeeper.hh"
//#include "J4CAL.hh"
//#include "J4CALCone.hh"
//#include "J4VCALMiniTower.hh"
//#include "J4CALEM.hh"
//#include "J4CALParameterList.hh"
//#include "J4TrackingAction.hh"
#include <cmath>
#include <utility>

J4IRBCALHit *J4IRBCALSD::fLastHit=0;
std::multimap<G4int,J4IRBCALHit*> J4IRBCALSD::fgBCALHits;

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4IRBCALSD::J4IRBCALSD( J4IRBCALSensor* detector )
 :J4VSD<J4IRBCALHit>( detector )
{
  //  BCAL Geometry
  //  BCAL.Front/Tail -> BCALLayer ---> BCALSensor
  //                                +-> BCALSubLayer
  //  std::cerr << " J4IRBCALSD .. constructed. " << std::endl;
  DefineCells(detector);

  //  J4TrackingAction::GetInstance()->Add(J4CALPreHitKeeper::GetInstance());
  //  J4TrackingAction::GetInstance()->Add(J4CALPostHitKeeper::GetInstance());
}

//=============================================================================
void J4IRBCALSD::DefineCells(J4IRBCALSensor *detector)
{
// Define cell for this sensor
  G4Tubs *solid=(G4Tubs*)detector->GetSolid();
  //  G4double rmin=solid->GetInnerRadiusMinusZ();
  //  G4double rmax=solid->GetOuterRadiusMinusZ();
  G4double zhlf=solid->GetZHalfLength();

  fLayer=(J4IRBCALLayer*)detector->GetMother();
  fBCAL=(J4IRBCAL*)(fLayer->GetMother());
  G4Tubs *sbmo=(G4Tubs*)fBCAL->GetSolid();
  G4double rminmo=sbmo->GetInnerRadius();
  G4double rmaxmo=sbmo->GetOuterRadius();
  //  G4double hzmo  =sbmo->GetZHalfLength();

  G4double zmo=fBCAL->GetZpos();
  //  std::cerr << "BCAL " <<  detector->GetMyID() << " zblock=" << zmo << std::endl;
  // Zcoordinate of the front surface of this sensor(zsensor) is 
  // BCAL.z_center + Layer.z_center + Sensor.z_center - sensor_halfwidth
  G4double zsensor=detector->GetZCenter()+(fLayer->GetTranslation()).z()
    +(zmo+sbmo->GetZHalfLength())-zhlf;
  //  std::cerr << "BCAL " <<  detector->GetName() << " zsensor=" << zsensor << std::endl;

  //  string fbname[2]={string("Front"),string("Tail")};
// Cell sizes are defined by the fron surface of BCAL Fron or 
// Tail, not by those at BCALSensor.  It defines ranges of costheta 
// it is then transfered to the radius of BCALSensor.
//  Signal position at the front surface of BCALSensor is used 
//  define the cell to get signal.
//  Here "Front" means the one closer to the IP  
// Default parameters  
// Radial division of Front BCAL: 8.2 cm -> 13.0cm : NDIVR=5; (DeltaR=0.96cm)
//                    Tail  BCAL: 9.2435 cm -> 17.696cm : NDIVPhi=9; (DeltaR=0.939cm) 
  fNDivR = J4ParameterTable::GetValue(
				 "J4IR.BCAL.NDIVR",5);
  fNDivPhi = J4ParameterTable::GetIValue(
	"J4IR.BCAL.NDIVPhi","10 10 10 10 10",fNDivR);

  G4double rstepmo=(rmaxmo-rminmo)/(G4double)fNDivR;
  //  std::cerr << " fNDivR=" << fNDivR << std::endl;
  //  std::cerr << " ind=" << ind << std::endl;
  for(G4int ir=0; ir<=fNDivR;ir++) {
	  G4double r=(rminmo+rstepmo*(G4double)ir)/zmo*zsensor;
	  fRbound.push_back(r);
	  if( ir != fNDivR ) { fPhiStep.push_back(pi2/(G4double)fNDivPhi[ir]) ;
	  //		  std::cerr << " PhiStep=" << fPhiStep[ir] << std::endl;
      }
   }   	

 
}
//=====================================================================
void J4IRBCALSD::GetRPhiBin(const G4ThreeVector x, G4int &ir, G4int &iphi)
{
  // Define CELL ID : ir = 0 to fNDivR-1,
  //    ir = fNDivR when r > rmax,
  //       = fNDivR+1 when r < rmin

  G4double r=x.perp();
  G4double phi=x.phi();
  if( phi < 0.0 ) { phi += pi2; }

  iphi = 0;
  ir   =fNDivR+2;
  if( r < fRbound[0] ) {
    ir = fNDivR+1;
  }
  else if ( r > fRbound[fNDivR] ) {
    ir=fNDivR;
  }
  else {
    for(G4int i=0;i<fNDivR;i++) {
      if( r >= fRbound[i] && r <= fRbound[i+1] ) {
  	   ir=i;
      break;
      }
    }
    iphi=(G4int)(phi/fPhiStep[ir]);

  }


}
//=====================================================================
//* destructor --------------------------------------------------------
J4IRBCALSD::~J4IRBCALSD()
{
  //#ifndef __GEANT452__
  //  if ( fCalPreHits )  delete fCalPreHits;
  //#endif
}

//=====================================================================
//* Initialize --------------------------------------------------------
void J4IRBCALSD::Initialize( G4HCofThisEvent* PreHCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"

//  std::cerr << " ----------------------------------" << std::endl;
//  std::cerr << " J4IRBCALSD .. Initialize called.  " << std::endl;
//  std::cerr << " ----------------------------------" << std::endl;
  
  MakeHitBuf( PreHCTE );
  fgBCALHits.clear();


}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4IRBCALSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{

  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);

  G4double              edep      = GetEnergyDeposit();
  if( edep <= 0.0 ) return FALSE;

//  std::cerr << "J4IRBCALSD::ProcessHit was called." << std::endl;
//  std::cerr << " Energy  Deposit = " << GetEnergyDeposit() << std::endl;

  J4VComponent* ptrBCAL = GetComponent(0);
  J4VComponent* ptrLayer = GetComponent(1);
  J4VComponent* ptrSensor = GetComponent(2);


  //Get perticle information
  //G4int                 preHitID = 0;
  //  G4int                 postHitID = J4TPCPostHitKeeper::GetInstance()->GetCurPostHitID();
  const G4ThreeVector&  pre       = GetPrePosition();
  const G4ThreeVector&  post      = GetPostPosition();
  //  const G4ThreeVector&  momentum  = GetMomentum();

//  std::cerr << " Mother Solid=" << ptrBCAL->GetMyID() ;
//  std::cerr << " Layer=" << ptrLayer->GetMyID() << std::endl ;

  G4int ir;
  G4int iphi;
  GetRPhiBin(pre, ir, iphi);

  G4int cellID=ptrBCAL->GetMyID()*10000000+100000*ptrLayer->GetMyID()+ir*1000+iphi;
//  std::cerr << " cellid=" << cellID << " ir=" << ir ;
//	std::cerr << " iphi=" << iphi << std::endl;

  G4int preHitID = 0 ;
  //  G4double              energy    = GetKineticEnergy();
  G4double              tof       = GetTof();
  G4int                 trackID   = GetTrackID();
  G4int                 motherTrackID = GetMotherTrackID();
  G4ParticleDefinition* particle = GetParticle(); 

  typedef std::multimap<G4int, J4IRBCALHit*>::iterator  MI;
  std::pair<MI,MI>  itr_range = fgBCALHits.equal_range(cellID);

  if( itr_range.first == fgBCALHits.end() ) {
    // This is new hit. Create a save into buffer
  
    J4IRBCALHit *aHit=new J4IRBCALHit(ptrSensor, preHitID, cellID, edep, tof, 
				   particle, pre, post,
				   trackID, motherTrackID);
    fgBCALHits.insert( std::make_pair( cellID, aHit) );
    ((J4IRBCALHitBuf*)GetHitBuf())->insert(aHit);
  }
  else {
    // Loop over hits i a cell, look for the same preHitID
    // if found, update existing hit. Else, make a new cell hit.
    G4bool makeNewHit = TRUE;
    for( MI p=itr_range.first; p!=itr_range.second; ++p ) {
      J4IRBCALHit *aHit = (J4IRBCALHit*)(p->second);
      G4int aPreHitID = aHit->GetPreHitID();
      if( aPreHitID == preHitID) {
	aHit->AddEdep(edep);
	// aHit->AddXcm(Xcm);
	if( tof < aHit->GetTof() ) {
	  aHit->SetTof(tof);
	  aHit->SetParticle(GetParticle());
	  aHit->SetTrackID(trackID);
	  aHit->SetMotherTrackID(motherTrackID);
	}
	makeNewHit=FALSE;
	break;
      }
    }
    if( makeNewHit ) {
      J4IRBCALHit *aHit=new J4IRBCALHit(ptrSensor, preHitID, cellID, edep, tof, 
					particle, pre, post,
					trackID, motherTrackID);
      fgBCALHits.insert( std::make_pair( cellID, aHit) );
      ((J4IRBCALHitBuf*)GetHitBuf())->insert(aHit);
    }
  }
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4IRBCALSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{	

//  std::cerr << "J4IRBCALSD::EndOfEvent was called " << std::endl;
//  G4int nHit= ( (J4IRBCALHitBuf*)GetHitBuf() ) -> entries();
//  if( nHit <= 0 ) return ;  


}

//=====================================================================
//* clear -------------------------------------------------------------

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4IRBCALSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4IRBCALSD::PrintAll()
{
  G4int nHit= ( (J4IRBCALHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** BCAL tracker Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4IRBCALHitBuf*)GetHitBuf() ) -> PrintAllHits();
}

//======================================================================
//* Is Exiting ---------------------------------------------------------
/*

G4bool J4IRBCALSD::IsExiting( const G4ThreeVector &pos, const G4ThreeVector &p  ) const
{
  J4CALParameterList* ptrList = J4CALParameterList::GetInstance();
  static G4double tol = 10.;
    
  if ( std::abs( pos.perp() - ptrList->GetCALOuterR() ) <= tol*kCarTolerance && p.x() * pos.x() + p.y() * pos.y() > 0.) 
    return true;

  if ( std::abs( std::abs( pos.z() ) - ptrList->GetCALOuterHalfZ() ) <= tol*kCarTolerance && p.z() * pos.z() > 0.)
     return true;
  return false;
}
  */