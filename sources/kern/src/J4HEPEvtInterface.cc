// $Id$
// ********************************************************************
// J4HEPEvtInterface
//
// (Author)
//    K.Hoshina, 29-May-2002  
// ********************************************************************

#include "./strstream"
#include <iostream>
#include <iomanip>

#include "G4ios.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4HEPEvtParticle.hh"
#include "G4Event.hh"
#include "G4StateManager.hh"
#include "J4HEPEvtInterface.hh"
#include "J4HEPEvtMessenger.hh"

// ------------------------------------------------------------
J4HEPEvtInterface::J4HEPEvtInterface(G4String file)
                  :fFileName(""), fHPlist(0),
                   fNskipEvents(0),
                   fMessenger(0)
{

  if( file != "" ) OpenHEPEvtFile(file); 
  G4ThreeVector zero(0,0,0);
  particle_position = zero;
  particle_time = 0.0;

  fMessenger = new J4HEPEvtMessenger(this);

}

// ------------------------------------------------------------
J4HEPEvtInterface::~J4HEPEvtInterface()
{
   if (fMessenger) delete fMessenger;
}

// ------------------------------------------------------------
void J4HEPEvtInterface::OpenHEPEvtFile(G4String file)
{
  if (file != "") fFileName = file; 
  if (fInputStream.is_open()) fInputStream.close();

  // change abortion level of G4Exeption temporary...
  // SuppressAbortion = 2 represents no abotion.
  G4int abortlevel_keep = G4StateManager::GetStateManager()->GetSuppressAbortion();
  G4StateManager::GetStateManager()->SetSuppressAbortion(2);

  fInputStream.open(fFileName);
  if (!fInputStream) {
     G4Exception("J4HEPEvtInterface:: check filename and retry. cannot open file " +fFileName );
  } else {
     G4cout << "HEPEvt input file : " << fFileName << " is opened." << G4endl;
  }

  // reset abortion level...
  G4StateManager::GetStateManager()->SetSuppressAbortion(abortlevel_keep);

}


