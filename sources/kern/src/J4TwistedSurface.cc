/*
 *  J4TwistedSurface.cc
 *  
 *
 *  Created by Kotoyo Hoshina on Thu Aug 01 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */

#include "J4TwistedSurface.hh"
#include "J4TwistedTubs.hh"

//#define __SOLIDDEBUG__
//#define __SOLIDDEBUGAREACODE__

//=====================================================================
//* constructor -------------------------------------------------------

J4TwistedSurface::J4TwistedSurface(const G4String         &name,
                                   const G4RotationMatrix &rot,
                                   const G4ThreeVector    &tlate,
                                         G4int             handedness,
                                   const G4double          kappa,
                                   const EAxis             axis0,
                                   const EAxis             axis1,
                                         G4double          axis0min,
                                         G4double          axis1min,
                                         G4double          axis0max,
                                         G4double          axis1max)
                 :J4VSurface(name, rot, tlate, handedness, axis0, axis1, axis0min, 
                             axis1min, axis0max, axis1max),
                  fKappa(kappa)
{
   if (axis0 == kZAxis && axis1 == kXAxis) {
       G4cerr << "JTwistedSurface::Constructor: Swap axis0 and axis1. abort. " << G4endl;
       abort();
   }
   SetCorners();
   SetBoundaries();
}

J4TwistedSurface::J4TwistedSurface(const G4String      &name,
                                         J4TwistedTubs *solid, 
                                         G4int          handedness)
                 :J4VSurface(name)
{  
   fHandedness = handedness;   // +z = +ve, -z = -ve
   fAxis[0]    = kXAxis; // in local coordinate system
   fAxis[1]    = kZAxis;
   fAxisMin[0] = solid->GetInnerRadius();  // Inner-hype radius at z=0
   fAxisMax[0] = solid->GetOuterRadius();  // Outer-hype radius at z=0
   fAxisMin[1] = solid->GetEndZ(0);
   fAxisMax[1] = solid->GetEndZ(1);

   fKappa = solid->GetKappa();
   fRot.rotateZ(fHandedness > 0 ? -0.5*(solid->GetDPhi()) : 0.5*(solid->GetDPhi()));
   fTrans.set(0, 0, 0);
   
   SetCorners(solid);
   SetBoundaries();
}


//=====================================================================
//* destructor --------------------------------------------------------
J4TwistedSurface::~J4TwistedSurface()
{
}

//=====================================================================
//* GetNormal ---------------------------------------------------------
G4ThreeVector J4TwistedSurface::GetNormal(const G4ThreeVector &tmpxx, 
                                                G4bool isGlobal) 
{
   // GetNormal returns a normal vector at a surface (or very close
   // to surface) point at tmpxx.
   // If isGlobal=TRUE, it returns the normal in global coordinate.
   //
   G4ThreeVector xx;
   if (isGlobal) {
      xx = fRot.inverse()*tmpxx - fTrans;
   } else {
      xx = tmpxx;
   }
   
   G4ThreeVector er(1, fKappa * xx.z(), 0);
   G4ThreeVector ez(0, fKappa * xx.x(), 1);
   G4ThreeVector normal = fHandedness*(er.cross(ez));

   if (isGlobal) {
      fCurrentNormal = fRot*(normal.unit());
   } else {
      fCurrentNormal = normal.unit();
   }
   return fCurrentNormal;
}

