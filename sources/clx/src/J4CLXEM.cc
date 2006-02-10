#include "J4CLXEM.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXEM::fFirstName= "EM" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXEM::J4CLXEM( J4VDetectorComponent *parent,
                                 G4int  nclones,
                                 G4int  nbrothers,
                                 G4int  me,
                                 G4int  copyno )
: J4VCLXMiniBlock( fFirstName, parent, nclones, nbrothers, me, copyno  )
{
    SetParameter();
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CLXEM::~J4CLXEM()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXEM::Create(J4VDetectorComponent *parent,
			     G4int nclones,
			     G4int nbrothers,
			     G4int me,
			     G4int copyno)
{
    return new J4CLXEMLayer(parent, nclones, nbrothers, me, copyno);
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CLXEM::SetParameter()
{
    J4CLXParameterList *ptrList = OpenParameterList();
    rmin = ptrList -> GetCLXInnerR();
    rmax = ptrList -> GetCLXOuterR();
    thick = ptrList -> GetEMThickness();
    dphi = ptrList -> GetTrapDeltaPhi();
}
