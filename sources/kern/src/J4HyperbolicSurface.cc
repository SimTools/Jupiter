/*
 *  J4HyperbolicSurface.cc
 *  
 *
 *  Created by Kotoyo Hoshina on Thu Aug 01 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */

//#define __SOLIDDEBUG__
//#define __SOLIDDEBUGAREACODE__

#include "J4HyperbolicSurface.hh"
#include "J4TwistedTubs.hh"

//=====================================================================
//* constructor -------------------------------------------------------

J4HyperbolicSurface::J4HyperbolicSurface(const G4String         &name,
                                         const G4RotationMatrix &rot,
                                         const G4ThreeVector    &tlate,
                                         const G4int             handedness,
                                         const G4double          kappa,
                                         const G4double          tanstereo,
                                         const G4double          r0,
                                         const EAxis             axis0,
                                         const EAxis             axis1,
                                               G4double          axis0min,
                                               G4double          axis1min,
                                               G4double          axis0max,
                                               G4double          axis1max )
                    :J4VSurface(name, rot, tlate, handedness, axis0, axis1, axis0min, 
                                axis1min, axis0max, axis1max),
                     fKappa(kappa), fTanStereo(tanstereo),
                     fTan2Stereo(tanstereo*tanstereo), fR0(r0), fR02(r0*r0)
{
   if (axis0 == kZAxis && axis1 == kPhi) {
      G4cerr << "J4HyperbolicSurface::Constructor: " 
             << "Swap axis0 and axis1. abort. " << G4endl;
      abort();
   }
   SetCorners();
   SetBoundaries();   
}

J4HyperbolicSurface::J4HyperbolicSurface(const G4String      &name,
                                               J4TwistedTubs *solid,
                                               G4int          handedness)
                    :J4VSurface(name)
{

   fHandedness = handedness;   // +z = +ve, -z = -ve
   fAxis[0]    = kPhi;
   fAxis[1]    = kZAxis;
   fAxisMin[0] = kInfinity;         // we cannot fix boundary min of Phi, because it depends on z.
   fAxisMax[0] = kInfinity;         // we cannot fix boundary min of Phi, because it depends on z.
   fAxisMin[1] = solid->GetEndZ(0);
   fAxisMax[1] = solid->GetEndZ(1);
   fKappa      = solid->GetKappa();

   if (handedness < 0) { // inner hyperbolic surface
      fTanStereo  = solid->GetTanInnerStereo();
      fR0         = solid->GetInnerRadius();
   } else {              // outer hyperbolic surface
      fTanStereo  = solid->GetTanOuterStereo();
      fR0         = solid->GetOuterRadius();
   }
   fTan2Stereo = fTanStereo * fTanStereo;
   fR02        = fR0 * fR0;
   
   fTrans.set(0, 0, 0);

   SetCorners(solid);
   SetBoundaries();
}

//=====================================================================
//* destructor --------------------------------------------------------
J4HyperbolicSurface::~J4HyperbolicSurface()
{
}

//=====================================================================
//* GetNormal ---------------------------------------------------------
G4ThreeVector J4HyperbolicSurface::GetNormal(const G4ThreeVector &tmpxx, 
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

   G4ThreeVector normal( xx.x(), xx.y(), -xx.z() * fTan2Stereo);
   normal *= fHandedness;
   normal = normal.unit();

   if (isGlobal) {
      fCurrentNormal = fRot * normal ;
   } else {
      fCurrentNormal = normal;
   }
   return fCurrentNormal;
}

//=====================================================================
//* Inside() ----------------------------------------------------------
EInside J4HyperbolicSurface::Inside(const G4ThreeVector &gp) const
{
   static const G4double halftol = 0.5 * kRadTolerance;
   G4ThreeVector p = fRot.inverse()*gp - fTrans;
   if (p.mag() < DBL_MIN) {
      return ::kOutside;
   }
   
#ifdef __SOLIDDEBUG__
   G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl;
   G4cerr <<">>>>> J4TwistedSurface:Inside : Start from p : "
      << p <<  " >>>>>> " << G4endl;
#endif
   

   G4double rhohype = GetRhoAtPZ(p);
   G4double distanceToOut = fHandedness * (rhohype - p.getRho());
   G4int areacode = GetAreaCode(p);

   EInside returncode;
   if ((areacode & kInside) == kInside) {
      if (distanceToOut >= halftol) {
         returncode = ::kInside;
      } else if (distanceToOut <= -halftol)  {
         returncode = ::kOutside;
      } else {
         returncode = ::kSurface;
      }
   } else if ((areacode & kBoundary) == kBoundary ||
              (areacode & kCorner) == kCorner) { 
      if (distanceToOut >= halftol) {
         returncode = ::kSurface;
      } else if (distanceToOut <= -halftol)  {
         returncode = ::kOutside;
      } else {
         returncode = ::kSurface;
      }
   } else {
      returncode =  ::kOutside;
   }
   return returncode; 
}

