// $Id$
//*************************************************************************
//* --------------------
//* J4IRFCALSD
//* --------------------
//* (Description)
//* 	Class for describing his/her sensitive detector.
//*     
//* (Update Record)
//*	2006/06/05 A.Miyamoto  Original version
//*************************************************************************
#include "J4IRFCAL.hh"
#include "J4IRFCALSD.hh"
#include "J4IRFCALLayer.hh"
#include "G4Cons.hh"
#include "J4ParameterTable.hh"
#include <cmath>
#include <utility>

J4IRFCALHit *J4IRFCALSD::fLastHit=0;
std::multimap<G4int,J4IRFCALHit*> J4IRFCALSD::fgFCALHits;

//=====================================================================
//---------------------
// class definition
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4IRFCALSD::J4IRFCALSD( J4IRFCALSensor* detector )
 :J4VSD<J4IRFCALHit>( detector )
{
  //  FCAL Geometry
  //  FCAL.Front/Tail -> FCALLayer ---> FCALSensor
  //                                +-> FCALSubLayer

  DefineCells(detector);

}

//=============================================================================
void J4IRFCALSD::DefineCells(J4IRFCALSensor *detector)
{
// Define cell for this sensor
  G4Cons *solid=(G4Cons*)detector->GetSolid();
  G4double zhlf=solid->GetZHalfLength();

  fLayer=(J4IRFCALLayer*)detector->GetMother();
  fFCAL=(J4IRFCAL*)(fLayer->GetMother());
  G4Cons *sbmo=(G4Cons*)fFCAL->GetSolid();
  G4double rminmo=sbmo->GetInnerRadiusMinusZ();
  G4double rmaxmo=sbmo->GetOuterRadiusMinusZ();

  G4double zmo=fFCAL->GetGeom(4);
  //  std::cerr << "FCAL " <<  detector->GetMyID() << " zblock=" << zmo << std::endl;
  // Zcoordinate of the front surface of this sensor(zsensor) is 
  // FCAL.z_center + Layer.z_center + Sensor.z_center - sensor_halfwidth
  G4double zsensor=detector->GetZCenter()+(fLayer->GetTranslation()).z()
    +(zmo+sbmo->GetZHalfLength())-zhlf;
  //  std::cerr << "FCAL " <<  detector->GetName() << " zsensor=" << zsensor << std::endl;

  std::string fbname[2]={std::string("Front"),std::string("Tail")};
// Cell sizes are defined by the fron surface of FCAL Fron or 
// Tail, not by those at FCALSensor.  It defines ranges of costheta 
// it is then transfered to the radius of FCALSensor.
//  Signal position at the front surface of FCALSensor is used 
//  define the cell to get signal.
//  Here "Front" means the one closer to the IP  
// Default parameters  
// Radial division of Front FCAL: 8.2 cm -> 13.0cm : NDIVR=5; (DeltaR=0.96cm)
//                    Tail  FCAL: 9.2435 cm -> 17.696cm : NDIVPhi=9; (DeltaR=0.939cm) 
  G4int ndivr[2]={5, 9};
  std::string ndivphi[2]={std::string("57 64 70 76 82"),
		     std::string("65 72 78 84 91 97 103 108 116")};  
  G4int ind=(fFCAL->GetMyID())%2; 
  std::string pname=std::string("J4IR.FCAL.")+fbname[ind]+std::string(".NDIVR");
  fNDivR = J4ParameterTable::GetValue(pname.data(),ndivr[ind]);
  pname=std::string("J4IR.FCAL.")+fbname[ind]+std::string(".NDIVPhi");
  fNDivPhi = J4ParameterTable::GetIValue(pname.data(),ndivphi[ind].data(),
					 ndivr[ind]);

  G4double rstepmo=(rmaxmo-rminmo)/(G4double)fNDivR;
  //  std::cerr << " fNDivR=" << fNDivR << std::endl;
  //  std::cerr << " ind=" << ind << std::endl;
  for(G4int ir=0; ir<=fNDivR;ir++) {
	  G4double r=(rminmo+rstepmo*(G4double)ir)/zmo*zsensor;
	  fRbound.push_back(r);
	  if( ir != fNDivR ) { fPhiStep.push_back(twopi/(G4double)fNDivPhi[ir]) ;
	  //		  std::cerr << " PhiStep=" << fPhiStep[ir] << std::endl;
      }
   }   	

 
}
//=====================================================================
void J4IRFCALSD::GetRPhiBin(const G4ThreeVector x, G4int &ir, G4int &iphi)
{
  // Define CELL ID : ir = 0 to fNDivR-1,
  //    ir = fNDivR when r > rmax,
  //       = fNDivR+1 when r < rmin

  G4double r=x.perp();
  G4double phi=x.phi();
  if( phi < 0.0 ) { phi += twopi; }

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
J4IRFCALSD::~J4IRFCALSD()
{
}

//=====================================================================
//* Initialize --------------------------------------------------------
void J4IRFCALSD::Initialize( G4HCofThisEvent* PreHCTE )
{
  //create hit collection(s) and
  //push H.C. to "Hit Collection of This Event"

//  std::cerr << " ----------------------------------" << std::endl;
//  std::cerr << " J4IRFCALSD .. Initialize called.  " << std::endl;
//  std::cerr << " ----------------------------------" << std::endl;
  
  MakeHitBuf( PreHCTE );
  fgFCALHits.clear();


}

//=====================================================================
//* ProcessHits -------------------------------------------------------
G4bool J4IRFCALSD::ProcessHits( G4Step* aStep, G4TouchableHistory* /* ROhist */ )
{

  //In order to use Get function, you must call SetNewStep() at first.
  SetNewStep(aStep);

  G4double              edep      = GetEnergyDeposit();
  if( edep <= 0.0 ) return FALSE;

//  std::cerr << "J4IRFCALSD::ProcessHit was called." << std::endl;
//  std::cerr << " Energy  Deposit = " << GetEnergyDeposit() << std::endl;

  J4VComponent* ptrFCAL = GetComponent(2);
  J4VComponent* ptrLayer = GetComponent(1);
  J4VComponent* ptrSensor = GetComponent(0);


  //Get perticle information
  const G4ThreeVector&  pre       = GetPrePosition();
  G4ThreeVector xcm(pre.x()*edep, pre.y()*edep, pre.z()*edep);

//  std::cerr << " Mother Solid=" << ptrFCAL->GetMyID() ;
//  std::cerr << " Layer=" << ptrLayer->GetMyID() << std::endl ;

  G4int ir;
  G4int iphi;
  GetRPhiBin(pre, ir, iphi);

  G4int cellID=ptrFCAL->GetMyID()*10000000+100000*ptrLayer->GetMyID()+ir*1000+iphi;
//  std::cerr << " cellid=" << cellID << " ir=" << ir ;
//  std::cerr << " iphi=" << iphi << std::endl;

  G4int preHitID = 0 ;
  G4double              tof       = GetTof();
  G4int                 trackID   = GetTrackID();
  G4int                 motherTrackID = GetMotherTrackID();
  G4ParticleDefinition* particle = GetParticle(); 

  typedef std::multimap<G4int, J4IRFCALHit*>::iterator  MI;
  std::pair<MI,MI>  itr_range = fgFCALHits.equal_range(cellID);

  if( itr_range.first == fgFCALHits.end() ) {
    // This is new hit. Create a save into buffer
  
    J4IRFCALHit *aHit=new J4IRFCALHit(ptrSensor, preHitID, cellID, edep, tof, 
				   particle, xcm, pre,
				   trackID, motherTrackID);
    fgFCALHits.insert( std::make_pair( cellID, aHit) );
    ((J4IRFCALHitBuf*)GetHitBuf())->insert(aHit);
  }
  else {
    // Loop over hits i a cell, look for the same preHitID
    // if found, update existing hit. Else, make a new cell hit.
    G4bool makeNewHit = TRUE;
    for( MI p=itr_range.first; p!=itr_range.second; ++p ) {
      J4IRFCALHit *aHit = (J4IRFCALHit*)(p->second);
      G4int aPreHitID = aHit->GetPreHitID();
      if( aPreHitID == preHitID) {
	aHit->AddEdep(edep);
	aHit->AddXcm(xcm);
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
      J4IRFCALHit *aHit=new J4IRFCALHit(ptrSensor, preHitID, cellID, edep, tof, 
					particle, xcm, pre,
					trackID, motherTrackID);
      fgFCALHits.insert( std::make_pair( cellID, aHit) );
      ((J4IRFCALHitBuf*)GetHitBuf())->insert(aHit);
    }
  }
  return TRUE;
}

//=====================================================================
//* EndOfEvent --------------------------------------------------------
void J4IRFCALSD::EndOfEvent( G4HCofThisEvent* /* PreHCTE */ )
{	
}

//=====================================================================
//* clear -------------------------------------------------------------

//=====================================================================
//* DrawAll -----------------------------------------------------------
void J4IRFCALSD::DrawAll() { }

//=====================================================================
//* PrintAll ----------------------------------------------------------
void J4IRFCALSD::PrintAll()
{
  G4int nHit= ( (J4IRFCALHitBuf*)GetHitBuf() ) -> entries();
  std::cout << "------------------------------------------" << std::endl
            << "*** FCAL tracker Hit (#hits=" << nHit << ")" << std::endl;
  ( (J4IRFCALHitBuf*)GetHitBuf() ) -> PrintAllHits();
}

