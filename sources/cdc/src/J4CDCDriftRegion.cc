// $Id$
//*************************************************************************
//* --------------------
//* J4CDCDriftRegion
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCDriftRegion.hh"
#include "J4CDCDriftRegionSD.hh"
#include "J4CDCSenseWire.hh"

//************************************************************************
//--------------------------------
// constants (detector parameters)
//--------------------------------



G4String J4CDCDriftRegion::fFirstName("DriftRegion");


//************************************************************************
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCDriftRegion::J4CDCDriftRegion(J4VDetectorComponent *parent,
                                   G4int                 nclones,
                                   G4int                 nbrothers, 
                                   G4int                 me,
                                   G4int                 copyno ) :
  		  J4VCDCDetectorComponent( fFirstName, parent, nclones,
                                           nbrothers, me, copyno ), 
                  fSenseWire(0)
{   
}


//=====================================================================
//* destructor --------------------------------------------------------

J4CDCDriftRegion::~J4CDCDriftRegion()
{	
  if(Deregister(fSenseWire)) delete fSenseWire;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCDriftRegion::Assemble()
{   
  if(!GetLV())
  {	  
    // define parameters
     J4CDCParameterList *list = OpenParameterList();
     
     G4double len        = GetZHalfLength(GetMother());
     G4double motherRmin = GetInnerRadius(GetMother());
     G4double dphi       = GetDeltaPhi(GetMother());
        
     G4int    myid       = GetMyID();
     G4double thick      = list->GetDriftRegionThick();
     G4double dummythick = list->GetDummyDriftRegionThick();
     G4double rmin       = motherRmin + thick * (myid) + dummythick;
     G4double rmax       = motherRmin + thick * (myid + 1) + dummythick;
       
    // MakeSolid ----------//
    OrderNewTubs (rmin, rmax, len, dphi );

    // MakeLogicalVolume --//
    G4String material = list->GetDriftRegionMaterial();
    MakeLVWith(OpenMaterialStore()->Order(material));
    
    // SetVisAttribute ----//
    PaintLV(list->GetDriftRegionVisAtt(),
            list->GetDriftRegionColor());   
    
         
    // Install daughter PV //
    // Install Sense Wire  //

    fSenseWire = new J4CDCSenseWire(this);
    Register(fSenseWire);
    fSenseWire->InstallIn(this);
    
    SetDaughter(fSenseWire);

  }
    
}

//=====================================================================
//* Cabling   ---------------------------------------------------------

void J4CDCDriftRegion::Cabling()
{

  J4CDCDriftRegionSD* sd = new J4CDCDriftRegionSD(this);
  Register(sd);
  SetSD(sd);
	
}
//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCDriftRegion::InstallIn(J4VComponent         *mother,
                                 G4RotationMatrix     *prot, 
                                 const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
    
  SetPVPlacement(0,0);
  
  if (!GetSD()) Cabling();
  
}

//=====================================================================
//* SwitchOn  --------------------------------------------------------
void J4CDCDriftRegion::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}

//=====================================================================
//* SwitchOff  --------------------------------------------------------
void J4CDCDriftRegion::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//=====================================================================
//* Draw  --------------------------------------------------------

void J4CDCDriftRegion::Draw()
{
  // set visualization attributes
  
}
	
//=====================================================================
//* Print  --------------------------------------------------------

void J4CDCDriftRegion::Print() const
{
}

	
	
