// $Id$
//*************************************************************************
//* --------------------
//* J4IRSD0
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  T.Aso	Original version.
//*************************************************************************

#include "J4IRSD0.hh"

#include "G4Tubs.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRSD0::fName("IRSD0");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRSD0::J4IRSD0(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno,
		                          G4bool reflect) :
              J4VIRAcceleratorComponent( fName, parent, nclones,
					 nbrothers, me, copyno,reflect  ),
	      J4AttMFieldMap()
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRSD0::~J4IRSD0()
{
  int i;
  for ( i = 0; i < _SD0NSUS_ ; i++){
      if(Deregister(fsus[i])) delete fsus[i];
  }
  if(Deregister(fsus)) delete[] fsus;
  for ( i = 0; i < _SD0NCOLLAR_ ; i++){
      if(Deregister(fcol[i])) delete fcol[i];
  }
 if(Deregister(fcol)) delete[] fcol;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRSD0::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
  	
    // MakeSolid ---------------
    G4String name( GetName() );
    name += ".master";
    G4VSolid *tube = new G4Tubs( name,0.,
				   _SD0INRADIUS_+_SD0THICK_,
                                     _SD0ZLEN_/2.+0.1*cm, 0, 2*M_PI);  
    Register(tube);
    SetSolid(tube);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(_SD0MAT_));
    
    // SetVisAttribute ---------------
    PaintLV(OpenParameterList()->GetIRVisAtt(), G4Color(1, 0, 0));
  	
    // Install daughter PV -----------

    fsus = new J4IRSD0SUS*[_SD0NSUS_];
    Register(fsus);

    for ( int i = 0; i < _SD0NSUS_; i++){
     fsus[i] = new J4IRSD0SUS(this,1,12,i,-1);
     Register(fsus[i]);
     fsus[i]->InstallIn(this);
     SetDaughter(fsus[i]);
    }

    fcol = new J4IRSD0Collar*[_SD0NCOLLAR_];
    Register(fcol);
    for ( int j = 0; j < _SD0NCOLLAR_; j++){  
     fcol[j] = new J4IRSD0Collar(this,1,6,j,-1);
     Register(fcol[j]);
     fcol[j]->InstallIn(this);
     SetDaughter(fcol[j]);
    }

  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRSD0::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRSD0::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix;
  rotM->rotateY(OpenParameterList()->GetCrossAngle());
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRSD0::GetTranslation(){
  G4ThreeVector* position= new G4ThreeVector; 
  G4double angle = OpenParameterList()->GetCrossAngle();
  position->setX(-(_SD0ZPOS_+_SD0ZLEN_/2.)*std::sin(angle));
  position->setZ( (_SD0ZPOS_+_SD0ZLEN_/2.)*std::cos(angle));
  //position->setX(-(_SD0ZPOS_+_SD0ZLEN_/2.)*std::sin(_IRCROS_));
  //position->setZ( (_SD0ZPOS_+_SD0ZLEN_/2.)*std::cos(_IRCROS_));
  return *position;
}
//* Draw  --------------------------------------------------------
void J4IRSD0::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRSD0::Print() const
{
}

	
	

