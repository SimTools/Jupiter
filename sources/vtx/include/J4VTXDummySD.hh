//
// Dummy sensitive used only to flag sensitivity
// in cells of RO geometry.
//

#ifndef J4VTXDummySD_h
#define J4VTXDummySD_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;

class J4VTXDummySD : public G4VSensitiveDetector
{
public:
  J4VTXDummySD();
  ~J4VTXDummySD() {};
  
  void Initialize(G4HCofThisEvent*HCE) {};
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist) {return false;}
  void EndOfEvent(G4HCofThisEvent*HCE) {};
  void clear() {};
  void DrawAll() {};
  void PrintAll() {};
};

J4VTXDummySD::J4VTXDummySD()
  : G4VSensitiveDetector("dummySD")
{}
#endif
