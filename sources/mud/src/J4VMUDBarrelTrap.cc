// $Id$
//*************************************************************************
//* --------------------
//* J4VMUDBarrelTrap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "G4Trap.hh"
#include "J4VMUDBarrelTrap.hh"
#include "J4MUDBarrelActive.hh"
#include "J4MUDBarrelAbs.hh"
#include "J4MUDBarrelActiveSD.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VMUDBarrelTrap::J4VMUDBarrelTrap(       const G4String& name, 
				    J4VDetectorComponent* parent,
                                                   G4int  nclones,
                                                   G4int  nbrothers, 
                                                   G4int  me,
                                                   G4int  copyno )
: J4VMUDDetectorComponent( name, parent, nclones, nbrothers, me, copyno  ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VMUDBarrelTrap::~J4VMUDBarrelTrap() {}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VMUDBarrelTrap::Assemble() 
{   
  if ( !GetLV() ) {

    J4MUDParameterList* ptrList = OpenParameterList();

     G4int    myID   = GetMyID();
     G4double len    = GetHalfL(myID);
     G4double thick  = GetThick(myID);
     G4double front  = GetFront(myID);

     // Make Trapezoid -----//
     G4double phitol = ptrList->GetPhiTolerance();
     G4double dphi   = ptrList->GetTrapDeltaPhi() - 2*phitol;
     G4double py     = 0.5*thick;
     G4double plx    = (front + thick)*std::tan(0.5*dphi);
     G4double px     = front*std::tan(0.5*dphi);
     G4double phi    = 0.0;

     // ------------------------------------------------------------------------ //
     //   in Barrel:                                                             //
     //                                                                          //
     //         \                   /   OM == rmin                               //
     //          \                 /    OA == OB == OM/std::cos( 0.5*arg(AOB) )  //
     //           C ---== N ==--- D     AM == BM == OM * std::tan( 0.5*arg(AOB) )//
     //            \  /   |   \  /    * MN == barrel_rmin - endcap_rmin          //
     //             \/    |    \/       CN == DN == ON * std::tan( 0.5*arg(AOB) )//
     //              \    |    /                                                 //
     //               A -_M_- B                                                  //
     //                \/ | \/          endcapInitialDy  == 0.5 * MN             //
     //                 \ | /           endcapInitialDx1 == AM                   //
     //                   O             endcapInitialDx2 == CN                   //
     //                                                                          //
     // ------------------------------------------------------------------------ //
     G4Trap* ptrTrap = new G4Trap( GetName(), len, 0., phi, py, px ,plx, 0., py, px, plx, 0. );
     Register( ptrTrap );
     SetSolid( ptrTrap );
  	
    // MakeLogicalVolume --//
    MakeLVWith( OpenMaterialStore()->Order( GetMaterial() ) );
        
    // SetVisAttribute ----//
    PaintLV( GetVisAtt(), GetColor() );
  }
}

void J4VMUDBarrelTrap::Cabling() 
{ }

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VMUDBarrelTrap::InstallIn( J4VComponent*        /* mother */,
                                  G4RotationMatrix*    /* prot   */, 
                                  const G4ThreeVector& /* tlate  */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.

  // Placement function into mother object...
  J4MUDParameterList* ptrList = OpenParameterList();
  
  G4int    myID     = GetMyID();
  G4int    motherID = GetMother()->GetMyID();
  G4double height   = GetFront( myID )+0.5*GetThick( myID );
  G4double phi      = ptrList->GetTrapDeltaPhi();
  G4double px       = height*std::cos(phi*motherID);
  G4double py       = height*std::sin(phi*motherID);
  G4double pz       = 0.0;
  G4ThreeVector position( px, py, pz );

  G4RotationMatrix* rotation = new G4RotationMatrix();
  G4double angle = 0.5*M_PI - phi*motherID;
  rotation->rotateZ( angle );
  SetPVPlacement( rotation, position );
  
  Cabling();
}

void J4VMUDBarrelTrap::Draw() { }
void J4VMUDBarrelTrap::Print() const { }
