// $Id$
#ifndef __J4TWISTEDTUBS__
#define __J4TWISTEDTUBS__
//*************************************************************************
//* --------------------
//* J4TWISTEDTUBS
//* --------------------
//* (Description)
//* J4TwistedTubs is a piece of twisted cylinder.
//*	A twisted cylinder which is placed along with z-axis and
//*	is separated into phi-segments should become a hyperboloid,
//*	and its each segmented piece should be tilted with a stereo angle. 
//*	J4TwistedTubs inherits J4TwistedTubs.¡¡ 
//*	It can have inner & outer surfaces as well as J4TwistedTubs, 
//*	but cannot has different stereo angles between inner 
//*	surface and outer surface.
//*	
//*     
//* (Update Record)
//*	2002/04/08  K.Hoshina	Original version.
//*************************************************************************

#include "G4VSolid.hh"
#include "G4EventManager.hh"
#include "J4FlatSurface.hh"
#include "J4TwistedSurface.hh"
#include "J4HyperbolicSurface.hh"
#include "J4PVPlacement.hh"

//#define __SOLIDDEBUG__

class G4SolidExtentList;
class G4ClippablePolygon;
class J4VComponent;


class J4TwistedTubs : public G4VSolid
{
 public:
 
  J4TwistedTubs(const G4String &pname,              // Name of instance
                      G4double  twistedangle,       // Twisted angle
                      G4double  endinnerrad,        // Inner radius at endcap 
                      G4double  endouterrad,        // Outer radius at endcap 
                      G4double  halfzlen,           // half z length 
                      G4double  dphi);              // Phi angle of a segment
                      
  J4TwistedTubs(const G4String &pname,              // Name of instance
                      G4double  twistedangle,       // Stereo angle
                      G4double  endinnerrad,        // Inner radius at endcap 
                      G4double  endouterrad,        // Outer radius at endcap 
                      G4double  halfzlen,           // half z length 
                      G4int     nseg,               // Number of segments in totalPhi
                      G4double  totphi);            // Total angle of all segments
                      
  J4TwistedTubs(const G4String &pname,              // Name of instance
                      G4double  twistedangle,       // Twisted angle
                      G4double  innerrad,           // Inner radius at z=0 
                      G4double  outerrad,           // Outer radius at z=0 
                      G4double  negativeEndz,       // -ve z endplate
                      G4double  positiveEndz,       // +ve z endplate
                      G4double  dphi);              // Phi angle of a segment

  J4TwistedTubs(const G4String &pname,              // Name of instance
                      G4double  twistedangle,       // Stereo angle
                      G4double  innerrad,           // Inner radius at z=0 
                      G4double  outerrad,           // Outer radius at z=0 
                      G4double  negativeEndz,       // -ve z endplate
                      G4double  positiveEndz,       // +ve z endplate
                      G4int     nseg,               // Number of segments in totalPhi
                      G4double  totphi);            // Total angle of all segments
                      
 // argument miss protection -------------------------------------------------
  J4TwistedTubs(const G4String &pname,              // Name of instance
                      G4double  twistedangle,       // Twisted angle
                      G4double  endinnerrad,        // Inner radius at endcap 
                      G4double  endouterrad,        // Outer radius at endcap 
                      G4double  halfzlen,           // half z length 
                      G4int     dphi)               // Phi angle of a segment??
                     :G4VSolid(pname)
  {
       std::cerr << "J4VTwistedTubs: dphi must be type G4double. abort." << std::endl;
       abort();
  }
  J4TwistedTubs(const G4String &pname,              // Name of instance
                      G4double  twistedangle,       // Twisted angle
                      G4double  innerrad,           // Inner radius at z=0 
                      G4double  outerrad,           // Outer radius at z=0 
                      G4double  negativeEndz,       // -ve z endplate
                      G4double  positiveEndz,       // +ve z endplate
                      G4int     dphi)               // Phi angle of a segment
                     :G4VSolid(pname)
  {
       std::cerr << "J4VTwistedTubs: dphi must be type G4double. abort." << std::endl;
       abort();
  }
 // argument miss protection end ------------------------------------------

