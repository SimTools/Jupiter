#include "J4CLXEMTrapCell.hh"
#include "J4CLXEMActiveSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXEMTrapCell::fFirstName= "EMTrapCell" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXEMTrapCell::J4CLXEMTrapCell(     J4VDetectorComponent* parent,
				      G4int  nclones,
				      G4int  nbrothers,
				      G4int  me,
				      G4int  copyno,
				      G4bool isXPlus)
    : J4VCLXTrapCell(fFirstName, parent, nclones, nbrothers, me, copyno, isXPlus)
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEMTrapCell::~J4CLXEMTrapCell()
{
}

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4CLXEMTrapCell::Cabling()
{
    if(!GetSD()) {
	J4CLXEMActiveSD* sd = new J4CLXEMActiveSD(this);
	Register(sd);
	SetSD(sd);
    }
}
