// $Id$
#ifndef __J4CALHIT__
#define __J4CALHIT__
//*************************************************************************
//* --------------------
//* J4CALHit
//* --------------------
//* (Description)
//*     Hit class for J4CAL 	
//*	Mother class : G4VHit
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*     2004/08/30  Ono Hiroaki  Add J4CALHitlet class inside of J4CALHit
//*************************************************************************
#include "J4VHit.hh"
#include "J4Output.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"

//=========================================================================
// TypeDef
class TVAddress;
class J4CALHit;
class J4CALHitlet;
typedef G4Allocator<J4CALHit> J4CALHitAllocator;
typedef G4THitsCollection<J4CALHit> J4CALHitBuf;

//=========================================================================
//---------------------
// class definition
//---------------------

class J4CALHit : public J4VHit {

public:
  J4CALHit();

  J4CALHit( J4VComponent* ptrDetector,
	    //    G4int         preHitID,
	    TVAddress*    ptrAddress,
            G4double      edep,
            G4double      tof,
	    const G4ThreeVector& xcm );
  
  virtual ~J4CALHit();

  inline void* operator new    ( size_t );
  inline void  operator delete ( void* aHit );

  virtual void Output( G4HCofThisEvent* HCTE );
  virtual void Draw();
  virtual void Print();

  // getter/setter

  
  //  inline G4int         GetPreHitID()      const { return fPreHitID; }
  //  inline TVAddress*    GetAddress()       const { return fAddress;  }
  inline G4double      GetCellEdep() const { return fCellEdep; }
  inline G4double      GetCellTof()  const { return fCellTof;  }
  inline G4ThreeVector GetCellXcm()  const { return fCellXcm;  }
 
  inline void SetAddress( TVAddress* a )     { fAddress   = a; }
  inline void SetCellEdep( G4double x )      { fCellEdep  = x; }
  inline void SetCellTof( G4double x )       { fCellTof   = x; }
  inline void SetCellXcm( G4ThreeVector v )  { fCellXcm   = v; }

  inline void AccumulateCellEdep( G4double ed )    { fCellEdep += ed; }
  inline void AccumulateCellXcm( G4ThreeVector v ) { fCellXcm  += v;  }
  static void SetOutput( J4Output* output )    { fgOutput = output; } 
    
  static J4CALHitAllocator  fgHitAllocator;
  static J4Output*          fgOutput;       // Pointer to Output Module

  class J4CALHitlet
  {
  public:
    J4CALHitlet()
      : fPreHitID(0), fAddress(0), fEdep(0), fTof(0), fXcm(0)
    { }
    
    J4CALHitlet( G4int         preHitID,
	      	 TVAddress*    ptrAddress,
		 G4double      edep,
                 G4double      tof,
                 const G4ThreeVector& xcm )
      : fPreHitID( preHitID ), fAddress( ptrAddress ), fEdep( edep ), fTof( tof ), fXcm( xcm )
    { }
    
    ~J4CALHitlet() { }
    //    inline void* operator new    ( size_t );
    //    inline void  operator delete ( void* aHit );
    //    virtual void Draw();                                         
    //    virtual void Print();

    // getter/setter
    inline G4int         GetPreHitID()      const { return fPreHitID; }
    //    inline TVAddress*    GetAddress()       const { return fAddress; }
    inline G4double      GetEnergyDeposit() const { return fEdep; }
    inline G4double      GetTof()           const { return fTof; }
    inline G4ThreeVector GetXcm()           const { return fXcm; }

    inline void SetPreHitID( G4int n )         { fPreHitID   = n; }
    //  inline void SetAddress( TVAddress* a )     { fAddress    = a; }
    inline void SetEnergyDeposit( G4double x ) { fEdep       = x; }
    inline void SetXcm( G4ThreeVector v )      { fXcm        = v; }

    inline void AccumulateEdep( G4double ed )    { fEdep   += ed; }
    inline void AccumulateXcm( G4ThreeVector v ) { fXcm    += v;  }
    inline void SetTof( G4double tof ) {
      if ( fTof > tof ) fTof = tof;
    }
    
  private:
    G4int         fPreHitID;
    TVAddress*    fAddress;
    G4double      fEdep;
    G4double      fTof;
    G4ThreeVector fXcm;
  };
  
  inline void AddHitlet( G4int         preHitID,
      		         TVAddress*    ptrAddress,
			 G4double      edep,
			 G4double      tof,
			 const G4ThreeVector& xcm )
  {
    fCellEdep += edep;
    fCellXcm  += xcm;
    J4CALHitlet* hitlet = new J4CALHitlet( preHitID, ptrAddress, edep, tof, xcm );
    fHitlets.push_back( hitlet );
  }
  
  inline void AddEdep( G4double edep )
  {
    fCellEdep += edep;
    G4int lastHitlet = fHitlets.size() -1;
    fHitlets[lastHitlet] -> J4CALHitlet::AccumulateEdep( edep );
  }
  
  inline void AddXcm( G4ThreeVector xcm )
  {
    fCellXcm += xcm;
    G4int lastHitlet = fHitlets.size() -1;
    fHitlets[lastHitlet] -> J4CALHitlet::AccumulateXcm( xcm );
  }

  inline void SetHitletTof( G4double tof ) {
    G4int lastHitlet = fHitlets.size() -1;
    fHitlets[lastHitlet] -> J4CALHitlet::SetTof( tof );
  }

  inline G4int GetPreHitID( G4int hlID )       { return fHitlets[hlID] -> J4CALHitlet::GetPreHitID();   }
  inline G4double GetHitletEdep( G4int hlID )  { return fHitlets[hlID] -> J4CALHitlet::GetEnergyDeposit(); }
  inline G4double GetHitletTof( G4int hlID )      { return fHitlets[hlID] -> J4CALHitlet::GetTof(); }
  
  inline G4ThreeVector GetHitletXcm( G4int hlID ) {
    if ( fHitlets[hlID] -> J4CALHitlet::GetEnergyDeposit() <= 0 )
      return fHitlets[hlID] -> J4CALHitlet::GetXcm();
    else
      return  ( fHitlets[hlID] -> J4CALHitlet::GetXcm() ) / ( fHitlets[hlID] -> J4CALHitlet::GetEnergyDeposit() ) ;
  }
  
  inline J4CALHitlet* GetHitlet( G4int hlID ) { return fHitlets[hlID]; }
  inline G4int GetNHitlets()                   { return (G4int)fHitlets.size(); }
  
  //inline void ClearHitlets() {
  //  fHitlets.clear();
  // }
  
private:
  TVAddress*      fAddress;
  G4double        fCellEdep;
  G4double        fCellTof;
  G4ThreeVector   fCellXcm;
  std::vector<J4CALHitlet*> fHitlets;
};

//----------------------------------------
// Allocator

void* J4CALHit::operator new( size_t )
{
  void* aHit;
  aHit = (void*)fgHitAllocator.MallocSingle();
  return aHit;
}

void J4CALHit::operator delete( void* aHit )
{
  fgHitAllocator.FreeSingle((J4CALHit*) aHit);
}

#endif
