#include "J4CLXHDLargeBoxCell.hh"
#include "J4CLXHDBoxCell.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXHDLargeBoxCell::fFirstName = "HDLargeBoxCell";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXHDLargeBoxCell::J4CLXHDLargeBoxCell(J4VDetectorComponent *parent,
					 G4int  nclones,
					 G4int  nbrothers,
					 G4int  me,
					 G4int  copyno )
    :J4VCLXLargeBoxCell(fFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXHDLargeBoxCell::~J4CLXHDLargeBoxCell()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4CLXHDLargeBoxCell::Cabling()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXBoxCell *J4CLXHDLargeBoxCell::CreateBox(J4VDetectorComponent *parent,
			     G4int nclones,
			     G4int nbrothers,
			     G4int me,
			     G4int copyno)
{
    return new J4CLXHDBoxCell(parent, nclones, nbrothers, me, copyno);
}
