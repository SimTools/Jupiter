// $Id$
//*************************************************************************
//* --------------------
//* J4CALBlock
//* --------------------
//* (Description)
//*    Base class for CAL blocks like EM or HD.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2004/11/14  K.Fujii	Derived from J4CALEM by S.Ono.
//*************************************************************************

#include "J4CALBlock.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "J4CALMiniCone.hh"

//=====================================================================
//---------------------
// Class Description
//---------------------
// None

//=====================================================================
//* constructor -------------------------------------------------------

J4CALBlock::J4CALBlock(      const G4String &firstname,
                                     G4bool  isem,
                       J4VDetectorComponent *parent,
                                      G4int  nclones,
                                      G4int  nbrothers, 
                                      G4int  me,
                                      G4int  copyno) 
          : J4VCALDetectorComponent(firstname,
                                    isem,
                                    parent,
                                    nclones,
                                    nbrothers,
                                    me,
                                    copyno)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALBlock::~J4CALBlock()
{
  G4int nMiniCones = fMiniCones.size();
  for (G4int i = 0; i < nMiniCones;i++ ) {
    if (Deregister(fMiniCones[i])) delete fMiniCones[i];
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALBlock::Assemble() 
{   
  if (!GetLV()) {

    G4Sphere *mother    = (G4Sphere *)(GetMother()->GetSolid()); 

    G4int    nMiniCones = GetNofMiniCones();
    G4double sphi       = mother->GetStartPhiAngle();
    G4double dphi       = mother->GetDeltaPhiAngle();
    G4double Thickness  = GetThickness();
    G4double rmin       = GetInnerRadius();
    G4double rmax       = rmin + Thickness; 
    G4double dtheta     = mother->GetDeltaThetaAngle(); 
    G4double stheta     = mother->GetStartThetaAngle();

    G4Sphere* block     = new G4Sphere(GetName(),
                                       rmin, rmax, sphi, dphi, stheta, dtheta);
    Register(block);
    SetSolid(block);

    MakeLVWith(OpenMaterialStore()->Order(GetMaterial()));

    PaintLV(GetVisAtt(), GetColor());
      
    for (G4int i = 0; i < nMiniCones; i++) {
      J4CALMiniCone* minicone = new J4CALMiniCone(this, IsEM(), 1, nMiniCones, i);
      fMiniCones.push_back(minicone);
      Register(minicone);
      minicone->InstallIn(this);
      SetDaughter( minicone );
    }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALBlock::Cabling()
{
#if 0
   if (!GetSD()) {
      J4CALBlockSD* sd = new J4CALBlockSD(this);
      Register(sd);
      SetSD(sd);
   }
#endif
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALBlock::InstallIn(J4VComponent    *  /* mother */,
                           G4RotationMatrix*  /* prot   */, 
                     const G4ThreeVector   &  /* tlate  */ ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   SetPVPlacement();
   
#if 0
  Cabling();
#endif
}


//* Draw  --------------------------------------------------------
void J4CALBlock::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALBlock::Print() const
{
}
