// $Id$
//*************************************************************************
//* --------------------
//* J4TwistedTubs
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/07/26  K.Hoshina	Original version.
//*************************************************************************

#include "J4TwistedTubs.hh"

#include "G4VoxelLimits.hh"
#include "G4AffineTransform.hh"
#include "G4SolidExtentList.hh"
#include "G4ClippablePolygon.hh"
#include "G4VPVParameterisation.hh"
#include "meshdefs.hh"

#include "G4VGraphicsScene.hh"
#include "G4Polyhedron.hh"
#include "G4VisExtent.hh"
#include "G4NURBS.hh"
#include "G4NURBStube.hh"
#include "G4NURBScylinder.hh"
#include "G4NURBStubesector.hh"

//#define __SOLIDDEBUG__

// ====================================================================
//--------------------------------
// constants 
//--------------------------------


//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4TwistedTubs::J4TwistedTubs(const G4String &pname,
                                   G4double  twistedangle,
                                   G4double  endinnerrad,
                                   G4double  endouterrad,
                                   G4double  halfzlen,
                                   G4double  dphi)
              :G4VSolid(pname), fDPhi(dphi)
{
   if (endinnerrad < DBL_MIN) {
      G4cerr << "J4VTwistedTubs: invalid endinnerrad" << G4endl;
      abort();
   }
      
   G4double sinhalftwist = sin(0.5 * twistedangle);

   G4double endinnerradX = endinnerrad * sinhalftwist;
   G4double innerrad     = sqrt( endinnerrad * endinnerrad
                                 - endinnerradX * endinnerradX );

   G4double endouterradX = endouterrad * sinhalftwist;
   G4double outerrad     = sqrt( endouterrad * endouterrad
                                 - endouterradX * endouterradX );
   
   // temporary treatment!!
   SetFields(twistedangle, innerrad, outerrad, -halfzlen, halfzlen);
   CreateSurfaces();
   
#ifdef __SOLIDDEBUG__

   G4cerr << "J4TwistedTubs::constracter ===========================" << G4endl;
   G4cerr << "   EndInnerRad(0,1)   : " << fEndInnerRadius[0]
          << " " << fEndInnerRadius[1] << G4endl;
   G4cerr << "   EndOuterRad(0,1)   : " << fEndOuterRadius[0]
          << " " << fEndOuterRadius[1] << G4endl;
   G4cerr << "   EndZ(0,1)          : " << fEndZ[0] << " " << fEndZ[1] << G4endl;
   G4cerr << "   Inner/Outer rad    : " << fInnerRadius << " "
          << fOuterRadius << G4endl;
   G4cerr << "   Inner/Outer Stereo : " << fInnerStereo << " "
          << fOuterStereo << G4endl;
   G4cerr << "   phitwist, deltaphi : " << fPhiTwist << " "
          << fDPhi << G4endl;
   G4cerr << "======================================================" << G4endl;
   
#endif
}

J4TwistedTubs::J4TwistedTubs(const G4String &pname,     
                                   G4double  twistedangle,    
                                   G4double  endinnerrad,  
                                   G4double  endouterrad,  
                                   G4double  halfzlen,
                                   G4int     nseg,
                                   G4double  totphi)
               :G4VSolid(pname)
{

   if (!nseg) G4cerr << "J4VTwistedTubs: invalid nseg" << G4endl;
   if (totphi == DBL_MIN || endinnerrad < DBL_MIN) {
      G4cerr << "J4VTwistedTubs: invalid totphi or endinnerrad" << G4endl;
      abort();
   }      

   G4double sinhalftwist = sin(0.5 * twistedangle);

   G4double endinnerradX = endinnerrad * sinhalftwist;
   G4double innerrad     = sqrt( endinnerrad * endinnerrad
                                 - endinnerradX * endinnerradX );

   G4double endouterradX = endouterrad * sinhalftwist;
   G4double outerrad     = sqrt( endouterrad * endouterrad
                                 - endouterradX * endouterradX );
   
   // temporary treatment!!
   fDPhi = totphi / nseg;
   SetFields(twistedangle, innerrad, outerrad, -halfzlen, halfzlen);
   CreateSurfaces();

}

