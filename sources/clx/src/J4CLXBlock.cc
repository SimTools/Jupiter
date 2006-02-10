#include "G4Trap.hh"
#include "J4CLXBlock.hh"
#include "J4CLXParameterList.hh"
#include "J4CLXEM.hh"
#include "J4CLXHD.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------
const G4String J4CLXBlock::fFirstName( "Block" );

//=====================================================================
//* constructor -------------------------------------------------------
J4CLXBlock::J4CLXBlock(J4VDetectorComponent* parent,
		       G4int  nclones,
		       G4int  nbrothers,
		       G4int  me,
		       G4int  copyno)
    :J4VCLXDetectorComponent(fFirstName, parent, nclones, nbrothers, me, copyno  )
{}

//=====================================================================
//* destructor --------------------------------------------------------
J4CLXBlock::~J4CLXBlock()
{
    if(Deregister(fEMcal)) delete fEMcal;
    if(Deregister(fHDcal)) delete fHDcal;
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4CLXBlock::Assemble()
{
    if(!GetLV()) {
	J4CLXParameterList* ptrList = OpenParameterList();

	G4double rmin = ptrList -> GetCLXInnerR();
	G4double rmax = ptrList -> GetCLXOuterR();
	G4double pz = ptrList->GetCLXInnerHalfZ();
	G4double dphi = ptrList -> GetTrapDeltaPhi();
	G4double phi =0.;

	G4double thick = rmax * std::cos(.5 * dphi) - rmin;
	G4double py = .5 * thick;
	G4double px = rmin * std::tan(.5 * dphi);
	G4double plx = rmax * std::sin(.5 * dphi);

	ptrTrap = new G4Trap(GetName(), pz, 0., phi, py, px, plx, 0, py, px, plx, 0);
	Register(ptrTrap);
	SetSolid(ptrTrap);

	// MakeLogicalVolume --//
	MakeLVWith(OpenMaterialStore()->Order(ptrList->GetBlockMaterial()));

	// SetVisAttribute ----//
	PaintLV(ptrList->GetBlockVisAtt(), ptrList->GetBlockColor());

	//Install daughter PV //
	fEMcal = new J4CLXEM(this);
	Register(fEMcal);
	fEMcal -> InstallIn(this);
	SetDaughter(fEMcal);

	fHDcal = new J4CLXHD(this);
	Register(fHDcal);
	fHDcal -> InstallIn(this);
	SetDaughter(fHDcal);
    }
}

//=====================================================================
//* Cabling   ---------------------------------------------------------
void J4CLXBlock::Cabling()
{ }

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4CLXBlock::InstallIn( J4VComponent*        /* mother */,
			    G4RotationMatrix*    /* prot   */,
			    const G4ThreeVector& /* tlate  */ )
{
    Assemble();			// You MUST call Assemble(); at first.

    // Placement function into mother object...
    J4CLXParameterList* ptrList = OpenParameterList();

    G4int copyno = GetCopyNo();
    G4double rmin = ptrList -> GetCLXInnerR();
    G4double rmax = ptrList -> GetCLXOuterR();
    G4double dphi = ptrList->GetTrapDeltaPhi();
    G4double thick = rmax * std::cos(.5 * dphi) - rmin;
    G4double pr = .5 * thick + rmin;
    G4double px = pr * std::sin(dphi * copyno);
    G4double py = pr * std::cos(dphi * copyno);
    G4double pz = 0.;
    G4ThreeVector position(px, py, pz);

    G4RotationMatrix* rotation = new G4RotationMatrix();
    G4double angle = copyno * dphi;
    rotation->rotateZ(angle);

    SetPVPlacement(rotation, position);

    Cabling();
}

void J4CLXBlock::Draw() { }
void J4CLXBlock::Print() const { }
