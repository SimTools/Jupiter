#include "J4CLXEMBoxCell.hh"
#include "J4CLXEMActiveSD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXEMBoxCell::fFirstName= "EMBoxCell" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXEMBoxCell::J4CLXEMBoxCell(J4VDetectorComponent* parent,
			       G4int  nclones,
			       G4int  nbrothers,
			       G4int  me,
			       G4int  copyno)
    : J4VCLXBoxCell(fFirstName, parent, nclones, nbrothers, me, copyno)
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEMBoxCell::~J4CLXEMBoxCell()
{
}

//=====================================================================
//* Cabling -----------------------------------------------------------
void J4CLXEMBoxCell::Cabling()
{
    if(!GetSD()) {
	J4CLXEMActiveSD* sd = new J4CLXEMActiveSD(this);
	Register(sd);
	SetSD(sd);
    }
}
