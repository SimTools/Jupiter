// $Id$
#ifndef __J4VCDCDETECTORCOMPONENT__
#define __J4VCDCDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VCDCDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4CDCMaterialStore.hh"
#include "J4CDCParameterList.hh"
#include "J4TwistedTubs.hh"
#include "G4String.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCDCDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  			   
  J4VCDCDetectorComponent( const G4String       &name, 
  			                  J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  J4VCDCDetectorComponent( const J4VCDCDetectorComponent &orig,
                                 G4int                    copyno);
  virtual ~J4VCDCDetectorComponent();

  inline virtual G4double GetInnerRadius(J4VComponent * cdctubs) const;
                          // returns inner radius at "Endcap".
  inline virtual G4double GetOuterRadius(J4VComponent * cdctubs) const;
                          // returns outer radius at "Endcap".
  inline virtual G4double GetInnerWeist (J4VComponent * cdctubs) const;
                          // returns inner radius at z = 0.
  inline virtual G4double GetOuterWeist (J4VComponent * cdctubs) const;
                          // returns outer radius at z = 0.
  inline virtual G4double GetZHalfLength(J4VComponent * cdctubs) const;
  inline virtual G4double GetDeltaPhi   (J4VComponent * cdctubs) const;
  inline virtual G4double GetPhiOffset  (J4VComponent * cdctubs) const;

protected:    
  J4VMaterialStore*       OpenMaterialStore();
  J4CDCParameterList*     OpenParameterList();
  
private:
  static J4CDCMaterialStore *fMaterialStore;
  static J4CDCParameterList *fParameterList;
  static G4String            fSubGroup;
       
};

//=====================================================================
//---------------------
// inline function
//---------------------

//* inline functions -----------------------------------

G4double J4VCDCDetectorComponent::GetInnerRadius(J4VComponent *cdctubs) const
{
   if (!(cdctubs->GetLV())) {
       G4cerr << "J4VCDCDetectorComponent::GetInnerRadius: LV is not exist yet."
              << " Name = " 
              << cdctubs->GetName() << G4endl;
       abort();
   } else if (dynamic_cast<G4Tubs *>(cdctubs->GetSolid())) {
       return ((G4Tubs *)cdctubs->GetSolid())->GetRMin();
   } else if (dynamic_cast<J4TwistedTubs *>(cdctubs->GetSolid())) {
       return ((J4TwistedTubs *)cdctubs->GetSolid())->GetEndInnerRadius();
   } else {
       G4cerr << "J4VCDCDetectorComponent::GetInnerRadius is not be impremented for "
              << cdctubs->GetName() << G4endl;
       abort();
   }
}  

G4double J4VCDCDetectorComponent::GetOuterRadius(J4VComponent *cdctubs) const
{
   if (!(cdctubs->GetLV())) {
       G4cerr << "J4VCDCDetectorComponent::GetOuterRadius: LV is not exist yet."
              << " Name = "
              << cdctubs->GetName() << G4endl;
       abort();
   } else if (dynamic_cast<G4Tubs *>(cdctubs->GetSolid())) {
       return ((G4Tubs *)cdctubs->GetSolid())->GetRMax();
   } else if (dynamic_cast<J4TwistedTubs *>(cdctubs->GetSolid())) {
       return ((J4TwistedTubs *)cdctubs->GetSolid())->GetEndOuterRadius();
   } else {
       G4cerr << "J4VCDCDetectorComponent::GetOuterRadius is not be impremented for "
              << cdctubs->GetName() << G4endl;
       abort();
   }
}

G4double J4VCDCDetectorComponent::GetInnerWeist(J4VComponent *cdctubs) const
{
   if (!(cdctubs->GetLV())) {
       G4cerr << "J4VCDCDetectorComponent::GetInnerWeist: LV is not exist yet."
              << " Name = " 
              << cdctubs->GetName() << G4endl;
       abort();
   } else if (dynamic_cast<G4Tubs *>(cdctubs->GetSolid())) {
       return ((G4Tubs *)cdctubs->GetSolid())->GetRMin();
   } else if (dynamic_cast<J4TwistedTubs *>(cdctubs->GetSolid())) {
       return ((J4TwistedTubs *)cdctubs->GetSolid())->GetInnerRadius();
   } else {
       G4cerr << "J4VCDCDetectorComponent::GetInnerWeist is not be impremented for "
              << cdctubs->GetName() << G4endl;
       abort();
   }
}  

