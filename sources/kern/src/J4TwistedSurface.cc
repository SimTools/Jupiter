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
       J4cerr << "JTwistedSurface::Constructor: Swap axis0 and axis1. abort. " << J4endl;
       abort();
   }
   fIsValidNorm = FALSE;
   SetCorners();
   SetBoundaries();
}

J4TwistedSurface::J4TwistedSurface(const G4String      &name,
                                         J4TwistedTubs *solid, 
                                         G4int          handedness)
                 :J4VSurface(name, solid)
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
   fIsValidNorm = FALSE;
   
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
      xx = ComputeLocalPoint(tmpxx);
      if ((xx - fCurrentNormal.p).mag() < 0.5 * kCarTolerance) {
         return ComputeGlobalDirection(fCurrentNormal.normal);
      }
   } else {
      xx = tmpxx;
      if (xx == fCurrentNormal.p) {
         return fCurrentNormal.normal;
      }
   }
   
   G4ThreeVector er(1, fKappa * xx.z(), 0);
   G4ThreeVector ez(0, fKappa * xx.x(), 1);
   G4ThreeVector normal = fHandedness*(er.cross(ez));

   if (isGlobal) {
      fCurrentNormal.normal = ComputeGlobalDirection(normal.unit());
   } else {
      fCurrentNormal.normal = normal.unit();
   }
   return fCurrentNormal.normal;
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

   G4ThreeVector p = ComputeLocalPoint(gp);
   G4ThreeVector v = ComputeLocalDirection(gv);
   G4ThreeVector xx[2]; 

#ifdef __SOLIDDEBUG__
   J4cerr << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v):Start"
          << J4endl;
   J4cerr << "         Name : " << GetName() << J4endl;
   J4cerr << "         gp   : " << gp << J4endl;
   J4cerr << "         gv   : " << gv << J4endl;
   J4cerr << "         p    : " << p << J4endl;
   J4cerr << "         v    : " << v << J4endl;
   J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
          << J4endl;
#endif


   // 
   // special case! 
   // p is origin or
   //

   G4double absvz = fabs(v.z());

   if ((absvz < DBL_MIN) && (fabs(p.x() * v.y() - p.y() * v.x()) < DBL_MIN)) {
      // no intersection

      isvalid[0] = FALSE;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid[0], 0, validate, &gp, &gv);
#ifdef __SOLIDDEBUG__
      J4cerr << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v):return"
             << J4endl;
      J4cerr << "         p is on z-axis and v(transverse) is parallel to "
             <<           "p(transverse). return 0." << J4endl; 
      J4cerr << "         NAME     : " << GetName() <<  J4endl;
      J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
#endif
      return 0;
   } 
   
   // 
   // special case end
   //

   
   G4double a = fKappa * v.x() * v.z();
   G4double b = fKappa * (v.x() * p.z() + v.z() * p.x()) - v.y();
   G4double c = fKappa * p.x() * p.z() - p.y();
   G4double D = b * b - 4 * a * c;             // discriminant

#ifdef __SOLIDDEBUG__
   J4cerr << "      ~~~ J4TwistedSurface::DistanceToSurface: a,b,c,D = "
          << J4endl;
   J4cerr << "      //*   NAME    " << GetName() << J4endl;
   J4cerr << "      //*   p, v    " << p << " , " << v << J4endl;
   J4cerr << "      //*   a,b,c,D " << a << " " << b << " " 
                                    << c << " " << D << J4endl;
   J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
          << J4endl;