J4TwistedTubs::J4TwistedTubs(const G4String &pname,
                                   G4double  twistedangle,
                                   G4double  innerrad,
                                   G4double  outerrad,
                                   G4double  negativeEndz,
                                   G4double  positiveEndz,
                                   G4double  dphi)
              :G4VSolid(pname), fDPhi(dphi)
{
   if (innerrad < DBL_MIN) {
      G4cerr << "J4VTwistedTubs: invalid innerrad" << G4endl;
      abort();
   }
                 
   SetFields(twistedangle, innerrad, outerrad, negativeEndz, positiveEndz);
   CreateSurfaces();
}

J4TwistedTubs::J4TwistedTubs(const G4String &pname,     
                                   G4double  twistedangle,    
                                   G4double  innerrad,  
                                   G4double  outerrad,  
                                   G4double  negativeEndz,
                                   G4double  positiveEndz,
                                   G4int     nseg,
                                   G4double  totphi)
               :G4VSolid(pname)
{
   if (!nseg) G4cerr << "J4VTwistedTubs: invalid nseg" << G4endl;
   if (totphi == DBL_MIN || innerrad < DBL_MIN) {
      G4cerr << "J4VTwistedTubs: invalid totphi or innerrad" << G4endl;
      abort();
   }
   
   fDPhi = totphi / nseg;
   SetFields(twistedangle, innerrad, outerrad, negativeEndz, positiveEndz);
   CreateSurfaces();
}


//=====================================================================
//* destructor --------------------------------------------------------

J4TwistedTubs::~J4TwistedTubs()
{

   if (fLowerEndcap)   delete fLowerEndcap;
   if (fUpperEndcap)   delete fUpperEndcap;
   if (fLatterTwisted) delete fLatterTwisted;
   if (fFormerTwisted) delete fFormerTwisted;
   if (fInnerHype)     delete fInnerHype;
   if (fOuterHype)     delete fOuterHype;

}

//=====================================================================
//* ComputeDimensions -------------------------------------------------

 void J4TwistedTubs::ComputeDimensions(G4VPVParameterisation* p,
                              const G4int n,
                              const G4VPhysicalVolume* pRep)
{
    G4cerr << "J4TwistedTubs::ComputeDimensions: J4TwistedTubs does not "
    << "support Parameterisation. abort. " << G4endl;
    abort();
}


//=====================================================================
//* CalculateExtent ---------------------------------------------------

