// $Id$
//*************************************************************************
//* --------------------
//* J4ExpHall
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "G4Box.hh"

#include "J4ExpHall.hh"
#include "J4VMaterialStore.hh"
#include "J4Parameter.hh"
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


J4VMaterialStore* J4ExpHall::fMaterialStore = 0;

static const G4ThreeVector dxyzExpHall(_EXPHALLHALFX_, 
                                       _EXPHALLHALFY_,
                                       _EXPHALLHALFZ_);
G4String J4ExpHall::fProjectName("JLC");
G4String J4ExpHall::fExpName("ExpName");

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4ExpHall::J4ExpHall(J4VComponent *parent,
                     G4int         nclones,
                     G4int         nbrothers, 
                     G4int         me,
                     G4int         copyno ) :
           J4VComponent( fProjectName, fExpName, parent, 
                         nclones, nbrothers, me, copyno  )
{ 
  
  Assemble();

}

// ====================================================================
//* destructor --------------------------------------------------------
J4ExpHall::~J4ExpHall()
{	
  if (Deregister(fMaterialStore)) delete fMaterialStore;
}

// ====================================================================
//* Assemble   --------------------------------------------------------
void J4ExpHall::Assemble()
{  
  if (!GetLV()){
  	
   G4VSolid *solid = new G4Box(fExpName, dxyzExpHall.x(), dxyzExpHall.y(), dxyzExpHall.z());
   Register(solid);
   SetSolid(solid);
   MakeLVWith(OpenMaterialStore()->Order(_EXPHALLMATERIAL_));
   
   PaintLV(FALSE, G4Colour(1., 1., 1.));
   
   SetPVPlacement();
  }	
}


//* InstallIn  --------------------------------------------------------

void J4ExpHall::InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot, 
                          const G4ThreeVector  &tlate ) 
{
}


//* Draw  --------------------------------------------------------
void J4ExpHall::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4ExpHall::Print() const
{
}

//* GetCenter -----------------------------------------------------
const G4ThreeVector& J4ExpHall::GetCenter() const
{
  return dxyzExpHall;	
}

//* OpenMaterialStore ---------------------------------------------
J4VMaterialStore* J4ExpHall::OpenMaterialStore()
{

  if (!fMaterialStore) {
     fMaterialStore = new J4VMaterialStore();
     Register(fMaterialStore);
  } 
  return fMaterialStore; 

}