#endif 

   if (fabs(a) < DBL_MIN) {
      if (fabs(b) > DBL_MIN) { 

         // single solution

         distance[0] = - c / b;
         xx[0]       = p + distance[0]*v;
         gxx[0]      = ComputeGlobalPoint(xx[0]);

         if (validate == kValidateWithTol) {
            areacode[0] = GetAreaCode(xx[0]);
            if (!IsOutside(areacode[0])) {
               if (distance[0] >= 0) isvalid[0] = TRUE;
            }
         } else if (validate == kValidateWithoutTol) {
            areacode[0] = GetAreaCode(xx[0], FALSE);
            if (IsInside(areacode[0])) {
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
               J4cerr 
               << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v):return" 
               << J4endl;
               J4cerr 
               << "         xx is out of boundary. return 0. " << J4endl; 
               J4cerr 
               << "         NAME      : " << GetName()  << J4endl;
               J4cerr 
               << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                      << J4endl;
#endif

               return 0;

            } 
         }
                 
         fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 1, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
         J4cerr 
         << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v):return" 
                << J4endl;
         J4cerr << "         Single solution. " << J4endl;
         J4cerr << "         NAME        : " << GetName() << J4endl;
         J4cerr << "         xx[0]       : " << xx[0] << J4endl;
         J4cerr << "         gxx[0]      : " << gxx[0] << J4endl;
         J4cerr << "         dist[0]     : " << distance[0] << J4endl;
         J4cerr << "         areacode[0] : " << hex << areacode[0] 
                << J4endl;
         J4cerr << "         isvalid[0]  : " << dec << isvalid[0] 
                << J4endl;
         J4cerr 
         << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
                << J4endl;
         if (isvalid[0] && GetSolid()->Inside(gxx[0]) != ::kSurface) {
            J4cerr << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v)" << J4endl;
            J4cerr << "      valid return value is not on surface! abort." << J4endl; 
            abort();
         } 
#endif

         return 1;
         
      } else {
         // if a=b=0 , v.y=0 and (v.x=0 && p.x=0) or (v.z=0 && p.z=0) .
         //    if v.x=0 && p.x=0, no intersection unless p is on z-axis
         //    (in that case, v is paralell to surface). 
         //    if v.z=0 && p.z=0, no intersection unless p is on x-axis
         //    (in that case, v is paralell to surface). 
         // return distance = infinity.

         fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 0, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
         J4cerr 
         << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v):return"
                << J4endl;
         J4cerr << "         paralell to the surface or on surface but"
                <<           " flying away opposit direction. return 0" 
                << J4endl; 
         J4cerr << "         a, b, c  : " <<  a  << " , " << b << " , " 
                                          << c << J4endl; 
         J4cerr << "         NAME     : " << GetName() << J4endl;
         J4cerr 
         << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                << J4endl;
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
         G4double bminusD = - b - D;

         // protection against round off error  
         //G4double protection = 1.0e-6;
         G4double protection = 0;
         if ( b * D < 0 && fabs(bminusD / D) < protection ) {
            G4double acovbb = (a*c)/(b*b);
            tmpdist[i] = - c/b * ( 1 - acovbb * (1 + 2*acovbb));
         } else { 
            tmpdist[i] = factor * bminusD;
         }

         D = -D;
         tmpxx[i] = p + tmpdist[i]*v;
         
         if (validate == kValidateWithTol) {
            tmpareacode[i] = GetAreaCode(tmpxx[i]);
            if (!IsOutside(tmpareacode[i])) {
               if (tmpdist[i] >= 0) tmpisvalid[i] = TRUE;
               continue;
            }
         } else if (validate == kValidateWithoutTol) {
            tmpareacode[i] = GetAreaCode(tmpxx[i], FALSE);
            if (IsInside(tmpareacode[i])) {
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
         gxx[0]      = ComputeGlobalPoint(tmpxx[0]);
         gxx[1]      = ComputeGlobalPoint(tmpxx[1]);
         areacode[0] = tmpareacode[0];
         areacode[1] = tmpareacode[1];
         isvalid[0]  = tmpisvalid[0];
         isvalid[1]  = tmpisvalid[1];
      } else {
         distance[0] = tmpdist[1];
         distance[1] = tmpdist[0];
         xx[0]       = tmpxx[1];
         xx[1]       = tmpxx[0];
         gxx[0]      = ComputeGlobalPoint(tmpxx[1]);
         gxx[1]      = ComputeGlobalPoint(tmpxx[0]);
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
      J4cerr << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v):return"
             << J4endl;
      J4cerr << "         NAME,        : " << GetName() << " , " << i 
             << J4endl;
      J4cerr << "         xx[0,1]      : " << xx[0] << " , " << xx[1] 
             << J4endl;
      J4cerr << "         gxx[0,1]     : " << gxx[0] << " , " << gxx[1] 
             << J4endl;
      J4cerr << "         dist[0,1]    : " << distance[0] << " , " 
                                           << distance[1] << J4endl;
      J4cerr << "         areacode[0,1]: " << hex << areacode[0] << " , " 
                                           << areacode[1] << dec << J4endl;
      J4cerr << "         isvalid[0,1] : " << isvalid[0] << " , " 
                                           << isvalid[1] << J4endl;
      J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
#endif

      // protection against roundoff error

      for (G4int k=0; k<2; k++) {
         if (!isvalid[k]) continue;
         if (GetSolid()->Inside(gxx[k]) != ::kSurface) {

            G4ThreeVector xxonsurface(xx[k].x(), fKappa * fabs(xx[k].x()) * xx[k].z() , xx[k].z());
            G4double      deltaY  =  (xx[k] - xxonsurface).mag();

#ifdef __SOLIDDEBUG__
            J4cerr << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v)" << J4endl;
            J4cerr << "      valid return value is not on surface! abort. k=" << k << J4endl; 
            J4cerr << " xxonsurface: " << xxonsurface << J4endl; 
            J4cerr << " deltaY     : " << deltaY << J4endl; 
#endif

            G4int maxcount = 10;
            G4int l;
            G4double      lastdeltaY = deltaY; 
            G4ThreeVector last = deltaY; 
            for (l=0; l<maxcount; l++) {
               G4ThreeVector surfacenormal = GetNormal(xxonsurface); 
               distance[k] = DistanceToPlaneWithV(p, v, xxonsurface, surfacenormal, xx[k]);
               deltaY      = (xx[k] - xxonsurface).mag();
               if (deltaY > lastdeltaY) {
               
               }
               gxx[k]      = ComputeGlobalPoint(xx[k]);
               J4cerr << " loop count, deltaY, xxonsurface, xx : " << l << " " << deltaY << " " 
                      << xxonsurface << " " << xx[k] << J4endl; 
#if 0
               if (GetSolid()->Inside(gxx[k])) {
#else
               if (deltaY <= 0.5*kCarTolerance) {
#endif
                  J4cerr << " gxx & distance replaced : gxx, distance " << gxx[k] << " " << distance[k] << J4endl; 
                  break;
               }
               xxonsurface.set(xx[k].x(), fKappa * fabs(xx[k].x()) * xx[k].z() , xx[k].z());
            }
            if (l == maxcount) {
               G4cerr << "J4TwistedSurface:DistanceToSurface(p,v): iteration exceeded maxloop count " 
                      << maxcount << ". abort." << G4endl;
               abort(); 
            }
         } 
      } 

      return 2;
      
   } else {
      // if D<0, no solution
      // if D=0, just grazing the surfaces, return kInfinity

      fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                     isvalid[0], 0, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
      J4cerr << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p,v):return"
             << J4endl;
      J4cerr << "         no solution or just grazing the surface. "
             <<           "return 0. " << J4endl; 
      J4cerr << "         NAME     : " << GetName() << J4endl;
      J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
