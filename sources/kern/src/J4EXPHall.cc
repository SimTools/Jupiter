// $Id$
//*************************************************************************
//* --------------------
//* J4EXPHall
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "G4Box.hh"

#include "J4EXPHall.hh"
#include "J4VMaterialStore.hh"
#include "J4VSensitiveDetector.hh"
#include "J4ParameterList.hh"
// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


J4VMaterialStore* J4EXPHall::fMaterialStore = 0;

G4String J4EXPHall::fProjectName("JLC");
G4String J4EXPHall::fEXPName("EXPName");

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4EXPHall::J4EXPHall(J4VComponent *parent,
                     G4int         nclones,
                     G4int         nbrothers, 
                     G4int         me,
                     G4int         copyno ) :
           J4VComponent( fProjectName, fEXPName, parent, 
                         nclones, nbrothers, me, copyno  )
{ 
  
      
  Assemble();

}

// ====================================================================
//* destructor --------------------------------------------------------
J4EXPHall::~J4EXPHall()
{	
#ifndef __GEANT452__
  if (Deregister(fMaterialStore)) delete fMaterialStore;
#endif
}

// ====================================================================
//* Assemble   --------------------------------------------------------
void J4EXPHall::Assemble()
{  
   if (!GetLV()){
      J4ParameterList *list = J4ParameterList::GetInstance();  	
      fSizeOfEXPHall.set(list->GetEXPHallHalfX(),
                         list->GetEXPHallHalfY(),
                         list->GetEXPHallHalfZ());
      G4VSolid *solid = new G4Box(fEXPName, 
                                  fSizeOfEXPHall.x(),
                                  fSizeOfEXPHall.y(),
                                  fSizeOfEXPHall.z());
      Register(solid);
      SetSolid(solid);
      MakeLVWith(OpenMaterialStore()->Order(list->GetEXPHallMaterial()));
   
      PaintLV(FALSE, G4Colour(1., 1., 1.));
   
      SetPVPlacement();
   }	
}


//=====================================================================
//* InstallIn  --------------------------------------------------------
void J4EXPHall::InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot, 
                          const G4ThreeVector  &tlate ) 
{
}

//=====================================================================
//* OutputAll ---------------------------------------------------------
void J4EXPHall::OutputAll(G4HCofThisEvent* HCTE, std::ofstream & ofs)
{

   
   if (GetSD()) {  
      if (IsOn()) {
          ofs << "*****_EXPHall_output_start_*****" << G4endl;
          GetSD()->OutputAll(HCTE);  
          ofs << "*****_EXPHall_output_end_*****" << G4endl; 
      }
   }

   J4ComponentArray daughters = GetDaughters();
   G4int ndaughters = daughters.entries();

   G4int i;

   for( i=0; i<ndaughters; i++) {
      ofs << "*****_" << daughters[i]->GetName() << "_output_start_*****" << G4endl; 
      daughters[i]->OutputAll(HCTE);
      ofs << "*****_" << daughters[i]->GetName() << "_output_end_*****" << G4endl; 
   }
}

//* Draw  --------------------------------------------------------
void J4EXPHall::Draw()
{
  // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4EXPHall::Print() const
{
}

//* OpenMaterialStore ---------------------------------------------
J4VMaterialStore* J4EXPHall::OpenMaterialStore()
{

  if (!fMaterialStore) {
     fMaterialStore = new J4VMaterialStore();
     Register(fMaterialStore);
  } 
  return fMaterialStore; 

}
