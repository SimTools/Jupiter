//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id$
//
// 

#include "G4Types.hh"
#include "G4ios.hh"

#include "G4Step.hh"
#include "G4StepPoint.hh"

#include "J4SteppingAction.hh"
#include "G4TrackStatus.hh"

#include "J4TrackingActionMessenger.hh"

G4int J4SteppingAction::fLoop=0;
G4int J4SteppingAction::fLastTID=-1;
G4double J4SteppingAction::fEcutSum=0.0;

J4SteppingAction::J4SteppingAction()
{ }

J4SteppingAction::~J4SteppingAction()
{ }

static std::ofstream fout;

// ==================================
void J4SteppingAction::UserSteppingAction(const G4Step* astep)
{
 // save the random number seed of this event, under condition
 //// if(condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();

/*
  G4cerr << "++Vol=" << astep->GetTrack()->GetVolume()->GetName() 
         << " :PreR=" << astep->GetPreStepPoint()->GetPosition().perp()/cm 
         << " :PosR=" << astep->GetPostStepPoint()->GetPosition().perp()/cm ;
  G4cerr << G4endl;
*/

  if( J4TrackingActionMessenger::GetDebugLevel() == 1 ) {
     static G4String lastVol="";
     static G4int    lastTID=-1;
     static G4double sumRadLen=0.0;
     static G4double sumNILen=0.0;
     static G4double lastTrackLength=0.0;
     static G4Material  *lastMat=0;
     G4Track *atrack=astep->GetTrack();
     G4String curVol=astep->GetTrack()->GetVolume()->GetName();
     G4int curTID=astep->GetTrack()->GetTrackID();
     static std::ofstream fostep;
     if( curTID != lastTID ) {
         sumRadLen=0.0;
         sumNILen=0.0;
         lastTrackLength=0.0;
	 G4String logfile=J4TrackingActionMessenger::GetDebugLogFileName();
	 fostep.open(logfile);
         fostep << "// curTID StepNo StepLen TrackLength VolName" 
	<< " MatIndex MatName StepRLen StepTRLen StepNILen StepTNILen"
        << " PostX PostY PostZ PostR PreX PreY PreZ PreR "
        << G4endl;
     }
     if( curTID != lastTID || curVol != lastVol ) {
       //     if( astep->IsLastStepInVolume() ) {
        G4double steplen=atrack->GetTrackLength()-lastTrackLength;
        G4double steprlen=0.0;
        G4double stepnilen=0.0;
        lastMat=atrack->GetMaterial();
        if( lastMat && steplen > 0.0) {
          steprlen=steplen/lastMat->GetRadlen();
          stepnilen=steplen/lastMat->GetNuclearInterLength();
        }
        lastTrackLength=atrack->GetTrackLength();
        sumRadLen+= steprlen;
        sumNILen+= stepnilen;

        G4cerr << "TID=" << curTID << " :Volume=" << curVol ;
        G4cerr << " :StepNumber=" << astep->GetTrack()->GetCurrentStepNumber();
        G4cerr << " :Step(mm)=" << steplen/cm ;
        G4cerr << " :TrackLength=" << lastTrackLength/cm ;
#if 0
	fostep << "// Step " << astep->GetTrack()->GetCurrentStepNumber() << G4endl;
	fostep << " val[0]=" << curTID << ";" << G4endl;
	fostep << " val[1]=" << astep->GetTrack()->GetCurrentStepNumber() << ";" << G4endl;
	fostep << " val[2]=" << steplen/cm << ";" << G4endl;
	fostep << " val[3]=" << lastTrackLength/cm << ";" << G4endl;
#endif
	fostep << curTID << " " 
	       << astep->GetTrack()->GetCurrentStepNumber() << " "
	       << steplen/cm << " "
	       << lastTrackLength/cm << " " 
		<< curVol << " " ; 
	
        if ( lastMat ) {
          G4cerr << " :Material=" << lastMat->GetName() ;
          G4cerr << " :MatIndex=" << lastMat->GetIndex() ;
	} 
        G4cerr << " :Rad_Len=" << steprlen << " :Total_Rad_Len=" << sumRadLen ;
        G4cerr << " :Nucl.IntLen=" << stepnilen << " :Total_NI_Len=" << sumNILen;
	G4cerr << " :PostX=" << astep->GetPostStepPoint()->GetPosition().x()/cm
	<< " :PostY=" << astep->GetPostStepPoint()->GetPosition().y()/cm
	<< " :PostZ=" << astep->GetPostStepPoint()->GetPosition().z()/cm
        << " :PostR=" << astep->GetPostStepPoint()->GetPosition().perp()/cm ;
	G4cerr << " :PreX=" << astep->GetPreStepPoint()->GetPosition().x()/cm
	<< " :PreY=" << astep->GetPreStepPoint()->GetPosition().y()/cm
	<< " :PreZ=" << astep->GetPreStepPoint()->GetPosition().z()/cm
        << " :PreR=" << astep->GetPreStepPoint()->GetPosition().perp()/cm ;
        G4cerr << G4endl;

	fostep << lastMat->GetIndex() << " " 
  	       << lastMat->GetName() << " "
	       <<  steprlen << " "
	       <<  sumRadLen << " " 
	       <<  stepnilen << " " 
	       <<  sumNILen << " "
	<< astep->GetPostStepPoint()->GetPosition().x()/cm << " " 
	<< astep->GetPostStepPoint()->GetPosition().y()/cm<< " "
	<< astep->GetPostStepPoint()->GetPosition().z()/cm<< " "
	<< astep->GetPostStepPoint()->GetPosition().perp()/cm<< " " 
	<< astep->GetPreStepPoint()->GetPosition().x()/cm<< " " 
	<< astep->GetPreStepPoint()->GetPosition().y()/cm<< " " 
	<< astep->GetPreStepPoint()->GetPosition().z()/cm<< " " 
	<< astep->GetPreStepPoint()->GetPosition().perp()/cm << " " 
	<< G4endl;

        lastTID=curTID;
        lastVol=curVol;
	//        lastMat=atrack->GetMaterial();
     }
  }


  G4int tid=astep->GetTrack()->GetTrackID();
  //  if( tid==545) {
  //  if( tid==2172) {
  G4double minstep=1.0e-4*mm;
  if( fLastTID != tid || astep->GetStepLength() > minstep ) {
    fLoop=0;
    fLastTID=tid;
  }
  fLoop ++;
#if 0
  if ( fLoop > 20 ) {
    if( ! fout.is_open() ) { 
      fout.open("plot.C"); 
      fout << "TNtupleD *nt=0; " << std::endl
	   << "void plot() " << std::endl
	   << "{" << std::endl
	   << "  nt=new TNtupleD(\"nt\",\"looped point\","
	   << " \"tid:x:y:z:r\" ); " << std::endl;
      fout.precision(12);
    }
    fout << "nt->Fill(" << tid 
	 << ".0," << astep->GetPostStepPoint()->GetPosition().x()
	 << "," << astep->GetPostStepPoint()->GetPosition().y()
	 << "," << astep->GetPostStepPoint()->GetPosition().z()
	 << "," << astep->GetPostStepPoint()->GetPosition().perp()
	 << ");" << std::endl ;
  }
#endif

#if 0
  if ( fLoop > 20 && astep->GetTrack()->GetCurrentStepNumber() > 10000 ) {
    G4double pmommev=astep->GetTrack()->GetMomentum().mag()/MeV;
    if( pmommev < 5.0 ) {
      G4int ind=astep->GetTrack()->GetVolume()->GetName().index("/IR");
      // G4cerr << " ind=" << ind << G4endl;
      if( ind > 0 ) {
        G4cerr << "Track " << astep->GetTrack()->GetTrackID()
	       << " is killed at " 
	       << astep->GetTrack()->GetVolume()->GetName()
               << " Etot(MeV)=" 
               << astep->GetTrack()->GetTotalEnergy()/MeV
               << " PID=" << astep->GetTrack()->GetDefinition()->GetPDGEncoding()
	       << G4endl;
        astep->GetTrack()->SetTrackStatus(fStopAndKill);
        fEcutSum += astep->GetTrack()->GetTotalEnergy();
      }
    }
  }
#endif

#if 0

  //  if ( fLoop > 20 && astep->GetTrack()->GetCurrentStepNumber()%1000 == 0 ) {
  if ( tid == 2611 ) {

  G4cerr << "J4SteppingAction::UserSteppingAction ..." << G4endl;
  G4cerr << " pre=" << astep->GetPreStepPoint()->GetPosition() ;
  G4cerr << " post=" << astep->GetPostStepPoint()->GetPosition() ;
  G4cerr << " step(mm)=" << astep->GetStepLength()/mm ;
  G4cerr << " step no.=" << astep->GetTrack()->GetCurrentStepNumber() ;
  G4cerr << G4endl;

  G4cerr << "track ID=" << astep->GetTrack()->GetTrackID() ;
  G4cerr << "PDG=" << astep->GetTrack()->GetDefinition()->GetPDGEncoding();
  G4cerr << " KE=" << astep->GetTrack()->GetKineticEnergy() ;
  G4cerr << " P(MeV)=" << astep->GetTrack()->GetMomentum().mag()/MeV ;
  G4cerr << " Pt(MeV)=" << astep->GetTrack()->GetMomentum().perp()/MeV ;
  G4cerr << " time=" << astep->GetTrack()->GetGlobalTime()/nanosecond ;
  G4cerr << " Volume=" << astep->GetTrack()->GetVolume()->GetName() ;
  //  G4cerr << " Next V.=" << astep->GetTrack()->GetNextVolume()->GetName();
  G4cerr << G4endl;
  }
#endif


#if 0
  G4double minstep=0.85e-4*mm;
  if( fLastTID != tid || astep->GetStepLength()/mm > minstep ) {
    fLoop=0;
    fLastTID=tid;
  }
  fLoop ++;
  if ( fLoop > 100 && astep->GetTrack()->GetCurrentStepNumber() > 1000 ) {
    G4cerr << "Possible Stepping Loop detected. "
	   << " at " << astep->GetTrack()->GetVolume()->GetName()
	   << G4endl;
    G4ThreeVector x=astep->GetPostStepPoint()->GetPosition();
    G4ThreeVector dx=astep->GetPostStepPoint()->GetMomentumDirection();
    G4ThreeVector nx=x + minstep*dx;
    G4cerr << " New position is moved to " 
	   << nx << G4endl;
    G4StepPoint *np=astep->GetPostStepPoint();
    np->SetPosition(nx);
  }
#endif

#if 0 //2005/1/20
  G4Track *atrack=astep->GetTrack();
  G4int aStepNo = atrack->GetCurrentStepNumber();
  if( aStepNo > 999 ) { 
    G4Track * aNonConstTrack = const_cast<G4Track*>(atrack);
    aNonConstTrack->SetTrackStatus(fStopAndKill);
    G4cerr << " Track terminated due to too many step " ;
    G4cerr << "track ID=" << astep->GetTrack()->GetTrackID() ;
    G4cerr << "PDG=" << astep->GetTrack()->GetDefinition()->GetPDGEncoding();
    G4cerr << " KE=" << astep->GetTrack()->GetKineticEnergy() ;
    G4cerr << " time=" << astep->GetTrack()->GetGlobalTime()/nanosecond ;
    G4cerr << " Volume=" << astep->GetTrack()->GetVolume()->GetName() ;
    G4cerr << G4endl;
    return;
  }
#endif //2005/1/20
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



