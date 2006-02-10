// $Id$
//*************************************************************************
//* --------------------
//* J4VCLXSubLayer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXSubLayer.hh"
#include "J4VCLXBoard.hh"
#include "J4CLXParameterList.hh"
#include "G4Trap.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4VCLXSubLayer::J4VCLXSubLayer( const G4String       &name,
                                J4VDetectorComponent *parent,
                                               G4int  nclones,
                                               G4int  nbrothers,
                                               G4int  me,
                                               G4int  copyno )
: J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCLXSubLayer::~J4VCLXSubLayer()
{
    if(Deregister(fBoard)) delete fBoard;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VCLXSubLayer::Assemble()
{
    if(!GetLV()){
	G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());

	G4double pz = mother -> GetZHalfLength();
	G4double py = .5 * GetEndThickness();
	G4double px = GetPx();
	G4double plx = GetPlx();
	G4double phi = 0.;

	// MakeSolid ----------//
	G4Trap* sublayer = new G4Trap(GetName(), pz, 0., phi, py, px, plx, 0, py, px, plx, 0);
	Register( sublayer );
	SetSolid( sublayer );

	// MakeLogicalVolume --//
	MakeLVWith( OpenMaterialStore() -> Order( GetMaterial()));

	// SetVisAttribute ----//
	PaintLV( GetVisAtt(), GetColor());

	// Install daughter PV //
	if(IsActive()) {
	    G4double stepZ = OpenParameterList() -> GetCellSize();
	    G4int nBoards = 2 * (G4int)(pz / stepZ);
	    fBoard = Create(this, nBoards);
	    Register(fBoard);
	    fBoard -> InstallIn(this);
	    SetDaughter(fBoard);
	}
    }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VCLXSubLayer::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VCLXSubLayer::InstallIn( J4VComponent*        /* mother */ ,
                                G4RotationMatrix*    /* prot   */ , 
                                const G4ThreeVector& /* tlate  */  ) 
{
   Assemble();			// You MUST call Assemble(); at first.

   // Placement function into mother object...
     G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());
     G4double mHalfThickness = mother -> GetYHalfLength1();

   G4double x = 0.;
   G4double y = GetStartThickness() + .5 * GetEndThickness() - mHalfThickness;
   G4double z = 0.;

   G4ThreeVector position(x, y, z);
   SetPVPlacement(0, position);

   // Cablig for SD
   Cabling();
}

//=====================================================================
//* Draw  --------------------------------------------------------
void J4VCLXSubLayer::Draw()
{
   // set visualization attributes
}

//* Print  --------------------------------------------------------
void J4VCLXSubLayer::Print() const
{ }
