// $Id$
//*************************************************************************
//* --------------------
//* J4CTLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CTLayer.hh"
#include "J4CTLayerSD.hh"
#include "J4CTParameterList.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4CTLayer::fFirstName("Layer");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CTLayer::J4CTLayer(J4VDetectorComponent* parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
  	   J4VCTDetectorComponent(fFirstName, parent, nclones,
                                  nbrothers, me, copyno),
  	   fRmin(0), fRmax(0), fLen(0), fTotalPhi(0), fOffset(0)
{   

  // Define Layer parameters ----------------//    

    J4CTParameterList * list = OpenParameterList();

    fRmin     = list->GetLayerInnerR(me);
    fRmax     = list->GetLayerOuterR(me);
    fLen      = list->GetLayerHalfZ(me);
    fTotalPhi = ((G4Tubs *)parent->GetLV()->GetSolid())->GetDeltaPhiAngle();
    fOffset   = 0.;
    
}

J4CTLayer::J4CTLayer(G4double 	           rmin,
                     G4double 	           rmax,
                     G4double 	           len,
                     G4double 	           offset, 
                     J4VDetectorComponent *parent,
                     G4int                 nclones,
                     G4int                 nbrothers, 
                     G4int                 me,
                     G4int                 copyno ) :
  	   J4VCTDetectorComponent(fFirstName, parent, nclones, 
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

J4CTLayer::~J4CTLayer()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CTLayer::Assemble() 
{   
  if(!GetLV())
  {	  
    // define geometry

    J4CTParameterList * list = OpenParameterList();
      
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

void J4CTLayer::Cabling()
{
  J4CTLayerSD* sd = new J4CTLayerSD(this);
  Register(sd);
  SetSD(sd);
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CTLayer::InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot, 
                          const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object ------//
  
  SetPVPlacement();
  
  if (!GetSD()) Cabling(); 
  
}


//* Draw  --------------------------------------------------------
void J4CTLayer::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CTLayer::Print() const
{
}

	
	
