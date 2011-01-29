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
  		  J4VCDCDriftRegion( fFirstName, parent, nclones,
                                           nbrothers, me, copyno ) 
{
#if 0
   std::cerr << "J4CDCStereoDriftRegion:: -----------------------------" << std::endl;
   std::cerr << " motherendrmin = " << GetInnerRadius(parent) << std::endl;
   std::cerr << " motherendrmax = " << GetOuterRadius(parent) << std::endl;
   std::cerr << " motherendr    = " << 0.5*(GetInnerRadius(parent)
                           + GetOuterRadius(parent)) << std::endl;
   std::cerr << " motherhalflen = " << GetZHalfLength(parent) << std::endl;
   std::cerr << " motherrmin    = " << GetInnerWeist(parent) << std::endl;
   std::cerr << " motherrmax    = " << GetOuterWeist(parent) << std::endl;
   std::cerr << " motherwirer   = " << 0.5*(GetInnerWeist(parent)
                            + GetOuterWeist(parent)) << std::endl;
#endif
}

J4CDCStereoDriftRegion::J4CDCStereoDriftRegion(
                        const J4CDCStereoDriftRegion &orig,
                              G4int                   copyno ) :
  		  J4VCDCDriftRegion( orig, copyno )
{
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
     G4double motherRmin      = GetInnerRadius(GetMother());
     G4double halfzlen        = GetZHalfLength(GetMother());
     G4double motherdphi      = GetDeltaPhi(GetMother());
     G4double twistedAng      = GetTwistedAngle();

             
     G4int    myid            = GetMyID();
     G4double thick           = list->GetDriftRegionThick();
     G4double dummythick      = list->GetDummyDriftRegionThick();
     G4double centerradius    = motherRmin + thick * (myid + 0.5) + dummythick;

     G4double measplanehalfthick = list->GetMeasPlaneHalfThick();
     G4double endinnerradius   = centerradius - measplanehalfthick;
     G4double endouterradius   = centerradius + measplanehalfthick;

     fTanStereo   = CalcTanStereo(twistedAng, centerradius, halfzlen);
     fRwaist      = CalcWaist(fTanStereo, centerradius, halfzlen);

#if 0
     std::cerr << "J4CDCStereoDriftRegion::Assemble -----------------------------" << std::endl;
     std::cerr << " motherendrmin = " << motherRmin << std::endl;
     std::cerr << " endinnerradius= " << endinnerradius << std::endl;
     std::cerr << " endouterradius= " << endinnerradius << std::endl;
     std::cerr << " motherdphi    = " << motherdphi << std::endl;
#endif
     
    // MakeSolid ----------//
     J4TwistedTubs* driftregion = new J4TwistedTubs(GetName(),
                                                    twistedAng,
                                                    endinnerradius,
                                                    endouterradius,
                                                    halfzlen,
                                                    motherdphi);
     Register(driftregion);
     SetSolid(driftregion);

     // MakeLogicalVolume --//
     G4String material = list->GetDriftRegionMaterial();
     MakeLVWith(OpenMaterialStore()->Order(material));
    
     // TwistedTubs MUST NOT OPTIMIZE !!
     GetLV()->SetOptimisation(FALSE);

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

void J4CDCStereoDriftRegion::InstallIn(J4VComponent  *,
                                 G4RotationMatrix    *,
                                 const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
    
  SetPVPlacement(0,G4ThreeVector(0.));
  
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

	
	
