// $Id$
//*************************************************************************
//* --------------------
//* J4MUDBarrel
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4MUDBarrel.hh"
#include "J4MUDBarrelSD.hh"
#include "J4MUDParameterList.hh"

G4String J4MUDBarrel::fFirstName( "Barrel" );

//=====================================================================
//* constructor -------------------------------------------------------
J4MUDBarrel::J4MUDBarrel( J4VDetectorComponent* parent,
                                       G4int  nclones,
                                       G4int  nbrothers, 
                                       G4int  me,
                                       G4int  copyno )
 : J4VMUDDetectorComponent( fFirstName, parent, nclones, nbrothers, me, copyno ),
   fRmin(0), fRmax(0), fLen(0), fDeltaPhi(0)
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4MUDBarrel::~J4MUDBarrel() { }

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4MUDBarrel::Assemble() 
{   
  if ( !GetLV() )
  {	  
    // define geometry
    //    J4MUDParameterList * ptrList = OpenParameterList();

  // Define Barrel parameters ----------------//    
  J4MUDParameterList * ptrList = OpenParameterList();

  G4int myid = GetMyID();

  fRmin     = ptrList -> GetBarrelInnerR(myid);
  fRmax     = ptrList -> GetBarrelOuterR(myid);
  fLen      = ptrList -> GetBarrelHalfZ();
  fDeltaPhi = ptrList -> GetBarrelDeltaPhi();

#if 0  
  G4cerr << myid << " "
	 << fRmin << " "
	 << fRmax << " "
	 << fLen << " "
	 << fDeltaPhi << " "
	 << G4endl;
#endif
  
  // MakeSolid ----------//
  OrderNewTubs ( fRmin, fRmax, fLen, fDeltaPhi );
    
  // MakeLogicalVolume --//  
  MakeLVWith( OpenMaterialStore()->Order( ptrList->GetBarrelMaterial() ) );
    
  // SetVisAttribute ----//
  PaintLV( ptrList->GetBarrelVisAtt(), ptrList->GetBarrelColor() );    
        
  // Install daughter PV //
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4MUDBarrel::Cabling()
{
  J4MUDBarrelSD* sd = new J4MUDBarrelSD( this );
  Register( sd );
  SetSD( sd );
} 

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4MUDBarrel::InstallIn( J4VComponent*        /* mother */,
                             G4RotationMatrix*    /* prot   */, 
                             const G4ThreeVector& /* tlate  */ )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  
  // Placement function into mother object ------//
  SetPVPlacement();
  
  if ( !GetSD() ) Cabling(); 
}
