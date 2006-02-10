#include "J4VCLXBoard.hh"
#include "G4Trap.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXBoard::J4VCLXBoard(       const G4String& name,
					J4VDetectorComponent* parent,
					G4int  nclones,
					G4int  nbrothers,
					G4int  me,
					G4int  copyno )
    : J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno  )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXBoard::~J4VCLXBoard()
{
    if(Deregister(fLargeBoxCell)) delete fLargeBoxCell;

    G4int nTraps = pTraps.size();
    for(G4int i = 0; i < nTraps; ++i) {
	if(pTraps[i] && Deregister(pTraps[i])) delete pTraps[i];
	}
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCLXBoard::Assemble()
{
    if(!GetLV()) {
	G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());

	G4double px = mother -> GetXHalfLength1();
	G4double plx = mother -> GetXHalfLength2();
	G4double py = mother -> GetYHalfLength1();
	G4double pz = .5 * OpenParameterList() -> GetCellSize();
	G4double phi = 0.0;

	G4Trap* ptrBoard = new G4Trap(GetName(), pz , 0., phi, py, px, plx, 0., py, px, plx, 0.);
	Register(ptrBoard);
	SetSolid(ptrBoard);

	// MakeLogicalVolume --//
	MakeLVWith(OpenMaterialStore()->Order(OpenParameterList()->GetBoardMaterial()));

	// SetVisAttribute ----//
	PaintLV(OpenParameterList()->GetBoardVisAtt(), OpenParameterList()->GetBoardColor());

	// Make AbsLayer and ActiveLayer objects ---//
	fLargeBoxCell = CreateLargeBoxCell(this);
	Register(fLargeBoxCell);
	fLargeBoxCell -> InstallIn(this);
	SetDaughter(fLargeBoxCell);

	for(G4int i = 0; i <= 1; ++i) {                                      //(0, 1) = (minus, plus)
	    J4VCLXTrapCell* fTrapCell = CreateTrap(this, 1, 2, i, -1, i);
	    pTraps.push_back(fTrapCell);
	    Register(fTrapCell);
	    fTrapCell -> InstallIn(this);
	    SetDaughter(fTrapCell);
	    }
    }
}

//=====================================================================
//* Cabling   ---------------------------------------------------------
void J4VCLXBoard::Cabling() {}

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VCLXBoard::InstallIn(J4VComponent*        /* mother */,
			    G4RotationMatrix*    /* prot   */,
			    const G4ThreeVector& /* tlate  */ )
{
    Assemble();			// You MUST call Assemble(); at first.

    //Placement function into mother object
    G4double stepZ = OpenParameterList() -> GetCellSize();
    G4double startZ = - .5 * GetNclones() * stepZ + .5 * stepZ;

    SetPVReplica(kZAxis, stepZ, startZ);

    Cabling();
}

void J4VCLXBoard::Draw() { }
void J4VCLXBoard::Print() const { }
