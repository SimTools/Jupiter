// $Id$
//*************************************************************************
//* --------------------
//* J4IRPairMonitorCompactSP
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRPairMonitorCompactSP.hh"
#include "J4IRWMaskParameterList.hh"

#include "G4Tubs.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRPairMonitorCompactSP::fName("IRPairMonitorCompactSP");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRPairMonitorCompactSP::J4IRPairMonitorCompactSP(
				       J4VComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,G4bool reflect ) :
            J4VIRDetectorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno,reflect  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRPairMonitorCompactSP::~J4IRPairMonitorCompactSP()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRPairMonitorCompactSP::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWMaskParameterList* wmList =
      new J4IRWMaskParameterList(OpenParameterList());
    G4double rmin = 0.*mm;
    G4double rmax = wmList->GetWMask2Radius();
    G4double zlen  = wmList->GetWMask2ZLength();
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".PM";
    G4VSolid *tube = new G4Tubs( name, rmin,rmax,zlen/2.,0,2*M_PI);  
                                       
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("vacuum"));
    
    // SetVisAttribute ---------------
    PaintLV(wmList->GetWMaskVisAtt(),G4Color(0.,1.,1.));
  	
    // Install daughter PV -----------
    fpm = new J4IRPairMonitorCompact(this,1,1,0,-1);
    Register(fpm);
    fpm->InstallIn(this);
    SetDaughter(fpm);
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRPairMonitorCompactSP::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRPairMonitorCompactSP::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRPairMonitorCompactSP::GetTranslation(){
  J4IRWMaskParameterList* wmList = 
    new J4IRWMaskParameterList(OpenParameterList());
  G4double zpos = wmList->GetWMask2ZPosition()+wmList->GetWMask2ZLength()/2.;

  G4ThreeVector* position = new G4ThreeVector(0,0.,zpos);
  return *position;
}
//* SwitchOn  --------------------------------------------------------
void J4IRPairMonitorCompactSP::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}
                                                                                              
//* SwitchOff  --------------------------------------------------------
void J4IRPairMonitorCompactSP::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4IRPairMonitorCompactSP::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRPairMonitorCompactSP::Print() const
{
}

	
	

