// $Id$
#ifndef __J4VSURFACE__
#define __J4VSURFACE__
//*************************************************************************
//* --------------------
//* J4VSurface
//* --------------------
//* (Description)
//*     Abstract base class for boundary surface of J4Solid.
//*     
//* (Update Record)
//*     2002/08/01  K.Hoshina   Original version.
//*************************************************************************

#include <iomanip>

#include "geomdefs.hh"
#include "G4RotationMatrix.hh"

class J4VSurface
{

 // enum type ----------------------------------------------------------------
 protected:

   enum EValidate      {kDontValidate = 0, kValidateWithTol = 1, 
                        kValidateWithoutTol = 2, kUninitialized = 3};
                        
 // member functions ----------------------------------------------------------
 public:

   J4VSurface (const G4String &name);
   J4VSurface (const G4String &name,
               const G4RotationMatrix &rot,
               const G4ThreeVector    &tlate,
                     G4int             handedness,
               const EAxis             axis1,
               const EAxis             axis2,
                     G4double          axis0min = -kInfinity,
                     G4double          axis1min = -kInfinity,
                     G4double          axis0max = kInfinity,
                     G4double          axis1max = kInfinity);

   virtual ~J4VSurface();
   
   static G4double   DistanceToPlane(const G4ThreeVector &p,
                                     const G4ThreeVector &x0,
                                     const G4ThreeVector &t1,
                                     const G4ThreeVector &t2,
                                           G4ThreeVector &xx,
                                           G4ThreeVector &n);

   static G4int      AmIOnLeftSide(G4ThreeVector ai, G4ThreeVector vec, G4bool withTol = TRUE);

   G4double          DistanceToBoundary(G4int areacode,
                                        G4ThreeVector &xx,
                                        const G4ThreeVector &p) ;


   G4double          DistanceToIn(const G4ThreeVector &gp,
                                  const G4ThreeVector &gv,
                                        G4ThreeVector &gxxbest);
   G4double          DistanceToOut(const G4ThreeVector &gp,
                                   const G4ThreeVector &gv,
                                         G4ThreeVector &gxxbest);
   G4double          DistanceTo(const G4ThreeVector &gp,
                                      G4ThreeVector &gxx);
      
   virtual G4int     DistanceToSurface(const G4ThreeVector &gp,
                                       const G4ThreeVector &gv,
                                             G4ThreeVector gxx[],
                                             G4double      distance[],
                                             G4int         areacode[],
                                             G4bool        isvalid[],
                                             EValidate      validate = kValidateWithTol) = 0;
                                             
   virtual G4int     DistanceToSurface(const G4ThreeVector &gp,
                                             G4ThreeVector gxx[],
                                             G4double      distance[],
                                             G4int         areacode[]) = 0;
                                             
   void              DebugPrint();

   // get method
   virtual G4String      GetName() const { return fName; }
   virtual G4ThreeVector GetNormal(const G4ThreeVector &xx, G4bool isGlobal) = 0;
   virtual void          GetBoundaryParameters(const G4int   &areacode,
                                               G4ThreeVector &d,
                                               G4ThreeVector &x0,
                                               G4int         &boundarytype) const;
   inline  G4bool        IsAxis0(G4int areacode) const;
   inline  G4bool        IsAxis1(G4int areacode) const;
   inline  G4int         GetAxisType(G4int areacode, G4int whichaxis) const;
  
   // set method
   inline void           SetAxis(G4int i, const EAxis axis)  { fAxis[i] = axis; }
   inline void           SetNeighbours(J4VSurface* axis0min, J4VSurface* axis1min, 
                                       J4VSurface* axis0max, J4VSurface* axis1max);
   

 protected:
 
   // get method
   inline  J4VSurface**  GetNeighbours()            { return fNeighbours; } 
   inline  G4int         GetNeighbours(G4int areacode, J4VSurface* surfaces[]); 
   inline  G4ThreeVector GetCorner(G4int areacode) const;
           void          GetBoundaryAxis(G4int areacode, EAxis axis[]) const;
           void          GetBoundaryLimit(G4int areacode, G4double limit[]) const;
   virtual G4int         GetAreaCode(const G4ThreeVector &xx, G4bool withtol = TRUE) const = 0;   
      
