// $Id$
//*************************************************************************
//* --------------------
//* J4CALHD
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALHD.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "J4CALMiniCone.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String& J4CALHD::firstName( "HD" );

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALHD::J4CALHD( J4VDetectorComponent *parent,
                                 G4int  nclones,
                                 G4int  nbrothers, 
                                 G4int  me,
                                 G4int  copyno ) 
 : J4CALBlock( firstName, this, parent, nclones, nbrothers, me, copyno )
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALHD::~J4CALHD()
{
  J4CALParameterList* ptrList = OpenParameterList();
  G4int nMiniCones = ptrList -> GetHDMiniConeNClones();
  for( G4int i = 0; i < nMiniCones; i++ ){
    if( Deregister(fMiniCones[i]) ) delete fMiniCones[i];
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALHD::Assemble() 
{   
 if ( !GetLV() ) {

    J4CALParameterList* ptrList = OpenParameterList();
    J4CALSubLayerParameterList* subList = ptrList -> GetSubLayerParam();
  
    G4Sphere *mother = (G4Sphere *)(GetMother()->GetSolid()); 

    const G4int    nMiniCones  = ptrList -> GetHDMiniConeNClones(); 
    const G4double EMThickness = (ptrList->GetEMNLayers())*(subList->GetTotalLayerSize("EM"));
    // const G4double HDThickness = (ptrList->GetHDNLayers())*(subList->GetTotalLayerSize("HD"));

    G4double rmin   = mother -> GetInsideRadius() + EMThickness;
    G4double rmax   = mother -> GetOuterRadius();
    G4double sphi   = mother -> GetStartPhiAngle();
    G4double dphi   = mother -> GetDeltaPhiAngle();
    G4double stheta = mother -> GetStartThetaAngle();
    G4double dtheta = mother -> GetDeltaThetaAngle();

    G4Sphere* block = new G4Sphere( GetName(), rmin, rmax, sphi, dphi, stheta, dtheta );
    Register( block );
    SetSolid( block );

    MakeLVWith( OpenMaterialStore()->Order(ptrList->GetHDMaterial()) );

    PaintLV( ptrList->GetHDVisAtt(), ptrList->GetHDColor() );
      
    for ( G4int i = 0; i < nMiniCones; i++ ) {
      J4CALMiniCone* minicone = new J4CALMiniCone( fBlock, 1, nMiniCones, i );
      fMiniCones.push_back( minicone );
      Register( minicone );
      minicone -> InstallIn( fBlock );
      SetDaughter( minicone );
    }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

//void J4CALHD::Cabling()
//{
//   if (!GetSD()) {
//      J4CALHDSD* sd = new J4CALHDSD(this);
//      Register(sd);
//      SetSD(sd);
//   }
//}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALHD::InstallIn( J4VComponent*        /* mother */,
                         G4RotationMatrix*    /* prot   */, 
                         const G4ThreeVector& /* tlate  */) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  
   // Placement function into mother object...
   SetPVPlacement();
   
}


//* Draw  --------------------------------------------------------
void J4CALHD::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALHD::Print() const
{
}
