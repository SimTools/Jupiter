// $Id$
//*************************************************************************
//* --------------------
//* J4VCALBlock
//* --------------------
//* (Description)
//*    Base class for CAL blocks like EM or HD.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2004/11/14  K.Fujii	Derived from J4CALEM by S.Ono.
//*************************************************************************

#include "J4VCALBlock.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "J4VCALMiniCone.hh"
#include "J4CALEMMiniCone.hh"
#include "J4CALHDMiniCone.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------
// None

//=====================================================================
//* constructor -------------------------------------------------------

J4VCALBlock::J4VCALBlock( const G4String       &name,
                          J4VDetectorComponent *parent,
                                         G4int  nclones,
                                         G4int  nbrothers, 
                                         G4int  me,
                                         G4int  copyno) 
: J4VCALDetectorComponent( name, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCALBlock::~J4VCALBlock()
{
  G4int nMiniCones = fMiniCones.size();
  for (G4int i = 0; i < nMiniCones;i++ ) {
    if (Deregister(fMiniCones[i])) delete fMiniCones[i];
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4VCALBlock::Assemble() 
{   
  if (!GetLV()) {

    G4Sphere *mother    = (G4Sphere *)(GetMother()->GetSolid()); 

    G4int    nMiniCones = GetNofMiniCones();
    G4double sphi       = mother->GetStartPhiAngle();
    G4double dphi       = mother->GetDeltaPhiAngle();
    G4double Thickness  = GetThickness();
    G4double rmin       = GetInsideRadius();
    G4double rmax       = rmin + Thickness; 
    G4double dtheta     = mother->GetDeltaThetaAngle(); 
    G4double stheta     = mother->GetStartThetaAngle();

    G4Sphere* block = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
    Register( block );
    SetSolid( block );

    MakeLVWith( OpenMaterialStore()->Order(GetMaterial()) );

    PaintLV( GetVisAtt(), GetColor() );

    for ( G4int i = 0; i < nMiniCones; i++ ) {
      J4VCALMiniCone* minicone = Create( this, 1, nMiniCones, i );
      fMiniCones.push_back( minicone );
      Register( minicone );
      minicone->InstallIn( this );
      SetDaughter( minicone );
    }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------
void J4VCALBlock::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VCALBlock::InstallIn(J4VComponent    *  /* mother */,
                           G4RotationMatrix*  /* prot   */, 
                     const G4ThreeVector   &  /* tlate  */ ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   SetPVPlacement();
   
   //Cabling();
}


//* Draw  --------------------------------------------------------
void J4VCALBlock::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4VCALBlock::Print() const
{
}