//=====================================================================
//* DistanceToSurface -------------------------------------------------
G4int J4HyperbolicSurface::DistanceToSurface(const G4ThreeVector &gp,
                                             const G4ThreeVector &gv,
                                                   G4ThreeVector  gxx[],
                                                   G4double       distance[],
                                                   G4int          areacode[],
                                                   G4bool         isvalid[],
                                                   EValidate      validate)
{
   //
   // Decide if and where a line intersects with a hyperbolic
   // surface (of infinite extent)
   //
   // Arguments:
   //     p       - (in) Point on trajectory
   //     v       - (in) Vector along trajectory
   //     r2      - (in) Square of radius at z = 0
   //     tan2phi - (in) tan(stereo)**2
   //     s       - (out) Up to two points of intersection, where the
   //                     intersection point is p + s*v, and if there are
   //                     two intersections, s[0] < s[1]. May be negative.
   // Returns:
   //     The number of intersections. If 0, the trajectory misses.
   //
   //
   // Equation of a line:
   //
   //       x = x0 + s*tx      y = y0 + s*ty      z = z0 + s*tz
   //
   // Equation of a hyperbolic surface:
   //
   //       x**2 + y**2 = r**2 + (z*tanPhi)**2
   //
   // Solution is quadratic:
   //
   //  a*s**2 + b*s + c = 0
   //
   // where:
   //
   //  a = tx**2 + ty**2 - (tz*tanPhi)**2
   //
   //  b = 2*( x0*tx + y0*ty - z0*tz*tanPhi**2 )
   //
   //  c = x0**2 + y0**2 - r**2 - (z0*tanPhi)**2
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
   
   G4ThreeVector p = fRot.inverse() * gp - fTrans;
   G4ThreeVector v = fRot.inverse() * gv;
   G4ThreeVector xx[2]; 

#ifdef __SOLIDDEBUG__
   G4cerr << "~~~~~ J4HyperbolicSurface:DistanceToSurface(p,v) : "
      << "Start from gp, gv, p, v :" << G4endl;
   G4cerr << "      "
      << GetName() << " , "
      << gp << " , "
      << gv << " , "
      << p << " , "
      << v << " ~~~~~ " << G4endl;
#endif
   
   //
   // special case!  p is on origin or on surface.
   // 

   G4double diff  = GetRhoAtPZ(p) - p.getRho(); 

   if (p.mag() == 0) {
       // p is origin. 
       // unique solution of 2-dimension question in r-z plane 
       // Equations:
       //    r^2 = fR02 + z^2*fTan2Stere0
       //    r = beta*z
       //        where 
       //        beta = vrho / vz
       // Solution (z value of intersection point):
       //    xxz = +- sqrt (fR02 / (beta^2 - fTan2Stereo))
       //

       G4double vz    = v.z();
       G4double absvz = abs(vz);
       G4double vrho  = v.getRho();       
       G4double vslope = vrho/vz;
       G4double vslope2 = vslope * vslope;
       if (vrho == 0 || (vrho/absvz) <= (absvz*fabs(fTanStereo)/absvz)) {
          // vz/vrho is bigger than slope of asymptonic line
          distance[0] = kInfinity;
          fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 0, validate, &gp, &gv);
#ifdef __SOLIDDEBUG__
          G4cerr << "~~~~~ J4HyperblicSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
                 << G4endl;
          G4cerr << "   vz/vrho is bigger than slope of asymptonic line. return 0. " << G4endl;
          G4cerr << "   NAME     : " << GetName() << G4endl;
          G4cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ "
                  << G4endl;
#endif
          return 0;
       }
       
       if (vz) { 
          G4double xxz  = sqrt(fR02 / (vslope2 - fTan2Stereo)) 
                          * (vz / fabs(vz)) ;
          G4double t = xxz / vz;
          xx[0].set(t*v.x(), t*v.y(), xxz);
       } else {
          // p.z = 0 && v.z =0
          xx[0].set(v.x()*fR0, v.y()*fR0, 0);  // v is a unit vector.
       }
       distance[0] = xx[0].mag();
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
           areacode[0] = kInside;
           if (distance[0] >= 0) isvalid[0] = TRUE;
       }
                 
       fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 1, validate, &gp, &gv);
