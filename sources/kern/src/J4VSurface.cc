 /*
 *  J4VSurface.cc
 *  
 *
 *  Created by Kotoyo Hoshina on Thu Aug 01 2002.
 *  Copyright (c) 2001 __MyCompanyName__. All rights reserved.
 *
 */
#include <iomanip.h>
#include "J4VSurface.hh"

//#define __SOLIDDEBUG__

const G4int  J4VSurface::kOutside        = 0x00000000;
const G4int  J4VSurface::kInside         = 0x10000000;
const G4int  J4VSurface::kBoundary       = 0x20000000;
const G4int  J4VSurface::kCorner         = 0x40000000;
const G4int  J4VSurface::kCorner0Min1Min = 0x40000101; 
const G4int  J4VSurface::kCorner0Max1Min = 0x40000201;
const G4int  J4VSurface::kCorner0Max1Max = 0x40000202; 
const G4int  J4VSurface::kCorner0Min1Max = 0x40000102; 
const G4int  J4VSurface::kAxisMin        = 0x00000101; 
const G4int  J4VSurface::kAxisMax        = 0x00000202; 
const G4int  J4VSurface::kAxisX          = 0x00000404;
const G4int  J4VSurface::kAxisY          = 0x00000808;
const G4int  J4VSurface::kAxisZ          = 0x00000C0C;
const G4int  J4VSurface::kAxisRho        = 0x00001010;
const G4int  J4VSurface::kAxisPhi        = 0x00001414;

// mask
const G4int  J4VSurface::kAxis0          = 0x0000FF00;
const G4int  J4VSurface::kAxis1          = 0x000000FF;
const G4int  J4VSurface::kSizeMask       = 0x00000303;
const G4int  J4VSurface::kAxisMask       = 0x0000FCFC;
const G4int  J4VSurface::kAreaMask       = 0XF0000000;

//=====================================================================
//* constructor -------------------------------------------------------

J4VSurface::J4VSurface(const G4String &name, G4VSolid *solid)
           :fName(name), fSolid(solid)
{

   fAxis[0]    = kUndefined;
   fAxis[1]    = kUndefined;
   fAxisMin[0] = kInfinity;
   fAxisMin[1] = kInfinity;
   fAxisMax[0] = kInfinity;
   fAxisMax[1] = kInfinity;
   fHandedness = 1;

   G4int i;
   for (i=0; i<4; i++) {
      fCorners[i].set(kInfinity, kInfinity, kInfinity);
      fNeighbours[i] = 0;
   }

   fCurrentNormal.p.set(kInfinity, kInfinity, kInfinity);
   
   fAmIOnLeftSide.me.set(kInfinity, kInfinity, kInfinity);
   fAmIOnLeftSide.vec.set(kInfinity, kInfinity, kInfinity);
}

J4VSurface::J4VSurface(const G4String         &name,
                       const G4RotationMatrix &rot,
                       const G4ThreeVector    &tlate,
                             G4int             handedness,
                       const EAxis             axis0 ,
                       const EAxis             axis1 ,
                             G4double          axis0min,
                             G4double          axis1min,
                             G4double          axis0max,
                             G4double          axis1max )
           :fName(name)
{
   fAxis[0]    = axis0;
   fAxis[1]    = axis1;
   fAxisMin[0] = axis0min;
   fAxisMin[1] = axis1min;
   fAxisMax[0] = axis0max;
   fAxisMax[1] = axis1max;
   fHandedness = handedness;
   fRot        = rot;
   fTrans      = tlate;

   G4int i;
   for (i=0; i<4; i++) {
      fCorners[i].set(kInfinity, kInfinity, kInfinity);
      fNeighbours[i] = 0;
   }

   fCurrentNormal.p.set(kInfinity, kInfinity, kInfinity);
   
   fAmIOnLeftSide.me.set(kInfinity, kInfinity, kInfinity);
   fAmIOnLeftSide.vec.set(kInfinity, kInfinity, kInfinity);
}

//=====================================================================
//* destructor --------------------------------------------------------
J4VSurface::~J4VSurface()
{

}