//=====================================================================
//* DistanceToSurface -------------------------------------------------
G4int J4TwistedSurface::DistanceToSurface(const G4ThreeVector &gp,
                                          const G4ThreeVector &gv,
                                                G4ThreeVector  gxx[],
                                                G4double       distance[],
                                                G4int          areacode[],
                                                G4bool         isvalid[],
                                                EValidate      validate)
{
   // Coordinate system:
   //
   //    The coordinate system is so chosen that the intersection of
   //    the twisted surface with the z=0 plane coincides with the
   //    x-axis. 
   //    Rotation matrix from this coordinate system (local system)
   //    to global system is saved in fRot field.
   //    So the (global) particle position and (global) velocity vectors, 
   //    p and v, should be rotated fRot.inverse() in order to convert
   //    to local vectors.
   //
   // Equation of a twisted surface:
   //
   //    x(rho(z=0), z) = rho(z=0)
   //    y(rho(z=0), z) = rho(z=0)*K*z
   //    z(rho(z=0), z) = z
   //    with
   //       K = tan(fPhiTwist/2)/fZHalfLen
   //
   // Equation of a line:
   //
   //    gxx = p + t*v
   //    with
   //       p = fRot.inverse()*gp  
   //       v = fRot.inverse()*gv
   //
   // Solution for intersection:
   //
   //    Required time for crossing is given by solving the
   //    following quadratic equation:
   //
   //       a*t^2 + b*t + c = 0
   //
   //    where
   //
   //       a = K*v_x*v_z
   //       b = K*(v_x*p_z + v_z*p_x) - v_y
   //       c = K*p_x*p_z - p_y
   //
   //    Out of the possible two solutions you must choose
   //    the one that gives a positive rho(z=0).
   //
   //
   
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
   G4ThreeVector xx[2]; 

#ifdef __SOLIDDEBUG__
   G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : "
          << "Start from gp, gv, p, v :" << G4endl;
   G4cerr << "      "
          << GetName() << " , "
          << gp << " , "
          << gv << " , "
          << p << " , "
          << v << " ~~~~~ " << G4endl;
#endif


   // 
   // special case! 
   // p is on z-axis or vt is parallel to pt, or 
   // p is on surface.
   //
   G4double absvz = fabs(v.z());
   if ((absvz < DBL_MIN) && (fabs(p.x() * v.y() - p.y() * v.x()) < DBL_MIN)) {
      isvalid[0] = FALSE;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid[0], 0, validate, &gp, &gv);
#ifdef __SOLIDDEBUG__
      G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
             << G4endl;
      G4cerr << "   p is on z-axis or v(transverse) is parallel to p(transverse)."
             << " return 0." << G4endl; 
      G4cerr << "   NAME     : " << GetName() <<  G4endl;
      G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
             << G4endl;
#endif
      return 0;
   } 
   
   G4ThreeVector xxatp;   // surface point at x = p.x, z = p.z
   xxatp.set(p.x(), p.x() * p.z() * fKappa, p.z());
   G4double diff = (p - xxatp).mag();

#ifdef __SOLIDDEBUG__ 
   G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : diff = "
          << diff << G4endl;
#endif

   if (diff <= 0.5 * kCarTolerance) {
      if (validate == kValidateWithTol) {   
          areacode[0] = GetAreaCode(p);   
          if ((areacode[0] & kAreaMask) != kOutside) {   
             distance[0] = 0;   
             gxx[0] = gp;   
             xx[0] = p;   
             isvalid[0] = TRUE;   
          }     
      } else if (validate == kValidateWithoutTol) {   
          areacode[0] = GetAreaCode(p, FALSE);   
          if ((areacode[0] & kAreaMask) == kInside) {   
             distance[0] = 0;   
             gxx[0] = gp;   
             xx[0] = p;   
             isvalid[0] = TRUE;   
          } 
      } else { // kDontValidate   
          areacode[0] = kInside;   
          distance[0] = 0;   
          gxx[0] = gp;   
          xx[0] = p;   
          isvalid[0] = TRUE;   
      }   

      fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],   
                                     isvalid[0], 1, validate, &gp, &gv);  

#ifdef __SOLIDDEBUG__
      G4cerr <<"~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : last return ~~~~~ " 
             << G4endl;
      G4cerr <<"   P is on surface. return 0. " << G4endl;
      G4cerr <<"   NAME        : " << GetName() << G4endl;
      G4cerr <<"   xx[0]       : " << xx[0] << G4endl;
      G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
      G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
      G4cerr <<"   areacode[0] : " << areacode[0] << G4endl;
      G4cerr <<"   isvalid[0]  : " << isvalid[0]  << G4endl;
      G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
             << G4endl;
#endif

      return 1;   

   }     
   // 
   // special case end
   //
   
   G4double a = fKappa * v.x() * v.z();
   G4double b = fKappa * (v.x() * p.z() + v.z() * p.x()) - v.y();
   G4double c = fKappa * p.x() * p.z() - p.y();
   G4double D = b * b - 4 * a * c;             // discriminant

#ifdef __SOLIDDEBUG__
   G4cerr << "//* J4TwistedSurface::DistanceToSurface: name, p, v, a,b,c,D = ------"
          << G4endl;
   G4cerr << "//*   NAME    " << GetName() << G4endl;
   G4cerr << "//*   p, v    " << p << " , " << v << G4endl;
   G4cerr << "//*   a,b,c,D " << a << " " << b << " " << c << " " << D << G4endl;
   G4cerr << "//*------------------------------------------------------------------"
          << G4endl;
