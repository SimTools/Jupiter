// $Id$
//*************************************************************************
//* --------------------
//* J4IRPairMonitorCompactBPout
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRPairMonitorCompactBPout.hh"
#include "J4IRWMaskParameterList.hh"

#include "G4Cons.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRPairMonitorCompactBPout::fName("IRPairMonitorCompactBPout");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRPairMonitorCompactBPout::J4IRPairMonitorCompactBPout(
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

J4IRPairMonitorCompactBPout::~J4IRPairMonitorCompactBPout()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRPairMonitorCompactBPout::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    J4IRWMaskParameterList* wmList =
      new J4IRWMaskParameterList(OpenParameterList());
    G4double angle = OpenParameterList()->GetCrossAngle();
    rmin = 0.*mm;
    r1max = 10.*mm;
    zlen  = 1.*mm;
    G4double r2max = r1max+2.*zlen*sin(abs(angle));
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".PMBPout";
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

void J4IRPairMonitorCompactBPout::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRPairMonitorCompactBPout::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRPairMonitorCompactBPout::GetTranslation(){
  J4IRWMaskParameterList* wmList = 
    new J4IRWMaskParameterList(OpenParameterList());
  G4double angle = OpenParameterList()->GetCrossAngle();

  G4double zpos = 
    wmList->GetWMask2ZPosition()+wmList->GetWMask2ZLength()/2.-zlen/2.;
  G4double xpos = zpos*sin(angle);

  G4ThreeVector* position = new G4ThreeVector;
  position->setX(xpos);

  return *position;
}
//* SwitchOn  --------------------------------------------------------
void J4IRPairMonitorCompactBPout::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}
                                                                                              
//* SwitchOff  --------------------------------------------------------
void J4IRPairMonitorCompactBPout::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4IRPairMonitorCompactBPout::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRPairMonitorCompactBPout::Print() const
{
}

	
	