#ifdef __SOLIDDEBUG__
       G4cerr << "~~~~~ J4HyperblicSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
              << G4endl;
       G4cerr << "   p is on origin. " << G4endl;
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

   } else if (diff * diff <= GetRhoAtPZ(p) * kCarTolerance) {
      if (validate == kValidateWithTol) {
          areacode[0] = GetAreaCode(p);
          if ((areacode[0] & kAreaMask) != kOutside) {
             distance[0] = 0; 
             gxx[0] = gp;
             isvalid[0] = TRUE;
          }   
      } else if (validate == kValidateWithoutTol) {
          areacode[0] = GetAreaCode(p, FALSE);
          if ((areacode[0] & kAreaMask) == kInside) {
             distance[0] = 0;
             gxx[0] = gp;
             isvalid[0] = TRUE;
          }
      } else { // kDontValidate                       
          areacode[0] = kInside;
          distance[0] = 0;
          gxx[0] = gp;
          isvalid[0] = TRUE;
      }
      fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                     isvalid[0], 1, validate, &gp, &gv);
#ifdef __SOLIDDEBUG__
      G4cerr << "~~~~~ J4HyperblicSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
         << G4endl;
      G4cerr << "   p is on surface. " << G4endl;
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
      
   }
    
   //
   // special case end.
   // 
   

   G4double a = v.x()*v.x() + v.y()*v.y() - v.z()*v.z()*fTan2Stereo;
   G4double b = 2.0 * ( p.x() * v.x() + p.y() * v.y() - p.z() * v.z() * fTan2Stereo );
   G4double c = p.x()*p.x() + p.y()*p.y() - fR02 - p.z()*p.z()*fTan2Stereo;
   G4double D = b*b - 4*a*c;          //discriminant
#ifdef __SOLIDDEBUG__
         G4cerr << "//* J4HyperbolicSurface::DistanceToSurface: name, p, v, a,b,c,D = ------------" << G4endl;
         G4cerr << "//*   NAME      : " << GetName() << G4endl;
         G4cerr << "//*   p, v      : " << p << " , " << v << G4endl;
         G4cerr << "//*   a,b,c,D   : " << a << " , " << b << " , " << c << " , " << D << G4endl; 
         G4cerr << "//*---------------------------------------------------------------------------" << G4endl;
#endif  
   
   if (fabs(a) < DBL_MIN) {
      if (fabs(b) > DBL_MIN) {           // single solution

         distance[0] = -c/b;
         xx[0] = p + distance[0]*v;
         gxx[0] = fRot*xx[0] + fTrans;

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
            areacode[0] = kInside;
            if (distance[0] >= 0) isvalid[0] = TRUE;
         }
                 
         fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 1, validate, &gp, &gv);
         fCurStatWithV.DebugPrint();
#ifdef __SOLIDDEBUG__
         G4cerr << "~~~~~ J4HyperblicSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
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
         fCurStatWithV.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                        isvalid[0], 0, validate, &gp, &gv);