#endif 


   if (fabs(a) < DBL_MIN) {
      if (fabs(b) > DBL_MIN) { 

         // single solution

         distance[0] = - c / b;
         xx[0]       = p + distance[0]*v;
         gxx[0]      = fRot*xx[0] + fTrans;

         if (validate == kValidateWithTol) {
            areacode[0] = GetAreaCode(xx[0]);
            if ((areacode[0] & kAreaMask) != kOutside) {
               if (distance[0] >= 0) isvalid[0] = TRUE;
            }
         } else if (validate == kValidateWithoutTol) {
            areacode[0] = GetAreaCode(xx[0], FALSE);
            if ((areacode[0] & kAreaMask) == kInside) {
               if (distance[0] >= 0) isvalid[0] = TRUE;
            }
         } else { // kDontValidate                       
            // we must omit x(rho,z) = rho(z=0) < 0
            if (xx[0].x() > 0) {
               areacode[0] = kInside;
               if (distance[0] >= 0) isvalid[0] = TRUE;
            } else {
               distance[0] = kInfinity;
               fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                              isvalid[0], 0, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
               G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : last return " 
                      << "~~~~~~ " << G4endl;
               G4cerr << "   xx is out of boundary. return 0. " << G4endl; 
               G4cerr << "   NAME      : " << GetName()  << G4endl;
               G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                      << "~~~~~~ " << G4endl;
#endif

               return 0;

            } 
         }
                 
         fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 1, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
         G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
                << G4endl;
         G4cerr << "   Single solution. " << G4endl;
         G4cerr << "   NAME        : " << GetName() << G4endl;
         G4cerr << "   xx[0]       : " << xx[0] << G4endl;
         G4cerr << "   gxx[0]      : " << gxx[0] << G4endl;
         G4cerr << "   dist[0]     : " << distance[0] << G4endl;
         G4cerr << "   areacode[0] : " << G4std::hex << areacode[0] << G4std::dec << G4endl;
         G4cerr << "   isvalid[0]  : " << isvalid[0]  << G4endl;
         G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
                << G4endl;
#endif

         return 1;
         
      } else {
         // if a=b=0 and c!=0, no solution, parallel to the surface
         // if a=b=c=0, the track is exactly on the surface, return kInfinity
         // if D < 0, no intersection.

         fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 0, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
         G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
                << G4endl;
         G4cerr << "   paralell to the surface or on surface but flying away opposit "
                <<     "direction. return 0. " << G4endl; 
         G4cerr << "   a, b, c  : " <<  a  << " , " << b << " , " << c << G4endl; 
         G4cerr << "   NAME     : " << GetName() << G4endl;
         G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
                << G4endl;
#endif

         return 0;

      }
      
   } else if (D > DBL_MIN) {   

      // double solutions

      D = sqrt(D);
      G4double      factor = 0.5/a;
      G4double      tmpdist[2] = {kInfinity, kInfinity};
      G4ThreeVector tmpxx[2];
      G4int         tmpareacode[2] = {kOutside, kOutside};
      G4bool        tmpisvalid[2]  = {FALSE, FALSE};
      G4int i;

      for (i=0; i<2; i++) {
         tmpdist[i] = factor*(-b - D);
         D = -D;
         tmpxx[i] = p + tmpdist[i]*v;
         
         if (validate == kValidateWithTol) {
            tmpareacode[i] = GetAreaCode(tmpxx[i]);
            if ((tmpareacode[i] & kAreaMask) != kOutside) {
               if (tmpdist[i] >= 0) tmpisvalid[i] = TRUE;
               continue;
            }
         } else if (validate == kValidateWithoutTol) {
            tmpareacode[i] = GetAreaCode(tmpxx[i], FALSE);
            if ((tmpareacode[i] & kAreaMask) == kInside) {
               if (tmpdist[i] >= 0) tmpisvalid[i] = TRUE;
               continue;
            }
         } else { // kDontValidate
            // we must choose x(rho,z) = rho(z=0) > 0
            if (tmpxx[i].x() > 0) {
               tmpareacode[i] = kInside;
               if (tmpdist[i] >= 0) tmpisvalid[i] = TRUE;
               continue;
            } else {
               tmpdist[i] = kInfinity;
               continue;
            }                     
         }
      }

      if (tmpdist[0] <= tmpdist[1]) {
         distance[0] = tmpdist[0];
         distance[1] = tmpdist[1];
         xx[0]       = tmpxx[0];
         xx[1]       = tmpxx[1];
         gxx[0]      = fRot*tmpxx[0] + fTrans;
         gxx[1]      = fRot*tmpxx[1] + fTrans;
         areacode[0] = tmpareacode[0];
         areacode[1] = tmpareacode[1];
         isvalid[0]  = tmpisvalid[0];
         isvalid[1]  = tmpisvalid[1];
      } else {
         distance[0] = tmpdist[1];
         distance[1] = tmpdist[0];
         xx[0]       = tmpxx[1];
         xx[1]       = tmpxx[0];
         gxx[0]      = fRot*tmpxx[1] + fTrans;
         gxx[1]      = fRot*tmpxx[0] + fTrans;
         areacode[0] = tmpareacode[1];
         areacode[1] = tmpareacode[0];
         isvalid[0]  = tmpisvalid[1];
         isvalid[1]  = tmpisvalid[0];
      }
         
      fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                     isvalid[0], 2, validate, &gp, &gv);
      fCurStatWithV.SetCurrentStatus(1, gxx[1], distance[1], areacode[1],
                                     isvalid[1], 2, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
      G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
             << G4endl;
      G4cerr << "   NAME,        : " << GetName() << " , " << i << G4endl;
      G4cerr << "   xx[0,1]      : " << xx[0] << " , " << xx[1] << G4endl;
      G4cerr << "   gxx[0,1]     : " << gxx[0] << " , " << gxx[1] << G4endl;
      G4cerr << "   dist[0,1]    : " << distance[0] << " , " << distance[1] << G4endl;
      G4cerr << "   areacode[0,1]: " << G4std::hex << areacode[0] << " , " << areacode[1] 
                                     << G4std::dec << G4endl;
      G4cerr << "   isvalid[0,1] : " << isvalid[0] << " , " << isvalid[1] << G4endl;
      G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " 
             << G4endl;
#endif

      return 2;
      
   } else {
      // if D<0, no solution
      // if D=0, just grazing the surfaces, return kInfinity

      fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                     isvalid[0], 0, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
      G4cerr << "~~~~~ J4TwistedSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
             << G4endl;
      G4cerr << "   paralell to the surface or on surface but flying away opposit "
             <<     "direction. return 0. " << G4endl; 
      G4cerr << "   NAME     : " << GetName() << G4endl;
      G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
             << G4endl;
#endif

      return 0;

   }
   G4cerr << "J4TwistedSurface::DistanceToSurface(p,v) illigal operation!! abort"
          << G4endl;
   abort(); 
}

