// $Id$
#ifndef __J4FLATSURFACE__
#define __J4FLATSURFACE__
//*************************************************************************
//* --------------------
//* J4FlatSurface
//* --------------------
//* (Description)
//* 	Class for flat boundary surface for J4Solid.
//*     
//* (Update Record)
//*	2002/08/01  K.Hoshina	Original version.
//*************************************************************************

#include "J4VSurface.hh"

class J4TwistedTubs;

class J4FlatSurface : public J4VSurface
{
public:

   J4FlatSurface(const G4String         &name,
                 const G4RotationMatrix &rot,
                 const G4ThreeVector    &tlate,
                 const G4ThreeVector    &n,
                 const EAxis             axis1 = kRho,
                 const EAxis             axis2 = kPhi,
                       G4double          axis0min = -kInfinity,
                       G4double          axis1min = -kInfinity,
                       G4double          axis0max = kInfinity,
                       G4double          axis1max = kInfinity );
                       
   J4FlatSurface(const G4String            &name,
                       J4TwistedTubs       *solid,
                       G4int                handedness) ;
                       
   virtual ~J4FlatSurface();
   
   virtual G4ThreeVector  GetNormal(const G4ThreeVector &xx, G4bool isGlobal = FALSE);

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
                                                  
protected:                                                  
   virtual G4int          GetAreaCode(const G4ThreeVector &xx, 
                                      G4bool withTol = TRUE) ;

private:

   virtual void           SetCorners();
   virtual void           SetBoundaries();


private:
   G4double               fHalfDPhi;
   
};

#endif