//=====================================================================
//* AmIOnLeftSide -----------------------------------------------------
G4int J4VSurface::AmIOnLeftSide(const G4ThreeVector &me, 
                                const G4ThreeVector &vec,
                                G4bool        withtol) 
{
   // AmIOnLeftSide returns phi-location of "me"
   // (phi relation between me and vec projected on z=0 plane).
   // If "me" is on -ve-phi-side of "vec", it returns 1.
   // On the other hand, if "me" is on +ve-phi-side of "vec",
   // it returns -1.
   // (The return value replesents z-coordinate of normal vector
   //  of me.cross(vec).)
   // If me is on boundary of vec, return 0.

   static G4RotationMatrix unitrot;  // unit matrix
   static const G4RotationMatrix rottol    = unitrot.rotateZ(0.5*kAngTolerance);
   static const G4RotationMatrix invrottol = unitrot.rotateZ(-1.*kAngTolerance);

   if (fAmIOnLeftSide.me == me 
       && fAmIOnLeftSide.vec == vec
       && fAmIOnLeftSide.withTol == withtol) {
      return fAmIOnLeftSide.amIOnLeftSide;
   }
   
   fAmIOnLeftSide.me      = me;
   fAmIOnLeftSide.vec     = vec;
   fAmIOnLeftSide.withTol = withtol;
   
   G4ThreeVector met   = (G4ThreeVector(me.x(), me.y(), 0.)).unit();
   G4ThreeVector vect  = (G4ThreeVector(vec.x(), vec.y(), 0.)).unit();
   
   G4ThreeVector ivect = invrottol * vect;
   G4ThreeVector rvect = rottol * vect;

   G4double metcrossvect = met.x() * vect.y() - met.y() * vect.x();
   
   if (withtol) {
      if (met.x() * ivect.y() - met.y() * ivect.x() > 0 && 
          metcrossvect >= 0)  {
         fAmIOnLeftSide.amIOnLeftSide = 1;
      } else if (met.x() * rvect.y() - met.y() * rvect.x() < 0 &&
                 metcrossvect <= 0)  {
         fAmIOnLeftSide.amIOnLeftSide = -1;
      } else {
         fAmIOnLeftSide.amIOnLeftSide = 0;
      }
   } else {
      if (metcrossvect > 0) {    
         fAmIOnLeftSide.amIOnLeftSide = 1;
      } else if (metcrossvect < 0 ) {
         fAmIOnLeftSide.amIOnLeftSide = -1;
      } else {       
         fAmIOnLeftSide.amIOnLeftSide = 0;
      }
   }

#ifdef __SOLIDDEBUG__
   J4cerr << "         === J4VSurface::AmIOnLeftSide ================"
          << J4endl;
   J4cerr << "         //# NAME , returncode  : " << fName << " " 
                       << fAmIOnLeftSide.amIOnLeftSide <<  J4endl;
   J4cerr << "         //# me, vec    : " << std::setprecision(14) << me 
                                          << " " << vec  << J4endl;
   J4cerr << "         //# met, vect  : " << met << " " << vect  << J4endl;
   J4cerr << "         //# ivec, rvec : " << ivect << " " << rvect << J4endl;
   J4cerr << "         //# met x vect : " << metcrossvect << J4endl;
   J4cerr << "         //# met x ivec : " << met.cross(ivect) << J4endl;
   J4cerr << "         //# met x rvec : " << met.cross(rvect) << J4endl;
   J4cerr << "         =============================================="
          << J4endl;
#endif

   return fAmIOnLeftSide.amIOnLeftSide;

}

//=====================================================================
//* DistanceToBoundary ------------------------------------------------
G4double J4VSurface::DistanceToBoundary(G4int areacode,
                                        G4ThreeVector &xx,
                                        const G4ThreeVector &p) 
{
   // DistanceToBoundary 
   //
   // return distance to nearest boundary from arbitrary point p 
   // in local coodinate.
   // Argument areacode must be one of them:
   // kAxis0 & kAxisMin, kAxis0 & kAxisMax,
   // kAxis1 & kAxisMin, kAxis1 & kAxisMax.
   //

   G4ThreeVector d;    // direction vector of the boundary
   G4ThreeVector x0;   // reference point of the boundary
   G4double      dist;
   G4int         boundarytype;

   if (IsAxis0(areacode) && IsAxis1(areacode)) {
      J4cerr << "J4VSurface::DistanceToBoundary: You are in the "
      << "corner area. This function returns a direction vector of "
      << "a boundary line. areacode = " << areacode << J4endl;
      abort();
   } else if (IsAxis0(areacode) || IsAxis1(areacode)) {
      GetBoundaryParameters(areacode, d, x0, boundarytype);
      if (boundarytype == kAxisPhi) {
         G4double t = x0.getRho() / p.getRho();
         xx.set(t*p.x(), t*p.y(), x0.z());
         dist = (xx - p).mag();
      } else { 
         // linear boundary
         // kAxisX, kAxisY, kAxisZ, kAxisRho
         dist = DistanceToLine(p, x0, d, xx);
      }
   } else {
      J4cerr << "J4VSurface::DistanceToBoundary: bad areacode of "
      << "boundary. areacode = " << areacode << J4endl;
      abort();
   }

   return dist;
   
}


