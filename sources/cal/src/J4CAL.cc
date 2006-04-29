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
#include "J4CALSD.hh"
#include "J4CALCone.hh"
#include "J4Timer.hh"
#include "J4ParameterTable.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

const G4String J4CAL::fFirstName= "CAL" ;

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CAL::J4CAL( J4VDetectorComponent *parent,
                             G4int  nclones,
                             G4int  nbrothers, 
                             G4int  me,
                             G4int  copyno )
: J4VCALDetectorComponent( fFirstName, parent, nclones,
                                       nbrothers, me, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CAL::~J4CAL()
{
#ifdef __DRAWONETOWER__
  if (fCones && Deregister(fCones)) delete fCones;
#else
#ifndef __GEANT452__
   if ( fCones ) {
      J4CALParameterList *ptrList = OpenParameterList(); 
      for ( G4int i = 0; i < ptrList->GetNcones(); i++ ) {
         if (Deregister(fCones[i])) delete fCones[i];
      }
      if (Deregister(fCones)) delete [] fCones;
   }
#endif
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CAL::Assemble() 
{   
   if ( !GetLV() ) {

      J4CALParameterList *ptrList = OpenParameterList(); 

      G4double rmin        = ptrList -> GetCALInnerR();
      G4double rmax        = ptrList -> GetCALOuterR();
      G4double len         = ptrList -> GetCALOuterHalfZ();
      G4double dphi        = ptrList -> GetCALDeltaPhi();
      G4double endcaprmin  = ptrList -> GetEndcapInnerR();
      G4double endcaphalfz = 0.5 * ( len - ptrList->GetCALInnerHalfZ() );
  	
      // MakeSolid ----------//
      OrderNewTubs( rmin, rmax, len, dphi, endcaphalfz, endcaprmin );
    
      // MakeLogicalVolume --//  
      MakeLVWith( OpenMaterialStore()->Order(ptrList->GetCALMaterial()) );
    
      // SetVisAttribute ----//
      PaintLV( ptrList->GetCALVisAtt(), ptrList->GetCALColor() );
  	
      // Install daughter PV //
#ifdef __DRAWONETOWER__
      G4int ncones = 1;
#else
      G4int ncones = ptrList->GetNcones();
#endif
      fCones = new J4CALCone* [ncones];
      Register(fCones);
      for ( G4int i = 0; i < ncones; i++ ) {
         fCones[i] = new J4CALCone( this, 1, ncones, i );
         Register( fCones[i] );
         fCones[i] -> InstallIn( this );
         SetDaughter( fCones[i] );
      }
   }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CAL::Cabling()
{
  if ( !GetSD() ) {
    J4CALSD* sd = new J4CALSD( this );
    Register( sd );
    SetSD( sd );
  }
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CAL::InstallIn( J4VComponent*         /* mother */,
                       G4RotationMatrix*     /* prot   */, 
                       const G4ThreeVector&  /* tlate  */  )
{ 
  static G4int timerID = -1;
  J4Timer timer( timerID, "J4CAL", "InstallIn()" );
  timer.Start(); 

  Assemble();			// You MUST call Assemble(); at first.
  
  G4UserLimits *myLimits=new G4UserLimits();
  G4double umaxtime= J4ParameterTable::GetValue("J4CAL.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime(umaxtime);
  GetLV()->SetUserLimits(myLimits);

  // Placement function into mother object...
  SetPVPlacement();
  
  // Cabling function to install SD
  Cabling();

  timer.Stop();
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