//=====================================================================
//* DistanceToSurface -------------------------------------------------
G4int J4TwistedSurface::DistanceToSurface(const G4ThreeVector &gp,
                                                G4ThreeVector  gxx[],
                                                G4double       distance[],
                                                G4int          areacode[])
{  
   fCurStat.ResetfDone(kDontValidate, &gp);

   if (fCurStat.IsDone()) {
      for (G4int i=0; i<fCurStat.GetNXX(); i++) {
         gxx[i] = fCurStat.GetXX(i);
         distance[i] = fCurStat.GetDistance(i);
         areacode[i] = fCurStat.GetAreacode(i);
      }
      return fCurStat.GetNXX();
   } else {
      // initialize
      for (G4int i=0; i<2; i++) {
         distance[i] = kInfinity;
         areacode[i] = kOutside;
         gxx[i].set(kInfinity, kInfinity, kInfinity);
      }
   }
   
   static const G4double halftol = 0.5 * kCarTolerance; 

   G4ThreeVector  p       = fRot.inverse()*gp - fTrans;
   G4ThreeVector  xx;
   G4int          parity  = (fKappa >= 0 ? 1 : -1);

#ifdef __SOLIDDEBUG__
   G4cerr <<"~~~~~ J4TwistedSurface:DistanceToSurface(p) : Start from gp, p : "
          << GetName() << " , "
          << gp << " , "
          << p << " ~~~~~ " << G4endl;
#endif
 
   // 
   // special case! if p is on z-axis, 
   // the track cannot cross with surface.
   // or if p is on surface, return distance = 0 immediatery .
   //
   
   G4ThreeVector  lastgxx[2];
   G4double       distfromlast[2];
   for (G4int i=0; i<2; i++) {
      lastgxx[i] = fCurStatWithV.GetXX(i);
      distfromlast[i] = (gp - lastgxx[i]).mag();
#ifdef __SOLIDDEBUG__
      G4cerr <<"//* J4TwistedSurface:DistanceToSurface(p) : lastgxx, distance from last = "
             << lastgxx[i] << " , " 
             << distfromlast[i] << G4endl;
#endif
   } 

   if ((gp - lastgxx[0]).mag() <= halftol || (gp - lastgxx[1]).mag() <= halftol) { 
      // last winner, or last poststep point is on the surface. 
      areacode[0] = kInside;
      distance[0] = 0;
      gxx[0] = gp;
      xx = p;
      G4bool isvalid = TRUE;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                             isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
      G4cerr <<"~~~~~ J4TwistedSurface:DistanceToSurface(p) : last return ~~~~~~~~ " << G4endl;
      G4cerr <<"   I'm a last winner ! or last poststep point is on my surface. " << G4endl;
      G4cerr <<"   NAME        : " << GetName() << G4endl;
      G4cerr <<"   xx          : " << xx << G4endl;
      G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
      G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
      G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << G4endl;
#endif

      return 1;

   }

   if (p.getRho() == 0) { 

      G4bool isvalid = FALSE;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid, 0, kDontValidate, &gp);

      return 0;

   } 

   // 
   // special case end
   //


   // set corner points of quadrangle try area ...

   G4ThreeVector A;       // foot of normal from p to boundary of kAxis0 & kAxisMin
   G4ThreeVector C;       // foot of normal from p to boundary of kAxis0 & kAxisMax
   G4ThreeVector B;       // point on boundary kAxis0 & kAxisMax at z = A.z()
   G4ThreeVector D;       // point on boundary kAxis0 & kAxisMin at z = C.z()
   G4double      distToA; // distance from p to A
   G4double      distToC; // distance from p to C 

   distToA = DistanceToBoundary(kAxis0 & kAxisMin, A, p);
   distToC = DistanceToBoundary(kAxis0 & kAxisMax, C, p);

   G4ThreeVector  d[2];    // direction vectors of boundary
   G4ThreeVector  x0[2];   // foot of normal from line to p 
   G4int          boundarytype[2];

   for (G4int i=0; i<2; i++) {
      if (i == 0) {
         GetBoundaryParameters((kAxis0 & kAxisMax), d[i], x0[i], boundarytype[i]);
         B = x0[i] + ((A.z() - x0[i].z()) / d[i].z()) * d[i]; // x0 + t*d , d is direction unit vector.
      } else {
         GetBoundaryParameters((kAxis0 & kAxisMin), d[i], x0[i], boundarytype[i]);
         D = x0[i] + ((C.z() - x0[i].z()) / d[i].z()) * d[i]; 
      }
   }

   // In order to set correct diagonal, swap A and D, C and B if needed.  
   G4ThreeVector pt(p.x(), p.y(), 0.); 
   G4ThreeVector At(A.x(), A.y(), 0.); 
   G4int         pside = AmIOnLeftSide(pt, At); 
   G4double      test  = (A.z() - C.z()) * parity * pside;  

   if (test == 0) {
      if (pside == 0) {
         // p is on surface.
         areacode[0] = kInside;
         distance[0] = 0;
         gxx[0] = gp;
         G4ThreeVector xx(p);
         G4bool isvalid = TRUE;
         fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
         G4cerr <<"~~~~~ J4TwistedSurface:DistanceToSurface(p) : last return ~~~~~~~~ " << G4endl;
         G4cerr <<"   I'm a last winner ! or last poststep point is on my surface. " << G4endl;
         G4cerr <<"   NAME        : " << GetName() << G4endl;
         G4cerr <<"   xx          : " << xx << G4endl;
         G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
         G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
         G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << G4endl;
#endif
         return 1;
      } else {
         // A.z = C.z(). return distance to line.
         d[0] = C - A;
         d[0] = d[0].unit();
         G4double t  = - d[0] * (A - p);
         xx = A + t * d[0];
         distance[0] = (xx - p).mag();

         areacode[0] = kInside;
         gxx[0] = fRot * xx + fTrans;
         G4bool isvalid = TRUE;
         fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
         G4cerr <<"~~~~~ J4TwistedSurface:DistanceToSurface(p) : last return ~~~~~~~~ " << G4endl;
         G4cerr <<"   NAME        : " << GetName() << G4endl;
         G4cerr <<"   xx          : " << xx << G4endl;
         G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
         G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
         G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << G4endl;
#endif
         return 1;
      } 

   } else if (test < 0) {

      // wrong diagonal. vector AC is crossing the surface!  
      // swap A and D, C and B
      G4ThreeVector tmp;
      tmp = A;
      A = D;
      D = tmp;
      tmp = C;
      C = B;
      B = tmp; 

   } else {
      // correct diagonal. nothing to do.  
   }


   // Now, we chose correct diaglnal.
   // First try. divide quadrangle into double triangle by diagonal and 
   // calculate distance to both surfaces.

   G4ThreeVector xxacb;   // foot of normal from plane ACB to p
   G4ThreeVector nacb;    // normal of plane ACD
   G4ThreeVector xxcad;   // foot of normal from plane CAD to p
   G4ThreeVector ncad;    // normal of plane CAD
   G4ThreeVector AB(A.x(), A.y(), 0);
   G4ThreeVector DC(C.x(), C.y(), 0);

   G4double distToACB = J4VSurface::DistanceToPlane(p, A, C-A, AB, xxacb, nacb) * parity;
   G4double distToCAD = J4VSurface::DistanceToPlane(p, C, C-A, DC, xxcad, ncad) * parity;

   // if calculated distance = 0, return  

   if (fabs(distToACB) <= halftol || fabs(distToCAD) <= halftol) {
      xx = (fabs(distToACB) < fabs(distToCAD) ? xxacb : xxcad); 
      areacode[0] = kInside;
      gxx[0] = fRot * xx + fTrans;
      distance[0] = 0;
      G4bool isvalid = TRUE;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0] , areacode[0],
                                isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
      G4cerr <<"~~~~~ J4TwistedSurface:DistanceToSurface(p) : last return ~~~~~~~~ " << G4endl;
      G4cerr <<"   NAME        : " << GetName() << G4endl;
      G4cerr <<"   xx          : " << xx << G4endl;
      G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
      G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
      G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << G4endl;
