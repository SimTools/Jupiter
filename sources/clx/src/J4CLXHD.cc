#include "J4CLXHD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String  J4CLXHD::fFirstName= "HD" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CLXHD::J4CLXHD( J4VDetectorComponent *parent,
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

J4CLXHD::~J4CLXHD()
{
}

//=====================================================================
//* Create ------------------------------------------------------------
J4VCLXLayer *J4CLXHD::Create(J4VDetectorComponent *parent,
			     G4int nclones,
			     G4int nbrothers,
			     G4int me,
			     G4int copyno)
{
    return new J4CLXHDLayer(parent, nclones, nbrothers, me, copyno);
}

//=====================================================================
//* SetParameters -----------------------------------------------------
void J4CLXHD::SetParameter()
{
    J4CLXParameterList *ptrList = OpenParameterList();
    rmin = ptrList -> GetCLXInnerR();
    rmax = ptrList -> GetCLXOuterR();
    thick = ptrList -> GetHDThickness();
    dphi = ptrList -> GetTrapDeltaPhi();
}