#ifdef __SOLIDDEBUG__
         G4cerr << "~~~~~ J4HyperblicSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
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
      
   } else if (D > DBL_MIN) {         // double solutions
      
      D = sqrt(D);
      G4double      factor = 0.5/a;
      G4double      tmpdist[2] = {kInfinity, kInfinity};
      G4ThreeVector tmpxx[2] ;
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
            tmpareacode[i] = kInside;
            if (tmpdist[i] >= 0) tmpisvalid[i] = TRUE;
            continue;
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
      G4cerr << "~~~~~ J4HyperblicSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
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
      G4cerr << "~~~~~ J4HyperblicSurface:DistanceToSurface(p,v) : last return ~~~~~~ "
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
    G4cerr << "J4HyperblicSurface::DistanceToSurface(p,v) illigal operation!! abort"
          << G4endl;
    abort();          
}

   
//=====================================================================
//* DistanceToSurface -------------------------------------------------
G4int J4HyperbolicSurface::DistanceToSurface(const G4ThreeVector &gp,
                                                   G4ThreeVector  gxx[],
                                                   G4double       distance[],
                                                   G4int          areacode[])
{
    // Find the approximate distance of a point of a hyperbolic surface.
    // The distance must be an underestimate. 
    // It will also be nice (although not necesary) that the estimate is
    // always finite no matter how close the point is.
    //
    // We arranged G4Hype::ApproxDistOutside and G4Hype::ApproxDistInside
    // for this function. See these discriptions.
    
   static const G4double halftol    = 0.5 * kRadTolerance;

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
   

   G4ThreeVector p = fRot.inverse() * gp - fTrans;
   G4ThreeVector xx;

#ifdef __SOLIDDEBUG__
   G4cerr <<"~~~~~ J4HyperbolicSurface:DistanceToSurface(p) : Start from gp, p : "
      << GetName() << " , "
      << gp << " , "
      << p << " ~~~~~ " << G4endl;
#endif

   //
   // special case!
   // If p is on surface, return distance = 0 immediatery .
   //
   G4ThreeVector  lastgxx[2];
   G4double       distfromlast[2];
   for (G4int i=0; i<2; i++) {
      lastgxx[i] = fCurStatWithV.GetXX(i);
      distfromlast[i] = (gp - lastgxx[i]).mag();
#ifdef __SOLIDDEBUG__
      G4cerr <<"//* J4HyperbolicSurface:DistanceToSurface(p) : lastgxx, distance from last = "
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
      G4cerr <<"~~~~~ J4HyperbolicSurface:DistanceToSurface(p) : last return ~~~~~~~~ " << G4endl;
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
      // p is on origin! return fR0.
      G4bool isvalid = TRUE;
      distance[0] = fR0;
      xx.set(fR0, 0, 0);
      gxx[0] = fRot*xx + fTrans;
      fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                                    isvalid, 0, kDontValidate, &gp);

#ifdef __SOLIDDEBUG__
      G4cerr <<"~~~~~ J4HyperbolicSurface:DistanceToSurface(p) : last return ~~~~~~~~ " << G4endl;
      G4cerr <<"   p is on origin dist = fR0, return 1. " << G4endl;
      G4cerr <<"   NAME        : " << GetName() << G4endl;
      G4cerr <<"   xx          : " << xx << G4endl;
      G4cerr <<"   gxx[0]      : " << gxx[0] << G4endl;
      G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
      G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << G4endl;
#endif
      return 1;
   }
   //
   // special case end
   //
       
   G4double rho = p.getRho();
   G4double pz  = fabs(p.z());             // use symmetory
   G4double r   = sqrt(fR02 + pz * pz * fTan2Stereo);
#ifdef __SOLIDDEBUG__
   G4cerr << "//* J4HyperbolicSurface::DistanceToSurface(p):---------------------------------" << G4endl;
   G4cerr << "//*   NAME     : " <<  GetName() << G4endl;
   G4cerr << "//*   fR02     : " <<  fR02 << G4endl;
   G4cerr << "//*   p.rho    : " <<  rho << G4endl;
   G4cerr << "//*   pz       : " <<  pz << G4endl;
   G4cerr << "//*   r(z=p.z) : " <<  r << G4endl;
   G4cerr << "//*-------------------------------------------------------------------------" << G4endl;