//=====================================================================
//* DistanceToIn ------------------------------------------------------
G4double J4VSurface::DistanceToIn(const G4ThreeVector &gp,
                                  const G4ThreeVector &gv,
                                        G4ThreeVector &gxxbest)
{
#ifdef __SOLIDDEBUG__
   J4cerr <<"   ..... J4VSurface:DistanceToIn(p,v) Start ....." << J4endl;
   J4cerr <<"      Name : " << fName << J4endl;
   J4cerr <<"      gp   : " << gp << J4endl;
   J4cerr <<"      gv   : " <<  gv << J4endl;
   J4cerr <<"   .............................................." << J4endl;
#endif
   
   G4ThreeVector gxx[2];
   G4double      distance[2]    = {kInfinity, kInfinity};
   G4int         areacode[2]    = {kOutside, kOutside};
   G4bool        isvalid[2]     = {FALSE, FALSE};
   G4double      bestdistance   = kInfinity;
   G4int         besti          = -1;  
   G4ThreeVector bestgxx(kInfinity, kInfinity, kInfinity);

   G4int         nxx = DistanceToSurface(gp, gv, gxx, distance, areacode, 
                                         isvalid, kValidateWithTol);

   for (G4int i=0; i< nxx; i++) {

      // skip this intersection if:
      //   - invalid intersection
      //   - particle goes outword the surface

      if (!isvalid[i]) {
         // xx[i] is kOutside or distance[i] < 0
         continue;      
      }

      G4ThreeVector normal = GetNormal(gxx[i], TRUE);

      if ((normal * gv) >= 0) {

#ifdef __SOLIDDEBUG__
         J4cerr << "   J4VSurface:DistanceToIn(p,v): "
                << "particle goes outword the surface " << J4endl;
#endif 
         continue; 
      }
      
      //
      // accept this intersection if the intersection is inside.
      //

      if (IsInside(areacode[i])) {
         if (distance[i] < bestdistance) {
            bestdistance = distance[i];
            bestgxx = gxx[i];
            besti   = i;

#ifdef __SOLIDDEBUG__
            J4cerr << "   J4VSurface:DistanceToIn(p,v): "
                   << " areacode kInside name, distance = "
                   << fName <<  " "<< bestdistance << J4endl;
#endif 
         }

      //
      // else, the intersection is on boundary or corner.
      //

      } else {

         J4VSurface *neighbours[2];
         G4bool      isaccepted[2] = {FALSE, FALSE};
         G4int       nneighbours   = GetNeighbours(areacode[i], neighbours);
            
         for (G4int j=0; j< nneighbours; j++) {
            // if on corner, nneighbours = 2.
            // if on boundary, nneighbours = 1.
            G4ThreeVector tmpgxx[2];
            G4double      tmpdist[2]     = {kInfinity, kInfinity};
            G4int         tmpareacode[2] = {kOutside, kOutside};
            G4bool        tmpisvalid[2]  = {FALSE, FALSE};
                  
            G4int tmpnxx = neighbours[j]->DistanceToSurface(
                                          gp, gv, tmpgxx, tmpdist,
                                          tmpareacode, tmpisvalid,
                                          kValidateWithTol);
            G4ThreeVector neighbournormal;

            for (G4int k=0; k< tmpnxx; k++) {

               //  
               // if tmpxx[k] is valid && kInside, the final winner must
               // be neighbour surface. return kInfinity. 
               // else , choose tmpxx on same boundary of xx, then check normal 
               //  

               if (IsInside(tmpareacode[k])) {

#ifdef __SOLIDDEBUG__
                  J4cerr << "   J4VSurface:DistanceToIn(p,v): "
                         << " intersection "<< tmpgxx[k] 
                         << " is inside of neighbour surface of " << fName 
                         << " . return kInfinity." << J4endl;
                  J4cerr <<"   ..... J4VSurface:DistanceToIn(p,v) : return .." << J4endl;
                  J4cerr <<"      No intersections " << J4endl; 
                  J4cerr <<"      NAME : " << fName << J4endl; 
                  J4cerr <<"   .............................................." << J4endl;
#endif 
                  if (tmpisvalid[k])  return kInfinity;
                  continue;

               //  
               // if tmpxx[k] is valid && kInside, the final winner must
               // be neighbour surface. return .  
               //

               } else if (IsSameBoundary(this,areacode[i], neighbours[j], tmpareacode[k])) { 
                  // tmpxx[k] is same boundary (or corner) of xx.
                 
                  neighbournormal = neighbours[j]->GetNormal(tmpgxx[k], TRUE);
                  if (neighbournormal * gv < 0) isaccepted[1] = TRUE;
               }
            } 

            // if nneighbours = 1, chabge isaccepted[1] before exiting neighboursurface loop.  

            if (nneighbours == 1) isaccepted[1] = TRUE;

         } // neighboursurface loop end

         // now, we can accept xx intersection

         if (isaccepted[0] == TRUE && isaccepted[1] == TRUE) {
            if (distance[i] < bestdistance) {
                bestdistance = distance[i];
                gxxbest = gxx[i];
                besti   = i;
#ifdef __SOLIDDEBUG__
               J4cerr << "   J4VSurface:DistanceToIn(p,v): "
                      << " areacode kBoundary & kBoundary distance = "
                      << fName  << " " << distance[i] << J4endl;
#endif 
            }
         }

      } // else end
   } // intersection loop end

   gxxbest = bestgxx;

#ifdef __SOLIDDEBUG__
   if (besti < 0) {
      J4cerr <<"   ..... J4VSurface:DistanceToIn(p,v) : return .." << J4endl;
      J4cerr <<"      No intersections " << J4endl; 
      J4cerr <<"      NAME : " << fName << J4endl; 
      J4cerr <<"   .............................................." << J4endl;
   } else {
      J4cerr <<"   ..... J4VSurface:DistanceToIn(p,v) : return .." << J4endl;
      J4cerr <<"      NAME, i  : " << fName << " , " << besti << J4endl; 
      J4cerr <<"      gxx[i]   : " << gxxbest << J4endl; 
      J4cerr <<"      bestdist : " << bestdistance << J4endl;
      J4cerr <<"   .............................................." << J4endl;
   } 
#endif

   return bestdistance;
}

