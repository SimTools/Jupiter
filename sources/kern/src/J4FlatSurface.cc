 /*
 *  J4FlatSurface.cc
 *  
 *
 *  Created by Kotoyo Hoshina on Thu Aug 01 2002.
 *
 */

#include "G4Version.hh"
#if G4VERSION_NUMBER >= 900
#include "G4GeometryTolerance.hh"
#endif

#include "J4FlatSurface.hh"
#include "J4TwistedTubs.hh"

//#define __SOLIDDEBUG__
//#define __SOLIDDEBUGAREACODE__

//=====================================================================
//* constructor -------------------------------------------------------

J4FlatSurface::J4FlatSurface(const G4String         &name,
                             const G4RotationMatrix &rot,
                             const G4ThreeVector    &tlate,
                             const G4ThreeVector    &n,
                             const EAxis             axis0 ,
                             const EAxis             axis1 ,
                                   G4double          axis0min,
                                   G4double          axis1min,
                                   G4double          axis0max,
                                   G4double          axis1max )
              :J4VSurface(name, rot, tlate, 0, axis0, axis1, axis0min, axis1min,
                          axis0max, axis1max)
{   
   if (axis0 == kPhi && axis1 == kRho) {
      J4cerr << "J4FlatSurface::Constructor: Swap axis0 and axis1. abort. " << J4endl;
      abort();
   }
   
   G4ThreeVector normal = rot.inverse()*n;
   fCurrentNormal.normal = normal.unit();   // in local coordinate system
   fIsValidNorm = TRUE;

   SetCorners();
   SetBoundaries();
}

J4FlatSurface::J4FlatSurface(const G4String      &name,
                                   J4TwistedTubs *solid,
                                   G4int          handedness) 
              :J4VSurface(name, solid)
{   
   fHandedness = handedness;   // +z = +ve, -z = -ve
   fAxis[0]    = kRho;         // in local coordinate system
   fAxis[1]    = kPhi;
   G4int i     = (handedness < 0 ? 0 : 1);
   fAxisMin[0] = solid->GetEndInnerRadius(i);  // Inner-hype radius at z=0
   fAxisMax[0] = solid->GetEndOuterRadius(i);  // Outer-hype radius at z=0
   fAxisMin[1] = -0.5*(solid->GetDPhi());
   fAxisMax[1] = -fAxisMin[1];
   fCurrentNormal.normal.set(0, 0, (fHandedness < 0 ? -1 : 1)); 
         // Unit vector, in local coordinate system
   fRot.rotateZ(solid->GetEndPhi(i));
   fTrans.set(0, 0, solid->GetEndZ(i));
   fIsValidNorm = TRUE;

   SetCorners();
   SetBoundaries();
}

//=====================================================================
//* destructor --------------------------------------------------------
J4FlatSurface::~J4FlatSurface()
{
}

//=====================================================================
//* GetNormal ---------------------------------------------------------
G4ThreeVector J4FlatSurface::GetNormal(const G4ThreeVector &, 
                                             G4bool isGlobal)
{
   if (isGlobal) {
      return ComputeGlobalDirection(fCurrentNormal.normal);
   } else {
      return fCurrentNormal.normal;
   }
}