   // set method
   virtual void          SetBoundary(const G4int         &axiscode, 
                                     const G4ThreeVector &direction,
                                     const G4ThreeVector &x0, 
                                     const G4int         &boundarytype);
                            // areacode must be one of them:
                            // kAxis0 & kAxisMin, kAxis0 & kAxisMax,
                            // kAxis1 & kAxisMin, kAxis1 & kAxisMax.
                            // boundarytype represents the shape of locus
                            // from the start point to end point of boundary.
                            // ex.
                            // kAxisRho = linear line which start point is
                            //            fixed at origin.
                            // kAxisPhi = part of circle which center placed 
                            //            the origin.
                            
          void           SetCorner(G4int areacode, G4double x, G4double y, G4double z);

 private:
   virtual void SetBoundaries() = 0;
   virtual void SetCorners()    = 0;
   
 // data members ------------------------------------------------------------------

 public:
   static const G4int  kOutside ;
   static const G4int  kInside  ;
   static const G4int  kBoundary;
   static const G4int  kCorner;
   static const G4int  kCorner0Min1Min;
   static const G4int  kCorner0Max1Min;
   static const G4int  kCorner0Max1Max;
   static const G4int  kCorner0Min1Max;
   static const G4int  kAxisMin;
   static const G4int  kAxisMax;
   static const G4int  kAxisX;
   static const G4int  kAxisY;
   static const G4int  kAxisZ;
   static const G4int  kAxisRho;
   static const G4int  kAxisPhi;

   static const G4int  kAxis0;
   static const G4int  kAxis1;
   static const G4int  kSizeMask;
   static const G4int  kAxisMask;
   static const G4int  kAreaMask;

 protected:
 
   class CurrentStatus 
   {
    public:
      CurrentStatus() 
      {
         G4int i;
         for (i=0; i<2; i++) {
            fDistance[i] = kInfinity;
            fAreacode[i] = kOutside;
            fIsValid[i]  = FALSE;
            fXX[i].set(kInfinity, kInfinity, kInfinity);
         }
         fNXX   = 0;
         fLastp.set(kInfinity, kInfinity, kInfinity);
         fLastv.set(kInfinity, kInfinity, kInfinity);
         fLastValidate = kUninitialized;
         fDone = FALSE;
      }
      
      inline G4ThreeVector GetXX(G4int i)       const { return fXX[i];       }
      inline G4double      GetDistance(G4int i) const { return fDistance[i]; }
      inline G4int         GetAreacode(G4int i) const { return fAreacode[i]; }
      inline G4int         GetNXX()             const { return fNXX;         }
      inline G4bool        IsDone()             const { return fDone;        }
      inline G4bool        IsValid(G4int i)     const { return fIsValid[i];  }

      inline void          SetCurrentStatus(G4int                i, 
                                            G4ThreeVector       &xx, 
                                            G4double            &dist, 
                                            G4int               &areacode, 
                                            G4bool              &isvalid,
                                            G4int                nxx,
                                            EValidate            validate,
                                            const G4ThreeVector *p, 
                                            const G4ThreeVector *v = 0)
                           {
                              fDistance[i]  = dist;
                              fAreacode[i]  = areacode;
                              fIsValid[i]   = isvalid;
                              fXX[i]        = xx;
                              fNXX          = nxx;
                              fLastValidate = validate;
                              if (p) {
                                 fLastp = *p;
                              } else {
                                 G4cerr << "J4VSurface::CurrentStatus::"
                                        << "SetCurrentStatus: p = 0! " << G4endl;
                                 abort();
                              }
                              if (v) {
                                 fLastv = *v;
                              } else {
                                 fLastv.set(kInfinity, kInfinity, kInfinity);
                              }
                              fDone = TRUE;
                           }

      inline void          ResetfDone(EValidate            validate,
                                      const G4ThreeVector *p, 
                                      const G4ThreeVector *v = 0)
                                      
                           {
                              if (validate == fLastValidate && p && *p == fLastp) {
                                 if (!v || (v && *v == fLastv))         return;
                              }
                              
                              G4int i;
                              G4ThreeVector xx(kInfinity, kInfinity, kInfinity);
                              for (i=0; i<2; i++) {
                                 fDistance[i] = kInfinity;
                                 fAreacode[i] = kOutside;
                                 fIsValid[i]  = FALSE;
                                 fXX[i] = xx[i];
                              }
                              fNXX   = 0;
                              fLastp.set(kInfinity, kInfinity, kInfinity);
                              fLastv.set(kInfinity, kInfinity, kInfinity);
                              fLastValidate = kUninitialized;
                              fDone = FALSE;
                           }