  virtual         ~J4TwistedTubs();
             
  void            ComputeDimensions(G4VPVParameterisation   *p,
                                    const G4int              n,
                                    const G4VPhysicalVolume *prep);
 
  G4bool          CalculateExtent(const EAxis               paxis,
                                  const G4VoxelLimits      &pvoxellimit,
                                  const G4AffineTransform  &ptransform,
                                        G4double           &pmin,
                                        G4double           &pmax ) const;

  G4double        DistanceToIn (const G4ThreeVector &p,
                                const G4ThreeVector &v ) const;

  G4double        DistanceToIn (const G4ThreeVector &p ) const;
   
  G4double        DistanceToOut(const G4ThreeVector &p, 
                                const G4ThreeVector &v,
                                const G4bool         calcnorm=G4bool(false),
                                      G4bool        *validnorm=0, 
                                      G4ThreeVector *n=0 ) const;

  G4double        DistanceToOut(const G4ThreeVector &p) const;
  
  EInside         Inside       (const G4ThreeVector &p) const;

  G4ThreeVector   SurfaceNormal(const G4ThreeVector &p) const;

  void            DescribeYourselfTo (G4VGraphicsScene &scene) const;
  G4Polyhedron   *CreatePolyhedron   () const;
  G4NURBS        *CreateNURBS        () const;

  std::ostream &StreamInfo(std::ostream& os) const;

  //* get functions *//
  
  inline G4double GetDPhi        () const { return fDPhi       ; }
  inline G4double GetPhiTwist    () const { return fPhiTwist   ; }
  inline G4double GetInnerRadius () const { return fInnerRadius; }
  inline G4double GetOuterRadius () const { return fOuterRadius; }
  inline G4double GetInnerStereo () const { return fInnerStereo; }
  inline G4double GetOuterStereo () const { return fOuterStereo; }
  inline G4double GetZHalfLength () const { return fZHalfLength; }
  inline G4double GetKappa       () const { return fKappa      ; }

  inline G4double GetTanInnerStereo () const { return fTanInnerStereo  ; }
  inline G4double GetTanInnerStereo2() const { return fTanInnerStereo2 ; }
  inline G4double GetTanOuterStereo () const { return fTanOuterStereo  ; }
  inline G4double GetTanOuterStereo2() const { return fTanOuterStereo2 ; }
  
  inline G4double GetEndZ           (G4int i) const { return fEndZ[i]       ; }
  inline G4double GetEndPhi         (G4int i) const { return fEndPhi[i]     ; }
  inline G4double GetEndInnerRadius (G4int i) const { return fEndInnerRadius[i]; }
  inline G4double GetEndOuterRadius (G4int i) const { return fEndOuterRadius[i]; }
  inline G4double GetEndInnerRadius () const 
                  { return (fEndInnerRadius[0] > fEndInnerRadius[1] ?
                    fEndInnerRadius[0] : fEndInnerRadius[1]); }
  inline G4double GetEndOuterRadius () const
                  { return (fEndOuterRadius[0] > fEndOuterRadius[1] ?
                    fEndOuterRadius[0] : fEndOuterRadius[1]); }
  
  G4VisExtent            GetExtent    () const;
  inline G4GeometryType  GetEntityType() const;

#ifdef __SOLIDDEBUG__
  J4VSurface * GetOuterHype() const { return fOuterHype; }
#endif
  
 private:
 
  inline void  SetFields(G4double phitwist, G4double innerrad, G4double outerrad,
                         G4double negativeEndz, G4double positiveEndz);
                     
  void         CreateSurfaces();

  
  static void  AddPolyToExtent( const G4ThreeVector     &v0,
                                const G4ThreeVector     &v1,
                                const G4ThreeVector     &w1,
                                const G4ThreeVector     &w0,
                                const G4VoxelLimits     &voxellimit,
                                const EAxis              axis,
                                      G4SolidExtentList &extentlist );


 //* data members *//
 
 private:
 
