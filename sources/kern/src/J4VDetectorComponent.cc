// $Id$
//*************************************************************************
//* --------------------
//* J4VDetectorComponent
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4UnionSolid.hh"


//************************************************************************
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -----------------------------------------------

J4VDetectorComponent::J4VDetectorComponent(const G4String& groupname,
					   const G4String& name,
					   J4VComponent* parent,
					   G4int     nclones,
					   G4int     nbrothers,
					   G4int     me,
                                           G4int     copyno)
                        :J4VComponent(groupname, name, parent,
                                      nclones, nbrothers, me, copyno)
{
} 

J4VDetectorComponent::J4VDetectorComponent(const G4String& groupname,
					   const G4String& name,
					   J4VDetectorComponent* parent,
					   G4int     nclones,
					   G4int     nbrothers,
					   G4int     me,
                                           G4int     copyno)
                        :J4VComponent(groupname, name, parent,
                                      nclones, nbrothers, me, copyno)
{
} 

//=====================================================================
//* destructor --------------------------------------------------------

J4VDetectorComponent::~J4VDetectorComponent()
{
}


//=====================================================================
//* GetDCPtrByName ----------------------------------------------------
J4VDetectorComponent* 
	J4VDetectorComponent::GetDCPtrByName(const G4String& name) 
{
   std::cerr << "******************************************************" << std::endl;
   std::cerr << " J4VDetectorComponent::GetDCPtrByName()               " << std::endl;
   std::cerr << " This method will be removed in next major upgrade.   " << std::endl;
   std::cerr << " Use new method J4VComponent::GetComponentPtrByName() " << std::endl;
   std::cerr << "******************************************************" << std::endl;

   J4ComponentArray familymembers = GetFamilyMembers();
   G4int n = familymembers.entries();
   
   for (G4int i=0; i<n; i++) {   	
      if (name == familymembers[i]->GetName()) {
          return (J4VDetectorComponent *)familymembers[i] ;
      } 	
   }

   std::cerr << " J4VDetectorComponent::GetDCPtrByName " << std::endl
          << "      Cannot find object name " << name << std::endl;
   return 0;
}


