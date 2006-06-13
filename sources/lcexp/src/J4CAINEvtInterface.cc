//
// ********************************************************************
// J4CAINEvtInterface
//
// See description in J4CAINEvtInterface.hh
//
// (Author)
//    Akiya Miyamoto, KEK, 20-May-2002  (akiya.miyamoto@kek.jp)
// ********************************************************************
//
//
// $Id$
// 
// --------------------------------------------------------------------

#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
#endif

#include "G4ios.hh"
#include "J4CAINEvtInterface.hh"
#include "J4CAINEvtMessenger.hh"
#include "G4ParticleTable.hh"

#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4Event.hh"
#include "G4StateManager.hh"

// ------------------------------------------------------------
J4CAINEvtInterface::J4CAINEvtInterface(G4String file)
                   :fFileName(""),  fNread(0),
                    fGamma(0), fElectron(0), fPositron(0),
                    fGenGamma(true), fGenElectron(true), fGenPositron(true),
                    fVerboseLevel(0), fTracksPerEvent(500), 
		    fCrossingAngle(0.0), 
		    fFirstRecord(1), fLastRecord(1999999999), fReadRecord(0),
                    fMessenger(0)
{

  if ( file != "" ) OpenCainFile(file); 

  G4ThreeVector zero(0,0,0);
  particle_position = zero;
  particle_time = 0.0;

  G4ParticleTable *particleTable=G4ParticleTable::GetParticleTable();

  fGamma=particleTable->FindParticle("gamma");
  fElectron=particleTable->FindParticle("e-");
  fPositron=particleTable->FindParticle("e+");

  fGenGamma=true;
  fGenElectron=true;
  fGenPositron=true;
  fGenDirection=1.0;

  fMessenger=new J4CAINEvtMessenger(this);

}