//=====================================================================
//* DistanceToOut(p, v) -----------------------------------------------
G4double J4VSurface::DistanceToOut(const G4ThreeVector &gp,
                                   const G4ThreeVector &gv,
                                         G4ThreeVector &gxxbest)
{
#ifdef __SOLIDDEBUG__
   J4cerr <<"   ..... J4VSurface:DistanceToOut(p,v) Start ....." << J4endl;
   J4cerr <<"      Name : " << fName << J4endl;
   J4cerr <<"      gp   : " << gp << J4endl;
   J4cerr <<"      gv   : " <<  gv << J4endl;
   J4cerr <<"   ..............................................." << J4endl;
#endif

   G4double      distance[2]    = {kInfinity, kInfinity};
   G4int         areacode[2]    = {kOutside, kOutside};
   G4bool        isvalid [2]    = {FALSE, FALSE};
   G4ThreeVector gxx[2];
   G4int         nxx;
   G4double      bestdistance   = kInfinity;
   G4int         besti          = -1;

   nxx = DistanceToSurface(gp, gv, gxx, distance, areacode,
                           isvalid, kValidateWithTol);
   G4int i;
   for (i=0; i<nxx; i++) {
      if (!(isvalid[i])) {
         continue;
      }

      G4ThreeVector normal = GetNormal(gxx[i], TRUE);
      if (normal * gv <= 0) {
         // particle goes toword inside of solid, return kInfinity
#ifdef __SOLIDDEBUG__
          J4cerr << "   J4VSurface:DistanceToOut(p,v): normal*gv < 0, normal " 
                 << fName << " " << normal 
                 << J4endl;
#endif 
      } else {
         // gxx[i] is accepted.
         if (distance[i] < bestdistance) {
            bestdistance = distance[i];
            gxxbest = gxx[i];
            besti   = i;
         }
      } 
   }

#ifdef __SOLIDDEBUG__
   if (besti < 0) {
      J4cerr <<"   ..... J4VSurface:DistanceToOut(p,v) : return ." << J4endl;
      J4cerr <<"      No intersections   " << J4endl; 
      J4cerr <<"      NAME     : " << fName << J4endl; 
      J4cerr <<"      bestdist : " << bestdistance << J4endl;
      J4cerr <<"   .............................................." << J4endl;
   } else {
      J4cerr <<"   ..... J4VSurface:DistanceToOut(p,v) : return ." << J4endl;
      J4cerr <<"      NAME, i  : " << fName << " , " << i << J4endl; 
      J4cerr <<"      gxx[i]   : " << gxxbest << J4endl; 
      J4cerr <<"      bestdist : " << bestdistance << J4endl;
      J4cerr <<"   .............................................. " << J4endl;
   } 
#endif

   return bestdistance;
 
}

