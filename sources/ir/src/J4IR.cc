// $Id$
//*************************************************************************
//* --------------------
//* J4IR
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IR.hh"
#include "J4IRParameter.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "J4UnionSolid.hh"
#include <math.h>


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IR::fFirstName("IR");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IR::J4IR(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno ) :
            J4VIRAcceleratorComponent( fFirstName, parent, nclones,
                                    nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IR::~J4IR()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IR::Assemble() 
{   
  if(!GetLV()){
  	
    // Calcurate parameters ----------
    G4double innersupporttubrad = _IRINNERSUPPORTTUBRAD_;
    G4double outerbeampiperad   = _IROUTERBEAMPIPERAD_;
    G4double thetamax           = _IRTHETAMAX_;
    G4double beampipehalfzlen   = tan(M_PI/2 - thetamax) * outerbeampiperad;
    G4double cylinderfrontz     = tan(M_PI/2 - thetamax) * innersupporttubrad;
    G4double conehalfz          = (cylinderfrontz -  beampipehalfzlen) / 2.0;	
    G4double cylinderhalfz      = (_IRZMID_ - cylinderfrontz) / 2.0;
    G4double boxhalfx           = _IRBOXHALFX_;
    G4double boxhalfy           = _IRBOXHALFY_;
    G4double boxhalfz           = (_IRZMAX_ - _IRZMID_) / 2.0;
    G4double coneglobalz        = beampipehalfzlen + conehalfz;
    G4double cylinderglobalz    = coneglobalz + conehalfz + cylinderhalfz;
    G4double boxglobalz         = cylinderglobalz + cylinderhalfz + boxhalfz;
    
  	
    // MakeSolid ---------------
    
    G4String beampipename( GetName() );
    beampipename += ".Beampipe";
    G4VSolid *beampipe = new G4Tubs( beampipename, 0, outerbeampiperad,
                                     beampipehalfzlen, 0, 2*M_PI);  
    G4String irconerightname( GetName() );
    irconerightname += ".IRconeright";
    G4VSolid *irconeright = new G4Cons( irconerightname, 0, outerbeampiperad, 0,
                                        innersupporttubrad, conehalfz, 0, 2*M_PI); 
    G4String irconeleftname( GetName() );
    irconeleftname += ".IRconelert";
    G4VSolid *irconeleft = new G4Cons( irconeleftname, 0, innersupporttubrad, 0,
                                       outerbeampiperad, conehalfz, 0, 2*M_PI); 
    G4String ircylindername1( GetName() );
    ircylindername1 += ".IRcylinder1";
    G4VSolid *ircylinder1 = new G4Tubs( ircylindername1, 0, innersupporttubrad,
                                       cylinderhalfz, 0, 2*M_PI);
    G4String ircylindername2( GetName() );
    ircylindername2 += ".IRcylinder2";
    G4VSolid *ircylinder2 = new G4Tubs( ircylindername2, 0, innersupporttubrad,
                                       cylinderhalfz, 0, 2*M_PI);
    G4String irboxname1( GetName() );
    irboxname1 += ".IRbox1";
    G4VSolid *irbox1 = new G4Box( irboxname1, boxhalfx, boxhalfy, boxhalfz);

    G4String irboxname2( GetName() );
    irboxname2 += ".IRbox2";
    G4VSolid *irbox2 = new G4Box( irboxname2, boxhalfx, boxhalfy, boxhalfz);
    
    G4String tmpsolid1name( GetName() );
    tmpsolid1name += ".tmpsolid1";
    G4ThreeVector tmpsolid1tlate(0, 0, coneglobalz);
    G4VSolid *tmpsolid1 = new J4UnionSolid(tmpsolid1name, beampipe, irconeright,
                                       0, tmpsolid1tlate );
    G4String tmpsolid2name( GetName() );
    tmpsolid2name += ".tmpsolid2";
    G4ThreeVector tmpsolid2tlate(0, 0, -coneglobalz);
    G4VSolid *tmpsolid2 = new J4UnionSolid(tmpsolid2name, tmpsolid1, irconeleft,
                                       0, tmpsolid2tlate );
    G4String tmpsolid3name( GetName() );
    tmpsolid3name += ".tmpsolid3";
    G4ThreeVector tmpsolid3tlate(0, 0, cylinderglobalz);
    G4VSolid *tmpsolid3 = new J4UnionSolid(tmpsolid3name, tmpsolid2, ircylinder1,
                                       0, tmpsolid3tlate );
    G4String tmpsolid4name( GetName() );
    tmpsolid4name += ".tmpsolid4";
    G4ThreeVector tmpsolid4tlate(0, 0, -cylinderglobalz);
    G4VSolid *tmpsolid4 = new J4UnionSolid(tmpsolid4name, tmpsolid3, ircylinder2,
                                       0, tmpsolid4tlate );
    G4String tmpsolid5name( GetName() );
    tmpsolid5name += ".tmpsolid5";
    G4ThreeVector tmpsolid5tlate(0, 0, boxglobalz);
    G4VSolid *tmpsolid5 = new J4UnionSolid(tmpsolid5name, tmpsolid4, irbox1,
                                       0, tmpsolid5tlate );

    G4ThreeVector lastsolidtlate(0, 0, -boxglobalz);
    G4VSolid *lastsolid = new J4UnionSolid(GetName(), tmpsolid5, irbox2,
                                       0, lastsolidtlate );
    Register(lastsolid);
    SetSolid(lastsolid);	// Don't forgat call it!


    // MakeLogicalVolume ------------- 
    MakeLVWith(OpenMaterialStore()->Order(_IRMATERIAL_)); 

    // SetVisAttribute ---------------
    PaintLV(_IRVISATT_, G4Color(1, 0, 1));
    
 
  	
    // Install daughter PV -----------
    
    
    
    
    
    
    
    
  		  
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IR::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4IR::InstallIn(J4VComponent         *mother,
                     G4RotationMatrix     *prot, 
                     const G4ThreeVector  &tlate )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4IR::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IR::Print() const
{
}

	
	