G4bool J4TwistedTubs::CalculateExtent( const EAxis              axis,
                                       const G4VoxelLimits     &voxelLimit,
                                       const G4AffineTransform &transform,
                                             G4double          &min,
                                             G4double          &max ) const
{

  G4SolidExtentList  extentList( axis, voxelLimit );
  G4double maxEndOuterRad = (fEndOuterRadius[0] > fEndOuterRadius[1] ?
                             fEndOuterRadius[0] : fEndOuterRadius[1]);
  G4double maxEndInnerRad = (fEndInnerRadius[0] > fEndInnerRadius[1] ?
                             fEndInnerRadius[0] : fEndInnerRadius[1]);
  G4double maxphi         = (fabs(fEndPhi[0]) > fabs(fEndPhi[1]) ?
                             fabs(fEndPhi[0]) : fabs(fEndPhi[1]));
   
  //
  // Choose phi size of our segment(s) based on constants as
  // defined in meshdefs.hh
  //
  // G4int numPhi = kMaxMeshSections;
  G4double sigPhi = 2*maxphi + fDPhi;
  G4double rFudge = 1.0/cos(0.5*sigPhi);
  G4double fudgeEndOuterRad = rFudge * maxEndOuterRad;
  
  //
  // We work around in phi building polygons along the way.
  // As a reasonable compromise between accuracy and
  // complexity (=cpu time), the following facets are chosen:
  //
  //   1. If fOuterRadius/maxEndOuterRad > 0.95, approximate
  //      the outer surface as a cylinder, and use one
  //      rectangular polygon (0-1) to build its mesh.
  //
  //      Otherwise, use two trapazoidal polygons that 
  //      meet at z = 0 (0-4-1)
  //
  //   2. If there is no inner surface, then use one
  //      polygon for each entire endcap.  (0) and (1)
  //
  //      Otherwise, use a trapazoidal polygon for each
  //      phi segment of each endcap.    (0-2) and (1-3)
  //
  //   3. For the inner surface, if fInnerRadius/maxEndInnerRad > 0.95,
  //      approximate the inner surface as a cylinder of
  //      radius fInnerRadius and use one rectangular polygon
  //      to build each phi segment of its mesh.   (2-3)
  //
  //      Otherwise, use one rectangular polygon centered
  //      at z = 0 (5-6) and two connecting trapazoidal polygons
  //      for each phi segment (2-5) and (3-6).
  //

  G4bool splitOuter = (fOuterRadius/maxEndOuterRad < 0.95);
  G4bool splitInner = (fInnerRadius/maxEndInnerRad < 0.95);
  
  //
  // Vertex assignments (v and w arrays)
  // [0] and [1] are mandatory
  // the rest are optional
  //
  //     +                     -
  //      [0]------[4]------[1]      <--- outer radius
  //       |                 |       
  //       |                 |       
  //      [2]---[5]---[6]---[3]      <--- inner radius
  //


  G4ClippablePolygon endPoly1, endPoly2;
  
  G4double phimax   = maxphi + 0.5*fDPhi;
  G4double phimin   = - phimax;

  G4ThreeVector v0, v1, v2, v3, v4, v5, v6;   // -ve phi verticies for polygon
  G4ThreeVector w0, w1, w2, w3, w4, w5, w6;   // +ve phi verticies for polygon

  //
  // decide verticies of -ve phi boundary
  //
  
  G4double cosPhi = cos(phimin);
  G4double sinPhi = sin(phimin);

  // Outer hyperbolic surface  

  v0 = transform.TransformPoint( 
       G4ThreeVector(fudgeEndOuterRad * cosPhi, fudgeEndOuterRad * sinPhi, 
                     + fZHalfLength));
  v1 = transform.TransformPoint( 
       G4ThreeVector(fudgeEndOuterRad * cosPhi, fudgeEndOuterRad * sinPhi, 
                     - fZHalfLength));
  if (splitOuter) {
     v4 = transform.TransformPoint(
          G4ThreeVector(fudgeEndOuterRad * cosPhi, fudgeEndOuterRad * sinPhi, 0));
  }
  
  // Inner hyperbolic surface  

  G4double zInnerSplit = 0.;
  if (splitInner) {
  
     v2 = transform.TransformPoint( 
          G4ThreeVector(maxEndInnerRad * cosPhi, maxEndInnerRad * sinPhi, 
                        + fZHalfLength));
     v3 = transform.TransformPoint( 
          G4ThreeVector(maxEndInnerRad * cosPhi, maxEndInnerRad * sinPhi, 
                        - fZHalfLength));
      
     // Find intersection of tangential line of inner
     // surface at z = fZHalfLength and line r=fInnerRadius.
     G4double dr = fZHalfLength * fTanInnerStereo2;
     G4double dz = maxEndInnerRad;
     zInnerSplit = fZHalfLength + (fInnerRadius - maxEndInnerRad) * dz / dr;

     // Build associated vertices
     v5 = transform.TransformPoint( 
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi, 
                        + zInnerSplit));
     v6 = transform.TransformPoint( 
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi, 
                        - zInnerSplit));
  } else {
  
     v2 = transform.TransformPoint(
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi, 
                        + fZHalfLength));
     v3 = transform.TransformPoint(
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi, 
                        - fZHalfLength));
  }
    
  
  //
  // decide verticies of +ve phi boundary
  // 
  
  cosPhi = cos(phimax);
  sinPhi = sin(phimax);
  
  // Outer hyperbolic surface  
  
  w0 = transform.TransformPoint(
       G4ThreeVector(fudgeEndOuterRad * cosPhi, fudgeEndOuterRad * sinPhi,
                     + fZHalfLength));
  w1 = transform.TransformPoint(
       G4ThreeVector(fudgeEndOuterRad * cosPhi, fudgeEndOuterRad * sinPhi,
                     - fZHalfLength));
  if (splitOuter) {
     G4double r = rFudge*fOuterRadius;
     
     w4 = transform.TransformPoint(G4ThreeVector( r*cosPhi, r*sinPhi, 0 ));
      
     AddPolyToExtent( v0, v4, w4, w0, voxelLimit, axis, extentList );
     AddPolyToExtent( v4, v1, w1, w4, voxelLimit, axis, extentList );
  } else {
     AddPolyToExtent( v0, v1, w1, w0, voxelLimit, axis, extentList );
  }
  
  // Inner hyperbolic surface
  
  if (splitInner) {
  
     w2 = transform.TransformPoint(
          G4ThreeVector(maxEndInnerRad * cosPhi, maxEndInnerRad * sinPhi, 
                        + fZHalfLength));
     w3 = transform.TransformPoint(
          G4ThreeVector(maxEndInnerRad * cosPhi, maxEndInnerRad * sinPhi, 
                        - fZHalfLength));
          
     w5 = transform.TransformPoint(
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi,
                        + zInnerSplit));
     w6 = transform.TransformPoint(
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi,
                        - zInnerSplit));
                                   
     AddPolyToExtent( v3, v6, w6, w3, voxelLimit, axis, extentList );
     AddPolyToExtent( v6, v5, w5, w6, voxelLimit, axis, extentList );
     AddPolyToExtent( v5, v2, w2, w5, voxelLimit, axis, extentList );
     
  } else {
     w2 = transform.TransformPoint(
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi,
                        + fZHalfLength));
     w3 = transform.TransformPoint(
          G4ThreeVector(fInnerRadius * cosPhi, fInnerRadius * sinPhi,
                        - fZHalfLength));

     AddPolyToExtent( v3, v2, w2, w3, voxelLimit, axis, extentList );
  }

  //
  // Endplate segments
  //
  AddPolyToExtent( v1, v3, w3, w1, voxelLimit, axis, extentList );
  AddPolyToExtent( v2, v0, w0, w2, voxelLimit, axis, extentList );
  
  //
  // Return min/max value
  //
  return extentList.GetExtent( min, max );
}