//=====================================================================
//* DistanceTo(p) -----------------------------------------------------
G4double J4VSurface::DistanceTo(const G4ThreeVector &gp,
                                      G4ThreeVector &gxxbest)
{
#ifdef __SOLIDDEBUG__
   J4cerr <<"   ..... J4VSurface:DistanceTo(p) Start ....." << J4endl;
   J4cerr <<"      Name : " << fName << J4endl;
   J4cerr <<"      gp   : " << gp << J4endl;
   J4cerr <<"   .........................................." << J4endl;
#endif
   G4double distance[2] = {kInfinity, kInfinity};
   G4int    areacode[2] = {kOutside, kOutside};
   G4ThreeVector gxx[2];
   G4int nxx;

   nxx = DistanceToSurface(gp, gxx, distance, areacode);
   gxxbest = gxx[0];

#ifdef __SOLIDDEBUG__
   J4cerr <<"   ..... J4VSurface:DistanceTo(p) : return .." << J4endl;
   J4cerr <<"      NAME     : " << fName << J4endl; 
   J4cerr <<"      gxx      : " << gxxbest << J4endl; 
   J4cerr <<"      bestdist : " << distance[0] << J4endl;
   J4cerr <<"   .........................................." << J4endl;
#endif

   return distance[0];
}

//=====================================================================
//* IsSameBoundary ----------------------------------------------------
G4bool J4VSurface::IsSameBoundary(J4VSurface *surface1, G4int areacode1,
                                  J4VSurface *surface2, G4int areacode2 ) const
{
   //
   // IsSameBoundary
   //
   // checking tool whether two boundaries on different surfaces are same or not.
   //

   G4bool testbitmode = TRUE;
   G4bool iscorner[2] = {IsCorner(areacode1, testbitmode), 
                         IsCorner(areacode2, testbitmode)};

   if (iscorner[0] && iscorner[1]) {
      // on corner 
      G4ThreeVector corner1 = 
           surface1->ComputeGlobalPoint(surface1->GetCorner(areacode1));
      G4ThreeVector corner2 = 
           surface2->ComputeGlobalPoint(surface2->GetCorner(areacode2));

      if ((corner1 - corner2).mag() < kCarTolerance) {
         return TRUE;
      } else {
         return FALSE;
      }
    
   } else if ((IsBoundary(areacode1, testbitmode) && (!iscorner[0])) &&
              (IsBoundary(areacode2, testbitmode) && (!iscorner[1]))) {
      // on boundary  
      G4ThreeVector d1, d2, ld1, ld2;
      G4ThreeVector x01, x02, lx01, lx02;
      G4int         type1, type2;
      surface1->GetBoundaryParameters(areacode1, ld1, lx01, type1);
      surface2->GetBoundaryParameters(areacode2, ld2, lx02, type2);

      x01 = surface1->ComputeGlobalPoint(lx01);
      x02 = surface2->ComputeGlobalPoint(lx02);
      d1  = surface1->ComputeGlobalDirection(ld1);
      d2  = surface2->ComputeGlobalDirection(ld2);

      if ((x01 - x02).mag() < kCarTolerance &&
          (d1 - d2).mag() < kCarTolerance) {
        return TRUE;
      } else {
        return FALSE;
      }

   } else {
      return FALSE;
   }
}