//=====================================================================
//* DistanceToSurface(p, v) ------------------------------------------
G4int J4FlatSurface::DistanceToSurface(const G4ThreeVector &gp,
                                       const G4ThreeVector &gv,
                                             G4ThreeVector  gxx[],
                                             G4double       distance[],
                                             G4int          areacode[],
                                             G4bool         isvalid[],
                                             EValidate      validate) 
{
   fCurStatWithV.ResetfDone(validate, &gp, &gv);
   
   if (fCurStatWithV.IsDone()) {
      G4int i;
      for (i=0; i<fCurStatWithV.GetNXX(); i++) {
         gxx[i] = fCurStatWithV.GetXX(i);
         distance[i] = fCurStatWithV.GetDistance(i);
         areacode[i] = fCurStatWithV.GetAreacode(i);
         isvalid[i]  = fCurStatWithV.IsValid(i);
      }
      return fCurStatWithV.GetNXX();
   } else {
      // initialize
      G4int i;
      for (i=0; i<2; i++) {
         distance[i] = kInfinity;
         areacode[i] = kOutside;
         isvalid[i]  = FALSE;
         gxx[i].set(kInfinity, kInfinity, kInfinity);
      }
   }

   G4ThreeVector p = ComputeLocalPoint(gp);
   G4ThreeVector v = ComputeLocalDirection(gv);

#ifdef __SOLIDDEBUG__
   J4cerr << "      ~~~~~ J4FlatSurface:DistanceToSurface(p,v) : Start" 
          << J4endl;
   J4cerr << "         Name : " << GetName() << J4endl;
   J4cerr << "         gp   : " << gp << J4endl;
   J4cerr << "         gv   : " << gv << J4endl;
   J4cerr << "         p    : " << p << J4endl;
   J4cerr << "         v    : " << v << J4endl;
   J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" 
          << J4endl;
#endif    
 
   //
   // special case!
   // if p is on surface, distance = 0. 
   //

   if (std::fabs(p.z()) == 0.) {   // if p is on the plane
      distance[0] = 0;
      G4ThreeVector xx = p;
      gxx[0] = ComputeGlobalPoint(xx);
      
      if (validate == kValidateWithTol) {
         areacode[0] = GetAreaCode(xx);
         if (!IsOutside(areacode[0])) {
            isvalid[0] = TRUE;
         }
      } else if (validate == kValidateWithoutTol) {
         areacode[0] = GetAreaCode(xx, FALSE);
         if (IsInside(areacode[0])) {
            isvalid[0] = TRUE;
         }
      } else { // kDontValidate
         areacode[0] = kInside;
         isvalid[0] = TRUE;
      }

#ifdef __SOLIDDEBUG__
      J4cerr << "      ~~~~~ J4FlatSurface:DistanceToSurface(p,v) : return"
             << J4endl;
      J4cerr << "         P is on surface. return 0. " << J4endl;
      J4cerr << "         NAME        : " << GetName() << J4endl;
      J4cerr << "         xx          : " << xx << J4endl;
      J4cerr << "         gxx[0]      : " << gxx[0] << J4endl;
      J4cerr << "         dist[0]     : " << distance[0] << J4endl;
      J4cerr << "         areacode[0] : " << areacode[0] << J4endl;
      J4cerr << "         isvalid[0]  : " << isvalid[0]  << J4endl;
      J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" 
             << J4endl;
      if (isvalid[0] && GetSolid()->Inside(gxx[0]) != ::kSurface) {
         J4cerr << " valid return value is not on surface! abort." << J4endl;
         abort();
      }
#endif

      return 1;

   }
   //
   // special case end
   //

   
   if (v.z() == 0) { 

      fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0], 
                                     isvalid[0], 0, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
      J4cerr << "      ~~~~~ J4FlatSurface:DistanceToSurface(p,v) : return"
             << J4endl;
      J4cerr << "         v.z = 0. no intersection. return 0. " << J4endl; 
      J4cerr << "         NAME     : " << GetName() << J4endl;
      J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" 
             << J4endl;
#endif   

      return 0;

   }
   
   distance[0] = - (p.z() / v.z());
      
   G4ThreeVector xx = p + distance[0]*v;
   gxx[0] = ComputeGlobalPoint(xx);

   if (validate == kValidateWithTol) {
      areacode[0] = GetAreaCode(xx);
      if (!IsOutside(areacode[0])) {
         if (distance[0] >= 0) isvalid[0] = TRUE;
      }
   } else if (validate == kValidateWithoutTol) {
      areacode[0] = GetAreaCode(xx, FALSE);
      if (IsInside(areacode[0])) {
         if (distance[0] >= 0) isvalid[0] = TRUE;
      }
   } else { // kDontValidate
      areacode[0] = kInside;
         if (distance[0] >= 0) isvalid[0] = TRUE;
   }

   fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                  isvalid[0], 1, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
   J4cerr <<"      ~~~~~ J4FlatSurface:DistanceToSurface(p,v) : return"
          << J4endl;
   J4cerr <<"         NAME        : " << GetName() << J4endl;
   J4cerr <<"         xx          : " << xx << J4endl;
   J4cerr <<"         gxx[0]      : " << gxx[0] << J4endl;
   J4cerr <<"         dist[0]     : " << distance[0] << J4endl;
   J4cerr <<"         areacode[0] : " << areacode[0] << J4endl;
   J4cerr <<"         isvalid[0]  : " << isvalid[0]  << J4endl;
   J4cerr <<"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" 
          << J4endl;
   if (isvalid[0] && GetSolid()->Inside(gxx[0]) != ::kSurface) {
      J4cerr << " valid return value is not on surface! abort." << J4endl;
      abort();
   }
#endif

   return 1;

}

