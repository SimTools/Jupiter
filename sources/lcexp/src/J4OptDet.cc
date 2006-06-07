// $Id$
//*************************************************************************
//* --------------------
//* J4OptDet
//* --------------------
//* (Description)
//* 	Optional detector class
//*     
//* (Update Record)
//*	2006/06/04   A.Miyamoto Original version.
//*************************************************************************

#include "J4OptDet.hh"
#include "J4OptDetSD.hh"
#include "J4OptDetMaterialStore.hh"
#include "J4ParameterTable.hh"

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4VSolid.hh"
#include "G4UserLimits.hh"

#include <cmath>
#include <vector>

J4OptDetMaterialStore* J4OptDet::fMaterialStore = 0;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4OptDet::J4OptDet(J4VComponent *parent, G4String name, 
		       G4int nbrothers, G4int me) :
            J4VDetectorComponent( G4String("J4OPT"), 
				  name, parent, 1, nbrothers, me, -1 ),
	    fName(name), fShapeID(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4OptDet::~J4OptDet()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4OptDet::Assemble() 
{   
  if(!GetLV()){

    std::ostringstream idstr;
    //    idstr.str(GetName());
    idstr << GetMyID() ;

    std::cerr << " J4OPT:  fName =" << fName.data()
	      << " GetName =" << GetName().data()
	      << " idstr=" << idstr.str().data() << std::endl;

    G4String pname;
    G4String vname;
    vname = fName.data()+G4String(".")+idstr.str();
    pname = vname + G4String(".ShapeID");
    fShapeID = J4ParameterTable::GetValue(pname.data(),0);
    // fIDShape=0(TUBS), 1(CONS)
    std::vector<double> geom;
    std::vector<int>    detid;
    pname = fName.data()+G4String(".ID");
    detid=J4ParameterTable::GetIValue(pname.data(),"1 ",GetNbrothers());
    fOptDetID=detid[GetMyID()];
    G4VSolid *vol=0;
    pname = vname + G4String(".Geometry");
    if( fShapeID == 0 ) {
      // Geom Parameter for TUBS: rmin, rmax, zmin, zmax in cm
      std::cerr << " OPTGeoPara=" << pname.data() << std::endl;
      geom=J4ParameterTable::GetDValue(pname.data(),
				      "1.0 1.2 420.0 421.1", 4);
      for(G4int i=0;i<4;i++) { geom[i] *= cm; fGeom[i]=geom[i];  }
      vol  =new G4Tubs(vname.data(),geom[0],geom[1],
		       (geom[3]-geom[2])*0.5,0,2*M_PI);
    }
    else if ( fShapeID == 1 ) {
      // Geom Parameter for TUBS: rmin1, rmax1, rmin2, rmax2, zmin, zmax in cm
      geom=J4ParameterTable::GetDValue(pname.data(),
				      "1.0 1.2 2.0, 2.2, 420.0 421.1", 6);
      for(G4int i=0;i<6;i++) { geom[i] *= cm; fGeom[i]=geom[i];  }
      vol  =new G4Cons(vname.data(),geom[0],geom[1],geom[2],geom[3],
		       (geom[5]-geom[4])*0.5,0,2*M_PI);
    }
    else {
      std::cerr << "Fatal parameter error in J4OptDet "
		<< ": Input ShapeID was " << fShapeID << std::endl;
      exit(-1);
    }

    Register(vol);
    SetSolid(vol);	// Don't forgat call it!
                                       
    // MakeLogicalVolume -------------

    G4String material("vacuum");
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ---------------
    pname = fName+G4String(".")+idstr.str()+G4String(".VisAtt");
    G4bool visatt = J4ParameterTable::GetValue(pname.data(),true);
   std::cerr << " OPTVisAtt=" << pname.data() << std::endl;

    pname = fName+G4String(".")+idstr.str()+G4String(".Color");
    std::vector<double> col=
      J4ParameterTable::GetDValue(pname.data(),"1.0 0.4 0.4 1.0",4);    

    std::cerr << " OPTCOLOR=" << pname.data() << std::endl;

    PaintLV(visatt, G4Color(col[0], col[1], col[2], col[3])); 
  		  
  }     
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------
J4VMaterialStore* J4OptDet::OpenMaterialStore()
{
   if (!fMaterialStore) {
      fMaterialStore = new J4OptDetMaterialStore();
      Register(fMaterialStore); 
      //      G4cerr << "*** Opend J4OptDetMaterialStore ***" << G4endl;
   }
    
   return fMaterialStore;
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4OptDet::Cabling()
{
    J4OptDetSD* sd = new J4OptDetSD(this);
    Register(sd);
    SetSD(sd);
}

//=====================================================================
void J4OptDet::InstallIn(J4VComponent      *, // mother
                                          G4RotationMatrix  *,
                                    const G4ThreeVector     &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  // Placement function into mother object...
  G4RotationMatrix* rotation = new G4RotationMatrix;
  G4ThreeVector position;
  position.setZ(GetZCenter());

  SetPVPlacement(rotation,position);

  if (!GetSD()) Cabling(); 

}

//* Draw  --------------------------------------------------------
void J4OptDet::Draw()
{
  // set visualization attributes
 
}
	
//* Print  --------------------------------------------------------
void J4OptDet::Print() const
{
}

	
	