// ------------------------------------------------------------
void J4CAINEvtInterface::OpenCainFile(G4String evfile)
{
  if( evfile != "" ) fFileName = evfile; 
  if (fInputStream.is_open()) fInputStream.close();

  // change abortion level of G4Exeption temporary...
  // SuppressAbortion = 2 represents no abotion.
  G4int abortlevel_keep = G4StateManager::GetStateManager()->GetSuppressAbortion();
  G4StateManager::GetStateManager()->SetSuppressAbortion(2);

  fInputStream.open(fFileName);
  if (!fInputStream) {
     G4Exception("G4CAINEvtInterface:: check filename and retry. cannot open file "+fFileName);
  } else {
     std::cout << "CAIN input file : " << fFileName << " is opened." << std::endl;
  }

  fReadRecord=0;

  // reset abortion level...
  G4StateManager::GetStateManager()->SetSuppressAbortion(abortlevel_keep);
 
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenDirection(G4double flag)
{
  fGenDirection=flag;
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenGamma(G4bool flag)
{
  fGenGamma=flag;
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenElectron(G4bool flag)
{
  fGenElectron=flag;
}

// ------------------------------------------------------------
void J4CAINEvtInterface::SetGenPositron(G4bool flag)
{
  fGenPositron=flag;
}


// ------------------------------------------------------------
J4CAINEvtInterface::~J4CAINEvtInterface()
{;}

// ------------------------------------------------------------
void J4CAINEvtInterface::GeneratePrimaryVertex(G4Event* evt)
{

  if( !fInputStream.is_open() ) { OpenCainFile(); }

  char input[512];

  //  G4int id, kgen;
  //  G4double weight, ct,cx,cy,cs,ce,cpx,cpy,cps,csx,csy,css;
  //  char genname[4];
  struct cainin {
    G4int id, kgen;
    G4double weight, ct,cx,cy,cs,ce,cpx,cpy,cps,csx,csy,css;
    char genname[4];    
  } tb;
  G4int maxread=fTracksPerEvent;
  G4int nread=0;  

  //  std::cerr << " fTracksPerEvent is " << fTracksPerEvent << std::endl;
  //  std::cerr << " Crossing Angle is " << fCrossingAngle/rad << std::endl;

  while(nread < maxread ) { 
    fInputStream.getline(input,512);
    if( fInputStream.eof()==1 ) {
      J4PrimaryGeneratorAction::GetPrimaryGeneratorAction()->SetAbortRun(true);
      std::cerr << "End of File while reading CAIN file, " ;
      std::cerr << fFileName << std::endl;
      std::cerr << "nread =" << nread << " maxread=" << maxread << std::endl;
      break;
    }
    if( input[0] == '!' ) continue;  // 1st column ! is comment
    for(G4int i=0;i<512;i++){  // Convert D to E
      if( input[i] == 'D' ) {
	input[i]='E'; 
      }

      if( input[i] == '\00' ) break;
    }
 
    std::istringstream sinput(input);
    sinput >>  tb.id >> tb.kgen >> tb.genname >> tb.weight >> tb.ct >> 
      tb.cx >> tb.cy >> tb.cs >> tb.ce >> tb.cpx >> tb.cpy >> 
      tb.cps >> tb.csx >> tb.csy >> tb.css ;

    G4bool samedir= (fGenDirection*tb.cps >= 0.0 ? true : false );
    if( !samedir ) continue;
    if( !( ( tb.id == 1 && fGenGamma ) || 
	    ( tb.id == 2 && fGenElectron ) ||
	    ( tb.id == 3 && fGenPositron )    ) ) continue;
    fReadRecord++;
    if( fReadRecord < fFirstRecord ) continue;
    if( fReadRecord > fLastRecord ) {
      J4PrimaryGeneratorAction::GetPrimaryGeneratorAction()->SetAbortRun(true);
      std::cerr << "Read " << fReadRecord << " record, which exceeds " << fLastRecord ;
      std::cerr << std::endl;
      std::cerr << "J4CAINEvtInterface requested to terminate job." << std::endl;
      break;
    }
    nread++;
    // Found tracks to be used for simulation.  Put it in the buffer
    // after crossing angle corrections.
    tb.ct *= m;  tb.cx *= m; tb.cy*=m ; tb.cs*= m ; 
    tb.ce*= eV ; tb.cpx *= eV ; tb.cpy *= eV ; tb.cps *= eV;

    if ( std::abs(fCrossingAngle) > 0.01*mrad ) {
      G4double p=std::sqrt(tb.cpx*tb.cpx+tb.cpy*tb.cpy+tb.cps*tb.cps);
      G4double betaf=p*std::sin(-0.5*fCrossingAngle/rad)/tb.ce;
      G4double gammaf=1.0/std::sqrt( (1+betaf)*(1-betaf) );

      G4double te=gammaf*(tb.ce + betaf*tb.cpx);
      G4double tpx=gammaf*(betaf*tb.ce + tb.cpx);
      tb.ce=te;
      tb.cpx=tpx;
    }

    if( fVerboseLevel > 0 ) {
      std::cout << "CAIN event generated: id=" << tb.id;
      std::cout << "(cx,cy,cs)=(" << tb.cx/mm << "," ;
      std::cout << tb.cy/mm << "," << tb.cs/mm << ") (mm) " ;
      std::cout << "(px,py,pz)=(" << tb.cpx/GeV << "," ;
      std::cout << tb.cpy/GeV << "," << tb.cps/GeV << ") (GeV) " << std::endl ;
    }

    // create new primaries and set them to the vertex
    G4ParticleDefinition *particle_definition;
    switch(tb.id) {
    case 1: 
      particle_definition=fGamma;
      break;
    case 2: 
      particle_definition=fElectron;
      break;
    case 3:
      particle_definition=fPositron;
      break;
    default:
      std::stringstream sout;
      sout << "Error: Undefined particle id " << tb.id << " is obtained" << std::ends;
      G4Exception(sout.str());
      return;
    }

    G4double mass=particle_definition->GetPDGMass();
    G4PrimaryParticle *particle=
      new G4PrimaryParticle(particle_definition, tb.cpx, tb.cpy, tb.cps);
    particle->SetMass( mass );
    particle->SetCharge( particle_definition->GetPDGCharge() );
    particle->SetPolarization( tb.csx, tb.csy, tb.css );
    particle->SetWeight( tb.weight );

    G4PrimaryVertex *vertex=  
    new G4PrimaryVertex(G4ThreeVector(tb.cx, tb.cy, tb.cs), tb.ct); 
    vertex->SetPrimary( particle );
    evt->AddPrimaryVertex( vertex );
  
  } // End of loop to get maxread particles

}

