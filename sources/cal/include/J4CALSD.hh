// $Id$
#ifndef __J4CALSD__
#define __J4CALSD__
//*************************************************************************
//* --------------------
//* J4CALSD
//* --------------------
//* (Description)
//* 	It appends Sensitive propaty to J4CALEM. 
//*	Mother class : J4VSD <- G4VSensitiveDetector
//*     
//* (Update Record)
//*	2003/03/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4VSD.hh"
#include "J4CALPreHit.hh"
#include "J4TrackingAction.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALSD : public J4VSD<J4CALPreHit>{
friend class J4TrackingAction;
  
public:

  J4CALSD( J4VDetectorComponent* detector );
  ~J4CALSD();

  virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
  virtual void   Initialize ( G4HCofThisEvent* PreHCTE );
  virtual void   EndOfEvent ( G4HCofThisEvent* PreHCTE );

  virtual void   DrawAll();
  virtual void   PrintAll(); 
 
  virtual void   OutputAll( G4HCofThisEvent* PreHCTE )
  {
    if ( GetHitBuf() )
    {
      J4VSD<J4CALPreHit>::OutputAll( PreHCTE );
    }
    else
    {
      G4cerr << "J4CALSD::OutputAll: No HitBuf! " << G4endl;
    }
  }

  inline virtual const J4CALSD& operator=( const J4VSD<J4CALPreHit> &right )
  {
    J4VSD<J4CALPreHit>::operator=( right );
    return *this;
  }
  
  // set/get functions

  inline J4CALPreHit* GetCurrentPreHitPtr() const { return fCurrentPreHitPtr; }
  inline static G4int GetCurrentPreHitID() { return fgCurrentPreHitID; }

private:
  inline void SetCurrentPreHitPtr( J4CALPreHit* p ) { fCurrentPreHitPtr = p; }
  inline static void SetCurrentPreHitID( G4int n )  { fgCurrentPreHitID = n; }
   
private:
  //J4CALPreHit  *fCalPreHits;
  J4CALPreHit*  fCurrentPreHitPtr;
  static G4int  fgCurrentPreHitID;
  static G4int  fgTrackRegID;
};

#endif