  G4double fPhiTwist;	       // Twist angle from -fZHalfLength to fZHalfLength
  G4double fInnerRadius;       // Inner-hype radius at z=0
  G4double fOuterRadius;       // Outer-hype radius at z=0
  G4double fEndZ[2];           // z at endcaps, [0] = -ve z, [1] = +ve z
  G4double fDPhi;	             // Phi-width of a segment fDPhi > 0
  G4double fZHalfLength;       // Half length along z-axis
 
  G4double fInnerStereo;       // Inner-hype stereo angle
  G4double fOuterStereo;       // Outer-hype stereo angle
  G4double fTanInnerStereo;    // tan(innerStereoAngle)
  G4double fTanOuterStereo;    // tan(outerStereoAngle)
  G4double fKappa;		       // tan(fPhiTwist/2)/fZHalfLen;
  G4double fEndInnerRadius[2]; // Inner-hype radii of endcaps [0] -ve z, [1] +ve z
  G4double fEndOuterRadius[2]; // Outer-hype radii of endcaps [0] -ve z, [1] +ve z
  G4double fEndPhi[2];         // Phi of endcaps, [0] = -ve z, [1] = +ve z
  
  G4double fInnerRadius2;      // fInnerRadius * fInnerRadius
  G4double fOuterRadius2;      // fOuterRadius * fOuterRadius
  G4double fTanInnerStereo2;   // fInnerRadius * fInnerRadius
  G4double fTanOuterStereo2;   // fInnerRadius * fInnerRadius
  G4double fEndZ2[2];          // fEndZ * fEndZ
  
  J4VSurface *fLowerEndcap;    // Surface of -ve z
  J4VSurface *fUpperEndcap;    // Surface of +ve z
  J4VSurface *fLatterTwisted;  // Surface of -ve phi
  J4VSurface *fFormerTwisted;  // Surface of +ve phi
  J4VSurface *fInnerHype;      // Surface of -ve r
  J4VSurface *fOuterHype;      // Surface of +ve r
    
  class       LastState {                // last Inside result
                public:
                   LastState()
                   {
                      p.set(kInfinity,kInfinity,kInfinity);
                      inside = kOutside;
                   }
                   virtual ~LastState(){}
                public:
                   G4ThreeVector p;
                   EInside       inside;
              };
              
  class       LastVector{                // last SurfaceNormal result
                public:
                   LastVector()
                   {
                      p.set(kInfinity,kInfinity,kInfinity);
                      vec.set(kInfinity,kInfinity,kInfinity);
                      surface = new J4VSurface*[1];
                   }
                   virtual ~LastVector()
                   {
                      delete [] surface;
                   }
                public:
                   G4ThreeVector   p;
                   G4ThreeVector   vec;
                   J4VSurface    **surface;
              };
              
  class       LastValue{                // last G4double value
                public:
                   LastValue()
                   {
                      p.set(kInfinity,kInfinity,kInfinity);
                      value = DBL_MAX;
                   }
                   virtual ~LastValue(){}
                public:
                   G4ThreeVector p;
                   G4double      value;
              };
              
  class       LastValueWithDoubleVector{ // last G4double value
                public:
                   LastValueWithDoubleVector()
                   {
                      p.set(kInfinity,kInfinity,kInfinity);
                      vec.set(kInfinity,kInfinity,kInfinity);
                      value = DBL_MAX;
                   }
                   virtual ~LastValueWithDoubleVector(){}
                public:
                   G4ThreeVector p;
                   G4ThreeVector vec;
                   G4double      value;
              };
              
  LastState    fLastInside;
  LastVector   fLastNormal;
  LastValue    fLastDistanceToIn;
  LastValue    fLastDistanceToOut;
  LastValueWithDoubleVector   fLastDistanceToInWithV;
  LastValueWithDoubleVector   fLastDistanceToOutWithV;
             
 };
 

//=====================================================================
//---------------------
// inline function
//---------------------