#endif
   
   if (rho > r + halftol) {  // p is outside of Hyperbolic surface
   
      // First point xx1
      G4double z1 = pz;
      G4double r1 = r;
      
      // Second point xx2
      G4double z2 = (rho * fTanStereo + pz) / (1 + fTan2Stereo);
      G4double r2 = sqrt(fR02 + z2 * z2 * fTan2Stereo);
      
      // Line between them
      G4double dr = r2 - r1;
      G4double dz = z2 - z1;

      G4double len = sqrt(dr * dr + dz * dz);
      if (len < DBL_MIN) {
         // The two points are the same?? I guess we
         // must have really bracketed the normal
         distance[0] = fabs(rho - r1);
      } else {
         // Distance
         // (rho - r1)*dz = len*distance
         distance[0] = (fabs(rho - r1) * fabs(dz)) / len;
      }
#ifdef __SOLIDDEBUG__
      G4cerr << "//* J4HyperbolicSurface::DistanceToSurface(p):-------" << G4endl;
      G4cerr << "//*   p is outside of Hyperbolic surface."  << G4endl;
      G4cerr << "//*   NAME     : " <<  GetName() << G4endl;
      G4cerr << "//*   Len      : " <<  len << G4endl;
      G4cerr << "//*   Distance : " <<  distance[0] << G4endl;
      G4cerr << "//*--------------------------------------------------" << G4endl;
#endif
            
   } else if (rho < r - halftol) { // p is inside of Hyperbolic surface.
      
     // Corresponding position and normal on hyperbolic
     // point xx1: point on Hyperbolic surface at z = p.z();
     G4double r1 = r;
     
     // dr, dz is tangential vector of Hyparbolic surface at xx1
     // dr = r, dz = z*tan2stereo
     G4double dr  = pz * fTan2Stereo;
     G4double dz  = r1;
     G4double len = sqrt(dr * dr + dz * dz);
      
     // Answer
     // distance  = fabs(r1 - rho) * cos(Bata)
     // cos(Bata) = dz / len
     distance[0] = fabs(r1 - rho) * fabs(dz) / len;
#ifdef __SOLIDDEBUG__
     G4cerr << "//* J4HyperbolicSurface::DistanceToSurface(p):--------" << G4endl;
     G4cerr << "//*   p is inside of Hyperbolic surface."  << G4endl;
     G4cerr << "//*   NAME     : " <<  GetName() << G4endl;
     G4cerr << "//*   Len      : " <<  len << G4endl;
     G4cerr << "//*   Distance : " <<  distance[0] << G4endl;
     G4cerr << "//*---------------------------------------------------" << G4endl;
#endif
          
   } else {  // p is on Hyperbolic surface.
   
      distance[0] = 0;
#ifdef __SOLIDDEBUG__
      G4cerr << "//* J4HyperbolicSurface::DistanceToSurface(p):--------" << G4endl;
      G4cerr << "//*   p is on of Hyperbolic surface."  << G4endl;
      G4cerr << "//*---------------------------------------------------" << G4endl;
#endif
   }
   
   areacode[0]    = kInside;
   G4bool isvalid = TRUE;
   fCurStat.SetCurrentStatus(0, gxx[0], distance[0], areacode[0],
                             isvalid, 1, kDontValidate, &gp);
#ifdef __SOLIDDEBUG__
   G4cerr <<"~~~~~ J4HyperbolicSurface:DistanceToSurface(p,v) : last return ~~~~~~~~ " << G4endl;
   G4cerr <<"   NAME        : " << GetName() << G4endl;
   G4cerr <<"   dist[0]     : " << distance[0] << G4endl;
   G4cerr <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ " << G4endl;
#endif
       return 1;
}

