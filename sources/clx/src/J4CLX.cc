// $Id$
//*************************************************************************
//* --------------------
//* J4CLX
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
#include "J4CLX.hh"
#include "J4CLXSD.hh"
#include "J4Timer.hh"
#include "J4CLXBlock.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLX::fFirstName= "CLX" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLX::J4CLX( J4VDetectorComponent *parent,
                             G4int  nclones,
                             G4int  nbrothers,
                             G4int  me,
                             G4int  copyno )
: J4VCLXDetectorComponent( fFirstName, parent, nclones,
                                       nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLX::~J4CLX()
{
    if ( fBlock ) {
	J4CLXParameterList *ptrList = OpenParameterList();
	G4int nTraps = ptrList->GetNTraps();
	for ( G4int i = 0; i < nTraps; i++ ) {
	    if (Deregister(fBlock[i])) delete fBlock[i];
	}
	if (Deregister(fBlock)) delete [] fBlock;
    }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CLX::Assemble()
{   
   if ( !GetLV() ) {

      J4CLXParameterList *ptrList = OpenParameterList(); 

      G4double rmin        = ptrList -> GetCLXInnerR();
      G4double rmax        = ptrList -> GetCLXOuterR();
      G4double len         = ptrList -> GetCLXOuterHalfZ();
      G4double dphi        = ptrList -> GetCLXDeltaPhi();
      G4double endcaprmin  = ptrList -> GetEndcapInnerR();
      G4double endcaphalfz = 0.5 * ( len - ptrList->GetCLXInnerHalfZ() );

      // MakeSolid ----------//
      OrderNewTubs( rmin, rmax, len, dphi, endcaphalfz, endcaprmin );
    
      // MakeLogicalVolume --//  
      MakeLVWith( OpenMaterialStore()->Order(ptrList->GetCLXMaterial()) );
    
      // SetVisAttribute ----//
      PaintLV( ptrList->GetCLXVisAtt(), ptrList->GetCLXColor() );
 
      // Install daughter PV //
      const G4int nTraps = ptrList->GetNTraps();

      fBlock = new J4CLXBlock* [nTraps];
      for ( G4int i = 0; i < nTraps; i++ ) {
	 fBlock[i] = new J4CLXBlock( this, nTraps, 1, 0, i );
         Register( fBlock[i] );
         fBlock[i] -> InstallIn( this );
         SetDaughter( fBlock[i] );
	 }
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CLX::Cabling()
{
    if(!GetSD()) {
	J4CLXSD* sd = new J4CLXSD(this);
	Register(sd);
	SetSD(sd);
    }

}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CLX::InstallIn( J4VComponent*         /* mother */,
                       G4RotationMatrix*     /* prot   */, 
                       const G4ThreeVector&  /* tlate  */  )
{ 
  static G4int timerID = -1;
  J4Timer timer( timerID, "J4CLX", "InstallIn()" );
  timer.Start(); 

  Assemble();			// You MUST call Assemble(); at first.
  
  // Placement function into mother object...
  SetPVPlacement();
  
  // Cabling function to install SD
  Cabling();

  timer.Stop();
}


//* Draw  --------------------------------------------------------
void J4CLX::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CLX::Print() const
{
}