inline
void J4TwistedTubs::SetFields(G4double phitwist, G4double innerrad, 
                              G4double outerrad, G4double negativeEndz, 
                              G4double positiveEndz)
{
   fPhiTwist     = phitwist;
   fEndZ[0]      = negativeEndz;
   fEndZ[1]      = positiveEndz;
   fEndZ2[0]     = fEndZ[0] * fEndZ[0];
   fEndZ2[1]     = fEndZ[1] * fEndZ[1];
   fInnerRadius  = innerrad;
   fOuterRadius  = outerrad;
   fInnerRadius2 = fInnerRadius * fInnerRadius;
   fOuterRadius2 = fOuterRadius * fOuterRadius;
   
   G4int    maxi; 
   if (fabs(fEndZ[0]) >= fabs(fEndZ[1])) {
      fZHalfLength = fabs(fEndZ[0]);
      maxi = 0;
   } else {
      fZHalfLength = fabs(fEndZ[1]);
      maxi = 1;
   }

   G4double parity         = (fPhiTwist > 0 ? 1 : -1); 
   G4double tanHalfTwist   = tan(0.5 * fPhiTwist);
   G4double innerNumerator = fabs(fInnerRadius * tanHalfTwist) * parity;
   G4double outerNumerator = fabs(fOuterRadius * tanHalfTwist) * parity;

   fTanInnerStereo    = innerNumerator / fZHalfLength; 
   fTanOuterStereo    = outerNumerator / fZHalfLength; 
   fTanInnerStereo2   = fTanInnerStereo * fTanInnerStereo;
   fTanOuterStereo2   = fTanOuterStereo * fTanOuterStereo;
   fInnerStereo       = atan2(innerNumerator,  fZHalfLength); 
   fOuterStereo       = atan2(outerNumerator,  fZHalfLength); 
   fEndInnerRadius[0] = sqrt(fInnerRadius2 + fEndZ2[0] * fTanInnerStereo2);
   fEndInnerRadius[1] = sqrt(fInnerRadius2 + fEndZ2[1] * fTanInnerStereo2);
   fEndOuterRadius[0] = sqrt(fOuterRadius2 + fEndZ2[0] * fTanOuterStereo2);
   fEndOuterRadius[1] = sqrt(fOuterRadius2 + fEndZ2[1] * fTanOuterStereo2);

   fKappa          = tanHalfTwist / fZHalfLength;
   fEndPhi[0]      = atan2(fEndZ[0] * tanHalfTwist, fZHalfLength);
   fEndPhi[1]      = atan2(fEndZ[1] * tanHalfTwist, fZHalfLength);

#ifdef __SOLIDDEBUG__
   std::cerr << "/********* J4TwistedTubs::SetField  Field Parameters ******************* " << std::endl;
   std::cerr << "/*   fPhiTwist                  : " << fPhiTwist << std::endl;
   std::cerr << "/*   fEndZ(0, 1)                : " << fEndZ[0] << " , " << fEndZ[1] << std::endl; 
   std::cerr << "/*   fEndPhi(0, 1)              : " << fEndPhi[0] << " , " << fEndPhi[1] << std::endl; 
   std::cerr << "/*   fInnerRadius, fOuterRadius : " << fInnerRadius << " , " << fOuterRadius << std::endl; 
   std::cerr << "/*   fEndInnerRadius(0, 1)      : " << fEndInnerRadius[0] << " , " 
          << fEndInnerRadius[1] << std::endl; 
   std::cerr << "/*   fEndOuterRadius(0, 1)      : " << fEndOuterRadius[0] << " , " 
          << fEndOuterRadius[1] << std::endl; 
   std::cerr << "/*   fInnerStereo, fOuterStereo : " << fInnerStereo << " , " << fOuterStereo << std::endl; 
   std::cerr << "/*   tanHalfTwist, fKappa       : " << tanHalfTwist << " , " << fKappa << std::endl; 
   std::cerr << "/*********************************************************************** " << std::endl;
#endif
}

inline
G4GeometryType J4TwistedTubs::GetEntityType() const
  {
    return G4String("J4TwistedTubs");
  }



#endif
