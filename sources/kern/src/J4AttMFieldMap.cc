// $Id$
//*************************************************************************
//* --------------------
//* J4AttMFieldMap
//* --------------------
//* (Description)
//* 	This class applies magnetic field.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************
 
#include "J4AttMFieldMap.hh"
#include "J4MFieldMapStore.hh"

//=====================================================================
//---------------------
// class description
//---------------------
J4AttMFieldMap::J4AttMFieldMap()
{
  fMFname = NULL;
  fIsOrigin = false;
  fMfield = NULL;
}

J4AttMFieldMap::~J4AttMFieldMap(){
 if ( fMfield ){ 
    J4MFieldMapStore::GetInstance()->RemoveMField(this);
    delete fMfield;
 }
}

void J4AttMFieldMap::InstallMField(J4VComponent* component)
{
  G4VPhysicalVolume* pv = component->GetPV();
  G4String mname = pv->GetName();
  fMFname = new G4String(mname);
  std::cout << "==ATTM===== PV Name " << mname << std::endl;
  G4ThreeVector xOOt(0.,0.,0.);
  G4RotationMatrix xOOr;
  
#ifndef __GEANT45__
  while(pv){
    xOOt = xOOt+pv->GetObjectTranslation();
    xOOr = xOOr*(pv->GetObjectRotationValue());
    component = component->GetMother();
    if(!component) break;
    pv        = component->GetPV();
  }
#else
  while( pv != NULL ){
    xOOt = xOOt+pv->GetObjectTranslation();
    xOOr = xOOr*(pv->GetObjectRotationValue());
    pv = pv->GetMother();
  }
#endif
  //delete pv; 

  G4ThreeVector xOOtOrigin(0.,0.,0.);
  G4RotationMatrix xOOrOrigin;
 
 if ( xOOt == xOOtOrigin && xOOr == xOOrOrigin ) {
    fIsOrigin = true;
    std::cout << "xxxxxxx Is Origin xxxxx " << mname << std::endl;
  }
 std::cout << "Translation " << xOOt << std::endl;

  fRot = xOOr;
  fRotInverse = xOOr.inverse();
  fTrans = xOOt;

  DefineGlobalMValidBox();

  J4MFieldMapStore* mfManager = J4MFieldMapStore::GetInstance();
  mfManager->AddMField(this);

}

void J4AttMFieldMap::DefineGlobalMValidBox(){
  if( fMfield ) {
    G4double lpos[3];
    fMfield->GetLocalValidBox(lpos);
    G4ThreeVector** corner = new G4ThreeVector* [8];

    corner[0] = new G4ThreeVector();
    corner[0]->set( lpos[0], lpos[1], lpos[2]);

    corner[1] = new G4ThreeVector();
    corner[1]->set(-lpos[0],lpos[1],lpos[2]);
      
    corner[2] = new G4ThreeVector();
    corner[2]->set( lpos[0], -lpos[1],lpos[2]);

    corner[3] = new G4ThreeVector();
    corner[3]->set(-lpos[0],-lpos[1],lpos[2]);

    corner[4] = new G4ThreeVector();
    corner[4]->set( lpos[0],lpos[1],-lpos[2]);

    corner[5] = new G4ThreeVector();
    corner[5]->set(-lpos[0],lpos[1],-lpos[2]);

    corner[6] = new G4ThreeVector();
    corner[6]->set( lpos[0],-lpos[1],-lpos[2]);

    corner[7] = new G4ThreeVector();
    corner[7]->set(-lpos[0],-lpos[1],-lpos[2]);

    std::cout << " corner X" << std::endl;
    for ( G4int i = 0; i < 8 ; i++){
      G4ThreeVector co(corner[i]->x(),corner[i]->y(),corner[i]->z());
      G4ThreeVector gcorner = fRot*co+fTrans;
      if ( i == 0 ){
	fMValidX[0] = gcorner.x(); 
	fMValidY[0] = gcorner.y(); 
	fMValidZ[0] = gcorner.z(); 
	fMValidX[1] = gcorner.x(); 
	fMValidY[1] = gcorner.y(); 
	fMValidZ[1] = gcorner.z(); 
      }else{
	if ( gcorner.x() < fMValidX[0] ) fMValidX[0] = gcorner.x();
	if ( gcorner.y() < fMValidY[0] ) fMValidY[0] = gcorner.y();
	if ( gcorner.z() < fMValidZ[0] ) fMValidZ[0] = gcorner.z();
	if ( gcorner.x() > fMValidX[1] ) fMValidX[1] = gcorner.x();
	if ( gcorner.y() > fMValidY[1] ) fMValidY[1] = gcorner.y();
	if ( gcorner.z() > fMValidZ[1] ) fMValidZ[1] = gcorner.z();
      } 
    }
    std::cout << " X0 " << fMValidX[0] << " X1 " << fMValidX[1] << std::endl;
    std::cout << " Y0 " << fMValidY[0] << " Y1 " << fMValidY[1] << std::endl;
    std::cout << " Z0 " << fMValidZ[0] << " Z1 " << fMValidZ[1] << std::endl;
  }
}

void J4AttMFieldMap::GetMFieldValue(const G4double point[3], 
				           G4double* bfield,
				           G4bool& onlyFlag)
{
  G4ThreeVector pos(point[0],point[1],point[2]);
  // Global to Local  position
  if( !fIsOrigin ) pos =fRotInverse*(pos-fTrans);

  G4ThreeVector gBf;

  //===============================
  fMfield->GetLocalFieldValue(pos,gBf,onlyFlag);
  //===============================

  // Local to Global B-Field
  if( !fIsOrigin ) gBf = fRot*gBf;
  
  bfield[0] = gBf.x();
  bfield[1] = gBf.y();
  bfield[2] = gBf.z();
}


G4bool J4AttMFieldMap::IsMValid(const G4double gpos[3]){

  G4bool xbool = gpos[0] > fMValidX[0] && gpos[0] < fMValidX[1] ;
  G4bool ybool = gpos[1] > fMValidY[0] && gpos[1] < fMValidY[1] ;
  G4bool zbool = gpos[2] > fMValidZ[0] && gpos[2] < fMValidZ[1] ;

  return (xbool && ybool && zbool );
}