//=====================================================================
//* AddPolyToExtent ---------------------------------------------------
void J4TwistedTubs::AddPolyToExtent( const G4ThreeVector &v0,
                                     const G4ThreeVector &v1,
                                     const G4ThreeVector &w1,
                                     const G4ThreeVector &w0,
                                     const G4VoxelLimits &voxelLimit,
                                     const EAxis          axis,
                                     G4SolidExtentList   &extentList ) 
{
    // Utility function for CalculateExtent
    //
    G4ClippablePolygon phiPoly;

    phiPoly.AddVertexInOrder( v0 );
    phiPoly.AddVertexInOrder( v1 );
    phiPoly.AddVertexInOrder( w1 );
    phiPoly.AddVertexInOrder( w0 );

    if (phiPoly.PartialClip( voxelLimit, axis )) {
        phiPoly.SetNormal( (v1-v0).cross(w0-v0).unit() );
        extentList.AddSurface( phiPoly );
    }
}


//=====================================================================
//* Inside ------------------------------------------------------------

EInside J4TwistedTubs::Inside(const G4ThreeVector& p) const
{
   static const G4double halftol = 0.5 * kRadTolerance;
#ifdef __SOLIDDEBUG__
   G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl; 
   G4cerr <<">>>>> J4TwistedTubs:Inside : Start from p : " 
          << p <<  " >>>>>> " << G4endl;  
#endif
   
   EInside  area          = ((J4HyperbolicSurface *)fOuterHype)->Inside(p);
   G4double fInnerHypeRho = ((J4HyperbolicSurface *)fInnerHype)->GetRhoAtPZ(p);
   G4double distanceToOut = p.getRho() - fInnerHypeRho;
   EInside  returnvalue; 

   if (area == kOutside) {
      returnvalue =  kOutside;
   } else if (area == kInside) {
      if (distanceToOut >= halftol)  {
         returnvalue = kInside;
      } else if (distanceToOut <= -halftol) {
         returnvalue =  kOutside;
      } else {
         returnvalue =  kSurface;
      }
   } else {                           // area == kSurface
      if (distanceToOut >= halftol)  {
         returnvalue =  kSurface;
      } else if (distanceToOut <= -halftol) {
         returnvalue =  kOutside;
      } else {
         returnvalue =  kSurface;
      }
   }

#ifdef __SOLIDDEBUG__ 
   G4cerr <<">>>>> J4TwistedTubs:Inside(p) : >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl;
   G4cerr <<"   area from HyperbolicSurface::Inside(p)   : " << area << G4endl;
   G4cerr <<"   inside(0:kOutside, 1:kSurface, 2:kInside : " << returnvalue << G4endl;
   G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
#endif   

   return returnvalue;

}

