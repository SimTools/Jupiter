// $Id$
//*************************************************************************
//* --------------------
//* J4VMUDEndcapTrap
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "G4Trap.hh"
#include "J4VMUDEndcapTrap.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VMUDEndcapTrap::J4VMUDEndcapTrap(       const G4String& name, 
				    J4VDetectorComponent* parent,
                                                   G4int  nclones,
                                                   G4int  nbrothers, 
                                                   G4int  me,
                                                   G4int  copyno )
: J4VMUDDetectorComponent( name, parent, nclones, nbrothers, me, copyno  ) 
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VMUDEndcapTrap::~J4VMUDEndcapTrap() {}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VMUDEndcapTrap::Assemble() 
{   
  if ( !GetLV() ) {

    J4MUDParameterList* ptrList = OpenParameterList();

     G4int myID = GetMyID();
     G4double rmin   = ptrList->GetEndcapInnerR();
     G4double height = GetHeight(myID) - rmin;
     G4double thick  = GetThick();
     G4double len    = 0.5*thick;

     // Make Trapezoid -----//
     G4double dphi   = ptrList->GetTrapDeltaPhi();
     G4double py     = 0.5 * height;
     G4double plx    = GetHeight( myID )*tan( 0.5*dphi );
     G4double px     = rmin*tan(0.5*dphi);
     G4double phi    = 0.0;

     // ------------------------------------------------------------------------ //
     //   in Endcap:                                                             //
     //                                                                          //
     //         \                   /   OM == rmin                               //
     //          \                 /    OA == OB == OM/cos( 0.5*arg(AOB) )       //
     //           C ---== N ==--- D     AM == BM == OM * tan( 0.5*arg(AOB) )     //
     //            \  /   |   \  /    * MN == barrel_rmin - endcap_rmin          //
     //             \/    |    \/       CN == DN == ON * tan( 0.5*arg(AOB) )     //
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

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4VMUDEndcapTrap::Cabling() 
{ }

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VMUDEndcapTrap::InstallIn( J4VComponent*        /* mother */,
                                  G4RotationMatrix*    /* prot */, 
                                  const G4ThreeVector& /* tlate  */ ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.

  // Placement function into mother object...
  J4MUDParameterList* ptrList = OpenParameterList();
  G4int    myID     = GetMyID();
  G4int    motherID = GetMother()->GetMyID();
  G4double rmin     = ptrList->GetEndcapInnerR();
  G4double height   = rmin + 0.5 * ( GetHeight(myID) - rmin );
  G4double phi      = ptrList->GetTrapDeltaPhi();
  
  G4double px       = height*cos(phi*motherID);
  G4double py       = height*sin(phi*motherID);
  G4double pz       = GetEndcapZ( myID );

  G4ThreeVector position( px, py, pz );
  
  G4RotationMatrix* rotation = new G4RotationMatrix();
  G4double angle = 0.5*M_PI - phi*motherID;
  rotation->rotateZ(angle);

  if ( myID < GetNLayers() )
    position.setZ(position.z());
  else
    position.setZ(-position.z());
  
  SetPVPlacement( rotation, position );

  Cabling();
}

void J4VMUDEndcapTrap::Draw() { }
void J4VMUDEndcapTrap::Print() const { }