//=====================================================================
//* GetAreaCode -------------------------------------------------------
G4int J4HyperbolicSurface::GetAreaCode(const G4ThreeVector &xx, 
                                             G4bool         withTol) const
{
   static const G4double ctol = 0.5 * kCarTolerance;
   G4int areacode = 0;
   
   //special case! if xx = 0, return kOutside.
   if (xx.mag() < DBL_MIN) {
      areacode |= (kAxis0 & kAxisPhi) | (kAxis1 & kAxisZ) | kOutside;
   }

   if ((fAxis[0] == kPhi && fAxis[1] == kZAxis))  {
      G4int zaxis   = 1;
      
      if (withTol) {
         G4int phiareacode = GetAreaCodeInPhi(xx);
#ifdef __SOLIDDEBUGAREACODE__
         G4cerr << "J4HyperbolicSurface::GetAreaCode: areacodeinphi = " 
                << GetName() << " " << G4std::hex << phiareacode << G4std::dec << G4endl;
#endif

         // inside or outside
         if (xx.z() >= fAxisMin[zaxis] + ctol 
                    && xx.z() <= fAxisMax[zaxis] - ctol
                    && phiareacode == kInside) {
            areacode |= (kAxis0 & kAxisPhi) | (kAxis1 & kAxisZ) | kInside;
#ifdef __SOLIDDEBUGAREACODE__
         G4cerr << "J4HyperbolicSurface::GetAreaCode: inside areacode = " 
                << GetName() << " "<< G4std::hex << areacode << G4std::dec << G4endl;
#endif
            return areacode;
         } else if (xx.z() <= fAxisMin[zaxis] - ctol 
                    || xx.z() >= fAxisMax[zaxis] + ctol
                    || phiareacode == kOutside) {
            areacode |= (kAxis0 & kAxisPhi) | (kAxis1 & kAxisZ) | kOutside;
#ifdef __SOLIDDEBUGAREACODE__
         G4cerr << "J4HyperbolicSurface::GetAreaCode: outside areacode = " 
                << GetName() << " "<< G4std::hex << areacode << G4std::dec << G4endl;
#endif
            return areacode;
         }
      
         // Now, xx is on boundary. Which boundary?
         // on boundary of z-axis
         if (xx.z() < fAxisMin[zaxis] + ctol) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMin)) | kBoundary;
#ifdef __SOLIDDEBUGAREACODE__
         G4cerr << "J4HyperbolicSurface::GetAreaCode: boundary1 areacode = " 
                << GetName() << " " << G4std::hex << areacode << G4std::dec << G4endl;
#endif
         } else if (xx.z() > fAxisMax[zaxis] - ctol) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMax)) | kBoundary;
#ifdef __SOLIDDEBUGAREACODE__
         G4cerr << "J4HyperbolicSurface::GetAreaCode: boundary2 areacode = " 
                << GetName() << " "<< G4std::hex << areacode << G4std::dec << G4endl;
#endif
         }
         // boundary of phi-axis
         if (phiareacode == kAxisMin) {
            areacode |= (kAxis0 & (kAxisPhi | kAxisMin));
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary;
            } 
#ifdef __SOLIDDEBUGAREACODE__
         G4cerr << "J4HyperbolicSurface::GetAreaCode: boundary3 areacode = " 
                << GetName() << " "<< G4std::hex << areacode << G4std::dec << G4endl;
#endif
         } else if (phiareacode == kAxisMax) {
            areacode |= (kAxis0 & (kAxisPhi | kAxisMax));
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary;
            } 
#ifdef __SOLIDDEBUGAREACODE__
         G4cerr << "J4HyperbolicSurface::GetAreaCode: boundary4 areacode = " 
                << GetName() << " "<< G4std::hex << areacode << G4std::dec << G4endl;
#endif
         }
         return areacode;
      
      } else {
         G4int phiareacode = GetAreaCodeInPhi(xx, FALSE);
         
         // inside
         if (xx.z() >= fAxisMin[zaxis]
             && xx.z() <= fAxisMax[zaxis]
             && phiareacode == kInside) {
            areacode |= (kAxis0 & kAxisPhi) | (kAxis1 & kAxisZ) | kInside;
            return (G4int)kInside;
         } 
                    
         // Now, xx is on boundary. Which boundary?
         // on boundary of z-axis
         if (xx.z() < fAxisMin[zaxis]) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMin)) | kBoundary;
         } else if (xx.z() > fAxisMax[zaxis]) {
            areacode |= (kAxis1 & (kAxisZ | kAxisMax)) | kBoundary;
         }
         // boundary of phi-axis
         if (phiareacode == kAxisMin) {
            areacode |= (kAxis0 & (kAxisPhi | kAxisMin));
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary; 
            } 
         } else if (phiareacode == kAxisMax) {
            areacode |= (kAxis0 & (kAxisPhi | kAxisMax));
            if (areacode & kBoundary) {
               areacode |= kCorner;  // xx is on the corner.
            } else {
               areacode |= kBoundary; 
            } 
         }
         return areacode;
      }
   } else {
      G4cerr << "J4HyperbolicSurface::GetAreaCode fAxis[0] = " << fAxis[0]
      << " fAxis[1] = " << fAxis[1]
      << " is yet implemented. Write the code yourself." << G4endl;
      abort();
   }
}

