// $Id$
//*************************************************************************
//* --------------------
//* J4IRFCALSubLayer
//* --------------------
//* (Description)
//* 	Class of FCAL aborber, sensor, and gap
//*     
//* (Update Record)
//*	2006/01/29   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRFCALSubLayer.hh"
#include "J4IRFCAL.hh"
#include "J4ParameterTable.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4VSolid.hh"

#include <cmath>
#include <vector>

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IRFCALSubLayer::fName("IRFCALSubLayer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRFCALSubLayer::J4IRFCALSubLayer(J4VAcceleratorComponent *parent,
			                  G4int  me) :
            J4VIRAcceleratorComponent( fName, parent, 1,
                                    1, me, -1 ) 
{   
  // me=0: Absorber
  //   =1: Gap
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRFCALSubLayer::~J4IRFCALSubLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRFCALSubLayer::Assemble() 
{   
  if(!GetLV()){

    J4IRFCALLayer *parent=(J4IRFCALLayer*)GetMother();
    G4Cons *solid=(G4Cons*)parent->GetSolid(); 
    G4int ind=2*GetMyID();

    G4double rmin1p=solid->GetInnerRadiusMinusZ();
    G4double rmax1p=solid->GetOuterRadiusMinusZ();
    G4double rmin2p=solid->GetInnerRadiusPlusZ();
    G4double rmax2p=solid->GetOuterRadiusPlusZ();
    G4double hzp   =solid->GetZHalfLength();

    fZpos[0]=0;
    fZpos[1]=J4ParameterTable::GetValue("J4IR.FCAL.AbsorberThickness",0.3)*cm;
    fZpos[2]=fZpos[1]+
      J4ParameterTable::GetValue("J4IR.FCAL.SensorThickness",0.03)*cm;
    fZpos[3]=2*hzp;
    
    G4double rmin1=rmin1p+(rmin2p-rmin1p)*fZpos[ind]/fZpos[3];
    G4double rmax1=rmax1p+(rmax2p-rmax1p)*fZpos[ind]/fZpos[3];
    G4double rmin2=rmin1p+(rmin2p-rmin1p)*fZpos[ind+1]/fZpos[3];
    G4double rmax2=rmax1p+(rmax2p-rmax1p)*fZpos[ind+1]/fZpos[3];
    G4double hz=(fZpos[ind+1]-fZpos[ind])*0.5;

    // MakeSolid ---------------
    std::ostringstream sname;
    sname.str(GetName());
    sname << GetMyID() << std::ends;

//    G4double margin = 0.00001*mm;
//    hz -= margin;

    G4VSolid *fcal = new G4Cons(sname.str(), rmin1, rmax1, rmin2, rmax2,
				hz, 0, 2*M_PI);
    Register(fcal);
    SetSolid(fcal);	// Don't forgat call it!
                                       
    // MakeLogicalVolume -------------

    G4int fid=(parent->GetMother()->GetMyID())%2;
    std::vector<G4String> ft;
    ft.push_back(G4String("Tail"));  // MyID=2, 4 (Tail)
    ft.push_back(G4String("Front")); // MyID=1, 3 (Front)


    std::vector<GeoInfo> geoinfo;
    geoinfo.push_back(GeoInfo(G4String("Absorber"),G4String("Tungsten"),
			      true,G4String("1.0, 0.0, 0.2, 1.0")));
    geoinfo.push_back(GeoInfo(G4String("Gap"),G4String("Air"),
			      false,G4String("0.7, 0.0, 0.2, 1.0")));

    G4int id=GetMyID();
    G4String key=G4String("J4IR.FCAL.")+ft[fid]
      +G4String(".")+geoinfo[id].name+G4String(".Material");
    G4String material=
      J4ParameterTable::GetValue(key.data(),geoinfo[id].material.data());
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    key=std::string("J4IR.VisAtt.FCAL.")+ft[fid]+G4String(".")+geoinfo[id].name;
    G4bool visatt=J4ParameterTable::GetValue(key,geoinfo[id].visatt);
    key=std::string("J4IR.Color.FCAL.")+ft[fid]+G4String(".")+geoinfo[id].name;
    std::vector<double> col=
      J4ParameterTable::GetDValue(key.data(),geoinfo[id].color.data(),4);    

    PaintLV(visatt, G4Color(col[0], col[1], col[2], col[3])); 
 		  
  }     
}

//* Cabling  ----------------------------------------------------------
void J4IRFCALSubLayer::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRFCALSubLayer::GetRotation()
{
  G4RotationMatrix* rotM = new G4RotationMatrix;
  // No rotation, because solid is rotated by the mother volume
  return rotM;
}

//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRFCALSubLayer::GetTranslation()
{
  

  G4int id=GetMyID()*2;
  G4double zcnt=-fZpos[3]*0.5+(fZpos[id]+fZpos[id+1])*0.5;

  G4ThreeVector* position = new G4ThreeVector();
  position->setZ(zcnt);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRFCALSubLayer::Draw()
{
  // set visualization attributes
 
}
	
//* Print  --------------------------------------------------------
void J4IRFCALSubLayer::Print() const
{
}

	
	

