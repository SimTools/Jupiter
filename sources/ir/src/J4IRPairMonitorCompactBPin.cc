// $Id$
//*************************************************************************
//* --------------------
//* J4IRPairMonitorCompactBPin
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRPairMonitorCompactBPin.hh"
#include "J4IRWMaskParameterList.hh"

#include "G4Cons.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRPairMonitorCompactBPin::fName("IRPairMonitorCompactBPin");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRPairMonitorCompactBPin::J4IRPairMonitorCompactBPin(
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

J4IRPairMonitorCompactBPin::~J4IRPairMonitorCompactBPin()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRPairMonitorCompactBPin::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWMaskParameterList* wmList =
      new J4IRWMaskParameterList(OpenParameterList());
    G4double angle = OpenParameterList()->GetCrossAngle();
    rmin = 0.*mm;
    r1max = 5.*mm;
    zlen  = 1.*mm;
    G4double r2max = r1max+2.*zlen*std::sin(std::abs(angle));
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".PMBPin";
    G4VSolid *cone = new G4Cons( name, rmin,r1max,rmin,r2max,zlen/2.,0,2*M_PI);  
                                       
    Register(cone);
    SetSolid(cone);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order("vacuum"));
    
    // SetVisAttribute ---------------
    PaintLV(wmList->GetWMaskVisAtt(),G4Color(0,0,0));
  	
    // Install daughter PV -----------
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRPairMonitorCompactBPin::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRPairMonitorCompactBPin::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRPairMonitorCompactBPin::GetTranslation(){
  J4IRWMaskParameterList* wmList = 
    new J4IRWMaskParameterList(OpenParameterList());
  G4double angle = OpenParameterList()->GetCrossAngle();

  G4double zpos = 
    wmList->GetWMask2ZPosition()+wmList->GetWMask2ZLength()/2.-zlen/2.;
  G4double xpos = zpos*std::sin(-angle);

  G4ThreeVector* position = new G4ThreeVector;
  position->setX(xpos);

  return *position;
}
//* SwitchOn  --------------------------------------------------------
void J4IRPairMonitorCompactBPin::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}
                                                                                              
//* SwitchOff  --------------------------------------------------------
void J4IRPairMonitorCompactBPin::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4IRPairMonitorCompactBPin::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRPairMonitorCompactBPin::Print() const
{
}

	
	

