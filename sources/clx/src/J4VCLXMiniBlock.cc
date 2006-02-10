#include "J4VCLXMiniBlock.hh"
#include "J4CLXParameterList.hh"
#include "G4Trap.hh"
#include "J4VCLXLayer.hh"
#include "J4CLXEMLayer.hh"
#include "J4CLXHDLayer.hh"

//=====================================================================
//* constructor -------------------------------------------------------
J4VCLXMiniBlock::J4VCLXMiniBlock(       const G4String& name,
					J4VDetectorComponent* parent,
					G4int  nclones,
					G4int  nbrothers,
					G4int  me,
					G4int  copyno )
    : J4VCLXDetectorComponent( name, parent, nclones, nbrothers, me, copyno  )
{ }

//=====================================================================
//* destructor --------------------------------------------------------
J4VCLXMiniBlock::~J4VCLXMiniBlock()
{
    G4int nLayers = fLayers.size();
    for(G4int i = 0; i < nLayers; ++i) {
	if(Deregister(fLayers[i])) delete fLayers[i];
	}
//    if(Deregister(layer)) delete layer;
}

//=====================================================================
//* Assemble   --------------------------------------------------------
void J4VCLXMiniBlock::Assemble()
{
    if(!GetLV()) {
	G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());

	G4double pz = mother -> GetZHalfLength();
	G4double py = GetPy();
	G4double px = GetPx();
	G4double plx = GetPlx();
	G4double phi = 0.0;
	G4int nLayers = GetNofLayers();

	G4Trap* ptrMiniTrap = new G4Trap(GetName(), pz, 0., phi, py, px, plx, 0., py, px, plx, 0.);
	Register(ptrMiniTrap);
	SetSolid(ptrMiniTrap);

	// MakeLogicalVolume --//
	MakeLVWith(OpenMaterialStore()->Order(GetMaterial()));

	// SetVisAttribute ----//
	PaintLV(GetVisAtt(), GetColor());

	for(G4int i = 0; i < nLayers; ++i) {
	    J4VCLXLayer* layer = Create(this, 1, nLayers, i);
	    fLayers.push_back(layer);
	    Register(layer);
	    layer -> InstallIn(this);
	    SetDaughter(layer);
	    }
    }
}

//=====================================================================
//* Cabling   ---------------------------------------------------------
void J4VCLXMiniBlock::Cabling() {}

//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4VCLXMiniBlock::InstallIn( J4VComponent*        /* mother */,
			    G4RotationMatrix*    /* prot   */,
			    const G4ThreeVector& /* tlate  */ )
{
    Assemble();			// You MUST call Assemble(); at first.

    //Placement function into mother object
    G4double x = 0.;
    G4double y = GetTrapPy();
    G4double z = 0.;

    G4ThreeVector position(x, y, z);
    SetPVPlacement(0, position);

    Cabling();
}

void J4VCLXMiniBlock::Draw() { }
void J4VCLXMiniBlock::Print() const { }