#endif

      return 1;

   }

#ifdef __SOLIDDEBUG__
   G4cerr << "//* J4TwistedSurface::DistanceToSurface(p):---------------------------------" << G4endl;
   G4cerr << "//*   NAME          : " << GetName() << G4endl;
   G4cerr << "//*   p             : " << p << G4endl; 
   G4cerr << "//*   A, C, parity  : " << A << " , " << C << " , " << parity << G4endl;
   G4cerr << "//*   nacb, ncad    : " << nacb << " , " << ncad << G4endl;
   G4cerr << "//*   xxacb, xxcad  : " << xxacb << " , " << xxcad << G4endl;
   G4cerr << "//*   distToACB, distToCAD  : " << distToACB << " , " << distToCAD << G4endl; 
   G4cerr << "//*-------------------------------------------------------------------------" << G4endl;
#endif
#ifdef __SOLIDDEBUG__
   G4cerr << "//* J4TwistedSurface::DistanceToSurface(p):---------------------------------" << G4endl;
   G4cerr << "//*   nacb * (p - xxacb) : " <<  nacb * (p -xxacb)  << G4endl;
   G4cerr << "//*   ncad * (p - xxcad) : " <<  ncad * (p -xxcad)  << G4endl;
   G4cerr << "//*-------------------------------------------------------------------------" << G4endl;