//=====================================================================
//* SurfaceNormal -----------------------------------------------------

G4ThreeVector J4TwistedTubs::SurfaceNormal( const G4ThreeVector& p) const
{
   //
   // return the normal unit vector to the Hyperbolical Surface at a point 
   // p on (or nearly on) the surface
   //
   //
   // Which of the three or four surfaces are we closest to?
   //
   // Initialize
#ifdef __SOLIDDEBUG__
   G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl; 
   G4cerr <<">>>>> J4TwistedTubs:SurfaceNormal : Start from p : " 
          << p <<  " >>>>>> " << G4endl;  
#endif

   G4double      distance = kInfinity;

   J4VSurface *surfaces[6];
   surfaces[0] = fLatterTwisted;
   surfaces[1] = fFormerTwisted;
   surfaces[2] = fInnerHype;
   surfaces[3] = fOuterHype;
   surfaces[4] = fLowerEndcap;
   surfaces[5] = fUpperEndcap;

   G4ThreeVector xx;
   G4ThreeVector bestxx;
   G4int i;
   G4int besti = -1;
   for (i=0; i< 6; i++) {
      G4double tmpdistance = surfaces[i]->DistanceTo(p, xx);
      if (tmpdistance < distance) {
         distance = tmpdistance;
         bestxx = xx;
         besti = i; 
      }
   }

   G4ThreeVector normal = surfaces[besti]->GetNormal(bestxx, TRUE);

#ifdef __SOLIDDEBUG__
   if (besti < 0) {
      G4cerr <<">>>>> J4TwistedTubs:SurfaceNormal(p) : last winner >>>>>>>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   No winner!  : " << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   } else {
      G4cerr <<">>>>> J4TwistedTubs:SurfaceNormal(p) : last winner >>>>>>>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   NAME        : " << surfaces[besti]->GetName() << G4endl;
      G4cerr <<"   bestxx      : " << bestxx << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<"   normal      : " << normal << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   }
#endif

   return normal;
   
}

//=====================================================================
//* DistanceToIn (p, v) -----------------------------------------------

G4double J4TwistedTubs::DistanceToIn (const G4ThreeVector& p,
                                      const G4ThreeVector& v ) const
{

   // The function returns kInfinity if no intersection or just grazing within tolerance.

#ifdef __SOLIDDEBUG__
   G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl; 
   G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p,v) : Start from p, v : " 
          << p << " , "  
          << v << " >>>>> " << G4endl;  
