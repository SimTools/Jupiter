// $Id$
//*************************************************************************
//* --------------------------
//* J4DetectorConstruction.cc
//* --------------------------
//* (Description)
//* 	
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************


#include "J4DetectorConstruction.hh"
#include "J4EXPHall.hh"


J4EXPHall* J4DetectorConstruction::fEXPHall = 0; 

//************************************************************************
//---------------------
// Class Description
//---------------------
 
//=====================================================================
//* constructor -------------------------------------------------------

J4DetectorConstruction::J4DetectorConstruction() : fComponents(64)
{  
   fEXPHall  = new J4EXPHall(0, 1, 1, 0);
   Register(fEXPHall);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4DetectorConstruction::~J4DetectorConstruction()
{
  if (Deregister(fEXPHall))  delete fEXPHall;
  if (fComponents.entries()) {
     unsigned int i;
     for (i=0; i<fComponents.entries(); i++) {
          if (Deregister(fComponents[i])) delete fComponents[i];
     }
  }
}

//=====================================================================
//* Construct   -------------------------------------------------------

G4VPhysicalVolume* J4DetectorConstruction::Construct()
{
    std::cerr << std::endl
           << "##------------------------------------------------##" << std::endl
           << "## ============================================== ##" << std::endl
           << "##   J4DetectorConstruction::Construct()          ##" << std::endl
           << "## ============================================== ##" << std::endl
           << "##                                                ##" << std::endl
           << "##    Start installing all of the components      ##" << std::endl
           << "##          into Experimental Hall...             ##" << std::endl
           << "##                                                ##" << std::endl
           << "##------------------------------------------------##" << std::endl
           << std::endl;
  
    G4int ncomponents = fComponents.entries();
    
    for (G4int i=0; i<ncomponents; i++) {
    		
    	J4VComponent* detector 
    		= (J4VComponent *)fComponents.operator[](i);     
    	detector->InstallIn(fEXPHall);
    	fEXPHall->SetDaughter(detector);
    	
    }  

    std::cerr << std::endl
           << "##------------------------------------------------##" << std::endl
           << "## ============================================== ##" << std::endl
           << "##   J4DetectorConstruction::Construct()          ##" << std::endl
           << "## ============================================== ##" << std::endl
           << "##                                                ##" << std::endl
           << "##    Finished installation of the components!    ##" << std::endl
           << "##                                                ##" << std::endl
           << "##------------------------------------------------##" << std::endl
           << std::endl;

  // ==============================================================
  // return PV of the world volume
    return fEXPHall->GetPV();
}

