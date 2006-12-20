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
   if( list->GetBFieldType() == 1 ) {  // (z,Bz,Bx)
     std::cerr << "Magnetic field map of Solenoid is obtained from" ;
     std::cerr << list->GetBFieldMapFileName() << std::endl;
     std::ifstream fin(list->GetBFieldMapFileName() );
     while(1) {
        G4double z, bz, bx;
	fin >> z >> bz >> bx;
        if( fin.eof() ) break;
        bx *= fParameterList->GetDIDFieldFactor();
        fBData.push_back(new G4ThreeVector(z*m, bz*tesla, bx*tesla) );
        fBDataZMax = z*m;
     }
     fBDataSize=fBData.size();
     std::cerr << "Reading BField map ..." ;
     std::cerr << "fBDataSize=" << fBDataSize ;
     std::cerr << " fBDataZMax=" << fBDataZMax/m << std::endl;
     fin.close();
   }
   else if( list->GetBFieldType() == 2 ) {  // (0,0,z) (Bz,Br,Bx)
     std::cerr << "Magnetic field map of Solenoid is obtained from" ;
     std::cerr << list->GetBFieldMapFileName() << std::endl;
     std::ifstream fin(list->GetBFieldMapFileName() );
     while(1) {
        G4double z, bz, br, bx;
        fin >> z >> bz >> br >> bx;
        if( fin.eof() ) break;
        bx *= fParameterList->GetDIDFieldFactor();
        fBDataPosition.push_back(new G4ThreeVector(0.0*m, 0.0*m, z*m) );  // x,y is no data.
        fBData.push_back(new G4ThreeVector(bz*tesla, br*tesla, bx*tesla) );
        fBDataZMax = z*m;
     }
     fBDataSize=fBDataPosition.size();  // fBDataPosition.size() and fBData.size() are equal.
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
     else if( fParameterList->GetBFieldType() == 1 ) {  
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
     else if( fParameterList->GetBFieldType() == 2 ) {  // (0,0,z) (Bz,Br,Bx)
        G4double absz = std::abs( position.z() );
        if( absz > fBDataZMax ) {
           bfield.setZ(0.0);
        }
        else {
           G4int index=(G4int)(absz/fBDataZMax*(G4double)(fBDataSize-1));
           G4ThreeVector *p0=fBDataPosition[index];
           G4ThreeVector *b0=fBData[index];
           G4double bx=0, by=0, bz=0;
                     // These are field added all component.
           G4double distance = position.z() * J4ParameterTable::GetValue("J4IR.Q.Angle",0.000)*rad;
                     // "distance" means the distance from z-axis.
                     // d = z * tan(theta) = z * theta (theta<<0).
           G4double radius = sqrt( position.x()*position.x() + position.y()*position.y() );
                     // "radius" means perpendicular oriented position from z-axis.
           G4double br=0, br_x=0, br_y=0, bx_serpentine=0;
                     // bx_serpentine means anti-DID field.
           if ( index == fBDataSize -1 ) { 
              br_x = (radius / distance) * b0->y() * (position.x() / radius);
              br_y = (radius / distance) * b0->y() * (position.y() / radius);
                     // br_x(y) has R dependence.
              bx_serpentine = b0->z();
              if( position.z() < 0.0 ) {
                 bx_serpentine *= -1.0;
              }
              bx = br_x + bx_serpentine;
              by = br_y;
              bz = b0->x();
              bfield.setX( bx );
              bfield.setY( by );
              bfield.setZ( bz );
           }
           else {
              G4ThreeVector *p1=fBDataPosition[index+1];
              G4ThreeVector *b1=fBData[index+1];
              if( position.z() != 0 ) {  // If z=0, Br and Bx_serpentine remain zero.
                 br = (b1->y()-b0->y())/(p1->z()-p0->z())*(absz-p0->z()) + b0->y();  // interpolate
                 br_x = (radius / distance) * br * (position.x() / radius);
                 br_y = (radius / distance) * br * (position.y() / radius);
                 bx_serpentine = (b1->z()-b0->z())/(p1->z()-p0->z())*(absz-p0->z()) + b0->z();
              }
              if( position.z() < 0.0 ) {
                 bx_serpentine *= -1.0;
              }
              bx = br_x + bx_serpentine;
              by = br_y;
              bz = (b1->x()-b0->x())/(p1->z()-p0->z())*(absz-p0->z()) + b0->x();
              bfield.setX(bx);
              bfield.setY(by);
              bfield.setZ(bz);
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

