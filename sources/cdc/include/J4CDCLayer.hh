// $Id$
#ifndef __J4CDCLAYER__
#define __J4CDCLAYER__
//*************************************************************************
//* --------------------
//* J4CDCLayer
//* --------------------
//* (Description)
//* 	Derivation class for CDC Layer.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCDetectorComponent.hh"
#include "J4CDCSuperLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCCell;
class J4CDCStereoCell;
class J4CDCLayer : public J4VCDCDetectorComponent {	
public:

  J4CDCLayer(J4VDetectorComponent* parent    = 0,
  	          G4int 		   nclones   = 1,
  	          G4int 		   nbrothers = 1, 
  	          G4int 		   me        = 0,
             G4int                 copyno    = -1 );
  	     
  J4CDCLayer(G4double              rmin,
             G4double              rmax,
             J4VDetectorComponent* parent       = 0,
             G4int                 nclones      = 1,
             G4int                 nbrothers    = 1, 
             G4int                 me           = 0, 
             G4int                 copyno       = -1,
             G4int                 layertype    = 0, // 0:axial, 1, -1:stereo
             G4double              twistedangle = 0);
  	     
  virtual ~J4CDCLayer();

  virtual void InstallIn(J4VComponent         *mother,
                         G4RotationMatrix     *prot  = 0,
                         const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw() ;
  virtual void	Print() const ;

  inline virtual G4double GetTwistedAngle()   const { return fTwistedAngle; }
  inline virtual G4double GetStereoAngle()    const { return fStereoAngle; }
  inline virtual G4double GetShieldWidth()    const { return fShieldWidth; }
  inline virtual G4String GetLayerType()      const { return fLayerType; }
  inline virtual G4int    GetNcellsPerLayer() const;
         virtual G4int    GetGlobalLayerNumber();
         
  
private:
  void   Assemble();    
  void   Cabling ();
  
private:
  
  static G4String   fFirstName;

  J4CDCCell        *fCell;
  J4CDCStereoCell **fStereoCells;
  G4double          fOffset;
  G4double          fTwistedAngle;
  G4double          fStereoAngle;
  G4double          fShieldWidth;
  G4double          fRmin;
  G4double          fRmax;
  G4String          fLayerType; // A:axial, V:inner stereo, U:outer stereo
  G4RotationMatrix  fRot;
};

//=====================================================================
//---------------------
// inline function
//---------------------

G4int J4CDCLayer::GetNcellsPerLayer() const
{ 
   if (dynamic_cast<J4CDCSuperLayer *>(GetMother())) { 
      return ((J4CDCSuperLayer *)GetMother())->GetNcellsPerLayer(); 
   } else {
      std::cerr << "J4CDCLayer::GetNcellsPerLayer: cast to J4CDCSuperLayer"
             << " failed. abort. " << std::endl;
      abort();
   }
}


#endif


