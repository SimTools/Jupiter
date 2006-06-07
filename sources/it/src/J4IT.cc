// $Id$
//*************************************************************************
//* --------------------
//* J4IT
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2005/07/26  A.Miyamoto  Updated to include Endcap IT
//*************************************************************************

#include <vector>
#include "J4IT.hh"
#include "J4ParameterList.hh"
#include "J4ITParameterList.hh"
#include "J4ParameterTable.hh"
#include "J4UnionSolid.hh"
#include "J4OptDet.hh"

#include "G4Cons.hh"
#include "G4Tubs.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IT::fFirstName("IT");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IT::J4IT(J4VDetectorComponent *parent,
                          G4int  nclones,
                          G4int  nbrothers, 
                          G4int  me,
                          G4int  copyno ) :
      J4VITDetectorComponent( fFirstName, parent, nclones,
                              nbrothers, me, copyno ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IT::~J4IT()
{
/*
  J4ITParameterList *list = OpenParameterList(); 
  if (fLayers){	
    G4int i;  
    for (i = 0; i < list->GetNlayers(); i++) {
     if(Deregister(fLayers[i])) delete fLayers [i];
    } 
    if (Deregister(fLayers)) delete [] fLayers;
  }
*/
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IT::Assemble() 
{   
  if(!GetLV()){
 
    J4ParameterList   *pl = J4ParameterList::GetInstance();

// --- Input parameters to define IT geometry

    G4int nbarrel = J4ParameterTable::GetValue("J4IT.NBarrel",4);
    G4double thick = J4ParameterTable::GetValue("J4IT.Layer.Thickness",0.05616)*cm;
//  thick is a total thickness of Silicon 
    std::vector<double> barrelR;
    barrelR  = J4ParameterTable::GetDValue("J4IT.Barrel.InnerRadius",
				"9.0  18.5  28.0  37.5",nbarrel);
    std::vector<double> barrelHZ;
    barrelHZ = J4ParameterTable::GetDValue("J4IT.Barrel.HalfZ", 
				"18.58  38.20  57.81  77.43",nbarrel);
    for(int i=0;i<nbarrel;i++) {
	barrelR[i] *= cm ;  barrelHZ[i] *= cm;
    }

    G4int nendcap = J4ParameterTable::GetValue("J4IT.NEndcap",7);
    std::vector<double> endcapRmin;
    endcapRmin = J4ParameterTable::GetDValue("J4IT.Endcap.Rmin",
			"3.0 5.5 8.0 8.0 8.0 8.0 8.0",nendcap);
    std::vector<double> endcapRmax;
    endcapRmax = J4ParameterTable::GetDValue("J4IT.Endcap.Rmax",
			"14.0 17.0 25.0 32.0 32.0 32.0 32.0",nendcap);
    std::vector<double> endcapZpos;
    endcapZpos = J4ParameterTable::GetDValue("J4IT.Endcap.Zpos",
			"20.0 35.0 50.0 65.0 90.0 115.0 140.0",nendcap);
    for(int i=0;i<nendcap;i++) {
	endcapRmin[i] *= cm ;  endcapRmax[i] *= cm; endcapZpos[i] *= cm; 
    }


    G4int nsolids = pl->GetIRNSolids();
    G4String bpname=GetName()+".Center";
    G4double rmax = pl->GetSupportTubInnerR();
    G4double zmax = pl->GetITZMax();

//  Central Tubs
    G4double rmin=barrelR[0];
    G4double z0 = barrelHZ[0];
    if( barrelHZ[0] > endcapZpos[0] ) { z0 = endcapZpos[0] - 2*thick; } 
    if( z0 < pl->GetIRREdges(0) ) {
	std::cerr << "Error ... Illegal IT geometry parameter " << std::endl;
        std::cerr << " Z coordinate of the first endcap IT must be larger than ";
        std::cerr << " central beryllium beam pipe " << std::endl;
        G4Exception("Input parameter error for J4IT casued abnormal termination");
    }

    G4VSolid *tmpv0 = new G4Tubs(bpname, rmin, rmax, z0, 0, 2*M_PI);

// Next to central Cons for both end-cap
    G4double ratbp=pl->GetIRREdges(0) + 
       (pl->GetIRREdges(1) - pl->GetIRREdges(0))/(pl->GetIRZEdges(1) - pl->GetIRZEdges(0))*
       (z0 - pl->GetIRZEdges(0)) + 0.1*mm;
// For positive side cons
    G4String tmpn1 = GetName()+".cp";
    G4double zhlf=( pl->GetIRZEdges(1) - z0 )*0.5;
    G4double zshift= (pl->GetIRZEdges(1) + z0 )*0.5;
    G4VSolid *tmpv1 = new G4Cons(tmpn1, ratbp, rmax, pl->GetIRREdges(1), rmax, 
	zhlf, 0, 2*M_PI);
    G4ThreeVector tmptr1(0, 0, zshift);
    G4String tmpn2 = GetName()+".jp";
    G4VSolid *tmpv2 = new J4UnionSolid(tmpn2, tmpv0, tmpv1, 0, tmptr1);

// For negative side cons
    G4String tmpn3 = GetName()+".cm";
    G4VSolid *tmpv3 = new G4Cons(tmpn3, pl->GetIRREdges(1), rmax, ratbp, rmax,  
	zhlf, 0, 2*M_PI);
    G4ThreeVector tmptr3(0, 0, -zshift);
    G4String tmpn4 = GetName()+".jm";
    G4VSolid *lastsolid = new J4UnionSolid(tmpn4, tmpv2, tmpv3, 0, tmptr3);
   
// Remaining IT volume is defined just as outside beam pipe

    std::ostringstream sname;
    G4VSolid *tmpsolid=0;

    G4int lasti=nsolids;
    for(int i=0 ; i<nsolids; i++ ) {  // Find last shape within ZMax
      if( zmax < pl->GetIRZEdges(i) ) {
	lasti = i+1;
        break;
      }
    } 

    for(int i=2;i<lasti;i++) {
      for(int j=0;j<2;j++) {
//      for(int j=0;j<1;j++) {
        G4double zend=pl->GetIRZEdges(i);
        if( zend > zmax ) { zend=zmax; }               
        G4double hzlen=(zend - pl->GetIRZEdges(i-1))*0.5;
        sname << GetName() << ".SolidTemp" << i << "-" << j << std::ends;
        if( pl->GetIRShapes(i) == 0 ) {
          tmpsolid = new G4Tubs(sname.str(), pl->GetIRREdges(i-1), rmax, hzlen, 0, 2*M_PI);
        }
        else {
          if( j == 0 ) {
  	    tmpsolid=new G4Cons(sname.str(), pl->GetIRREdges(i-1), rmax,
			pl->GetIRREdges(i), rmax, hzlen, 0, 2*M_PI);
          }
	  else {
  	    tmpsolid=new G4Cons(sname.str(), pl->GetIRREdges(i), rmax, 
			pl->GetIRREdges(i-1), rmax, hzlen, 0, 2*M_PI);
	  }
        }
        G4double  zpos = pl->GetIRZEdges(i-1) + hzlen ;
	if ( j == 1 ) zpos *= -1 ;
        G4ThreeVector tmptrans(0, 0, zpos);
        sname << GetName() << ".SolidJoin" << i << "-" << j << std::ends;
        if( i == lasti-1 && j == 1 ) { sname << GetName() << std::ends ; }
        G4VSolid *irjoin = new J4UnionSolid(sname.str(), lastsolid, tmpsolid, 0, tmptrans);
        lastsolid = irjoin;
      }
    }
    Register(lastsolid);
    SetSolid(lastsolid);	// Don't forgat call it!

    J4ITParameterList *list = OpenParameterList(); 
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()->Order(list->GetITMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetITVisAtt(), list->GetITColor());
  	
    // Install daughter PV //
    // Install Layer       //
    // IT layer consists of N layers of barrel and M layers of Endcap(forward)

    G4int nlayers = nbarrel + 2*nendcap;
    fLayers = new J4ITLayer* [nlayers];
    Register(fLayers);
    for(int i=0; i<nbarrel;i++) {
       fLayers[i] = new J4ITLayer(barrelR[i], barrelR[i]+thick, barrelHZ[i], 0.0, 
				  this, 1, nlayers, i);
       Register(fLayers[i]);
       fLayers[i]->InstallIn(this);
       SetDaughter(fLayers[i]);
    }
    for(int i=0;i<nendcap;i++) {
      for(int j=0;j<2;j++) {
	G4int ip=nbarrel+2*i+j;
        G4double zpos=endcapZpos[i];
	if( j == 1 ) zpos *= -1.0 ;
	fLayers[ip] = new J4ITLayer(endcapRmin[i], endcapRmax[i], 0.5*thick, 
		zpos, this, 1, nlayers, ip);
	Register(fLayers[ip]);
	fLayers[ip]->InstallIn(this);
	SetDaughter(fLayers[ip]);
      }
    }

  int ndet=J4ParameterTable::GetValue("J4IT.OptDet.N",0);
  std::cerr << " J4IT.OptDet.N" << ndet << std::endl;
  for(G4int idet=0;idet<ndet;idet++){
    std::cerr << " Going to create J4IT.OptDet .. idet=" << idet << std::endl;
    J4OptDet *opt=new J4OptDet(this, G4String("J4IT.OptDet"), ndet, idet);
    Register(opt);
    opt->InstallIn(this);
    SetDaughter(opt);
  }

  }



}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IT::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4IT::InstallIn(J4VComponent         * /* mother */,
                     G4RotationMatrix     * /* prot */  , 
                     const G4ThreeVector  & /* tlate */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}



//* Draw  --------------------------------------------------------
void J4IT::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IT::Print() const
{
}
