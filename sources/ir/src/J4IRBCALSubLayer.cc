// $Id$
//*************************************************************************
//* --------------------
//* J4IRBCALSubLayer
//* --------------------
//* (Description)
//* 	Class of BCAL aborber, sensor, and gap
//*     
//* (Update Record)
//*	2006/01/29   A.Miyamoto Original version.
//*************************************************************************

#include "J4IRBCALSubLayer.hh"
#include "J4IRBCAL.hh"
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

G4String J4IRBCALSubLayer::fName("IRBCALSubLayer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IRBCALSubLayer::J4IRBCALSubLayer(J4VAcceleratorComponent *parent,
			                  G4int  me) :
            J4VIRAcceleratorComponent( fName, parent, 1,
                                    2, me, -1 ) 
{   
  // me=0: Absorber
  //   =1: Gap
  // nbrother = 2 fixed
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IRBCALSubLayer::~J4IRBCALSubLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IRBCALSubLayer::Assemble() 
{   
  if(!GetLV()){

    J4IRBCALLayer *parent=(J4IRBCALLayer*)GetMother();
    G4Tubs *solid=(G4Tubs*)parent->GetSolid(); 
    G4int ind=2*GetMyID();

    G4double tolerance=1.E-5*mm;
    G4double rmin=solid->GetInnerRadius()+tolerance;
    G4double rmax=solid->GetOuterRadius()-tolerance;
    G4double hzp =solid->GetZHalfLength();

    fZpos[0]=0;
    fZpos[1]=J4ParameterTable::GetValue("J4IR.BCAL.AbsorberThickness",0.3)*cm;
    fZpos[2]=fZpos[1]+
      J4ParameterTable::GetValue("J4IR.BCAL.SensorThickness",0.03)*cm;
    fZpos[3]=2*hzp;
    
    G4double hz=(fZpos[ind+1]-fZpos[ind])*0.5;

    // MakeSolid ---------------
    std::ostringstream sname;
    //     sname.str(GetName());
    sname << fName << GetMyID() << std::ends;

    //    std::cerr << " IRBCALSubLayer .. GetName=" << GetName() 
    //	      << "MyID=" << GetMyID() 
    //	      << " ind=" << ind
    //	      << " sname=" << sname.str()
    //	      << std::endl;
//    G4double margin = 0.00001*mm;
//    hz -= margin;

    G4VSolid *bcal = new G4Tubs(sname.str(), rmin, rmax, hz, 0, 2*M_PI);
    Register(bcal);
    SetSolid(bcal);	// Don't forgat call it!
                                       
    // MakeLogicalVolume -------------

    std::vector<GeoInfo> geoinfo;
    geoinfo.push_back(GeoInfo(G4String("Absorber"),G4String("Tungsten"),
			      true,G4String("1.0, 0.0, 0.2, 1.0")));
    geoinfo.push_back(GeoInfo(G4String("Gap"),G4String("Air"),
			      false,G4String("0.7, 0.0, 0.2, 1.0")));

    G4int id=GetMyID();
    G4String key=G4String("J4IR.BCAL.")
      +geoinfo[id].name+G4String(".Material");
    G4String material=
      J4ParameterTable::GetValue(key.data(),geoinfo[id].material.data());
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    key=std::string("J4IR.VisAtt.BCAL.")+geoinfo[id].name;
    G4bool visatt=J4ParameterTable::GetValue(key,geoinfo[id].visatt);
    key=std::string("J4IR.Color.BCAL.")+geoinfo[id].name;
    std::vector<double> col=
      J4ParameterTable::GetDValue(key.data(),geoinfo[id].color.data(),4);    

    PaintLV(visatt, G4Color(col[0], col[1], col[2], col[3])); 
 		  
  }     
}

//* Cabling  ----------------------------------------------------------
void J4IRBCALSubLayer::Cabling()
{
}
//=====================================================================
//* GetRotation  --------------------------------------------------------
G4RotationMatrix* J4IRBCALSubLayer::GetRotation()
{
  G4RotationMatrix* rotM = new G4RotationMatrix;
  // No rotation, because solid is rotated by the mother volume
  return rotM;
}

//* GetTranslate  --------------------------------------------------------
G4ThreeVector& J4IRBCALSubLayer::GetTranslation()
{
  
  G4int id=GetMyID()*2;
  G4double zcnt=-fZpos[3]*0.5+(fZpos[id]+fZpos[id+1])*0.5;

  G4ThreeVector* position = new G4ThreeVector();
  position->setZ(zcnt);
  return *position;
}

//* Draw  --------------------------------------------------------
void J4IRBCALSubLayer::Draw()
{
  // set visualization attributes
 
}
	
//* Print  --------------------------------------------------------
void J4IRBCALSubLayer::Print() const
{
}

	
	

