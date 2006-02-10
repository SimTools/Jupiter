#include "J4VCLXLargeBoxCell.hh"
#include "J4CLXParameterList.hh"
#include "G4Trap.hh"
#include "G4Box.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXLargeBoxCell::J4VCLXLargeBoxCell(const G4String       &name,
				       J4VDetectorComponent *parent,
				       G4int  nclones,
				       G4int  nbrothers,
				       G4int  me,
				       G4int  copyno )
    :J4VCLXDetectorComponent(name, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXLargeBoxCell::~J4VCLXLargeBoxCell()
{
    if(Deregister(fBoxCell)) delete fBoxCell;
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCLXLargeBoxCell::Assemble()
{
    if(!GetLV()) {
	G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());
	J4CLXParameterList *ptrList = OpenParameterList();

	G4double cellSize = ptrList -> GetCellSize();

	G4double pz = mother -> GetZHalfLength();
	G4double py = mother -> GetYHalfLength1();
	G4double px = (G4int)(mother -> GetXHalfLength1() / cellSize) * cellSize;

	// MakeSolid ----------//
	G4Box* largeBoxCell = new G4Box(GetName(), px, py, pz);
	Register(largeBoxCell);
	SetSolid(largeBoxCell);

	// MakeLogicalVolume --//
	MakeLVWith( OpenMaterialStore() -> Order(ptrList -> GetLargeBoxCellMaterial()));

	// SetVisAttribute ----//
	PaintLV( ptrList -> GetLargeBoxCellVisAtt(), ptrList -> GetLargeBoxCellColor());

	// Make AbsLayer and ActiveLayer objects ---//
	G4int nCells = 2 * (G4int)(px / cellSize);
	fBoxCell = CreateBox(this, nCells);
	Register(fBoxCell);
	fBoxCell -> InstallIn(this);
	SetDaughter(fBoxCell);

    }
}
//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4VCLXLargeBoxCell::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VCLXLargeBoxCell::InstallIn( J4VComponent*        /* mother */ ,
                                G4RotationMatrix*    /* prot   */ , 
                                const G4ThreeVector& /* tlate  */  ) 
{
   Assemble();			// You MUST call Assemble(); at first.

   // Placement function into mother object...
   SetPVPlacement();

   // Cablig for SD
   Cabling();
}

//=====================================================================
//* Draw  --------------------------------------------------------
void J4VCLXLargeBoxCell::Draw()
{
   // set visualization attributes
}

//* Print  --------------------------------------------------------
void J4VCLXLargeBoxCell::Print() const
{ }
