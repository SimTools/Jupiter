// $ Id: $
#ifndef __J4VCLXActiveSD__
#define __J4VCLXActiveSD__
//*************************************************************************
//* --------------------
//* J4VCLXActiveSD
//* --------------------
//* (Description)
//* 	Derivation class for Sensitive Detector.
//*     Mother : J4VSD
//*    
//* (Update Record)
//*      2006/05/01 H.Ono Original version
//*************************************************************************
#include "J4VSD.hh"
#include "J4VComponent.hh"
#include "J4CLXHit.hh"
#include "J4VCLXBlock.hh"
#include "J4VCLXLayer.hh"

#include <map>

//=====================================================================
//---------------------
// class definition
//---------------------
class J4VCLXActiveSD : public J4VSD<J4CLXHit> {
public:
    J4VCLXActiveSD(J4VDetectorComponent* ptrDetector);
    ~J4VCLXActiveSD();

    virtual G4bool ProcessHits( G4Step* aStep, G4TouchableHistory* ROhist );
    virtual void   Initialize ( G4HCofThisEvent* HCTE );
    virtual void   EndOfEvent ( G4HCofThisEvent* HCTE );

    virtual void   DrawAll();
    virtual void   PrintAll();

    virtual void   OutputAll( G4HCofThisEvent* HCTE )
	{
	    if( GetHitBuf() ) {
		J4VSD<J4CLXHit>::OutputAll( HCTE );
	    } else {
		G4cerr << "J4VCLXActiveSD::OutputAll: No HitBuf! " << G4endl;
	    }
	}

    using J4VSD<J4CLXHit>::operator=;

    inline static void SetHCID( G4int i ) { fgLastHCID = i; }

private:
  static G4int fgLastHCID;
  static std::multimap<G4int, J4CLXHit*> fgClxHits;
  J4CLXHit* fCLXHits;
  
};

#endif
