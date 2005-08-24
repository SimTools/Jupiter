// $Id$
//*************************************************************************
//* --------------------
//* J4SOLMField
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4SOLMField.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4SOLMField::J4SOLMField(J4SOLParameterList* list)
            :J4VMField(), fParameterList(list)
{   
   fBDataZMax = 0.0;
   fBDataSize = 0;
   if( list->GetBFieldType() == 1 ) {
     std::cerr << "Magnetic field map of Solenoid is obtained from" ;
     std::cerr << list->GetBFieldMapFileName() << std::endl;
     std::ifstream fin(list->GetBFieldMapFileName() );
     while(1) {
        G4double z, bz, bx;
	fin >> z >> bz >> bx;
        if( fin.eof() ) break;
        fBData.push_back(new G4ThreeVector(z*m, bz*tesla, bx*tesla) );
        fBDataZMax = z*m;
     }
     fBDataSize=fBData.size();
     std::cerr << "Reading BField map ..." ;
     std::cerr << "fBDataSize=" << fBDataSize ;
     std::cerr << " fBDataZMax=" << fBDataZMax/m << std::endl;
     fin.close();
   }
}

//=====================================================================
//* destructor --------------------------------------------------------
J4SOLMField::~J4SOLMField()
{
}

//=====================================================================
void J4SOLMField::GetLocalFieldValue(G4ThreeVector &position,
                                     G4ThreeVector &bfield,
                                     G4bool        &onlyFlag)
{

  onlyFlag = false;
	
//  G4double maxBRad    = fParameterList->GetSOLOuterR();
  G4double maxBRad    = fParameterList->GetSOLCoilOuterR();
  G4double maxBZ      = fParameterList->GetSOLHalfZ();
  G4double maxBRad_sq = maxBRad * maxBRad;
    
  if(  std::abs(position.z()) < maxBZ 
       && (sqr(position.x())+sqr(position.y())) < maxBRad_sq ) {  
// Uniform magnetc field
     if ( fParameterList->GetBFieldType() == 0 ) {
        G4double zBfield    = fParameterList->GetBField();	
        bfield.setZ(zBfield); 
     }
 // DID map case  (Assumes equal spacing of each data points )
     else {  
        G4double  absz=std::abs(position.z());
        if ( absz > fBDataZMax ) {
           bfield.setZ(0.0);
        }
        else { // Interpolate 
           G4int index=(G4int)(absz/fBDataZMax*(G4double)(fBDataSize-1)); 
				// fBDataSize is fBData.size()
           G4ThreeVector *b0=fBData[index];
           if ( index == fBDataSize -1 ) {
              bfield.setZ(b0->y());
              bfield.setX(b0->z());
	   }
           else {
              G4ThreeVector *b1=fBData[index+1];
              G4double  bz=(b1->y()-b0->y())/(b1->x()-b0->x())*(absz-b0->x()) + b0->y();
              G4double  bx=(b1->z()-b0->z())/(b1->x()-b0->x())*(absz-b0->x()) + b0->z();
              if( position.z() < 0.0 ) bx *= -1.0;
              bfield.setZ(bz);
              bfield.setX(bx);
           }
        }
     }
  }
}

//=====================================================================
void J4SOLMField::GetLocalValidBox(G4double* lpos){

  lpos[0] = fParameterList->GetSOLOuterR();
  lpos[1] = fParameterList->GetSOLOuterR();
  lpos[2] = fParameterList->GetSOLHalfZ();


  return;
}
//=====================================================================