#endif
   
   // Initialize
   G4double      distance = kInfinity;   
   
   // If p is outside endcaps, check intersection on endcaps;
   if (p.z() > fEndZ[1] || p.z() < fEndZ[0]) {
      if (p.z()*v.z() >= 0) {
#ifdef __SOLIDDEBUG__
         G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p,v) : last winner >>>>>>>>>>>>>>>> " << G4endl;
         G4cerr <<"   No winner!  : " << G4endl;
         G4cerr <<"   bestdist    : " << distance << G4endl;
         G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
#endif
         return kInfinity;
      }

      J4VSurface *endcap = (p.z() < fEndZ[0] ? fLowerEndcap : fUpperEndcap);
      G4ThreeVector xx(0,0,0);
      distance = endcap->DistanceToIn(p, v, xx);
      if (distance != kInfinity) {
         // intersection is on endcap.
#ifdef __SOLIDDEBUG__
         G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p,v) : last winner >>>>>>>>>>>>>>>> " << G4endl;
         G4cerr <<"   NAME        : " << endcap->GetName() << G4endl;
         G4cerr <<"   bestxx      : " << xx << G4endl;
         G4cerr <<"   bestdist    : " << distance << G4endl;
         G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
#endif
         return distance;
      }
   }  // endcaps have been treated.


   // find intersections and choose nearest one.
   J4VSurface *surfaces[4];
   surfaces[0] = fLatterTwisted;
   surfaces[1] = fFormerTwisted;
   surfaces[2] = fInnerHype;
   surfaces[3] = fOuterHype;

   G4ThreeVector xx;
   G4ThreeVector bestxx;
   G4int i;
   G4int besti = -1;
   for (i=0; i< 4; i++) {
      G4double tmpdistance = surfaces[i]->DistanceToIn(p, v, xx);
      if (tmpdistance < distance) {
         distance = tmpdistance;
         bestxx = xx;
         besti = i;
      }
   }

#ifdef __SOLIDDEBUG__
   if (besti < 0) {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p,v) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   No winner!  : " << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   } else {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p,v) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   NAME        : " << surfaces[besti]->GetName() << G4endl;
      G4cerr <<"   bestxx      : " << bestxx << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   }
#endif

   return distance;
   
}
 
//=====================================================================
//* DistanceToIn (p) --------------------------------------------------

G4double J4TwistedTubs::DistanceToIn (const G4ThreeVector& p) const
{

   // Initialize
   G4double      distance = kInfinity;   
#ifdef __SOLIDDEBUG__  
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl; 
      G4cerr << ">>>>> J4TwistedTubs::DistanceToIn(p): start from p : "
             <<  p << " >>>>> " << G4endl;
#endif

   // If p is outside endcaps, check intersection on endcaps;
   if (p.z() > fEndZ[1] || p.z() < fEndZ[0]) {

      J4VSurface *endcap = (p.z() < 0 ? fLowerEndcap : fUpperEndcap);
      G4ThreeVector xx(0,0,0);
      distance = endcap->DistanceTo(p, xx);
      if (distance != kInfinity) {
         // intersection is on endcap.
         G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p) : last winner >>>>>>>>>>>>>>>> " << G4endl;
         G4cerr <<"   NAME        : " << endcap->GetName() << G4endl;
         G4cerr <<"   bestxx      : " << xx << G4endl;
         G4cerr <<"   bestdist    : " << distance << G4endl;
         G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
         return distance;
      }
   }  // endcaps have been treated.

       
   // find intersections and choose nearest one.
   J4VSurface *surfaces[4];
   surfaces[0] = fLatterTwisted;
   surfaces[1] = fFormerTwisted;
   surfaces[2] = fInnerHype;
   surfaces[3] = fOuterHype;

   G4int i;
   G4int besti = -1;
   G4ThreeVector xx;
   G4ThreeVector bestxx;
   for (i=0; i< 4; i++) {
      G4double tmpdistance = surfaces[i]->DistanceTo(p, xx);
      if (tmpdistance < distance)  {
         distance = tmpdistance;
         bestxx = xx;
         besti = i;
      }
   }

