// $Id$
//*************************************************************************
//* --------------------
//* J4VTXPixelArea
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXPixelArea.hh"
#include "G4Box.hh"
#ifndef __HOSHINA__ 
#include "J4VTXROGeometry.hh"
#endif
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4VTXPixelArea::fFirstName("PixelArea");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

#ifdef __HOSHINA__
J4VTXPixelArea::J4VTXPixelArea(J4VDetectorComponent* parent)
  	   :J4VVTXDetectorComponent(fFirstName, parent, 1,1, 0, -1), 
            fDxyzPixelArea(0), fxyzPixelArea(0),fPixelArray(0)
#else
J4VTXPixelArea::J4VTXPixelArea(J4VDetectorComponent* parent)
  	   :J4VVTXDetectorComponent(fFirstName, parent, 1,1, 0, -1),
            fDxyzPixelArea(0), fxyzPixelArea(0)
#endif
{   
  // Define PixelArea parameters ----------------//    
  fDxyzPixelArea = new G4ThreeVector(DXYZ_PIXELAREA);
  Register(fDxyzPixelArea);
  fxyzPixelArea  = new G4ThreeVector(XYZ_PIXELAREA);
  Register(fxyzPixelArea);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VTXPixelArea::~J4VTXPixelArea()
{
  if (Deregister(fDxyzPixelArea)) delete fDxyzPixelArea;
  if (Deregister(fxyzPixelArea))  delete fxyzPixelArea;
#ifdef __HOSHINA__
  if (Deregister(fPixelArray)) delete fPixelArray; 
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VTXPixelArea::Assemble() 
{   
  if (!GetLV())
  {	  
    // define geometry
      
    // MakeSolid ----------//
    G4VSolid *solid = new G4Box(GetName(),fDxyzPixelArea->x()/2.,
		                 fDxyzPixelArea->y()/2.,
		                 fDxyzPixelArea->z()/2.);
    Register(solid);
    SetSolid(solid);
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(_PIXELAREAMATERIAL_));
    
    // SetVisAttribute ----//
    PaintLV( _PIXELAREAVISATT_ , G4Color(0.0,0.0,0.0));    

    SetMaxAllowedStep(0.001*mm);
        
    // Install daughter PV //
    // Install PixelArea      //

#ifdef __HOSHINA__

    fPixelArray = new J4VTXPixelArray(this, NZPIXEL);
    Register(fPixelArray); 
    fPixelArray->InstallIn(this);
    SetDaughter(fPixelArray);

#endif

  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VTXPixelArea::Cabling()
{
  if(!GetLV()) Assemble();

#ifdef __HOSHINA__

  // nothing to do here.

#else

  J4VTXPixelAreaSD* sd = new J4VTXPixelAreaSD(this);
  Register(sd);
  J4VTXROGeometry* ro = new J4VTXROGeometry("VTXRO");
  Register(ro);
  ro->BuildROGeometry();
  sd->SetROgeometry(ro);
  SetSD(sd);

#endif

}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VTXPixelArea::InstallIn(J4VComponent         *mother,
                               G4RotationMatrix     *prot, 
                               const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  SetPVPlacement(prot,*fxyzPixelArea);

  if (!GetSD()) Cabling(); 
  
}


//* SwitchOn  --------------------------------------------------------
void J4VTXPixelArea::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}

//* SwitchOff  --------------------------------------------------------
void J4VTXPixelArea::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4VTXPixelArea::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4VTXPixelArea::Print() const
{
  G4cout << "-J4VTXPixelArea(mm)-  " <<G4endl;
  G4cout << "dx " << fDxyzPixelArea->x()/mm 
       << " dy "<< fDxyzPixelArea->y()/mm 
       << " dz "<< fDxyzPixelArea->z()/mm 
       << G4endl;
  G4cout << "x " << fxyzPixelArea->x()/mm 
       << " y "<< fxyzPixelArea->y()/mm 
       << " z "<< fxyzPixelArea->z()/mm 
       << G4endl;
  G4cout << "----------------" << G4endl;
  
}
