// $Id$
//*************************************************************************
//* --------------------
//* J4CAL
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CAL.hh"


// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CAL::fFirstName("CAL");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CAL::J4CAL(J4VDetectorComponent *parent,
                            G4int  nclones,
                            G4int  nbrothers, 
                            G4int  me,
                            G4int  copyno ) :
       J4VCALDetectorComponent(fFirstName, parent, nclones,
                               nbrothers, me, copyno),
       fCones(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CAL::~J4CAL()
{
//ifndef __GEANT452__
#if 0
   if (fCones) {
      J4CALParameterList *list = OpenParameterList(); 
      for (G4int i=0; i < list->GetNcones(); i++) {
         if (Deregister(fCones[i])) delete fCones[i];
      }
      if (Deregister(fCones)) delete [] fCones;
   }
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CAL::Assemble() 
{   
   if(!GetLV()){
      J4CALParameterList *list = OpenParameterList(); 
  	
      G4double rmin        = list->GetCALInnerR();
      G4double rmax        = list->GetCALOuterR();
      G4double len         = list->GetCALOuterHalfZ();
      G4double dphi        = list->GetCALDeltaPhi();
      G4double endcaprmin  = list->GetEndcapInnerR();
      G4double endcaphalfz = 0.5 * (len - list->GetCALInnerHalfZ());
  	
      // MakeSolid ----------//
      OrderNewTubs (rmin, rmax, len, dphi, endcaphalfz, endcaprmin);
    
      // MakeLogicalVolume --//  
      MakeLVWith(OpenMaterialStore()->Order(list->GetCALMaterial()));
    
      // SetVisAttribute ----//
      PaintLV(list->GetCALVisAtt(), list->GetCALColor());
  	
      // Install daughter PV //
  		  
      G4int ncones = list->GetNcones();
      fCones       = new J4CALCone* [ncones];
      Register(fCones);
      for (G4int i=0; i<ncones; i++) {
         fCones[i] = new J4CALCone(this, 1, ncones, i );
         Register(fCones[i]);
         fCones[i] ->InstallIn(this);
         SetDaughter(fCones[i]);
      }

   }
      
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CAL::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CAL::InstallIn(J4VComponent         *mother,
                      G4RotationMatrix     *prot, 
                      const G4ThreeVector  &tlate )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}


//* Draw  --------------------------------------------------------
void J4CAL::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CAL::Print() const
{
}

	
	


