#include "J4CLXHDBoxCell.hh"
#include "J4CLXHDActiveSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXHDBoxCell::fFirstName= "HDBoxCell" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXHDBoxCell::J4CLXHDBoxCell(J4VDetectorComponent* parent,
			       G4int  nclones,
			       G4int  nbrothers,
			       G4int  me,
			       G4int  copyno)
    : J4VCLXBoxCell(fFirstName, parent, nclones, nbrothers, me, copyno)
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXHDBoxCell::~J4CLXHDBoxCell()
{
}

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4CLXHDBoxCell::Cabling()
{
    if(!GetSD()) {
	J4CLXHDActiveSD* sd = new J4CLXHDActiveSD(this);
	Register(sd);
	SetSD(sd);
    }
}
