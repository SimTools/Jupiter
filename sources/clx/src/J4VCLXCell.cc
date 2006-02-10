#include "J4VCLXCell.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXCell::J4VCLXCell(       const G4String& name,
			      J4VDetectorComponent* parent,
			      G4int  nclones,
			      G4int  nbrothers,
			      G4int  me,
			      G4int  copyno )
    : J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno  )
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXCell::~J4VCLXCell()
{}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCLXCell::Assemble()
{}

//=====================================================================
//* Cabling   ---------------------------------------------------------
void J4VCLXCell::Cabling() {}

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VCLXCell::InstallIn( J4VComponent*        /* mother */,
			    G4RotationMatrix*    /* prot   */,
			    const G4ThreeVector& /* tlate  */ )
{}

void J4VCLXCell::Draw() { }
void J4VCLXCell::Print() const { }