G4double J4VCDCDetectorComponent::GetOuterWeist(J4VComponent *cdctubs) const
{
   if (!(cdctubs->GetLV())) {
       G4cerr << "J4VCDCDetectorComponent::GetOuterWeist: LV is not exist yet."
              << " Name = " 
              << cdctubs->GetName() << G4endl;
       abort();
   } else if (dynamic_cast<G4Tubs *>(cdctubs->GetSolid())) {
       return ((G4Tubs *)cdctubs->GetSolid())->GetRMax();
   } else if (dynamic_cast<J4TwistedTubs *>(cdctubs->GetSolid())) {
       return ((J4TwistedTubs *)cdctubs->GetSolid())->GetOuterRadius();
   } else {
       G4cerr << "J4VCDCDetectorComponent::GetOuterWeist is not be impremented for "
              << cdctubs->GetName() << G4endl;
       abort();
   }
}  

G4double J4VCDCDetectorComponent::GetZHalfLength(J4VComponent *cdctubs) const
{
   if (!(cdctubs->GetLV())) {
       G4cerr << "J4VCDCDetectorComponent::GetZHalfLength: LV is not exist yet."
              << " Name = " 
              << cdctubs->GetName() << G4endl;
       abort();
   } else if (dynamic_cast<G4Tubs *>(cdctubs->GetSolid())) {
       return ((G4Tubs *)cdctubs->GetSolid())->GetZHalfLength();
   } else if (dynamic_cast<J4TwistedTubs *>(cdctubs->GetSolid())) {
       return ((J4TwistedTubs *)cdctubs->GetSolid())->GetZHalfLength();
   } else {
       G4cerr << "J4VCDCDetectorComponent::GetZHalfLength is not be impremented for "
              << cdctubs->GetName() << G4endl;
       abort();
   }
}

G4double J4VCDCDetectorComponent::GetDeltaPhi(J4VComponent *cdctubs) const
{
   if (!(cdctubs->GetLV())) {
       G4cerr << "J4VCDCDetectorComponent::GetDeltaPhi: LV is not exist yet."
              << " Name = " 
              << cdctubs->GetName() << G4endl;
       abort();
   } else if (dynamic_cast<G4Tubs *>(cdctubs->GetSolid())) {
       return ((G4Tubs *)cdctubs->GetSolid())->GetDeltaPhiAngle();
   } else if (dynamic_cast<J4TwistedTubs *>(cdctubs->GetSolid())) {
       return ((J4TwistedTubs *)cdctubs->GetSolid())->GetDPhi();
   } else {
       G4cerr << "J4VCDCDetectorComponent::GetDeltaPhi is not be impremented for "
              << cdctubs->GetName() << G4endl;
       abort();
   }
}

G4double J4VCDCDetectorComponent::GetPhiOffset(J4VComponent *cdctubs) const
{
   if (!(cdctubs->GetLV())) {
       G4cerr << "J4VCDCDetectorComponent::GetPhiOffset: LV is not exist yet."
              << " Name = " 
              << cdctubs->GetName() << G4endl;
       abort();
   } else if (dynamic_cast<G4Tubs *>(cdctubs->GetSolid())) {
       return ((G4Tubs *)cdctubs->GetSolid())->GetStartPhiAngle();
   } else if (dynamic_cast<J4TwistedTubs *>(cdctubs->GetSolid())) {
       return 0;
   } else {
       G4cerr << "J4VCDCDetectorComponent::GetPhiOffset is not be impremented for "
              << cdctubs->GetName() << G4endl;
       abort();
   }
}

#endif


