// $Id$
//*************************************************************************
//* --------------------
//* J4ITLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4ITLayer.hh"
#include "J4ITLayerSD.hh"
#include "J4ITParameterList.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4ITLayer::fFirstName("Layer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4ITLayer::J4ITLayer(J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VITDetectorComponent(fFirstName, parent, nclones,
                                  nbrothers, me, copyno),
  	   fRmin(0), fRmax(0), fLen(0), fTotalPhi(0), fOffset(0)
{   

  // Define Layer parameters ----------------//    

    J4ITParameterList * list = OpenParameterList();

    fRmin     = list->GetLayerInnerR(me);
    fRmax     = list->GetLayerOuterR(me);
    fLen      = list->GetLayerHalfZ(me);
//    fTotalPhi = ((G4Tubs *)parent->GetLV()->GetSolid())->GetDeltaPhiAngle();
//    This statement won't work.  Put dphi by hand
    
    fTotalPhi = list->GetLayerDeltaPhi();
    fOffset   = 0.;
    
}

J4ITLayer::J4ITLayer(G4double 	           rmin,
                     G4double 	           rmax,
                     G4double 	           len,
                     G4double 	           offset, 
                     J4VDetectorComponent *parent,
                     G4int                 nclones,
                     G4int                 nbrothers, 
                     G4int                 me,
                     G4int                 copyno ) :
  	   J4VITDetectorComponent(fFirstName, parent, nclones, 
                                  nbrothers, me, copyno),
  	   fRmin(0), fRmax(0), fLen(0), fTotalPhi(0), fOffset(0) 
{   

    fRmin = rmin;
    fRmax = rmax;
    fLen  = len; 
    fTotalPhi = ((G4Tubs *)parent->GetLV()->GetSolid())->GetDeltaPhiAngle();
    fOffset   = offset;
    
    				
}

//=====================================================================
//* destructor --------------------------------------------------------

J4ITLayer::~J4ITLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4ITLayer::Assemble() 
{   
  if(!GetLV())
  {	  
    // define geometry

    J4ITParameterList * list = OpenParameterList();
      
    // MakeSolid ----------//
    OrderNewTubs (fRmin, fRmax, fLen, fTotalPhi );
    
    // MakeLogicalVolume --//  
    MakeLVWith(OpenMaterialStore()-> Order(list->GetLayerMaterial()));
    
    // SetVisAttribute ----//
    PaintLV(list->GetLayerVisAtt() , list->GetLayerColor());    
        
    // Install daughter PV //
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4ITLayer::Cabling()
{
  J4ITLayerSD* sd = new J4ITLayerSD(this);
  Register(sd);
  SetSD(sd);
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4ITLayer::InstallIn(J4VComponent         * /* mother */,
                          G4RotationMatrix     * /* prot   */, 
                          const G4ThreeVector  & /* tlate  */) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement();
  
  if (!GetSD()) Cabling(); 
  
}


//* Draw  --------------------------------------------------------
void J4ITLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4ITLayer::Print() const
{
}

	
	
