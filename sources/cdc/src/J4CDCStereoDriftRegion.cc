// $Id$
//*************************************************************************
//* --------------------
//* J4CDCStereoDriftRegion
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCStereoDriftRegion.hh"
#include "J4CDCSenseWire.hh"
#include "J4CDCStereoDriftRegionSD.hh"

//************************************************************************
//--------------------------------
// constants (detector parameters)
//--------------------------------



G4String J4CDCStereoDriftRegion::fFirstName("StereoDriftRegion");


//************************************************************************
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCStereoDriftRegion::J4CDCStereoDriftRegion(J4VDetectorComponent *parent,
                                   G4int                 nclones,
                                   G4int                 nbrothers, 
                                   G4int                 me,
                                   G4int                 copyno ) :
  		  J4VCDCDetectorComponent( fFirstName, parent, nclones,
                                           nbrothers, me, copyno ), 
                  fSenseWire(0)
{
#if 0
   G4cerr << "J4CDCDriftRegion:: -----------------------------" << G4endl;
   G4cerr << " motherendrmin = " << GetInnerRadius(parent) << G4endl;
   G4cerr << " motherendrmax = " << GetOuterRadius(parent) << G4endl;
   G4cerr << " motherendr    = " << 0.5*(GetInnerRadius(parent)
                           + GetOuterRadius(parent)) << G4endl;
   G4cerr << " motherhalflen = " << GetZHalfLength(parent) << G4endl;
   G4cerr << " motherrmin    = " << GetInnerWeist(parent) << G4endl;
   G4cerr << " motherrmax    = " << GetOuterWeist(parent) << G4endl;
   G4cerr << " motherwirer   = " << 0.5*(GetInnerWeist(parent)
                            + GetOuterWeist(parent)) << G4endl;
#endif
}


//=====================================================================
//* destructor --------------------------------------------------------

J4CDCStereoDriftRegion::~J4CDCStereoDriftRegion()
{	
  if(Deregister(fSenseWire)) delete fSenseWire;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCStereoDriftRegion::Assemble()
{   
  if(!GetLV())
  {	  
    // define parameters
     J4CDCParameterList *list = OpenParameterList();
     G4double motherRmin  = GetInnerRadius(GetMother());
     G4double halfzlen    = GetZHalfLength(GetMother());
     G4double motherdphi  = GetDeltaPhi(GetMother());
     G4double twistedAng  = GetTwistedAngle();
             
     G4int    myid        = GetMyID();
     G4double thick       = list->GetDriftRegionThick();
     G4double dummythick  = list->GetDummyDriftRegionThick();
     G4double endinnerrad = motherRmin 
                            + thick * (myid) + dummythick;
     G4double endouterrad = motherRmin
                            + thick * (myid + 1) + dummythick;
#if 0
     G4cerr << "J4CDCDriftRegion::Assemble -----------------------------" << G4endl;
     G4cerr << " motherendrmin = " << motherRmin << G4endl;
     G4cerr << " endinnerrad   = " << endinnerrad << G4endl;
     G4cerr << " endouterrad   = " << endinnerrad << G4endl;
     G4cerr << " motherdphi    = " << motherdphi << G4endl;
#endif
     
    // MakeSolid ----------//
     J4TwistedTubs* driftregion = new J4TwistedTubs(GetName(),
                                                    twistedAng,
                                                    endinnerrad,
                                                    endouterrad,
                                                    halfzlen,
                                                    motherdphi);
     Register(driftregion);
     SetSolid(driftregion);

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

void J4CDCStereoDriftRegion::Cabling()
{
  J4CDCStereoDriftRegionSD* sd = new J4CDCStereoDriftRegionSD(this);
  Register(sd);
  SetSD(sd);
}
//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCStereoDriftRegion::InstallIn(J4VComponent         *mother,
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
void J4CDCStereoDriftRegion::SwitchOn(G4String opt)
{
  J4VDetectorComponent::SwitchOn(opt);
}

//=====================================================================
//* SwitchOff  --------------------------------------------------------
void J4CDCStereoDriftRegion::SwitchOff(G4String opt)
{
  J4VDetectorComponent::SwitchOff(opt);
}

//=====================================================================
//* Draw  --------------------------------------------------------

void J4CDCStereoDriftRegion::Draw()
{
  // set visualization attributes
  
}
	
//=====================================================================
//* Print  --------------------------------------------------------

void J4CDCStereoDriftRegion::Print() const
{
}

	
	