      inline void          DebugPrint()
                           {
                              G4cerr << "CurrentStatus::Dist0,1= " << fDistance[0] 
                              << " " << fDistance[1] << " areacode = " << fAreacode[0] 
                              << " " << fAreacode[1] << G4endl;
                           }

    private:
      G4double             fDistance[2];
      G4ThreeVector        fXX[2];
      G4int                fAreacode[2];
      G4bool               fIsValid[2];
      G4int                fNXX;
      G4ThreeVector        fLastp;
      G4ThreeVector        fLastv;
      EValidate            fLastValidate;
      G4bool               fDone;
   };
      
   class Boundary 
   {
    public:
      Boundary() : fBoundaryAcode(-1), fBoundaryType(0){}
      
      void SetFields(const G4int         &areacode, 
                     const G4ThreeVector &d, 
                     const G4ThreeVector &x0, 
                     const G4int         &boundarytype)
      {
         fBoundaryAcode     = areacode;
         fBoundaryDirection = d;
         fBoundaryX0        = x0;
         fBoundaryType      = boundarytype;
      }
      
      G4bool IsEmpty() const 
      {
         if (fBoundaryAcode == -1) return TRUE;
         return FALSE;
      }
      
      G4bool GetBoundaryParameters(const G4int         &areacode, 
                                         G4ThreeVector &d,
                                         G4ThreeVector &x0, 
                                         G4int         &boundarytype) const 
      {  
         // areacode must be one of them:
         // kAxis0 & kAxisMin, kAxis0 & kAxisMax,
         // kAxis1 & kAxisMin, kAxis1 & kAxisMax
         if (areacode != (fBoundaryAcode & kSizeMask)) return FALSE;
         d  = fBoundaryDirection;
         x0 = fBoundaryX0;
         boundarytype = fBoundaryType;
         return TRUE;
      }

    private:
      G4int          fBoundaryAcode;
      G4ThreeVector  fBoundaryDirection;
      G4ThreeVector  fBoundaryX0;
      G4int          fBoundaryType;
   };

   EAxis               fAxis[2];
   G4double            fAxisMin[2];
   G4double            fAxisMax[2];
   CurrentStatus       fCurStatWithV;
   CurrentStatus       fCurStat;
   G4RotationMatrix    fRot;
   G4ThreeVector       fTrans;
   G4int               fHandedness;
   G4ThreeVector       fCurrentNormal; //
                        
 private:
                     
   J4VSurface         *fNeighbours[4]; // {0,1,2,3} = kAxis0min, kAxis1min, 
                                       //             kAxis0max, kAxis1max
   G4ThreeVector       fCorners[4];    // corners of the surface in local coordinate
   Boundary            fBoundaries[4]; // boundaries of the surface.
   G4String            fName;
    
};

//========================================================
// inline function
//========================================================

G4bool J4VSurface::IsAxis0(G4int areacode) const 
{
   if (areacode & kAxis0) return TRUE;
   return FALSE;
}

G4bool J4VSurface::IsAxis1(G4int areacode) const 
{
   if (areacode & kAxis1) return TRUE;
   return FALSE;
}

G4int J4VSurface::GetAxisType(G4int areacode, G4int whichaxis) const
{
   G4int axiscode = areacode & kAxisMask & whichaxis;
   
   if (axiscode == (kAxisX & kAxis0) ||
       axiscode == (kAxisX & kAxis1)) {
      return kAxisX;
   } else if (axiscode == (kAxisY & kAxis0) ||
              axiscode == (kAxisY & kAxis1)) {
      return kAxisY;
   } else if (axiscode == (kAxisZ & kAxis0) ||
              axiscode == (kAxisZ & kAxis1)) {
      return kAxisZ;
   } else if (axiscode == (kAxisRho & kAxis0) ||
              axiscode == (kAxisRho & kAxis1)) {
      return kAxisRho;
   } else if (axiscode == (kAxisPhi & kAxis0) ||
              axiscode == (kAxisPhi & kAxis1)) {
      return kAxisPhi;
   } else {
      G4cerr << "J4VSurface::GetAxisType: areacode= "
             << areacode << " is not supported. abort. " << G4endl;
      abort();
   }
}

