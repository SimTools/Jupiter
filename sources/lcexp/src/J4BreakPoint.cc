//*************************************************************************
//* --------------------
//* J4BreakPoint
//* --------------------
//* (Description)
//*     Base class to book keep break ponit information.
//* (Update Record)
//*     2005/12/14  S.Yamamoto     Original version.
//*************************************************************************

#include "J4BreakPoint.hh"
#include <iostream>

std::map<G4int, J4BreakPoint*> J4BreakPoint::fgBreakPointMap; 
J4Output *J4BreakPoint::fgOutputPtr = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4BreakPoint::J4BreakPoint(const G4Track *tp)
             :fTrackID(tp->GetTrackID()),
	      fParentID(tp->GetParentID()),
	      fCharge(tp->GetDefinition()->GetPDGCharge()),
	      fParticleID(tp->GetDefinition()->GetPDGEncoding()),
	      fGlobalTime(tp->GetGlobalTime()),
	      fPosition(tp->GetPosition()),
	      fFourMomentum(tp->GetMomentum(),tp->GetTotalEnergy()),
	      fKineticEnergy(GetKineticEnergy())
{
  fgBreakPointMap.insert(std::pair<G4int, J4BreakPoint*>(fTrackID, this));
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4BreakPoint::~J4BreakPoint()
{
}

//=====================================================================
//* GetBreakPoint -----------------------------------------------------
J4BreakPoint * J4BreakPoint::GetBreakPoint(G4int trackID)
{
  return fgBreakPointMap[trackID];
}

//=====================================================================
//* Clear -------------------------------------------------------------
void J4BreakPoint::Clear()
{
  std::map<G4int, J4BreakPoint*>::iterator iter;
  for (iter  = fgBreakPointMap.begin();
       iter != fgBreakPointMap.end(); iter++) {
    delete iter->second;
  }
  fgBreakPointMap.clear();
}

//=====================================================================
//* Output ------------------------------------------------------------

void J4BreakPoint::Output()
{
  if (fgOutputPtr) fgOutputPtr->Output(0);
}

//=====================================================================
//* DebugPrint --------------------------------------------------------

void J4BreakPoint::DebugPrint(const char*)
{
  G4cerr <<"DebugPrint Called" <<G4endl;
  std::map<G4int, J4BreakPoint*>::iterator iter;
  for (iter  = fgBreakPointMap.begin(); 
       iter != fgBreakPointMap.end(); iter++) {
    G4int    mid    = iter->second->GetParentID();
    G4int    pid    = iter->second->GetParticleID();
    G4double charge = iter->second->GetCharge();
    G4double momx   = iter->second->GetFourMomentum().x()*(1./GeV);
    G4double momy   = iter->second->GetFourMomentum().y()*(1./GeV);
    G4double momz   = iter->second->GetFourMomentum().z()*(1./GeV);
    G4double mom    = iter->second->GetFourMomentum().v().mag()*(1./GeV);
    G4double ene    = iter->second->GetFourMomentum().t()*(1./GeV);
    G4double kene   = iter->second->GetKineticEnergy()*(1./GeV);
    G4double mass   = iter->second->GetFourMomentum().m()*(1./GeV);
    G4double posx   = iter->second->GetPosition().x()*(1./cm);
    G4double posy   = iter->second->GetPosition().y()*(1./cm);
    G4double posz   = iter->second->GetPosition().z()*(1./cm);
    G4double posr   = iter->second->GetPosition().mag()*(1./cm);
    G4double perp   = iter->second->GetPosition().perp()*(1./cm);
    G4bool   inbp   = (perp<=23.)  ? TRUE : FALSE;
    G4bool   outbp  = (perp<=39.5) ? TRUE : FALSE;
    G4bool   intpc  = (perp<=206.) ? TRUE : FALSE;

    G4cerr << "| TrackID = "    << iter->first
           << "| ParentID = "   << mid
           << "| ParticleID = " << pid
           << "| Charge = "     << charge
           << "| Momx = "       << momx
           << "| Momy = "       << momy
           << "| Momz = "       << momz
           << "| Mom = "        << mom
           << "| E = "          << ene
           << "| KE = "         << kene
           << "| Mass = "       << mass
           << "| Posx = "       << posx
           << "| Posy = "       << posy
           << "| Posz = "       << posz
           << "| R = "          << posr
           << "| InBP = "       << inbp 
           << "| OutBP = "      << outbp
           << "| InTPC = "      << intpc    
           << "| Perp = "       << perp  << " |" << G4endl;
  }
}