//=====================================================================
//* GetBoundaryParameters ---------------------------------------------
void J4VSurface::GetBoundaryParameters(const G4int         &areacode,
                                             G4ThreeVector &d,
                                             G4ThreeVector &x0,
                                             G4int         &boundarytype) const
{
   // areacode must be one of them:
   // kAxis0 & kAxisMin, kAxis0 & kAxisMax,
   // kAxis1 & kAxisMin, kAxis1 & kAxisMax.
   
   G4int i;
   for (i=0; i<4; i++) {
      if (fBoundaries[i].GetBoundaryParameters(areacode, d, x0,
                                               boundarytype)) {
         return;
      }
   }

   J4cerr << "   J4VSurface::GetBoundaryParameters: boundary at areacode "
      << hex << areacode << dec << " is not be registerd. abort. " << J4endl;
   abort();

}

//=====================================================================
//* GetBoundaryAtPZ ---------------------------------------------------
G4ThreeVector J4VSurface::GetBoundaryAtPZ(G4int areacode,
                                          const G4ThreeVector &p) const
{
   // areacode must be one of them:
   // kAxis0 & kAxisMin, kAxis0 & kAxisMax,
   // kAxis1 & kAxisMin, kAxis1 & kAxisMax.

   if (areacode & kAxis0 && areacode & kAxis1) {
      J4cerr << "   J4VSurface::GetBoundaryAtPZ: You are in the "
      << "corner area. This function returns a direction vector of "
      << "a boundary line. abort. areacode = " << areacode << J4endl;
      abort();
   }

   G4ThreeVector d;
   G4ThreeVector x0;
   G4int         boundarytype;
   G4bool        found = FALSE;
   
   for (G4int i=0; i<4; i++) {
      if (fBoundaries[i].GetBoundaryParameters(areacode, d, x0, 
                                                boundarytype)){
         found = TRUE;
         continue;
      }
   }

   if (!found) {
      J4cerr << "   J4VSurface::GetBoundaryAtPZ: boundary at areacode "
         << areacode << " is not be registerd. abort. " << J4endl;
      abort();
   }

   if (((boundarytype & kAxisPhi) == kAxisPhi) ||
       ((boundarytype & kAxisRho) == kAxisRho)) {
      J4cerr << "   J4VSurface::GetBoundaryAtPZ: boundary at areacode "
      << areacode << " is not a z-depended line. abort. " << J4endl;
      abort();
   }

   return ((p.z() - x0.z()) / d.z()) * d + x0;
}

//=====================================================================
//* SetCorner ---------------------------------------------------------
void J4VSurface::SetCorner(G4int areacode, G4double x, G4double y, G4double z)
{
   if ((areacode & kCorner) != kCorner){
      J4cerr << "   J4VSurface::GetCorner: area code must represents corner. "
      << "your areacode = " << areacode << J4endl;
      abort();
   }

   if ((areacode & kCorner0Min1Min) == kCorner0Min1Min) {
      fCorners[0].set(x, y, z);
   } else if ((areacode & kCorner0Max1Min) == kCorner0Max1Min) {
      fCorners[1].set(x, y, z);
   } else if ((areacode & kCorner0Max1Max) == kCorner0Max1Max) {
      fCorners[2].set(x, y, z);
   } else if ((areacode & kCorner0Min1Max) == kCorner0Min1Max) {
      fCorners[3].set(x, y, z);
   }

}

//=====================================================================
//* SetBoundaryAxis ---------------------------------------------------
void J4VSurface::GetBoundaryAxis(G4int areacode, EAxis axis[]) const
{

   if ((areacode & kBoundary) != kBoundary) {
      J4cerr << "   J4VSurface::GetBoundaryAxis: "
             << "you are not on boudary. abort." << J4endl;
      abort();
   }

   G4int i;
   for (i=0; i<2; i++) {

      G4int whichaxis;
      if (i == 0) {
         whichaxis = kAxis0;
      } else if (i == 1) {
         whichaxis = kAxis1;
      }
      
      // extracted axiscode of whichaxis
      G4int axiscode = whichaxis & kAxisMask & areacode ; 
      if (axiscode) {
         if (axiscode == (whichaxis & kAxisX)) {
            axis[i] = kXAxis;
         } else if (axiscode == (whichaxis & kAxisY)) {
            axis[i] = kYAxis;
         } else if (axiscode == (whichaxis & kAxisZ)) {
            axis[i] = kZAxis;
         } else if (axiscode == (whichaxis & kAxisRho)) {
            axis[i] = kRho;
         } else if (axiscode == (whichaxis & kAxisPhi)) {
            axis[i] = kPhi;
         } else {
            J4cerr << "   J4VSurface::GetBoundaryAxis: areacode " << areacode
            << " is not be supported. abort. " << J4endl;
            abort();
         }
      }
   }

}