void J4VSurface::SetNeighbours(J4VSurface* axis0min, J4VSurface* axis1min, 
                               J4VSurface* axis0max, J4VSurface* axis1max)
{
   fNeighbours[0] = axis0min;
   fNeighbours[1] = axis1min;
   fNeighbours[2] = axis0max;
   fNeighbours[4] = axis1max;
}

G4int J4VSurface::GetNeighbours(G4int areacode, J4VSurface** surfaces) 
{
   G4int i = 0;
   
   if (areacode & (kAxis0 | kAxisMin)) {
       surfaces[i] = fNeighbours[0];
       i++;
   }
   if (areacode & (kAxis1 | kAxisMin)) {
       surfaces[i] = fNeighbours[1];
       i++;
       if (i == 2) return i;
   }
   if (areacode & (kAxis0 | kAxisMax)) {
       surfaces[i] = fNeighbours[2];
       i++;
       if (i == 2) return i;
   }
   if (areacode & (kAxis1 | kAxisMax)) {
       surfaces[i] = fNeighbours[3];
       i++;
       if (i == 2) return i;
   }
   
   return i;
}

G4ThreeVector J4VSurface::GetCorner(G4int areacode) const
{
   if (!(areacode & kCorner)){
      G4cerr << "J4VSurface::GetCorner: area code must represents corner. " 
             << "your areacode = " << areacode << G4endl;
      abort();
   }
   
   if ((areacode & kCorner0Min1Min) == kCorner0Min1Min) { 
      return fCorners[0];
   } else if ((areacode & kCorner0Max1Min) == kCorner0Max1Min) { 
      return fCorners[1];
   } else if ((areacode & kCorner0Max1Max) == kCorner0Max1Max) {
      return fCorners[2];
   } else if ((areacode & kCorner0Min1Max) == kCorner0Min1Max) { 
      return fCorners[3];
   } else {
      G4cerr << "J4VSurface::GetCorner: areacode= "
             << areacode << " is not supported. abort. " << G4endl;
      abort();
   }
}


#if 0
void J4VSurface::Decode(G4int areacode, G4bool &isCorner, EAxis &axis, 
                        G4double &value, G4bool &isMin) const
{
  if (areacode & kAxis0min && areacode & kAxis1min) {
      axis[0]  = fAxis[0];
      value[0] = fAxisMin[0];
      isMin[0] = TRUE;
      axis[1]  = fAxis[1];
      value[1] = fAxisMin[1];
      isMin[1] = TRUE;
      isCorner = TRUE;
   } else if (areacode & kAxis1min && areacode & kAxis0max) { 
      axis[0]  = fAxis[1];
      value[0] = fAxisMin[1];
      isMin[0] = TRUE;
      axis[1]  = fAxis[0];
      value[1] = fAxisMax[0];
      isMin[1] = FALSE;
      isCorner = TRUE;
   } else if (areacode & kAxis0max && areacode & kAxis1max) { 
      axis[0]  = fAxis[0];
      value[0] = fAxisMax[0];
      isMin[0] = FALSE;
      axis[1]  = fAxis[1];
      value[1] = fAxisMax[1];
      isMin[1] = FALSE;
      isCorner = TRUE;
   } else if (areacode & kAxis1max) && areacode & kAxis0min) {
      axis[0]  = fAxis[1];
      value[0] = fAxisMax[1];
      isMin[0] = FALSE;
      axis[1]  = fAxis[0];
      value[1] = fAxisMin[0];
      isMin[1] = TRUE;
      isCorner = TRUE;
   } else if (areacode & kAxis0min) { 
      axis[0]  = fAxis[0];
      value[0] = fAxisMin[0];
      isMin[0] = TRUE;
      isCorner = FALSE;
   } else if (areacode & kAxis1min) { 
      axis[0]  = fAxis[1];
      value[0] = fAxisMin[1];
      isMin[0] = TRUE;
      isCorner = FALSE;
   } else if (areacode & kAxis0max) {
      axis[0]  = fAxis[0];
      value[0] = fAxisMax[0];
      isMin[0] = FALSE;
      isCorner = FALSE;
   } else if (areacode & kAxis1max) { 
      axis[0]  = fAxis[1];
      value[0] = fAxisMax[1];
      isMin[0] = FALSE;
      isCorner = FALSE;
   }
       G4cerr << "J4VSurface::Decode: the argument must be area mask. " 
          << "your areacode = " << areacode << G4endl;
}

#endif

#endif

