// $Id$
// ====================================================================
//    J4EventAction.hh
//
//    A user's optional action class which defines the user's action
//    at the begining and the end of each event.
//    The two virtual methods BeginOfEventAction() and EndOfEventAction() 
//    are invoked at the beginning and the end of one event processing. 
//
//    Be aware that BeginOfEventAction() is invoked when a G4Event object is
//    sent to G4EventManager. Thus the primary vertexes/particles have already
//    been made by the primary generator. 
//    In case the user wants to do something before generating primaries 
//    (i.e., store random number status), do it in the 
//    G4VUserPrimaryGeneratorAction concrete class.
//
//                                   .JLC-CDC, 2001
// ====================================================================
#ifndef J4_EVENT_ACTION_H
#define J4_EVENT_ACTION_H 

#include "G4UserEventAction.hh"
#include "G4Timer.hh"

// ====================================================================
//
//      class definition
//
// ====================================================================

class G4Event;

class J4EventAction : public G4UserEventAction {
public:
  J4EventAction();
  ~J4EventAction() { }

  // methods
  virtual void BeginOfEventAction(const G4Event* anEvent);
  virtual void EndOfEventAction(const G4Event* anEvent);

private:
  G4Timer fEventTimer;
  
};  

#endif

