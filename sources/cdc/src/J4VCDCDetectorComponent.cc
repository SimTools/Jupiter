// $Id$
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

#include "J4VCDCDetectorComponent.hh"


J4CDCMaterialStore* J4VCDCDetectorComponent::fMaterialStore = 0;

G4String J4VCDCDetectorComponent::fSubGroup("CDC");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* constructor -----------------------------------------------

J4VCDCDetectorComponent::J4VCDCDetectorComponent(
                                const G4String       &name, 
                                J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name,
                                              parent, nclones,	 
                                              nbrothers, me, copyno )   
{ 
}

J4VCDCDetectorComponent::J4VCDCDetectorComponent( 
                             const J4VCDCDetectorComponent &orig,
                                   G4int                    copyno)
                        :J4VDetectorComponent(orig, copyno)
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCDCDetectorComponent::~J4VCDCDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VCDCDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4CDCMaterialStore();
        Register(fMaterialStore);
  	G4cerr << "*** Opend J4CDCMaterialStore ***" << G4endl;
   }
    
   return fMaterialStore;
}

//=====================================================================
//* GetInnerRadius    -------------------------------------------------

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

//=====================================================================
//* GetOuterRadius    -------------------------------------------------

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

//=====================================================================
//* GetInnerWeist -----------------------------------------------------

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

//=====================================================================
//* GetOuterWeist -----------------------------------------------------

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

//=====================================================================
//* GetZHalfLength ----------------------------------------------------

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

//=====================================================================
//* GetDeltaPhi -------------------------------------------------------

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

//=====================================================================
//* GetPhiOffset ------------------------------------------------------

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

//=====================================================================
//* CalcStereoAngle ---------------------------------------------------

G4double J4VCDCDetectorComponent::CalcTanStereo(G4double phitwist,
                                                  G4double r,
                                                  G4double halflen)
{
   return r * sin(0.5 * phitwist) / halflen; 
}

//=====================================================================
//* CalcWaist -----------------------------------------------------

G4double J4VCDCDetectorComponent::CalcWaist(G4double tanstereo,
                                            G4double radius,
                                            G4double halflen) 
{
   return sqrt(radius * radius - 
               halflen * halflen * tanstereo * tanstereo); 
} 

