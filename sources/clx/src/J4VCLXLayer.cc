#include "J4VCLXLayer.hh"
#include "J4CLXParameterList.hh"
#include "G4Trap.hh"

//====================================================================
//---------------------
// Class Description
//---------------------

//====================================================================
//* constructor ------------------------------------------------------

J4VCLXLayer::J4VCLXLayer(const G4String &name,
			 J4VDetectorComponent *parent,
			 G4int nclones,
			 G4int nbrothers,
			 G4int me,
			 G4int copyno)
    : J4VCLXDetectorComponent(name, parent, nclones, nbrothers, me, copyno)
{}

//====================================================================
//* destructor -------------------------------------------------------

J4VCLXLayer::~J4VCLXLayer()
{
    if(Deregister(fAbsLayer)) delete fAbsLayer;
    if(Deregister(fActiveLayer)) delete fActiveLayer;
}

//====================================================================
//* Assemble ---------------------------------------------------------
void J4VCLXLayer::Assemble()
{
    if(!GetLV()) {
	G4Trap *mother = (G4Trap *)(GetMother() -> GetSolid());

	G4double pxmin = mother -> GetXHalfLength1();
	G4double pz = mother -> GetZHalfLength();

	G4double dphi = OpenParameterList() -> GetTrapDeltaPhi();

	G4int myID = GetMyID();
	G4double thickness = GetLayerThickness();

	G4double py = .5 * thickness;
	G4double px = pxmin + myID * thickness * std::tan(.5 * dphi) + .25 * thickness * std::tan(.5 * dphi);
	G4double plx = px + thickness * std::tan(.5 * dphi);
	G4double phi = 0.;

	// MakeSolid ----------//
	G4Trap* layer = new G4Trap(GetName(), pz, 0., phi, py, px, plx, 0., py, px, plx, 0.);
	Register(layer);
	SetSolid(layer);

	// MakeLogicalVolume --//
	MakeLVWith(OpenMaterialStore() -> Order(GetMaterial()));

	// SetVisAttribute ----//
	PaintLV(GetVisAtt(), GetColor());

	// Make AbsLayer and ActiveLayer objects ---//
	fAbsLayer = CreateAbs(this);
	Register(fAbsLayer);
	fAbsLayer -> InstallIn(this);
	SetDaughter(fAbsLayer);

	fActiveLayer = CreateActive(this);
	Register(fActiveLayer);
	fActiveLayer -> InstallIn(this);
	SetDaughter(fActiveLayer);
    }

}

//====================================================================
//* Cabling  ---------------------------------------------------------

void J4VCLXLayer::Cabling()
{}

//====================================================================
// * InstallIn -------------------------------------------------------
void J4VCLXLayer::InstallIn(J4VComponent* /*mother*/,
			    G4RotationMatrix* /*prot*/,
			    const G4ThreeVector& /*tlate*/)
{
    Assemble();

    //Placement function into mother object...
    G4int myID = GetMyID();
    G4double thickness = GetLayerThickness();

    G4double x = 0.;
    G4double y = (.75 + myID - .5 * GetNbrothers()) * thickness;
    G4double z = 0.;
    G4ThreeVector position(x, y, z);
    SetPVPlacement(0, position);

    // Cabling function for SD object...
    //Cabling();
}


//* Draw -------------------------------------------------------------
void J4VCLXLayer::Draw()
{
    // set visualizatin attributes
}

//* Print ------------------------------------------------------------
void J4VCLXLayer::Print() const
{}
