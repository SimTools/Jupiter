// $Id$
#ifndef __J4TWISTEDSURFACE__
#define __J4TWISTEDSURFACE__
//*************************************************************************
//* --------------------
//* J4TwistedSurface
//* --------------------
//* (Description)
//* 	Class for twisted boundary surface for J4Solid.
//*     
//* (Update Record)
//*	2002/08/01  K.Hoshina	Original version.
//*************************************************************************


#include "J4VSurface.hh"

class J4TwistedTubs;

class J4TwistedSurface : public J4VSurface
{
public:
   
   J4TwistedSurface(const G4String         &name,
                    const G4RotationMatrix &rot,        // rotation of 0.5*(phi-width of a segment)
                    const G4ThreeVector    &tlate,
                    G4int                   handedness, // right hand = 1, left hand = -1
                    const G4double          kappa,      // tan(TwistAngle/2)/fZHalfLen
                    const EAxis             axis0 = kXAxis,
                    const EAxis             axis1 = kZAxis,
                          G4double          axis0min = -kInfinity,
                          G4double          axis1min = -kInfinity,
                          G4double          axis0max = kInfinity,
                          G4double          axis1max = kInfinity );
                          
   J4TwistedSurface(const G4String &name, J4TwistedTubs *solid, G4int handedness);

   virtual ~J4TwistedSurface();
   
   virtual G4ThreeVector  GetNormal(const G4ThreeVector &xx, G4bool isGlobal = FALSE) ;   

   virtual G4int          DistanceToSurface(const G4ThreeVector &gp,
                                            const G4ThreeVector &gv,
                                                  G4ThreeVector  gxx[],
                                                  G4double       distance[],
                                                  G4int          areacode[],
                                                  G4bool         isvalid[],
                                                  EValidate      validate = kValidateWithTol);
                                                  
   virtual G4int          DistanceToSurface(const G4ThreeVector &gp,
                                                  G4ThreeVector  gxx[],
                                                  G4double       distance[],
                                                  G4int          areacode[]);
 
 private:
   virtual G4double       DistanceToPlane(const G4ThreeVector &p,
                                          const G4ThreeVector &A,
                                          const G4ThreeVector &B,
                                          const G4ThreeVector &C,
                                          const G4ThreeVector &D,
                                          const G4int          parity,
                                                G4ThreeVector &xx,
                                                G4ThreeVector &n);

   virtual G4int          GetAreaCode(const G4ThreeVector &xx, 
                                            G4bool         withTol = TRUE) const;

   virtual void           SetCorners();
   virtual void           SetCorners(J4TwistedTubs *solid);
   virtual void           SetBoundaries();
   


private:

   G4double       fKappa;          // tan(TwistedAngle/2)/HalfLenZ;
  
};   

#endif