#ifdef __SOLIDDEBUG__
   if (besti < 0) {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   No winner!  : " << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   } else {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToIn(p) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   NAME        : " << surfaces[besti]->GetName() << G4endl;
      G4cerr <<"   bestxx      : " << bestxx << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   }
#endif

   return distance;
   
}

//=====================================================================
//* DistanceToOut (p, v) ----------------------------------------------

G4double J4TwistedTubs::DistanceToOut( const G4ThreeVector& p,
                                       const G4ThreeVector& v,
                                       const G4bool calcNorm,
                                       G4bool *validNorm, G4ThreeVector *norm ) const
{
   //
   // Calculate distance to surface of shape from `inside', allowing for tolerance
   //
#ifdef __SOLIDDEBUG__
   G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl; 
   G4cerr <<">>>>> J4TwistedTubs:DistanceToOut(p,v) : Start from p, v : " 
          << p << " , "  
          << v << " >>>>> " << G4endl;  
#endif
   
   // Initialize
   G4double      distance = kInfinity;
       
   // find intersections and choose nearest one.
   J4VSurface *surfaces[6];
   surfaces[0] = fLatterTwisted;
   surfaces[1] = fFormerTwisted;
   surfaces[2] = fInnerHype;
   surfaces[3] = fOuterHype;
   surfaces[4] = fLowerEndcap;
   surfaces[5] = fUpperEndcap;
   
   G4int i;
   G4int besti = -1;
   G4ThreeVector xx;
   G4ThreeVector bestxx;
   for (i=0; i< 6; i++) {
      G4double tmpdistance = surfaces[i]->DistanceToOut(p, v, xx);
      if (tmpdistance < distance) {
         distance = tmpdistance;
         bestxx = xx; 
         besti = i;
      }
   }

   if (calcNorm) {
      if (besti != -1) {
         *norm = (surfaces[besti]->GetNormal(p, TRUE));
         *validNorm = (besti < 4 ? FALSE : TRUE);
      }
   }

#ifdef __SOLIDDEBUG__
   if (besti < 0) {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToOut(p,v) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   No winner!  : " << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   } else {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToOut(p,v) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   NAME        : " << surfaces[besti]->GetName() << G4endl;
      G4cerr <<"   bestxx      : " << bestxx << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   }
#endif

   return distance;
       
}


//=====================================================================
//* DistanceToOut (p) ----------------------------------------------

G4double J4TwistedTubs::DistanceToOut( const G4ThreeVector& p ) const
{
   //
   // Calculate distance to surface of shape from `inside', allowing for tolerance
   //
#ifdef __SOLIDDEBUG__  
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << G4endl; 
      G4cerr << ">>>>> J4TwistedTubs::DistanceToOut(p): start from p : "
             <<  p << " >>>>> " << G4endl;
#endif
   
   // Initialize
   G4double      distance = kInfinity;
   
   // find intersections and choose nearest one.
   J4VSurface *surfaces[6];
   surfaces[0] = fLatterTwisted;
   surfaces[1] = fFormerTwisted;
   surfaces[2] = fInnerHype;
   surfaces[3] = fOuterHype;
   surfaces[4] = fLowerEndcap;
   surfaces[5] = fUpperEndcap;

   G4int i;
   G4int besti = -1;
   G4ThreeVector xx;
   G4ThreeVector bestxx;
   for (i=0; i< 6; i++) {
      G4double tmpdistance = surfaces[i]->DistanceTo(p, xx);
      if (tmpdistance < distance) {
         distance = tmpdistance;
         bestxx = xx;
         besti = i;
      }
   }

#ifdef __SOLIDDEBUG__
   if (besti < 0) {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToOut(p) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   No winner!  : " << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   } else {
      G4cerr <<">>>>> J4TwistedTubs:DistanceToOut(p) : last winner >>>>>>>>>>>>>>>> " << G4endl;
      G4cerr <<"   NAME        : " << surfaces[besti]->GetName() << G4endl;
      G4cerr <<"   bestxx      : " << bestxx << G4endl;
      G4cerr <<"   bestdist    : " << distance << G4endl;
      G4cerr <<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << G4endl;
   }
#endif

   return distance;

}

