 /*
 *  J4FlatSurface.cc
 *  
 *
 *  Created by Kotoyo Hoshina on Thu Aug 01 2002.
 *
 */

#include "J4FlatSurface.hh"
#include "J4TwistedTubs.hh"

//#define __SOLIDDEBUG__

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
      G4cerr << "J4FlatSurface::Constructor: Swap axis0 and axis1. abort. " << G4endl;
      abort();
   }
   
   fCurrentNormal = (rot.inverse()*n).unit();   // in local coordinate system

   SetCorners();
   SetBoundaries();
}

J4FlatSurface::J4FlatSurface(const G4String      &name,
                                   J4TwistedTubs *solid,
                                   G4int          handedness) 
              :J4VSurface(name)
{   
   fHandedness = handedness;   // +z = +ve, -z = -ve
   fAxis[0]    = kRho;         // in local coordinate system
   fAxis[1]    = kPhi;
   G4int i     = (handedness < 0 ? 0 : 1);
   fAxisMin[0] = solid->GetEndInnerRadius(i);  // Inner-hype radius at z=0
   fAxisMax[0] = solid->GetEndOuterRadius(i);  // Outer-hype radius at z=0
   fAxisMin[1] = -0.5*(solid->GetDPhi());
   fAxisMax[1] = -fAxisMin[1];
   fCurrentNormal.set(0, 0, (fHandedness < 0 ? -1 : 1)); // Unit vector, in local coordinate system
   fRot.rotateZ(solid->GetEndPhi(i));
   fTrans.set(0, 0, solid->GetEndZ(i));

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
G4ThreeVector J4FlatSurface::GetNormal(const G4ThreeVector &xx, G4bool isGlobal)
{
   if (isGlobal) {
      return fRot*fCurrentNormal;
   } else {
      return fCurrentNormal;
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

   G4ThreeVector p = fRot.inverse()*gp - fTrans;
   G4ThreeVector v = fRot.inverse()*gv;

#ifdef __SOLIDDEBUG__
   G4cerr << "~~~~~ J4FlatSurface:DistanceToSurface(p,v) : Start from gp, gv,"
          << " p, v ,n :" << G4endl;
   G4cerr << "      "
          << GetName() << " , "
          << gp << " , "
          << gv << " , "
          << p << " , "
          << v << " , " 
          << fCurrentNormal << " ~~~~~ " << G4endl;
#endif    
 
   //
   // special case!
   // if p is on surface, distance = 0. 
   //

   if (fabs(p.z()) <= 0.5 * kCarTolerance) {   // if p is on the plane, return 1
      distance[0] = 0;
      G4ThreeVector xx = p;
      gxx[0] = fRot*xx + fTrans;
      
      if (validate == kValidateWithTol) {
         areacode[0] = GetAreaCode(xx);
         if ((areacode[0] & kAreaMask) != kOutside) {
            isvalid[0] = TRUE;
         }
      } else if (validate == kValidateWithoutTol) {
         areacode[0] = GetAreaCode(xx, FALSE);
         if ((areacode[0] & kAreaMask) == kInside) {
            isvalid[0] = TRUE;
         }
      } else { // kDontValidate
         areacode[0] = kInside;
         isvalid[0] = TRUE;
      }

#ifdef __SOLIDDEBUG__
      G4cerr << "~~~~~ J4FlatSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
             << G4endl;
      G4cerr << "   P is on surface. return 0. " << G4endl;
      G4cerr << "   NAME        : " << GetName() << G4endl;
      G4cerr << "   xx          : " << xx << G4endl;
      G4cerr << "   gxx[0]      : " << gxx[0] << G4endl;
      G4cerr << "   dist[0]     : " << distance[0] << G4endl;
      G4cerr << "   areacode[0] : " << areacode[0] << G4endl;
      G4cerr << "   isvalid[0]  : " << isvalid[0]  << G4endl;
      G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
             << G4endl;
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
      G4cerr << "~~~~~ J4FlatSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
             << G4endl;
      G4cerr << "  v.z = 0. no intersection. return 0. " << G4endl; 
      G4cerr << "   NAME     : " << GetName() << G4endl;
      G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
             << G4endl;
#endif   

      return 0;

   }
   
   distance[0] = - (p.z() / v.z());
      
   G4ThreeVector xx = p + distance[0]*v;
   gxx[0] = fRot*xx + fTrans;

   if (validate == kValidateWithTol) {
      areacode[0] = GetAreaCode(xx);
      if ((areacode[0] & kAreaMask) != kOutside) {
         if (distance[0] > 0) isvalid[0] = TRUE;
      }
   } else if (validate == kValidateWithoutTol) {
      areacode[0] = GetAreaCode(xx, FALSE);
      if ((areacode[0] & kAreaMask) == kInside) {
         if (distance[0] > 0) isvalid[0] = TRUE;
      }
   } else { // kDontValidate
      areacode[0] = kInside;
      if (distance[0] > 0) isvalid[0] = TRUE;
   }

   fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                  isvalid[0], 1, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
   G4cerr <<"~~~~~ J4FlatSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
          << G4endl;
   G4cerr <<"   NAME        : " << GetName() << G4endl;
   G4cerr <<"   xx          : " << xx << G4endl;
   G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
   G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
   G4cerr <<"   areacode[0] : " << areacode[0] << G4endl;
   G4cerr <<"   isvalid[0]  : " << isvalid[0]  << G4endl;
   G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
          << G4endl;
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
   
   G4ThreeVector p = fRot.inverse()*gp - fTrans;

   // The plane is placed on origin with making its normal 
   // parallel to z-axis. 
   if (fabs(p.z()) <= 0.5 * kCarTolerance) {   // if p is on the plane, return 1
      distance[0] = 0;
      G4ThreeVector xx = p;
      gxx[0] = fRot*xx + fTrans;
   } else {
      distance[0] = fabs(p.z());
      G4ThreeVector xx(p.x(), p.y(), 0);  
      gxx[0] = fRot*xx + fTrans;
   }

   areacode[0] = kInside;
   G4bool isvalid = TRUE;
   fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                             isvalid, 1, kDontValidate, &gp);
   return 1;

}

//=====================================================================
//* GetAreaCode -------------------------------------------------------
G4int J4FlatSurface::GetAreaCode(const G4ThreeVector &xx, 
                                       G4bool withTol) const
{

   G4RotationMatrix unitrot; // unit matrix
   static const G4double         rtol      = 0.5*kRadTolerance;
   static const G4RotationMatrix rottol    = unitrot.rotateZ(0.5*kAngTolerance);
   static const G4RotationMatrix invrottol = unitrot.rotateZ(-0.5*kAngTolerance);
   
   G4int areacode = 0;

   if (fAxis[0] == kRho && fAxis[1] == kPhi) {
      G4int rhoaxis = 0;

      G4ThreeVector dphimin;   // direction of phi-minimum boundary
      G4ThreeVector dphimax;   // direction of phi-maximum boundary
      dphimin = GetCorner(kCorner0Max1Min);
      dphimax = GetCorner(kCorner0Max1Max);
      
      if (withTol) {
         
         // inside or outside
         if (xx.getRho() >= fAxisMin[rhoaxis] + rtol 
                    && xx.getRho() <= fAxisMax[rhoaxis] - rtol
                    && xx.cross(rottol*dphimin).z() <= 0
                    && xx.cross(invrottol*dphimax).z() >= 0 ) {
            areacode |= (kAxis0 & kAxisRho) | (kAxis1 & kAxisPhi) | kInside;
            return areacode;
         } else if (xx.getRho() <= fAxisMin[rhoaxis] - rtol 
                    || xx.getRho() >= fAxisMax[rhoaxis] + rtol
                    || xx.cross(invrottol*dphimin).z() >= 0
                    || xx.cross(rottol*dphimax).z() <= 0 ) {
            areacode |= (kAxis0 & kAxisRho) | (kAxis1 & kAxisPhi) | kOutside;
            return areacode;
         }
         
         // Now, xx is on boundary. Which boundary?
         // on boundary of rho-axis
         if (xx.getRho() <= fAxisMin[rhoaxis] + rtol) {
            areacode |= (kAxis0 & (kAxisRho | kAxisMin)) | kBoundary; // rho-min
         } else if (xx.getRho() >= fAxisMax[rhoaxis] - rtol) {
            areacode |= (kAxis0 & (kAxisRho | kAxisMax)) | kBoundary; // rho-max
         }         
         // on boundary of phi-axis
         if (xx.cross(rottol*dphimin).z() > 0) { 
            areacode |= (kAxis1 & (kAxisPhi | kAxisMin)); // phi-min
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary;
            }
         } else if (xx.cross(invrottol*dphimax).z() < 0) {
            areacode |= (kAxis1 & (kAxisPhi | kAxisMax)); // phi-max
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary;
            }
         }
         return areacode;

      } else {

         // inside
         if (xx.getRho() >= fAxisMin[rhoaxis]
             && xx.getRho() <= fAxisMax[rhoaxis]
             && xx.cross(dphimin).z() <= 0
             && xx.cross(dphimax).z() >= 0 ) {
            areacode |= (kAxis0 & kAxisRho) | (kAxis1 & kAxisPhi) | kInside;
            return areacode;
         }
         
         // Now, xx is out of boundary. Which boundary?
         // out of boundary of rho-axis
         if (xx.getRho() < fAxisMin[rhoaxis]) {
            areacode |= (kAxis0 & (kAxisRho | kAxisMin)) | kBoundary;
         } else if (xx.getRho() > fAxisMax[rhoaxis]) {
            areacode |= (kAxis0 & (kAxisRho | kAxisMax)) | kBoundary;
         }
         // out of boundary of phi-axis
         if (xx.cross(dphimin).z() > 0 ) {
            areacode |= (kAxis1 & (kAxisPhi | kAxisMin)) ;
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary;
            }
         } else if (xx.cross(dphimax).z() < 0 ) {
            areacode |= (kAxis1 & (kAxisPhi | kAxisMax)) ;
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary;
            }
         }
         return areacode;
      }
   } else {

      G4cerr << "J4FlatSurface::GetAreaCode(withTol) fAxis[0] = " << fAxis[0]
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << G4endl;
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
         x = fAxisMin[rhoaxis]*cos(fAxisMin[phiaxis]);
         y = fAxisMin[rhoaxis]*sin(fAxisMin[phiaxis]);
         z = 0;
         SetCorner(kCorner0Min1Min, x, y, z);
      // corner of Axis0max and Axis1min
         x = fAxisMax[rhoaxis]*cos(fAxisMin[phiaxis]);
         y = fAxisMax[rhoaxis]*sin(fAxisMin[phiaxis]);
         z = 0;
         SetCorner(kCorner0Max1Min, x, y, z);
      // corner of Axis0max and Axis1max
         x = fAxisMax[rhoaxis]*cos(fAxisMax[phiaxis]);
         y = fAxisMax[rhoaxis]*sin(fAxisMax[phiaxis]);
         z = 0;
         SetCorner(kCorner0Max1Max, x, y, z);
      // corner of Axis0min and Axis1max
         x = fAxisMin[rhoaxis]*cos(fAxisMax[phiaxis]);
         y = fAxisMin[rhoaxis]*sin(fAxisMax[phiaxis]);
         z = 0;
         SetCorner(kCorner0Min1Max, x, y, z);
       
   } else {
      G4cerr << "J4FlatSurface::SetCorners fAxis[0] = " << fAxis[0]
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << G4endl;
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
   
      G4ThreeVector direction(0., 0., 0.);
      SetBoundary(kAxis0 & kAxisMin, direction,
                  GetCorner(kCorner0Min1Min), kAxisPhi);
      
      SetBoundary( kAxis0 & kAxisMax, direction,
                  GetCorner(kCorner0Min1Max), kAxisPhi);
      
      direction = GetCorner(kCorner0Max1Min) - GetCorner(kCorner0Min1Min);
      SetBoundary(kAxis1 & kAxisMin, direction.unit(), 
                  GetCorner(kCorner0Min1Min), kAxisRho); 
   
      direction = GetCorner(kCorner0Max1Max) - GetCorner(kCorner0Min1Max);
      SetBoundary(kAxis1 & kAxisMax, direction.unit(), 
                  GetCorner(kCorner0Min1Max), kAxisRho);
                                 
   } else {
      G4cerr << "J4FlatSurface::SetBoundaries fAxis[0] = " << fAxis[0] 
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << G4endl;
      abort();
   }
}

                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           
                                           

