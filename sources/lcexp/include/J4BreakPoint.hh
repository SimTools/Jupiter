#ifndef __J4BREAKPOINT__ 
#define __J4BREAKPOINT__ 
//*************************************************************************
//* --------------------
//* class J4BreakPoint
//* --------------------
//* (Description)
//*     Class to store break point information.
//*    
//* (Update Record)
//*     2005/12/14  S.Yamamoto   Original version.
//*************************************************************************
//

#include "G4Track.hh"
#include "J4Output.hh"
#include <map>

class J4BreakPoint 
{
public:
  J4BreakPoint(const G4Track* aTrack);
  virtual ~J4BreakPoint();

  // Getter
  inline G4int           GetTrackID()       const { return fTrackID;        }
  inline G4int           GetParentID()      const { return fParentID;       }
  inline G4double        GetCharge()        const { return fCharge;         }
  inline G4int           GetParticleID()    const { return fParticleID;     }
  inline G4double        GetGlobalTime()    const { return fGlobalTime;     }
  inline G4ThreeVector   GetPosition()      const { return fPosition;       }
  inline G4LorentzVector GetFourMomentum()  const { return fFourMomentum;   }
  inline G4double        GetKineticEnergy() const { return fKineticEnergy;  }

  static J4BreakPoint  * GetBreakPoint(G4int trackID);
  static std::map<G4int, J4BreakPoint*> & 
                         GetBreakPointMap();
  static void            SetOutput(J4Output *outp);
  static void            Clear();
  static void            Output();
  static void            DebugPrint(const char* opt = "");

private:
  G4int           fTrackID;
  G4int           fParentID;
  G4double        fCharge;
  G4int           fParticleID;
  G4double        fGlobalTime;      // Time since the event in which the track belongs is created.
  G4ThreeVector   fPosition;        // Current positon
  G4LorentzVector fFourMomentum;
  G4double        fKineticEnergy;
  static std::map<G4int, J4BreakPoint*>  fgBreakPointMap; //! TrackID to BreakPoint map
  static J4Output                       *fgOutputPtr;     //! TrackID to BreakPoint map
};
#endif
