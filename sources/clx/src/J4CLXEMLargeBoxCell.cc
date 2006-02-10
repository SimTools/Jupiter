#include "J4CLXEMLargeBoxCell.hh"
#include "J4CLXEMBoxCell.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CLXEMLargeBoxCell::fFirstName = "EMLargeBoxCell";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXEMLargeBoxCell::J4CLXEMLargeBoxCell(J4VDetectorComponent *parent,
					 G4int  nclones,
					 G4int  nbrothers,
					 G4int  me,
					 G4int  copyno )
    :J4VCLXLargeBoxCell(fFirstName, parent, nclones, nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEMLargeBoxCell::~J4CLXEMLargeBoxCell()
{
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4CLXEMLargeBoxCell::Cabling()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXBoxCell *J4CLXEMLargeBoxCell::CreateBox(J4VDetectorComponent *parent,
			     G4int nclones,
			     G4int nbrothers,
			     G4int me,
			     G4int copyno)
{
    return new J4CLXEMBoxCell(parent, nclones, nbrothers, me, copyno);
}