//=====================================================================
//* DiscribeYourselfTo ------------------------------------------------

void J4TwistedTubs::DescribeYourselfTo (G4VGraphicsScene& scene) const 
{
  scene.AddThis (*this);
}

//=====================================================================
//* GetExtent ---------------------------------------------------------

G4VisExtent J4TwistedTubs::GetExtent() const 
{
  // Define the sides of the box into which the G4Tubs instance would fit.
  G4double maxEndOuterRad = (fEndOuterRadius[0] > fEndOuterRadius[1] ? 0 : 1);
  return G4VisExtent( -maxEndOuterRad, maxEndOuterRad, 
                      -maxEndOuterRad, maxEndOuterRad, 
                      -fZHalfLength, fZHalfLength );
}

//=====================================================================
//* CreatePolyhedron --------------------------------------------------

G4Polyhedron* J4TwistedTubs::CreatePolyhedron () const 
{
   //  return new G4PolyhedronHype (fRMin, fRMax, fDz, fSPhi, fDPhi);
   return 0;
}

//=====================================================================
//* CreateNUBS --------------------------------------------------------
G4NURBS* J4TwistedTubs::CreateNURBS () const 
{
   G4double maxEndOuterRad = (fEndOuterRadius[0] > fEndOuterRadius[1] ? 0 : 1);
   G4double maxEndInnerRad = (fEndOuterRadius[0] > fEndOuterRadius[1] ? 0 : 1);
   return new G4NURBStube(maxEndInnerRad, maxEndOuterRad, fZHalfLength); 
   // Tube for now!!!
}

//=====================================================================
//* CreateSurfaces ----------------------------------------------------
void J4TwistedTubs::CreateSurfaces() 
{
   
   // create 6 surfaces of TwistedTub.
   G4ThreeVector x0(0, 0, fEndZ[0]);
   G4ThreeVector n (0, 0, -1);
   fLowerEndcap = new J4FlatSurface("LowerEndcap",this, -1);
   fUpperEndcap = new J4FlatSurface("UpperEndcap",this, 1);

   G4RotationMatrix    rotHalfDPhi;
   rotHalfDPhi.rotateZ(0.5*fDPhi);
   fLatterTwisted = new J4TwistedSurface("LatterTwisted", this, 1);
   fFormerTwisted = new J4TwistedSurface("FormerTwisted", this, -1);
   fInnerHype     = new J4HyperbolicSurface("InnerHype", this, -1);
   fOuterHype     = new J4HyperbolicSurface("OuterHype", this, 1);

#ifdef __SOLIDDEBUG__
   fLowerEndcap->DebugPrint();
   fUpperEndcap->DebugPrint();
   fLatterTwisted->DebugPrint();
   fFormerTwisted->DebugPrint();
   fInnerHype->DebugPrint();
   fOuterHype->DebugPrint();
#endif

   // set neighbour surfaces.
   fLowerEndcap->SetNeighbours(fInnerHype, fLatterTwisted, fOuterHype, fFormerTwisted);
   fUpperEndcap->SetNeighbours(fInnerHype, fLatterTwisted, fOuterHype, fFormerTwisted);
   fLatterTwisted->SetNeighbours(fInnerHype, fLowerEndcap, fOuterHype, fUpperEndcap);
   fFormerTwisted->SetNeighbours(fInnerHype, fLowerEndcap, fOuterHype, fUpperEndcap);
   fInnerHype->SetNeighbours(fLatterTwisted, fLowerEndcap, fFormerTwisted, fUpperEndcap);
   fOuterHype->SetNeighbours(fLatterTwisted, fLowerEndcap, fFormerTwisted, fUpperEndcap);
   
}