#endif

      return 0;

   }
   J4cerr << "      J4TwistedSurface::DistanceToSurface(p,v) "
          << "illigal operation!! abort"
          << J4endl;
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

   G4ThreeVector  p       = ComputeLocalPoint(gp);
   G4ThreeVector  xx;
   G4int          parity  = (fKappa >= 0 ? 1 : -1);

#ifdef __SOLIDDEBUG__
   J4cerr << "      ~~~~~ J4TwistedSurface:DistanceToSurface(p):Start"
          << J4endl;
   J4cerr << "         Name : " << GetName() << J4endl;
   J4cerr << "         gp   : " << gp << J4endl;
   J4cerr << "         p    : " << p << J4endl;
   J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
          << J4endl;
#endif
 
   // 
   // special case! 
   // If p is on surface, or
   // p is on z-axis, 
   // return here immediatery.
   //
   
   G4ThreeVector  lastgxx[2];
   G4double       distfromlast[2];
   for (G4int i=0; i<2; i++) {
      lastgxx[i] = fCurStatWithV.GetXX(i);
      distfromlast[i] = (gp - lastgxx[i]).mag();
   } 

   if ((gp - lastgxx[0]).mag() < halftol || (gp - lastgxx[1]).mag() < halftol) { 
      // last winner, or last poststep point is on the surface.
      xx = p;
      distance[0] = 0;
      gxx[0] = gp;

#ifdef __BOUNDARYCHECK__     
      areacode[0] = GetAreaCode(xx, FALSE);
      if (IsInside(areacode[0])) {
         distance[0] = 0;
         gxx[0] = gp;
      } else {
         // xx is out of boundary or corner
         if (IsCorner(areacode[0])) {
            xx = GetCorner(areacode[0]);
            distance[0] = (xx - p).mag();
         } else {
            distance[0] = DistanceToBoundary(areacode[0], xx, p);
         }
         gxx[0] = ComputeGlobalPoint(xx);
      }
#endif

      G4bool isvalid = TRUE;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                             isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
      J4cerr <<"      ~~~~~ J4TwistedSurface:DistanceToSurface(p):return" 
             << J4endl;
      J4cerr <<"         I'm a last winner !" << J4endl;
      J4cerr <<"         Otherwise last poststep point is on my surface."
             << J4endl;
      J4cerr <<"         NAME        : " << GetName() << J4endl;
      J4cerr <<"         xx          : " << xx << J4endl;
      J4cerr <<"         gxx[0]      : " << gxx[0] << J4endl;
      J4cerr <<"         dist[0]     : " << distance[0] << J4endl;
      J4cerr <<"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
#endif

      return 1;

   }
          
   if (p.getRho() == 0) { 
      // p is on z-axis. Namely, p is on twisted surface (invalid area).
      // We must return here, however, returning distance to x-minimum
      // boundary is better than return 0-distance.
      //
      G4bool isvalid = TRUE;
      if (fAxis[0] == kXAxis && fAxis[1] == kZAxis) {
         distance[0] = DistanceToBoundary(kAxis0 & kAxisMin, xx, p);
         areacode[0] = kInside;
      } else {
         distance[0] = 0;
         xx.set(0., 0., 0.);
      }
      gxx[0] = ComputeGlobalPoint(xx);
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid, 0, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
      J4cerr <<"      ~~~~~ J4TwistedSurface:DistanceToSurface(p):return"
             << J4endl;
      J4cerr <<"         p is on z-axis. return x-axis-min or 0 " 
             << J4endl;
      J4cerr <<"         NAME        : " << GetName() << J4endl;
      J4cerr <<"         dist[0]     : " << distance[0] << J4endl;
      J4cerr <<"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
#endif
      return 1;
      
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
   
   // is p.z between a.z and c.z?
   // p.z must be bracketed a.z and c.z.
   if (A.z() > C.z()) {
      if (p.z() > A.z()) {
         A = GetBoundaryAtPZ(kAxis0 & kAxisMin, p);
      } else if (p.z() < C.z()) {
         C = GetBoundaryAtPZ(kAxis0 & kAxisMax, p);
      }
   } else {
      if (p.z() > C.z()) {
         C = GetBoundaryAtPZ(kAxis0 & kAxisMax, p);
      } else if (p.z() < A.z()) {
         A = GetBoundaryAtPZ(kAxis0 & kAxisMin, p);
      }
   }
   

   G4ThreeVector  d[2];     // direction vectors of boundary
   G4ThreeVector  x0[2];    // foot of normal from line to p 
   G4int          btype[2]; // boundary type

   for (G4int i=0; i<2; i++) {
      if (i == 0) {
         GetBoundaryParameters((kAxis0 & kAxisMax), d[i], x0[i], btype[i]);
         B = x0[i] + ((A.z() - x0[i].z()) / d[i].z()) * d[i]; 
         // x0 + t*d , d is direction unit vector.
      } else {
         GetBoundaryParameters((kAxis0 & kAxisMin), d[i], x0[i], btype[i]);
         D = x0[i] + ((C.z() - x0[i].z()) / d[i].z()) * d[i]; 
      }
   }

   // In order to set correct diagonal, swap A and D, C and B if needed.  
   G4ThreeVector pt(p.x(), p.y(), 0.);
   G4double      rc = fabs(p.x());
   G4ThreeVector surfacevector(rc, rc * fKappa * p.z(), 0.); 
   G4int         pside = AmIOnLeftSide(pt, surfacevector); 
   G4double      test  = (A.z() - C.z()) * parity * pside;  

   if (test == 0) {
      if (pside == 0) {
         // p is on surface.
         xx = p;
         distance[0] = 0;
         gxx[0] = gp;

#ifdef __BOUNDARYCHECK__     
         areacode[0] = GetAreaCode(xx, FALSE);
         if (IsInside(areacode[0])) {
            distance[0] = 0;
            gxx[0] = gp;
         } else {
            // xx is out of boundary or corner
            if (IsCorner(areacode[0])) {
               xx = GetCorner(areacode[0]);
               distance[0] = (xx - p).mag();
            } else {
               distance[0] = DistanceToBoundary(areacode[0], xx, p);
            }
            gxx[0] = ComputeGlobalPoint(xx);
         }
#endif

         G4bool isvalid = TRUE;
         fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
         J4cerr <<"      ~~~~~ J4TwistedSurface:DistanceToSurface(p):return"
                << J4endl;
         J4cerr <<"         I'm a last winner !" << J4endl;
         J4cerr <<"         Otherwise last poststep point is on my surface."
                << J4endl;
         J4cerr <<"         NAME        : " << GetName() << J4endl;
         J4cerr <<"         xx          : " << xx << J4endl;
         J4cerr <<"         gxx[0]      : " << gxx[0] << J4endl;
         J4cerr <<"         dist[0]     : " << distance[0] << J4endl;
         J4cerr <<"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
#endif
         return 1;
      } else {
         // A.z = C.z(). return distance to line.
         d[0] = C - A;
         distance[0] = DistanceToLine(p, A, d[0], xx);
         areacode[0] = kInside;
         gxx[0] = ComputeGlobalPoint(xx);
         G4bool isvalid = TRUE;
         fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
         J4cerr <<"      ~~~~~ J4TwistedSurface:DistanceToSurface(p):return"
                << J4endl;
         J4cerr <<"         NAME        : " << GetName() << J4endl;
         J4cerr <<"         xx          : " << xx << J4endl;
         J4cerr <<"         gxx[0]      : " << gxx[0] << J4endl;
         J4cerr <<"         dist[0]     : " << distance[0] << J4endl;
         J4cerr <<"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                << J4endl;
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
      gxx[0] = ComputeGlobalPoint(xx);
      distance[0] = 0;
      G4bool isvalid = TRUE;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0] , areacode[0],
                                isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
      J4cerr <<"      ~~~~~ J4TwistedSurface:DistanceToSurface(p):return"
             << J4endl;
      J4cerr <<"         NAME        : " << GetName() << J4endl;
      J4cerr <<"         xx          : " << xx << J4endl;
      J4cerr <<"         gxx[0]      : " << gxx[0] << J4endl;
      J4cerr <<"         dist[0]     : " << distance[0] << J4endl;
      J4cerr <<"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
#endif

      return 1;

   }

#ifdef __SOLIDDEBUG__
   J4cerr << "      ~~~ J4TwistedSurface::DistanceToSurface(p):~~~~~~~"
          << J4endl;
   J4cerr << "      //*   NAME          : " << GetName() << J4endl;
   J4cerr << "      //*   p             : " << p << J4endl; 
   J4cerr << "      //*   A, C, parity  : " << A << " , " << C << " , " 
                                            << parity << J4endl;
   J4cerr << "      //*   nacb, ncad    : " << nacb << " , " << ncad 
          << J4endl;
   J4cerr << "      //*   xxacb, xxcad  : " << xxacb << " , " << xxcad 
          << J4endl;
   J4cerr << "      //*   distToACB, distToCAD  : " << distToACB << " , "
                                                << distToCAD << J4endl; 
   J4cerr << "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
          << J4endl;
#endif
   
   if (distToACB * distToCAD > 0 && distToACB < 0) {
      // both distToACB and distToCAD are negative.
      // divide quadrangle into double triangle by diagonal
      G4ThreeVector normal;
      distance[0] = DistanceToPlane(p, A, B, C, D, parity, xx, normal);
   } else {
      if (distToACB * distToCAD > 0) {
         // both distToACB and distToCAD are positive.
         // Take smaller one.
         if (distToACB <= distToCAD) {
            distance[0] = distToACB;
            xx   = xxacb;
         } else {
            distance[0] = distToCAD;
            xx   = xxcad;
         }
      } else {
         // distToACB * distToCAD is negative.
         // take positive one
         if (distToACB > 0) {
            distance[0] = distToACB;
            xx   = xxacb;
         } else {
            distance[0] = distToCAD;
            xx   = xxcad;
         }
      }

#ifdef __BOUNDARYCHECK__     
      // boundary check 
      G4ThreeVector xxt(xx.x(), xx.y(), 0.);
      G4double      xxrc     = fabs(xx.x());
      G4ThreeVector xxsurfacevector(xxrc, xxrc * fKappa * xx.z(), 0.);
      G4int         xxpside  = AmIOnLeftSide(xxt, xxsurfacevector);
      G4double      xxtest   = pside * xxpside;
      G4int         areacode = 0;

      if (xxtest < 0) {
         if (fabs(xx.x() - fAxisMin[0]) < fabs(xx.x() -fAxisMax[0])) {
            // fAxisMin[0] : kAxisX minimum.
            areacode |= (kAxis0 & kAxisMin);
            distance[0] = DistanceToBoundary(areacode, xx, p);
         } else {
            // kAxisX maximum.
            areacode |= (kAxis0 & kAxisMax);
            distance[0] = DistanceToBoundary(areacode, xx, p);
         }
      }
#endif
      
   }
   areacode[0] = kInside;
   gxx[0]      = ComputeGlobalPoint(xx);
   G4bool isvalid = TRUE;
   fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                             isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
      J4cerr <<"      ~~~~~ J4TwistedSurface:DistanceToSurface(p):return"
             << J4endl;
      J4cerr <<"         NAME        : " << GetName() << J4endl;
      J4cerr <<"         xx          : " << xx << J4endl;
      J4cerr <<"         gxx[0]      : " << gxx[0] << J4endl;
      J4cerr <<"         dist[0]     : " << distance[0] << J4endl;
      J4cerr <<"      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
             << J4endl;
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
   static const G4double halftol = 0.5 * kCarTolerance;
   
   G4ThreeVector M = 0.5*(A + B);
   G4ThreeVector N = 0.5*(C + D);
   G4ThreeVector xxanm;  // foot of normal from p to plane ANM
   G4ThreeVector nanm;   // normal of plane ANM
   G4ThreeVector xxcmn;  // foot of normal from p to plane CMN
   G4ThreeVector ncmn;   // normal of plane CMN

   G4double distToanm = J4VSurface::DistanceToPlane(p, A, (N - A), (M - A), xxanm, nanm) * parity;
   G4double distTocmn = J4VSurface::DistanceToPlane(p, C, (M - C), (N - C), xxcmn, ncmn) * parity;

   // if p is behind of both surfaces, abort.
   if (distToanm * distTocmn > 0 && distToanm < 0) {
      J4cerr << "      J4TwistedSurface::DistanceToPlane: p is "
             << "behind the surfaces. abort." << J4endl;
      abort();
   }

   // if p is on surface, return 0.
   if (fabs(distToanm) <= halftol) {
      xx = xxanm;
      n  = nanm * parity;
      return 0;
   } else if (fabs(distTocmn) <= halftol) {
      xx = xxcmn;
      n  = ncmn * parity;
      return 0;
   }
   
   if (distToanm <= distTocmn) {
      if (distToanm > 0) {
         // both distanses are positive. take smaller one.
         xx = xxanm;
         n  = nanm * parity;
         return distToanm;
      } else {
         // take -ve distance and call the function recursively.
         return DistanceToPlane(p, A, M, N, D, parity, xx, n);
      }
   } else {
      if (distTocmn > 0) {
         // both distanses are positive. take smaller one.
         xx = xxcmn;
         n  = ncmn * parity;
         return distTocmn;
      } else {
         // take -ve distance and call the function recursively.
         return DistanceToPlane(p, C, N, M, B, parity, xx, n);
      }
   }
}

