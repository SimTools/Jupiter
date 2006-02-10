#include "J4VCLXTrapCell.hh"
#include "J4CLXParameterList.hh"
#include "G4Trap.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXTrapCell::J4VCLXTrapCell(       const G4String& name,
				      J4VDetectorComponent* parent,
				      G4int  nclones,
				      G4int  nbrothers,
				      G4int  me,
				      G4int  copyno,
				      G4bool isXPlus)
    : J4VCLXCell( name, parent, nclones, nbrothers, me, copyno  ),
      xPlus(isXPlus)
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXTrapCell::~J4VCLXTrapCell()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCLXTrapCell::Assemble()
{
    if(!GetLV()) {
	G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());

	G4double mpx = mother -> GetXHalfLength1();
	G4double mplx = mother -> GetXHalfLength2();
	G4double stepX = OpenParameterList() -> GetCellSize();

	G4double pz = mother -> GetZHalfLength();
	G4double py = mother -> GetYHalfLength1();
	G4double px = .5 * (mpx - (G4int)(mpx / stepX) * stepX);
	G4double plx = .5 * (mplx - (G4int)(mpx / stepX) * stepX);

	G4double phi = 0.;
	G4double alp = std::atan((plx - px) / (2 * py));
	if(!IsXPlus()) alp = -alp;

	G4Trap *ptrTrapCell = new G4Trap(GetName(), pz, 0., phi, py, px, plx, alp, py, px, plx, alp);
	Register(ptrTrapCell);
	SetSolid(ptrTrapCell);

	// MakeLogicalVolume --//
	MakeLVWith(OpenMaterialStore()->Order(GetMaterial()));

	// SetVisAttribute ----//
	PaintLV(GetVisAtt(), GetColor());

    }
}

//=====================================================================
//* Cabling   ---------------------------------------------------------
void J4VCLXTrapCell::Cabling() {}

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VCLXTrapCell::InstallIn( J4VComponent*        /* mother */,
			    G4RotationMatrix*    /* prot   */,
			    const G4ThreeVector& /* tlate  */ )
{
    Assemble();			// You MUST call Assemble(); at first.

    //Placement function into mother object
    G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());
    G4double mpx = mother -> GetXHalfLength1();
    G4double mplx = mother -> GetXHalfLength2();
    G4double stepX = OpenParameterList() -> GetCellSize();
    G4double boxLength = (G4int)(mpx / stepX) * stepX;
    G4double px = .5 * (mpx - boxLength);
    G4double plx = .5 * (mplx - boxLength);

    G4double z = 0.;
    G4double y = 0.;
    G4double x = boxLength + .5 * (plx + px);
    if(!IsXPlus()) x = -x;

    G4ThreeVector position(x, y, z);
    SetPVPlacement(0, position);

    Cabling();
}

void J4VCLXTrapCell::Draw() { }
void J4VCLXTrapCell::Print() const { }
