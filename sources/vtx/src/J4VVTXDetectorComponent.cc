// $Id$
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

#include "J4VVTXDetectorComponent.hh"

J4VTXMaterialStore* J4VVTXDetectorComponent::fMaterialStore = 0;

G4String J4VVTXDetectorComponent::fSubGroup("VTX");

#if (__GNUC__>=3)
#ifndef max
#define max(a,b) ((a) >= (b) ? (a) : (b))
#endif
#endif

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VVTXDetectorComponent::J4VVTXDetectorComponent(
			   	const G4String       &name, 
  			   	J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) :
                         J4VDetectorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
                         		      nbrothers, me, copyno  ),
                         fUserLimits(0)   
{ 
#include "J4VTXParameter.icc"
}

J4VVTXDetectorComponent::J4VVTXDetectorComponent(
                               const J4VVTXDetectorComponent &orig, 
                                     G4int                    copyno)
                        :J4VDetectorComponent(orig, copyno), 
                         fUserLimits(orig.fUserLimits)   
{ 
#include "J4VTXParameter.icc"
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VVTXDetectorComponent::~J4VVTXDetectorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
   if(Deregister(fUserLimits))    delete fUserLimits;
}

//=====================================================================
//* SetMaxAllowedStep

void J4VVTXDetectorComponent::SetMaxAllowedStep(G4double maxStep){

    if (fUserLimits) {
       TBookKeeper::GetBookKeeper()->Deregister(fUserLimits);
       delete fUserLimits;  
    }

    fUserLimits = new G4UserLimits;
    Register(fUserLimits); 
    fUserLimits->SetMaxAllowedStep(maxStep);
    GetLV()->SetUserLimits(fUserLimits);

} 

#ifdef __HOSHINA__
#else
//=====================================================================
//* SetPVPlacement ----------------------------------------------------

void J4VVTXDetectorComponent::SetPVPlacement(G4RotationMatrix *pRot,
                                             const G4ThreeVector &tlate, 
					     G4int copyNo,
					     G4LogicalVolume* mothelog)   
{
  G4LogicalVolume*  motherLV = (GetMother() ? GetMother()->GetLV():mothelog);  
  G4VPhysicalVolume *pv = new G4PVPlacement(pRot,		// Rotation matrix
    		     	   tlate, 		// Three vector of center position
    			   GetLV(), 		// Logical volume
    			   GetName(),	 	// Name of Physical volume
    		           motherLV,  		// Mother Logical
    			   FALSE,		// pMany
    			   copyNo  ); 		// pCopyNo	
  Register(pv);
  SetPV(pv);
}  
#endif

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VVTXDetectorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4VTXMaterialStore();
        Register(fMaterialStore);
  	G4cerr << "*** Opend J4VTXMaterialStore ***" << G4endl;
  }
    
   return fMaterialStore;
}


