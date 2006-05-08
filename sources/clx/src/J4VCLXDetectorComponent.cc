// $Id$
//*************************************************************************
//* -----------------------
//* J4VCLXDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXDetectorComponent.hh"

J4CLXMaterialStore* J4VCLXDetectorComponent::fgMaterialStore = 0;

G4String J4VCLXDetectorComponent::fgSubGroup( "CLX" );

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VCLXDetectorComponent::J4VCLXDetectorComponent(
			   	const G4String       &name, 
  			   	J4VDetectorComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno ) 
: J4VDetectorComponent( fgSubGroup, name, 
                        parent, nclones,	 
                        nbrothers, me, copyno  )
{ 
}

//=====================================================================
//* Copy constructor -----------------------------------------------
J4VCLXDetectorComponent::J4VCLXDetectorComponent( const J4VCLXDetectorComponent& orig,
						  G4int copyno )
  : J4VDetectorComponent( orig, copyno )
{
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VCLXDetectorComponent::~J4VCLXDetectorComponent()
{	
   if ( Deregister( fgMaterialStore ) ) delete fgMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VCLXDetectorComponent::OpenMaterialStore()
{
   if ( !fgMaterialStore ) {
     fgMaterialStore = new J4CLXMaterialStore();
     Register( fgMaterialStore );
     std::cerr << "*** Opend J4CLXMaterialStore ***" << std::endl;
  }
    
   return fgMaterialStore;
}