//=====================================================================
//* DistanceToSurface(p) ----------------------------------------------
G4int J4FlatSurface::DistanceToSurface(const G4ThreeVector &gp,
                                             G4ThreeVector  gxx[],
                                             G4double       distance[],
                                             G4int          areacode[])
{
   // Calculate distance to plane in local coordinate,
   // then return distance and global intersection points.
   //  

   fCurStat.ResetfDone(kDontValidate, &gp);

   if (fCurStat.IsDone()) {
      G4int i;
      for (i=0; i<fCurStat.GetNXX(); i++) {
         gxx[i] = fCurStat.GetXX(i);
         distance[i] = fCurStat.GetDistance(i);
         areacode[i] = fCurStat.GetAreacode(i);
      }
      return fCurStat.GetNXX();
   } else {
      // initialize
      G4int i;
      for (i=0; i<2; i++) {
         distance[i] = kInfinity;
         areacode[i] = kOutside;
         gxx[i].set(kInfinity, kInfinity, kInfinity);
      }
   }
   
   G4ThreeVector p = ComputeLocalPoint(gp);
   G4ThreeVector xx;

   // The plane is placed on origin with making its normal 
   // parallel to z-axis. 
#if G4VERSION_NUMBER < 900
   if (std::fabs(p.z()) <= 0.5 * kCarTolerance) {   // if p is on the plane, return 1
#else
   if (std::fabs(p.z()) <= 0.5 * G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()) {   // if p is on the plane, return 1
#endif
      distance[0] = 0;
      xx = p;
   } else {
      distance[0] = std::fabs(p.z());
      xx.set(p.x(), p.y(), 0);  
   }

#ifdef __BOUNDARYCHECK__
   areacode[0] = GetAreaCode(xx, FALSE);
   if (!IsInside(areacode[0])) {
      // xx is out of boundary. 
      // return distance to boundary or corner.
      if (IsCorner(areacode[0])) {
         xx = GetCorner(areacode[0]);
         distance[0] = (xx - p).mag();
      } else {
         distance[0] = DistanceToBoundary(areacode[0], xx, p);
      }
   }
#endif

   gxx[0] = ComputeGlobalPoint(xx);
   areacode[0] = kInside;
   G4bool isvalid = TRUE;
   fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                             isvalid, 1, kDontValidate, &gp);
   return 1;

}

//=====================================================================
//* GetAreaCode -------------------------------------------------------
G4int J4FlatSurface::GetAreaCode(const G4ThreeVector &xx, 
                                       G4bool withTol)
{

#if G4VERSION_NUMBER < 900
   static const G4double rtol = 0.5*kRadTolerance;
#else
   static const G4double rtol = 0.5*G4GeometryTolerance::GetInstance()->GetRadialTolerance();
#endif
   
   G4int areacode = kInside;

   if (fAxis[0] == kRho && fAxis[1] == kPhi) {
      G4int rhoaxis = 0;
     // G4int phiaxis = 0;

      G4ThreeVector dphimin;   // direction of phi-minimum boundary
      G4ThreeVector dphimax;   // direction of phi-maximum boundary
      dphimin = GetCorner(kCorner0Max1Min);
      dphimax = GetCorner(kCorner0Max1Max);   
      
      if (withTol) {

         G4bool isoutside = FALSE;

         // test boundary of rho-axis

         if (xx.getRho() <= fAxisMin[rhoaxis] + rtol) {

            areacode |= (kAxis0 & (kAxisRho | kAxisMin)) | kBoundary; // rho-min
            if (xx.getRho() < fAxisMin[rhoaxis] - rtol) isoutside = TRUE; 
            
         } else if (xx.getRho() >= fAxisMax[rhoaxis] - rtol) {

            areacode |= (kAxis0 & (kAxisRho | kAxisMax)) | kBoundary; // rho-max
            if (xx.getRho() > fAxisMax[rhoaxis] + rtol) isoutside = TRUE; 

         }         
         
         // test boundary of phi-axis

         if (AmIOnLeftSide(xx, dphimin) >= 0) {           // xx is on dphimin

            areacode |= (kAxis1 & (kAxisPhi | kAxisMin)); 
            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary;

            if (AmIOnLeftSide(xx, dphimin) > 0) isoutside = TRUE; 

         } else if (AmIOnLeftSide(xx, dphimax) <= 0) {    // xx is on dphimax

            areacode |= (kAxis1 & (kAxisPhi | kAxisMax)); 
            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary;

            if (AmIOnLeftSide(xx, dphimax) < 0) isoutside = TRUE; 

         }
         
         // if isoutside = TRUE, clear inside bit.
         // if not on boundary, add axis information. 

         if (isoutside) {
            G4int tmpareacode = areacode & (~kInside);
            areacode = tmpareacode;
         } else if ((areacode & kBoundary) != kBoundary) {
            areacode |= (kAxis0 & kAxisRho) | (kAxis1 & kAxisPhi);
         }

      } else {

         // out of boundary of rho-axis

         if (xx.getRho() < fAxisMin[rhoaxis]) {
            areacode |= (kAxis0 & (kAxisRho | kAxisMin)) | kBoundary;
         } else if (xx.getRho() > fAxisMax[rhoaxis]) {
            areacode |= (kAxis0 & (kAxisRho | kAxisMax)) | kBoundary;
         }
         
         // out of boundary of phi-axis

         if (AmIOnLeftSide(xx, dphimin, FALSE) >= 0) {       // xx is leftside or
            areacode |= (kAxis1 & (kAxisPhi | kAxisMin)) ;   // boundary of dphimin
            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary;

         } else if (AmIOnLeftSide(xx, dphimax, FALSE) <= 0) { // xx is rightside or
            areacode |= (kAxis1 & (kAxisPhi | kAxisMax)) ;    // boundary of dphimax
            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary;
           
         }

         if ((areacode & kBoundary) != kBoundary) {
            areacode |= (kAxis0 & kAxisRho) | (kAxis1 & kAxisPhi);
         }

      }

      return areacode;

   } else {

      J4cerr << "      J4FlatSurface::GetAreaCode(withTol) fAxis[0] = " << fAxis[0]
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << J4endl;
      abort();
   }
}
                                      
                                           
//=====================================================================
//* SetCorners ---------------------------------------------------
void J4FlatSurface::SetCorners()
{
   // Set Corner points in local coodinate.
   
   if (fAxis[0] == kRho && fAxis[1] == kPhi) {
       
      G4int rhoaxis = 0;  // kRho
      G4int phiaxis = 1;  // kPhi
      
      G4double x, y, z;
      // corner of Axis0min and Axis1min
         x = fAxisMin[rhoaxis]*std::cos(fAxisMin[phiaxis]);
         y = fAxisMin[rhoaxis]*std::sin(fAxisMin[phiaxis]);
         z = 0;
         SetCorner(kCorner0Min1Min, x, y, z);
      // corner of Axis0max and Axis1min
         x = fAxisMax[rhoaxis]*std::cos(fAxisMin[phiaxis]);
         y = fAxisMax[rhoaxis]*std::sin(fAxisMin[phiaxis]);
         z = 0;
         SetCorner(kCorner0Max1Min, x, y, z);
      // corner of Axis0max and Axis1max
         x = fAxisMax[rhoaxis]*std::cos(fAxisMax[phiaxis]);
         y = fAxisMax[rhoaxis]*std::sin(fAxisMax[phiaxis]);
         z = 0;
         SetCorner(kCorner0Max1Max, x, y, z);
      // corner of Axis0min and Axis1max
         x = fAxisMin[rhoaxis]*std::cos(fAxisMax[phiaxis]);
         y = fAxisMin[rhoaxis]*std::sin(fAxisMax[phiaxis]);
         z = 0;
         SetCorner(kCorner0Min1Max, x, y, z);
       
   } else {
      J4cerr << "      J4FlatSurface::SetCorners fAxis[0] = " << fAxis[0]
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << J4endl;
      abort();   
   }
}