#endif

   if (distance[0] < 0 || distance[1] < 0)
   {
      G4ThreeVector normal;
      distance[0] = DistanceToPlane(p, A, B, C, D, parity, xx, normal);

   } else if ( distance[0] * distance[1] < 0) {

      if (distToACB > 0) {
         distance[0] = distToACB;
         xx   = xxacb;
      } else {
         distance[0] = distToCAD;
         xx   = xxcad;
      }

   } else {

      if (distToACB <= distToCAD) {
         distance[0] = distToACB;
         xx   = xxacb;
      } else {
         distance[0] = distToCAD;
         xx   = xxcad;
      }

   }

   areacode[0] = kInside;
   gxx[0]      = fRot * xx + fTrans;
   G4bool isvalid = TRUE;
   fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                             isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
      G4cerr <<"~~~~~ J4TwistedSurface:DistanceToSurface(p) : last return ~~~~~~~~ " << G4endl;
      G4cerr <<"   NAME        : " << GetName() << G4endl;
      G4cerr <<"   xx          : " << xx << G4endl;
      G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
      G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
      G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << G4endl;
#endif
   return 1;
   
}

//=====================================================================
//* DistanceToPlane -------------------------------------------------
G4double J4TwistedSurface::DistanceToPlane(const G4ThreeVector &p,
                                           const G4ThreeVector &A,
                                           const G4ThreeVector &B,
                                           const G4ThreeVector &C,
                                           const G4ThreeVector &D,
                                           const G4int          parity,
                                                 G4ThreeVector &xx,
                                                 G4ThreeVector &n)
{
   G4ThreeVector M = 0.5*(A + B);
   G4ThreeVector N = 0.5*(C + D);
   G4ThreeVector xxanm;  // foot of normal from p to plane ANM
   G4ThreeVector nanm;   // normal of plane ANM
   G4ThreeVector xxcmn;  // foot of normal from p to plane CMN
   G4ThreeVector ncmn;   // normal of plane CMN

   G4double distToanm = J4VSurface::DistanceToPlane(p, A, (N - A), (M - A), xxanm, nanm) * parity;
   G4double distTocmn = J4VSurface::DistanceToPlane(p, C, (M - C), (N - C), xxcmn, ncmn) * parity;

   if (distToanm <= distTocmn) {
      if (distToanm >= 0) {
         xx = xxanm;
         n  = nanm * parity;
         return distToanm;
      } else {
         return DistanceToPlane(p, A, M, N, D, parity, xx, n);
      }
   } else {
      if (distTocmn >= 0) {
         xx = xxcmn;
         n  = ncmn * parity;
         return distTocmn;
      } else {
         return DistanceToPlane(p, C, N, M, B, parity, xx, n);
      }
   }
}

