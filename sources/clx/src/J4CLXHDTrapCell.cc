#include "J4CLXHDTrapCell.hh"
#include "J4CLXHDActiveSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXHDTrapCell::fFirstName= "HDTrapCell" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXHDTrapCell::J4CLXHDTrapCell(     J4VDetectorComponent* parent,
				      G4int  nclones,
				      G4int  nbrothers,
				      G4int  me,
				      G4int  copyno,
				      G4bool isXPlus)
    : J4VCLXTrapCell(fFirstName, parent, nclones, nbrothers, me, copyno, isXPlus)
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXHDTrapCell::~J4CLXHDTrapCell()
{
}

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4CLXHDTrapCell::Cabling()
{
    if(!GetSD()) {
	J4CLXHDActiveSD* sd = new J4CLXHDActiveSD(this);
	Register(sd);
	SetSD(sd);
    }
}
