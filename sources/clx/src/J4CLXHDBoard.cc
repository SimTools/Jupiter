#include "J4CLXHDBoard.hh"
#include "J4CLXHDLargeBoxCell.hh"
#include "J4CLXHDTrapCell.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXHDBoard::fFirstName= "HDBoard";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXHDBoard::J4CLXHDBoard(J4VDetectorComponent *parent,
			   G4int  nclones,
			   G4int  nbrothers,
			   G4int  me,
			   G4int  copyno )
    :J4VCLXBoard(fFirstName, parent, nclones, nbrothers, me, copyno  )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXHDBoard::~J4CLXHDBoard()
{}

J4VCLXLargeBoxCell *J4CLXHDBoard::CreateLargeBoxCell(J4VDetectorComponent *parent,
						     G4int nclones,
						     G4int nbrothers,
						     G4int me,
						     G4int copyno)
{
    return new J4CLXHDLargeBoxCell(parent, nclones, nbrothers, me, copyno);
}

J4VCLXTrapCell *J4CLXHDBoard::CreateTrap(J4VDetectorComponent *parent,
					 G4int nclones,
					 G4int nbrothers,
					 G4int me,
					 G4int copyno,
					 G4bool isXPlus)
{
    return new J4CLXHDTrapCell(parent, nclones, nbrothers, me, copyno, isXPlus);
}
