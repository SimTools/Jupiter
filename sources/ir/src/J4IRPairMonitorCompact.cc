// $Id$
//*************************************************************************
//* --------------------
//* J4IRPairMonitorCompact
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRPairMonitorCompact.hh"
#include "J4IRWMaskParameterList.hh"

#include "G4Tubs.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRPairMonitorCompact::fName("IRPairMonitorCompact");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRPairMonitorCompact::J4IRPairMonitorCompact(
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

J4IRPairMonitorCompact::~J4IRPairMonitorCompact()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRPairMonitorCompact::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWMaskParameterList* wmList =
      new J4IRWMaskParameterList(OpenParameterList());
    G4double rmin = 0.*mm;
    G4double rmax = wmList->GetWMask2Radius();
    G4double zlen  = 1.*mm;
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".PM";
    G4VSolid *tube = new G4Tubs( name, rmin,rmax,zlen/2.,0,2*M_PI);  
                                       
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("Silicon"));
    
    // SetVisAttribute ---------------
    PaintLV(wmList->GetWMaskVisAtt(),G4Color(0.,0.,1.));
  	
    // Install daughter PV -----------
    fbpIn = new J4IRPairMonitorCompactBPin(this,1,1,0,-1);
    Register(fbpIn);
    fbpIn->InstallIn(this);
    SetDaughter(fbpIn);

    fbpOut = new J4IRPairMonitorCompactBPout(this,1,1,0,-1);
    Register(fbpOut);
    fbpOut->InstallIn(this);
    SetDaughter(fbpOut);
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRPairMonitorCompact::Cabling()
{
  if(!GetLV() ) Assemble();
  if ( OpenParameterList()->IsPairMonitorSD() ){
    //J4IRPairMonitorSD* sd = new J4IRPairMonitorSD(this);
    //Register(sd);
    //SetSD(sd);
  }
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRPairMonitorCompact::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRPairMonitorCompact::GetTranslation(){
  G4ThreeVector* position = new G4ThreeVector;
  return *position;
}
//* SwitchOn  --------------------------------------------------------
void J4IRPairMonitorCompact::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}
                                                                                              
//* SwitchOff  --------------------------------------------------------
void J4IRPairMonitorCompact::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4IRPairMonitorCompact::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRPairMonitorCompact::Print() const
{
}

	
	

