// $Id$
#ifndef __J4VVTXDETECTORCOMPONENT__
#define __J4VVTXDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VVTXDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4VTXMaterialStore.hh"
#include "G4UserLimits.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VVTXDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VVTXDetectorComponent( const G4String       &name, 
  			   J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  J4VVTXDetectorComponent( const J4VVTXDetectorComponent &orig, 
                                        G4int                    copyno);

  virtual ~J4VVTXDetectorComponent();
  void  SetMaxAllowedStep(G4double maxStep);

#ifdef __HOSHINA__

  // use default SetPVPlacement method.

#else
  virtual void SetPVPlacement (G4RotationMatrix *pRot = 0,
                               const G4ThreeVector &tlate = 0,
			       G4int copyNo=0,
			       G4LogicalVolume* motherlog=0);
#endif
      
protected:    
  J4VMaterialStore* 	 OpenMaterialStore();

  #include "J4VTXParameter.hh"
  
private:
  static J4VTXMaterialStore *fMaterialStore;
  static G4String            fSubGroup;
  G4UserLimits              *fUserLimits;
       
};



#endif



