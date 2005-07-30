// $Id$
//*************************************************************************
//* --------------------
//* J4IRSlantTubs
//* --------------------
//* (Description)
//* 	General purpose tube solid
//*     
//* (Update Record)
//*	2005/07/22  A.Miyamoto 	Original version.
//*************************************************************************

#include "J4IRSlantTubs.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "J4SubtractionSolid.hh"
#include <cmath>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRSlantTubs::J4IRSlantTubs(G4String name, G4double rmin, G4double rmax, 
	   G4double hzlen, G4double zcnt, G4double rot,
			 J4VAcceleratorComponent *parent,
                           G4int  nclones   ,
                           G4int  nbrothers , 
                           G4int  me        ,
 	                   G4int  copyno    ,
	                   G4bool reflect ):
         J4VIRAcceleratorComponent( name, parent, nclones,
                                    nbrothers, me, copyno,reflect  ),
	fName(name), fRmin(rmin), fRmax(rmax), fHZlen(hzlen), fZcnt(zcnt),
	fRotation(rot)
{   
	fMaterial="Vaccum";
	fVisAtt=FALSE;
        fColor=G4Color(0.0, 0.0, 0.0, 1.0);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRSlantTubs::~J4IRSlantTubs()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRSlantTubs::Assemble() 
{   
  if(!GetLV()){
  	
    // MakeSolid ---------------
    G4double absrot=std::abs(fRotation);
    G4double rotation=fRotation;
    if( IsReflected() ) { rotation *= -1; }
    G4double hzlen=fHZlen/std::cos(fRotation)+fRmax*std::tan(absrot);
   
    G4String tubname=fName+".tubs";
    G4VSolid *tube = new G4Tubs( tubname, fRmin/std::cos(absrot), 
				fRmax/std::cos(absrot), hzlen, 0, 2*M_PI);  

    G4String tname1=fName+".box1";
//    G4double hzbox=fRmax*std::sin(absrot);
    G4double hxbox=fRmax*std::cos(absrot);
    G4double hybox=fRmax;

    G4String boxname1=fName+".box1";
    G4double hzsize=fRmax;
    G4VSolid *box1 = new G4Box(boxname1, 5*hxbox, 5*hybox, hzsize);
    G4RotationMatrix *rotm=new G4RotationMatrix();
    rotm->rotateY(rotation);
    G4double zshift=(fHZlen+fRmax)/std::cos(rotation)-fRmax*std::tan(absrot);
    G4ThreeVector trans(0,0,-zshift);

    G4String boxname2=fName+".box2";
    G4VSolid *box2=new J4SubtractionSolid(boxname2, tube, box1, rotm, trans);

    G4String boxname3=fName + ".box3";
    G4VSolid *box3 = new G4Box(boxname3, 5*hxbox, 5*hybox, hzsize);
    G4ThreeVector transp(0, 0, zshift);
    G4VSolid *solid=new J4SubtractionSolid(fName, box2, box3, rotm, transp);

    Register(solid);
    SetSolid(solid);	// Don't forgat call it!

    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(fMaterial));
    
    // PaintLV -----------------------
    PaintLV(fVisAtt, fColor);
  	
    // Install daughter PV -----------
  		  
  }     
//  std::cerr << " J4IRSlantTubs::Assemble() ... end " << std::endl;
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IRSlantTubs::Cabling()
{
}

//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRSlantTubs::GetRotation(){
  G4RotationMatrix* rotM = new G4RotationMatrix();
  rotM->rotateY(-fRotation);
  return rotM;
}
//=====================================================================
//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRSlantTubs::GetTranslation()
{
  G4ThreeVector *position=new G4ThreeVector( -fZcnt*std::sin(-fRotation), 
		0.0, fZcnt*std::cos(-fRotation) ) ;

  return *position;
}
                                                                                
                                                                               

//* Draw  --------------------------------------------------------
void J4IRSlantTubs::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IRSlantTubs::Print() const
{
}

	
	