//=====================================================================
//* GetAreaCode -------------------------------------------------------
G4int J4TwistedSurface::GetAreaCode(const G4ThreeVector &xx, 
                                          G4bool withTol) const
{
   // We must use the function in local coordinate system.
   // See the description of DistanceToSurface(p,v).
   
   static const G4double ctol = 0.5 * kCarTolerance;
   G4int areacode = 0;
   
   if (fAxis[0] == kXAxis && fAxis[1] == kZAxis) {
      G4int xaxis = 0;
      G4int zaxis = 1;

#ifdef __SOLIDDEBUGAREACODE__
      G4cerr << "//# J4TwistedSurface::GetAreaCode: ----------------------------" << G4endl;
      G4cerr << "//#    fAxisMin,Max(xaxis)  : " << fAxisMin[xaxis] << " , " << fAxisMax[xaxis] << G4endl;
      G4cerr << "//#    fAxisMin,Max(zaxis)  : " << fAxisMin[zaxis] << " , " << fAxisMax[zaxis] << G4endl;
      G4cerr << "//# -----------------------------------------------------------" << G4endl;
#endif
      
      if (withTol) {
         
         // inside or outside
         if (xx.x() >= fAxisMin[xaxis] + ctol 
             && xx.x() <= fAxisMax[xaxis] - ctol 
             && xx.z() >= fAxisMin[zaxis] + ctol 
             && xx.z() <= fAxisMax[zaxis] - ctol) {
            areacode |= (kAxis0 & kAxisX) | (kAxis1 & kAxisZ) | kInside;
            return areacode;
         } else if (xx.x() <= fAxisMin[xaxis] - ctol 
                    || xx.x() >= fAxisMax[xaxis] + ctol
                    || xx.z() <= fAxisMin[zaxis] - ctol 
                    || xx.z() >= fAxisMax[zaxis] + ctol) {
            areacode |= (kAxis0 & kAxisX) | (kAxis1 & kAxisZ) | kOutside;
            return areacode;
         }
         
         // Now, xx is out of boundary. Which boundary?
         // boundary of x-axis
         if (xx.x() < fAxisMin[xaxis] + ctol) {
            areacode |= (kAxis0 & (kAxisX | kAxisMin)) | kBoundary; 
         } else if (xx.x() > fAxisMax[xaxis] - ctol) {
            areacode |= (kAxis0 & (kAxisX | kAxisMax)) | kBoundary;
         }
         
         // boundary of z-axis
         if (xx.z() < fAxisMin[zaxis] + ctol) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMin)); 
            if (areacode & kBoundary) {
                areacode |= kCorner;  // xx is on the corner.
            } else {
                areacode |= kBoundary;
            } 
         } else if (xx.z() > fAxisMax[zaxis] - ctol) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMax));
            if (areacode & kBoundary) {
                areacode |= kCorner;  // xx is on the corner.
            } else {
                areacode |= kBoundary; 
            }
         }
         return areacode;
         
      } else {
      
         // inside
         if (xx.x() >= fAxisMin[xaxis]
             && xx.x() <= fAxisMax[xaxis]
             && xx.z() >= fAxisMin[zaxis] 
             && xx.z() <= fAxisMax[zaxis]) {
            areacode |= (kAxis0 & kAxisX) | (kAxis1 & kAxisZ) | kInside;
            return areacode;
         }
         
         // Now, xx is out of boundary. Which boundary?
         // boundary of x-axis
         if (xx.x() < fAxisMin[xaxis] ) {
            areacode |= (kAxis0 & (kAxisX | kAxisMin)) | kBoundary;
         } else if (xx.x() > fAxisMax[xaxis]) {
            areacode |= (kAxis0 & (kAxisX | kAxisMax)) | kBoundary;
         }
         
         // boundary of z-axis
         if (xx.z() < fAxisMin[zaxis]) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMin));
            if (areacode & kBoundary) {
                areacode |= kCorner;  // xx is on the corner.
            } else {
                areacode |= kBoundary; 
            }
         } else if (xx.z() > fAxisMax[zaxis]) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMax)) ;
            if (areacode & kBoundary) {
                areacode |= kCorner;  // xx is on the corner.
            } else {
                areacode |= kBoundary; 
            }
         }
         return areacode;
      }
   } else {

      G4cerr << "J4FlatSurface::GetAreaCode fAxis[0] = " << fAxis[0]
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << G4endl;
      abort();
   }   
}