//=====================================================================
//* GetAreaCodeInPhi ------------------------------------------------------
G4int J4HyperbolicSurface::GetAreaCodeInPhi(const G4ThreeVector &xx,
                                                  G4bool withTol) const
{
   G4RotationMatrix unitrot; // unit matrix
   static const G4RotationMatrix rottol    = unitrot.rotateZ(0.5*kAngTolerance);
   static const G4RotationMatrix invrottol = unitrot.rotateZ(-0.5*kAngTolerance);
   
   G4ThreeVector lowerlimit; // lower phi-boundary limit-point at z = xx.z()
   G4ThreeVector upperlimit; // upper phi-boundary limit-point at z = xx.z()
   G4ThreeVector lowerdir;   // direction unit vector of lower phi-boundary line
   G4ThreeVector upperdir;   // direction unit vector of upper phi-boundary line
   G4ThreeVector lowerx0;    // reference point of lower phi-boundary line
   G4ThreeVector upperx0;    // reference point of upper phi-boundary line
   G4int lowerboundarytype;
   G4int upperboundarytype;

   GetBoundaryParameters( kAxis0 & kAxisMin, lowerdir, lowerx0, lowerboundarytype); // kAxis0 = kPhi,
   GetBoundaryParameters( kAxis0 & kAxisMax, upperdir, upperx0, upperboundarytype); // 
   lowerlimit = ((xx.z() - lowerx0.z()) / lowerdir.z()) * lowerdir + lowerx0;
   upperlimit = ((xx.z() - upperx0.z()) / upperdir.z()) * upperdir + upperx0;

   G4ThreeVector    rottol_upperlimit    = rottol*upperlimit;
   G4ThreeVector    rottol_lowerlimit    = rottol*lowerlimit;
   G4ThreeVector    invrottol_upperlimit = invrottol*upperlimit;
   G4ThreeVector    invrottol_lowerlimit = invrottol*lowerlimit;

#ifdef __SOLIDDEBUGAREACODE__
   G4cerr << "//* J4HyperbolicSurface::GetAreaCodeInPhi ================================== " << G4endl;
   G4cerr << "//*    NAME       : " << GetName() << G4endl; 
   G4cerr << "//*    xx         : " << xx << G4endl; 
   G4cerr << "//*    lowerx0    : " << lowerx0 << G4endl; 
   G4cerr << "//*    upperx0    : " << upperx0 << G4endl; 
   G4cerr << "//*    upperlimit : " << upperlimit << G4endl; 
   G4cerr << "//*    lowerlimit : " << lowerlimit << G4endl; 
   G4cerr << "//*========================================================================= " << G4endl;
 
#endif
   
   if (withTol) {
         
      if (xx.cross(rottol_lowerlimit).z() <= 0 
                 && xx.cross(invrottol_upperlimit).z() >= 0 ) {
         return (G4int)kInside;
      } else if (xx.cross(invrottol_lowerlimit).z() >= 0 
                 || xx.cross(rottol_upperlimit).z() <= 0) {
         return (G4int)kOutside;
      }
   
      // Now, xx is on boundary. Which boundary?
      if (xx.cross(rottol_lowerlimit).z() > 0) { 
         return kAxisMin;
      } else if (xx.cross(invrottol_upperlimit).z() < 0) {
         return kAxisMax;
      } else {
         G4cerr << "J4HyperbolicSurface::GetAreaInPhi: illeagal condition. abort. "
                << G4endl;
         abort();
      }


   } else {
   
      if (xx.cross(lowerlimit).z() <= 0
          && xx.cross(upperlimit).z() >= 0 ) {
         return (G4int)kInside;
      } 
            
      // Now, xx is on boundary. Which boundary?
      if (xx.cross(lowerlimit).z() > 0) {
         return kAxisMin;
      } else if (xx.cross(upperlimit).z() < 0) {
         return kAxisMax;
      } else {
         G4cerr << "J4HyperbolicSurface::GetAreaInPhi: illeagal condition. abort. "
                << G4endl;
         abort();
      }
   }
   
}