//=====================================================================
//* GetAreaCode -------------------------------------------------------
G4int J4TwistedSurface::GetAreaCode(const G4ThreeVector &xx, 
                                          G4bool withTol)
{
   // We must use the function in local coordinate system.
   // See the description of DistanceToSurface(p,v).
   
   static const G4double ctol = 0.5 * kCarTolerance;
   G4int areacode = kInside;
   
   if (fAxis[0] == kXAxis && fAxis[1] == kZAxis) {
      G4int xaxis = 0;
      G4int zaxis = 1;

#ifdef __SOLIDDEBUGAREACODE__
      J4cerr << "         === J4TwistedSurface::GetAreaCode ============"
             << J4endl;
      J4cerr << "         //#    fAxisMin,Max(xaxis)  : " 
             << fAxisMin[xaxis] << " , " << fAxisMax[xaxis] << J4endl;
      J4cerr << "         //#    fAxisMin,Max(zaxis)  : " 
             << fAxisMin[zaxis] << " , " << fAxisMax[zaxis] << J4endl;
      J4cerr << "         =============================================="
             << J4endl;
#endif
      
      if (withTol) {

         G4bool isoutside   = FALSE;

         // test boundary of xaxis

         if (xx.x() < fAxisMin[xaxis] + ctol) {
            areacode |= (kAxis0 & (kAxisX | kAxisMin)) | kBoundary; 
            if (xx.x() <= fAxisMin[xaxis] - ctol) isoutside = TRUE;

         } else if (xx.x() > fAxisMax[xaxis] - ctol) {
            areacode |= (kAxis0 & (kAxisX | kAxisMax)) | kBoundary;
            if (xx.x() >= fAxisMin[xaxis] + ctol)  isoutside = TRUE;
         }

         // test boundary of z-axis

         if (xx.z() < fAxisMin[zaxis] + ctol) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMin)); 

            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary;
            if (xx.z() <= fAxisMin[zaxis] - ctol) isoutside = TRUE;

         } else if (xx.z() > fAxisMax[zaxis] - ctol) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMax));

            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary; 
            if (xx.z() >= fAxisMax[zaxis] + ctol) isoutside = TRUE;
         }

         // if isoutside = TRUE, clear inside bit.             
         // if not on boundary, add axis information.             
         
         if (isoutside) {
            G4int tmpareacode = areacode & (~kInside);
            areacode = tmpareacode;
         } else if ((areacode & kBoundary) != kBoundary) {
            areacode |= (kAxis0 & kAxisX) | (kAxis1 & kAxisZ);
         }           
         
      } else {

         // boundary of x-axis

         if (xx.x() < fAxisMin[xaxis] ) {
            areacode |= (kAxis0 & (kAxisX | kAxisMin)) | kBoundary;
         } else if (xx.x() > fAxisMax[xaxis]) {
            areacode |= (kAxis0 & (kAxisX | kAxisMax)) | kBoundary;
         }
         
         // boundary of z-axis

         if (xx.z() < fAxisMin[zaxis]) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMin));
            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary; 
           
         } else if (xx.z() > fAxisMax[zaxis]) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMax)) ;
            if   (areacode & kBoundary) areacode |= kCorner;  // xx is on the corner.
            else                        areacode |= kBoundary; 
         }

         if ((areacode & kBoundary) != kBoundary) {
            areacode |= (kAxis0 & kAxisX) | (kAxis1 & kAxisZ);
         }           
      }

      return areacode;

   } else {

      J4cerr << "          J4FlatSurface::GetAreaCode fAxis[0] = " << fAxis[0]
             << " fAxis[1] = " << fAxis[1]
             << " is yet implemented. Write the code yourself." << J4endl;
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
      J4cerr << "J4FlatSurface::SetCorners fAxis[0] = " << fAxis[0]
      << " fAxis[1] = " << fAxis[1]
      << " is yet implemented. Write the code yourself." << J4endl;
      abort();
   }
}

//=====================================================================
//* SetCorners() ------------------------------------------------------
void J4TwistedSurface::SetCorners()
{
   J4cerr << "J4FlatSurface::SetCorners" 
   << " is yet implemented. Write the code yourself." << J4endl;
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
      J4cerr << "J4FlatSurface::SetBoundaries fAxis[0] = " << fAxis[0]
      << " fAxis[1] = " << fAxis[1]
      << " is yet implemented. Write the code yourself." << J4endl;
      abort();
   }
}

