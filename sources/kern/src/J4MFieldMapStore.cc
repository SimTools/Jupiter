// $Id$
//*************************************************************************
//* --------------------
//* J4MFieldMapStore
//* -------------------
//* (Description)
//* 	This class applies magnetic field.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4MFieldMapStore.hh"

J4MFieldMapStore* J4MFieldMapStore::fpInstance = 0;

//=====================================================================
//---------------------
// class description
//---------------------
J4MFieldMapStore::J4MFieldMapStore()
                 : G4MagneticField(), fcurCount(0)
{
  fmagCollection  = new J4AttMFieldMap* [100]; 
}

void J4MFieldMapStore::GetFieldValue(const  G4double  point[3], 
                                            G4double* bfield ) const
{

  bfield[0] = 0.;
  bfield[1] = 0.;
  bfield[2] = 0.;

  G4double bfc[3]; 
  G4bool onlyFlag;
  for ( int i = 0; i < fcurCount; i++) {
    if ( fmagCollection[i]&&fmagCollection[i]->IsMValid(point) ) {
      fmagCollection[i]->GetMFieldValue(point,bfc,onlyFlag);
      //G4cout << " End of GetMFieldValue " 
      //	   << bfc[0]/tesla << " " 
      //	   << bfc[1]/tesla << " " 
      //	   << bfc[2]/tesla << " " << i << G4endl;
      if ( onlyFlag == true ) {
	bfield[0] = bfc[0];
	bfield[1] = bfc[1];  
	bfield[2] = bfc[2]; 
	break;
      } else {
	bfield[0] += bfc[0];
	bfield[1] += bfc[1];  
	bfield[2] += bfc[2]; 
      }
    }
  }

#if 0
  if ( bfield[0] != 0 || bfield[1] !=0 || bfield[2] !=0 ){
    G4cout << "bfield " << bfield[0]/tesla
	 << " "       << bfield[1]/tesla 
	 << " "       << bfield[2]/tesla 
	 << "Position " << point[0]/m
	 << " "       << point[1]/m 
	 << " "       << point[2]/m << G4endl;
  }
#endif
}


