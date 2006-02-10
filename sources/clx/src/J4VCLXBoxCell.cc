#include "J4VCLXBoxCell.hh"
#include "J4CLXParameterList.hh"
#include "G4Box.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXBoxCell::J4VCLXBoxCell(       const G4String& name,
			      J4VDetectorComponent* parent,
			      G4int  nclones,
			      G4int  nbrothers,
			      G4int  me,
			      G4int  copyno )
    : J4VCLXCell( name, parent, nclones, nbrothers, me, copyno  )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXBoxCell::~J4VCLXBoxCell()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCLXBoxCell::Assemble()
{
    if(!GetLV()) {
	G4Box *mother = (G4Box *)(GetMother() -> GetSolid());

	G4double pz = mother -> GetZHalfLength();
	G4double py = mother -> GetYHalfLength();
	G4double px = .5 * OpenParameterList() -> GetCellSize();

	G4Box *ptrBoxCell = new G4Box(GetName(), px, py, pz);
	Register(ptrBoxCell);
	SetSolid(ptrBoxCell);

	// MakeLogicalVolume --//
	MakeLVWith(OpenMaterialStore()->Order(GetMaterial()));


	// SetVisAttribute ----//
	PaintLV(GetVisAtt(), GetColor());

    }
}

//=====================================================================
//* Cabling   ---------------------------------------------------------
void J4VCLXBoxCell::Cabling() {}

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VCLXBoxCell::InstallIn( J4VComponent*        /* mother */,
			    G4RotationMatrix*    /* prot   */,
			    const G4ThreeVector& /* tlate  */ )
{
    Assemble();			// You MUST call Assemble(); at first.

    //Placement function into mother object
    G4double stepX = OpenParameterList() -> GetCellSize();

    G4double offset = .5 * stepX - (G4int)(GetNclones() / 2) * stepX;
    SetPVReplica(kXAxis, stepX, offset);

    Cabling();
}

void J4VCLXBoxCell::Draw() { }
void J4VCLXBoxCell::Print() const { }