//=====================================================================
//* SetCorners(solid) -------------------------------------------------
void J4TwistedSurface::SetCorners(J4TwistedTubs *solid)
{
   // Set Corner points in local coodinate.   

   if (fAxis[0] == kXAxis && fAxis[1] == kZAxis) {
   
      G4int i;
      G4double endPhi[2];
      G4double endInnerRad[2];
      G4double endOuterRad[2];
      G4double endZ[2];
      for (i=0; i<2; i++) { // i=0,1 : -ve z, +ve z
         endPhi[i]      = solid->GetEndPhi(i);
         endInnerRad[i] = solid->GetEndInnerRadius(i);
         endOuterRad[i] = solid->GetEndOuterRadius(i);
         endZ[i]        = solid->GetEndZ(i);
      }
      
      G4int zmin = 0 ;  // at -ve z
      G4int zmax = 1 ;  // at +ve z

      G4double x, y, z;
      
      // corner of Axis0min and Axis1min
      x = endInnerRad[zmin]*cos(endPhi[zmin]);
      y = endInnerRad[zmin]*sin(endPhi[zmin]);
      z = endZ[zmin];
      SetCorner(kCorner0Min1Min, x, y, z);
      
      // corner of Axis0max and Axis1min
      x = endOuterRad[zmin]*cos(endPhi[zmin]);
      y = endOuterRad[zmin]*sin(endPhi[zmin]);
      z = endZ[zmin];
      SetCorner(kCorner0Max1Min, x, y, z);
      
      // corner of Axis0max and Axis1max
      x = endOuterRad[zmax]*cos(endPhi[zmax]);
      y = endOuterRad[zmax]*sin(endPhi[zmax]);
      z = endZ[zmax];
      SetCorner(kCorner0Max1Max, x, y, z);
      
      // corner of Axis0min and Axis1max
      x = endInnerRad[zmax]*cos(endPhi[zmax]);
      y = endInnerRad[zmax]*sin(endPhi[zmax]);
      z = endZ[zmax];
      SetCorner(kCorner0Min1Max, x, y, z);

   } else {
      G4cerr << "J4FlatSurface::SetCorners fAxis[0] = " << fAxis[0]
      << " fAxis[1] = " << fAxis[1]
      << " is yet implemented. Write the code yourself." << G4endl;
      abort();
   }
}

//=====================================================================
//* SetCorners() ------------------------------------------------------
void J4TwistedSurface::SetCorners()
{
   G4cerr << "J4FlatSurface::SetCorners" 
   << " is yet implemented. Write the code yourself." << G4endl;
   abort();
}

//=====================================================================
//* SetBoundaries() ------------------------------------------------------
void J4TwistedSurface::SetBoundaries()
{
   // Set direction-unit vector of boundary-lines in local coodinate. 
   //   
   G4ThreeVector direction;
   
   if (fAxis[0] == kXAxis && fAxis[1] == kZAxis) {
      
      // kAxis0 & kAxisMin
      direction = GetCorner(kCorner0Min1Max) - GetCorner(kCorner0Min1Min);
      direction = direction.unit();
      SetBoundary(kAxis0 & (kAxisX | kAxisMin), direction, 
                  GetCorner(kCorner0Min1Min), kAxisZ) ;
      
      // kAxis0 & kAxisMax
      direction = GetCorner(kCorner0Max1Max) - GetCorner(kCorner0Max1Min);
      direction = direction.unit();
      SetBoundary(kAxis0 & (kAxisX | kAxisMax), direction, 
                  GetCorner(kCorner0Max1Min), kAxisZ);
                  
      // kAxis1 & kAxisMin
      direction = GetCorner(kCorner0Max1Min) - GetCorner(kCorner0Min1Min);
      direction = direction.unit();
      SetBoundary(kAxis1 & (kAxisZ | kAxisMin), direction, 
                  GetCorner(kCorner0Min1Min), kAxisX);
                  
      // kAxis1 & kAxisMax
      direction = GetCorner(kCorner0Max1Max) - GetCorner(kCorner0Min1Max);
      direction = direction.unit();
      SetBoundary(kAxis1 & (kAxisZ | kAxisMax), direction, 
                  GetCorner(kCorner0Min1Max), kAxisX);
                  
   } else {
      G4cerr << "J4FlatSurface::SetBoundaries fAxis[0] = " << fAxis[0]
      << " fAxis[1] = " << fAxis[1]
      << " is yet implemented. Write the code yourself." << G4endl;
      abort();
   }
}