//=====================================================================
//* SetCorners(solid) -------------------------------------------------
void J4HyperbolicSurface::SetCorners(J4TwistedTubs *solid)
{
   // Set Corner points in local coodinate.

   if (fAxis[0] == kPhi && fAxis[1] == kZAxis) {

      G4int i;
      G4double endPhi[2];
      G4double endRad[2];
      G4double endZ[2];
      G4double halfdphi = 0.5*(solid->GetDPhi());
      
      for (i=0; i<2; i++) { // i=0,1 : -ve z, +ve z
         endPhi[i] = solid->GetEndPhi(i);
         endZ[i]   = solid->GetEndZ(i);
         endRad[i] = (fHandedness == 1 ? solid->GetEndOuterRadius(i)
                                      : solid->GetEndInnerRadius(i));
      }

      G4int zmin = 0 ;  // at -ve z
      G4int zmax = 1 ;  // at +ve z

      G4double x, y, z;
      
      // corner of Axis0min and Axis1min
      x = endRad[zmin]*cos(endPhi[zmin] - halfdphi);
      y = endRad[zmin]*sin(endPhi[zmin] - halfdphi);
      z = endZ[zmin];
      SetCorner(kCorner0Min1Min, x, y, z);
      
      // corner of Axis0max and Axis1min
      x = endRad[zmin]*cos(endPhi[zmin] + halfdphi);
      y = endRad[zmin]*sin(endPhi[zmin] + halfdphi);
      z = endZ[zmin];
      SetCorner(kCorner0Max1Min, x, y, z);
      
      // corner of Axis0max and Axis1max
      x = endRad[zmax]*cos(endPhi[zmax] + halfdphi);
      y = endRad[zmax]*sin(endPhi[zmax] + halfdphi);
      z = endZ[zmax];
      SetCorner(kCorner0Max1Max, x, y, z);
      
      // corner of Axis0min and Axis1max
      x = endRad[zmax]*cos(endPhi[zmax] - halfdphi);
      y = endRad[zmax]*sin(endPhi[zmax] - halfdphi);
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
void J4HyperbolicSurface::SetCorners()
{
   G4cerr << "J4FlatSurface::SetCorners"
   << " is yet implemented. Write the code yourself." << G4endl;
   abort();
}

//=====================================================================
//* SetBoundaries() ---------------------------------------------------
void J4HyperbolicSurface::SetBoundaries()
{
   // Set direction-unit vector of phi-boundary-lines in local coodinate.
   // kAxis0 must be kPhi.
   // This fanction set lower phi-boundary and upper phi-boundary.

   if (fAxis[0] == kPhi && fAxis[1] == kZAxis) {

      G4ThreeVector direction;
      // kAxis0 & kAxisMin
      direction = GetCorner(kCorner0Min1Max) - GetCorner(kCorner0Min1Min);
      direction = direction.unit();
      SetBoundary(kAxis0 & (kAxisPhi | kAxisMin), direction, 
                   GetCorner(kCorner0Min1Min), kAxisZ);

      // kAxis0 & kAxisMax
      direction = GetCorner(kCorner0Max1Max) - GetCorner(kCorner0Max1Min);
      direction = direction.unit();
      SetBoundary(kAxis0 & (kAxisPhi | kAxisMax), direction, 
                  GetCorner(kCorner0Max1Min), kAxisZ);

      // kAxis1 & kAxisMin
      direction = GetCorner(kCorner0Max1Min) - GetCorner(kCorner0Min1Min);
      direction = direction.unit();
      SetBoundary(kAxis1 & (kAxisZ | kAxisMin), direction, 
                   GetCorner(kCorner0Min1Min), kAxisPhi);

      // kAxis1 & kAxisMax
      direction = GetCorner(kCorner0Max1Max) - GetCorner(kCorner0Max1Min);
      direction = direction.unit();
      SetBoundary(kAxis1 & (kAxisZ | kAxisMax), direction, 
                  GetCorner(kCorner0Max1Min), kAxisPhi);
   } else {
      G4cerr << "J4HyperbolicSurface::SetBoundaries fAxis[0] = " << fAxis[0]
      << " fAxis[1] = " << fAxis[1]
      << " is yet implemented. Write the code yourself." << G4endl;
      abort();
   }
   
}





