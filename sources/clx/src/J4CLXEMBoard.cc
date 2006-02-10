#include "J4CLXEMBoard.hh"
#include "J4CLXEMLargeBoxCell.hh"
#include "J4CLXEMTrapCell.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXEMBoard::fFirstName= "EMBoard";

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXEMBoard::J4CLXEMBoard(J4VDetectorComponent *parent,
			   G4int  nclones,
			   G4int  nbrothers,
			   G4int  me,
			   G4int  copyno )
    :J4VCLXBoard(fFirstName, parent, nclones, nbrothers, me, copyno  )
{
}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXEMBoard::~J4CLXEMBoard()
{}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLargeBoxCell *J4CLXEMBoard::CreateLargeBoxCell(J4VDetectorComponent *parent,
						     G4int nclones,
						     G4int nbrothers,
						     G4int me,
						     G4int copyno)
{
    return new J4CLXEMLargeBoxCell(parent, nclones, nbrothers, me, copyno);
}

J4VCLXTrapCell *J4CLXEMBoard::CreateTrap(J4VDetectorComponent *parent,
					 G4int nclones,
					 G4int nbrothers,
					 G4int me,
					 G4int copyno,
					 G4bool isXPlus)
{
    return new J4CLXEMTrapCell(parent, nclones, nbrothers, me, copyno, isXPlus);
}

