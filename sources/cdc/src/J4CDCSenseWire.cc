// $Id$
//*************************************************************************
//* --------------------
//* J4CDCSenseWire
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCSenseWire.hh"
#include "J4CDCSenseWireSD.hh"

#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CDCSenseWire::fFirstName("SenseWire");


//=====================================================================
//---------------------
// Class Description
//---------------------

//* constructor -------------------------------------------------------
J4CDCSenseWire::J4CDCSenseWire(J4VDetectorComponent *parent,
                                              G4int  nclones,
                                              G4int  nbrothers, 
                                              G4int  me,
                                              G4int  copyno ) :
  		J4VCDCDetectorComponent( fFirstName, parent, nclones, 
  					 nbrothers, me, copyno  ),
                fRot(0)
{
   G4double halflen      = GetZHalfLength(parent);
   G4double endrmin      = GetInnerRadius(parent);
   G4double endrmax      = GetOuterRadius(parent);
   G4double endwirer     = 0.5 * (endrmin + endrmax);
   G4String layertype    = GetLayerType();
   
   if (layertype != "A") {
      G4double halftwist    = 0.5 * GetTwistedAngle();
      G4double sinhalftwist = sin(halftwist);
      G4double coshalftwist = sqrt((1 + sinhalftwist)*(1 - sinhalftwist));

      G4double wireEndX = endwirer * coshalftwist;
      G4double wireEndY = endwirer * sinhalftwist;
      G4double stereoangle = atan2(wireEndY, halflen);

      fWireEnd.set(wireEndX, wireEndY, halflen);
      fRot = new G4RotationMatrix();
      Register(fRot);
      fRot->rotateX(-stereoangle);
   } else {
      fWireEnd.set(endwirer, 0., halflen);
   }
}

//* destructor --------------------------------------------------------
J4CDCSenseWire::~J4CDCSenseWire()
{
   if (Deregister(fRot))     delete fRot;
}

//* Assemble   --------------------------------------------------------
void J4CDCSenseWire::Assemble()
{
   if(!GetLV()) {
  		
      // define parameter
      J4CDCParameterList *list = OpenParameterList();
   
      G4double len  = GetZHalfLength(GetMother());
      G4double rmin = 0;
      G4double rmax = list->GetSenseWireRadius();
        
      // Asssemble LogicalVolume...
   
      // MakeSolid        
      OrderNewTubs(rmin, rmax, len );		  	       
    
      // Define LV    
      G4String material = list->GetSenseWireMaterial();
      MakeLVWith(OpenMaterialStore()->Order(material));
      
      // Set VisAttribute
      PaintLV (list->GetSenseWireVisAtt(), list->GetSenseWireColor());	  
  }
}

//* Cabling  ----------------------------------------------------------

void J4CDCSenseWire::Cabling()
{
  if(!GetLV()) Assemble(); 

  J4CDCSenseWireSD* sd = new J4CDCSenseWireSD(this);
  Register(sd);
  SetSD(sd);
}

//* InstallIn  --------------------------------------------------------

void J4CDCSenseWire::InstallIn(J4VComponent         *mother,
                               G4RotationMatrix     *prot, 
                               const G4ThreeVector  &tlate ) 
{
	
 //* Assemble its LogicalVolume...	 
  
  Assemble();		// You MUST call Assemble(); at first.
  
 //* Install the SenseWire in a DriftRegion...
   G4double rmin  = GetInnerWeist(GetMother());
   G4double rmax  = GetOuterWeist(GetMother());
   G4ThreeVector translate(0.5*(rmin + rmax), 0., 0.);
   G4double stereoangle = 0;
   if (fRot) {
      stereoangle = fRot->getDelta();
   }
   
   SetPVPlacement(fRot, translate);

  //if (!GetSD()) Cabling();     
}


//* SwitchOn  --------------------------------------------------------
void J4CDCSenseWire::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}

//* SwitchOff  --------------------------------------------------------
void J4CDCSenseWire::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//* Draw  --------------------------------------------------------
void J4CDCSenseWire::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDCSenseWire::Print() const
{
}

	