//=====================================================================
//* SetBoundaryLimit --------------------------------------------------
void J4VSurface::GetBoundaryLimit(G4int areacode, G4double limit[]) const
{
   if (areacode & kCorner) {
      if (areacode & kCorner0Min1Max) {
         limit[0] = fAxisMin[0];
         limit[1] = fAxisMin[1];
      } else if (areacode & kCorner0Max1Min) {
         limit[0] = fAxisMax[0];
         limit[1] = fAxisMin[1];
      } else if (areacode & kCorner0Max1Max) {
         limit[0] = fAxisMax[0];
         limit[1] = fAxisMax[1];
      } else if (areacode & kCorner0Min1Max) {
         limit[0] = fAxisMin[0];
         limit[1] = fAxisMax[1];
      }
   } else if (areacode & kBoundary) {
      if (areacode & (kAxis0 | kAxisMin)) {
         limit[0] = fAxisMin[0];
      } else if (areacode & (kAxis1 | kAxisMin)) {
         limit[0] = fAxisMin[1];
      } else if (areacode & (kAxis0 | kAxisMax)) {
         limit[0] = fAxisMax[0];
      } else if (areacode & (kAxis1 | kAxisMax)) {
         limit[0] = fAxisMax[1];
      }
   } else {
      J4cerr << "   J4VSurface::GetBoundaryLimit: you are not on boudary. "
      << "your areacode = " << areacode << J4endl;
   }
}

//=====================================================================
//* SetBoundary --------------------------------------------------
void J4VSurface::SetBoundary(const G4int         &axiscode,
                             const G4ThreeVector &direction,
                             const G4ThreeVector &x0,
                             const G4int         &boundarytype)
{
   G4int code = (~kAxisMask) & axiscode;
   if ((code == (kAxis0 & kAxisMin)) ||
       (code == (kAxis0 & kAxisMax)) ||
       (code == (kAxis1 & kAxisMin)) ||
       (code == (kAxis1 & kAxisMax))) {

      G4int i;
      G4bool done = FALSE;
      for (i=0; i<4; i++) {
         if (fBoundaries[i].IsEmpty()) {
            fBoundaries[i].SetFields(axiscode, direction,
                                     x0, boundarytype);
            done = TRUE;
            break;
         }
      }

      if (!done) {
         J4cerr << "   J4VSurface::SetBoundary: No. of boundary exeeded 4. "
                << "abort. " << J4endl;
         abort();
      }

   } else {

      J4cerr << "   J4VSurface::SetBoundary: invalid axiscode "
             << std::hex << axiscode << std::dec
             << " . abort. " << J4endl;
      abort();
   }
}

//=====================================================================
//* DebugPrint --------------------------------------------------
void J4VSurface::DebugPrint()
{
   G4ThreeVector A = fRot * GetCorner(kCorner0Min1Min) + fTrans;
   G4ThreeVector B = fRot * GetCorner(kCorner0Max1Min) + fTrans;
   G4ThreeVector C = fRot * GetCorner(kCorner0Max1Max) + fTrans;
   G4ThreeVector D = fRot * GetCorner(kCorner0Min1Max) + fTrans;
  
   J4cerr << "/* J4VSurface::DebugPrint:---------------------------------" << J4endl;
   J4cerr << "/* NAME = " << fName << J4endl;
   J4cerr << "/* Axis = " << hex << fAxis[0] << " " << hex << fAxis[1] 
          << " (0,1,2,3,5 = kXAxis,kYAxis,kZAxis,kRho,kPhi)" << dec << J4endl;
   J4cerr << "/* BoundaryLimit(in local) fAxis0(min, max) = ("<<fAxisMin[0] 
          << ", " << fAxisMax[0] << ")" << J4endl;
   J4cerr << "/* BoundaryLimit(in local) fAxis1(min, max) = ("<<fAxisMin[1] 
          << ", " << fAxisMax[1] << ")" << J4endl;
   J4cerr << "/* Cornar point kCorner0Min1Min = " << A << J4endl;
   J4cerr << "/* Cornar point kCorner0Max1Min = " << B << J4endl;
   J4cerr << "/* Cornar point kCorner0Max1Max = " << C << J4endl;
   J4cerr << "/* Cornar point kCorner0Min1Max = " << D << J4endl;
   J4cerr << "/*---------------------------------------------------------" << J4endl;

}

                             