// ------------------------------------------------------------
void J4HEPEvtInterface::GeneratePrimaryVertex(G4Event* evt)
{

  if (!fInputStream.is_open()) { OpenHEPEvtFile(); }
  G4int NHEP;     // number of entries
  G4int ISTHEP;   // status code
  G4int IDHEP;    // PDG code
  G4int JDAHEP1;  // first daughter
  G4int JDAHEP2;  // last daughter
  G4double PHEP1; // px in GeV
  G4double PHEP2; // py in GeV
  G4double PHEP3; // pz in GeV
  G4double PHEP5; // mass in GeV
  
#ifdef __THEBE__
#ifdef __DUMPREADDATA__  
  std::ofstream ofs;
  ofs.open("readpythia_event.data");
#endif
#endif
  
  // skip events. Default is no skip.
  for (G4int i=0; i<fNskipEvents; i++) {  
     fInputStream >> NHEP;
     if (fInputStream.eof()) {
        G4Exception("End-Of-File : HEPEvt input file");
        return;
     }
     
     G4cerr << "J4HEPEvtInterFace::GeneratePrimaryVertex: Skipped event "
            << i << G4endl;
     
#ifdef __THEBE__
#ifdef __DUMPREADDATA__  
     ofs << "J4HEPEvtInterFace::GeneratePrimaryVertex:_Skipped_event_" 
         << i << "_==========================" << G4endl;
     ofs << NHEP << G4endl;
#endif
#endif

     // skip events .....
     for (G4int IHEP=0; IHEP<NHEP; IHEP++) {
        fInputStream >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2
                     >> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5;
                     
#ifdef __THEBE__
#ifdef __DUMPREADDATA__  
        ofs << std::setw(10) << ISTHEP 
            << std::setw(10) << IDHEP 
            << std::setw(10) << JDAHEP1 
            << std::setw(10) << JDAHEP2
            << std::setiosflags(std::ios::scientific) << std::setprecision(8) 
            << std::setw(16) << PHEP1 
            << std::setw(16) << PHEP2 
            << std::setw(16) << PHEP3 
            << std::setw(16) << PHEP5 
            << std::resetiosflags(std::ios::scientific) << G4endl;
#endif
#endif

     }   
  }
  
  // Skip events end.
  // Make new primary vertex.

  fInputStream >> NHEP;
  if (fInputStream.eof()) {
     G4Exception("End-Of-File : HEPEvt input file");
     return;
  }
  
#ifdef __THEBE__
#ifdef __DUMPREADDATA__
  ofs << "J4HEPEvtInterFace::GeneratePrimaryVertex:_Loaded_event_"
     << fNskipEvents << "_==========================" << G4endl;
  ofs << NHEP << G4endl;
#endif
#endif

  for (G4int IHEP=0; IHEP<NHEP; IHEP++) {
    // read data......
    fInputStream >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2
                 >> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5;
                 
#ifdef __THEBE__
#ifdef __DUMPREADDATA__
    ofs << std::setw(10) << ISTHEP
        << std::setw(10) << IDHEP
        << std::setw(10) << JDAHEP1
        << std::setw(10) << JDAHEP2
        << std::setw(16) << PHEP1
        << std::setw(16) << PHEP2
        << std::setw(16) << PHEP3
        << std::setw(16) << PHEP5 << G4endl;
#endif
#endif
     
    // create G4PrimaryParticle object
    G4PrimaryParticle* particle 
      = new G4PrimaryParticle( IDHEP, PHEP1*GeV, PHEP2*GeV, PHEP3*GeV );
    particle->SetMass( PHEP5*GeV );

    // create G4HEPEvtParticle object
    G4HEPEvtParticle* hepParticle
      = new G4HEPEvtParticle( particle, ISTHEP, JDAHEP1, JDAHEP2 );

    // Store
    fHPlist.push_back( hepParticle );
  }
#ifdef __THEBE__
#ifdef __DUMPREADDATA__
  ofs.close();
#endif
#endif
  
  // check if there is at least one particle
  if (fHPlist.size() == 0) return; 

  // make connection between daughter particles decayed from 
  // the same mother
  for (size_t i=0; i<fHPlist.size(); i++) {
    if (fHPlist[i]->GetJDAHEP1() > 0) {//  it has daughters
    
      G4int jda1 = fHPlist[i]->GetJDAHEP1()-1; // FORTRAN index starts from 1
      G4int jda2 = fHPlist[i]->GetJDAHEP2()-1; // but C++ starts from 0.
      G4PrimaryParticle* mother = fHPlist[i]->GetTheParticle();
      for (G4int j=jda1; j<=jda2; j++) {
        G4PrimaryParticle* daughter = fHPlist[j]->GetTheParticle();
        if (fHPlist[j]->GetISTHEP()>0) {
          mother->SetDaughter( daughter );
          fHPlist[j]->Done();
        }
      }
    }
  }

  // create G4PrimaryVertex object
  G4PrimaryVertex* vertex = new G4PrimaryVertex(particle_position,particle_time);

  // put initial particles to the vertex
  for (size_t ii=0; ii<fHPlist.size(); ii++)
  {
    if (fHPlist[ii]->GetISTHEP() > 0) // ISTHEP of daughters had been 
                                       // set to negative
    {
      G4PrimaryParticle* initialParticle = fHPlist[ii]->GetTheParticle();
      vertex->SetPrimary( initialParticle );
    }
  }

  // clear G4HEPEvtParticles
  //fHPlist.clearAndDestroy();
  for (size_t iii=0;iii<fHPlist.size();iii++) { 
     delete fHPlist[iii]; 
  }
  fHPlist.clear();

  // Put the vertex to G4Event object
  evt->AddPrimaryVertex( vertex );
}