//=====================================================================
//* SetBoundaries() -------------------------------------------
void J4FlatSurface::SetBoundaries()
{
   // Set direction-unit vector of phi-boundary-lines in local coodinate.
   // Don't call the function twice.
   
   if (fAxis[0] == kRho && fAxis[1] == kPhi) {
   
      G4ThreeVector direction;
      // kAxis0 & kAxisMin
      direction = GetCorner(kCorner0Min1Max) - GetCorner(kCorner0Min1Min);
      direction = direction.unit();
      SetBoundary(kAxis0 & (kAxisPhi | kAxisMin), direction,
                  GetCorner(kCorner0Min1Min), kAxisPhi);
                  
      // kAxis0 & kAxisMax
      direction = GetCorner(kCorner0Max1Max) - GetCorner(kCorner0Max1Min);
      direction = direction.unit();
      SetBoundary(kAxis0 & (kAxisPhi | kAxisMax), direction,
                  GetCorner(kCorner0Max1Min), kAxisPhi);

      // kAxis1 & kAxisMin
      direction = GetCorner(kCorner0Max1Min) - GetCorner(kCorner0Min1Min);
      direction = direction.unit();
      SetBoundary(kAxis1 & (kAxisRho | kAxisMin), direction,
                  GetCorner(kCorner0Min1Min), kAxisRho);
      
      // kAxis1 & kAxisMax
      direction = GetCorner(kCorner0Max1Max) - GetCorner(kCorner0Min1Max);
      direction = direction.unit();
      SetBoundary(kAxis1 & (kAxisRho | kAxisMax), direction,
                  GetCorner(kCorner0Min1Max), kAxisPhi);
                                       
   } else {
      J4cerr << "      J4FlatSurface::SetBoundaries fAxis[0] = " << fAxis[0] 
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << J4endl;
      abort();
   }
}

                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           

