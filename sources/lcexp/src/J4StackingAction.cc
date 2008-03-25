//$Id: 
//*************************************************************************
//* --------------------
//* J4StackingAction
//* --------------------
//* (Description)
//*    Derivated class for UserStackingAction. 
//*
//* (Update Record)
//*     2000/12/08  K.Hoshina   Original version.
//*************************************************************************

#include "J4StackingAction.hh"
#include "G4Track.hh"
#include <limits>

G4int J4StackingAction::fgTopOfStackID = std::numeric_limits<int>::max();

//=====================================================================
//* Constructor -------------------------------------------------------
J4StackingAction::J4StackingAction()
{
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4StackingAction::~J4StackingAction()
{
}

//=====================================================================
//* ClassifynewTrack --------------------------------------------------
G4ClassificationOfNewTrack J4StackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
   fgTopOfStackID = aTrack->GetTrackID();
   return fUrgent;
}

