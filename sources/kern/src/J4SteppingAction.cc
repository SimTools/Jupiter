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


J4SteppingAction::J4SteppingAction()
{ }

J4SteppingAction::~J4SteppingAction()
{ }

void J4SteppingAction::UserSteppingAction(const G4Step* astep)
{
 // save the random number seed of this event, under condition
 //// if(condition) G4RunManager::GetRunManager()->rndmSaveThisEvent();

  /*
  G4cerr << "J4SteppingAction::UserSteppingAction ..." << G4endl;
  G4cerr << " pre=" << astep->GetPreStepPoint()->GetPosition() ;
  G4cerr << " post=" << astep->GetPostStepPoint()->GetPosition() ;
  G4cerr << " step=" << astep->GetStepLength() ;
  G4cerr << " step no.=" << astep->GetTrack()->GetCurrentStepNumber() ;
  G4cerr << G4endl;

  G4cerr << "track ID=" << astep->GetTrack()->GetTrackID() ;
  G4cerr << "PDG=" << astep->GetTrack()->GetDefinition()->GetPDGEncoding();
  G4cerr << " KE=" << astep->GetTrack()->GetKineticEnergy() ;
  G4cerr << " time=" << astep->GetTrack()->GetGlobalTime()/nanosecond ;
  G4cerr << " Volume=" << astep->GetTrack()->GetVolume()->GetName() ;
  //  G4cerr << " Next V.=" << astep->GetTrack()->GetNextVolume()->GetName();
  G4cerr << G4endl;
  */

  G4Track *atrack=astep->GetTrack();
  G4int aStepNo = atrack->GetCurrentStepNumber();
#if 0 //2005/1/20
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



