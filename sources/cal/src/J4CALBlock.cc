// $Id$
//*************************************************************************
//* --------------------
//* J4CALBlock
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALBlock.hh"
//#include "J4CALBlockSD.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "J4CALMiniCone.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

//G4String J4CALBlock::fFirstName("Block");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

//J4CALBlock::J4CALBlock(const G4String&  firstName,
J4CALBlock::J4CALBlock( const G4String&  firstName,
                            J4CALBlock*  ptrBlock,
                   J4VDetectorComponent  *parent,
                                  G4int  nclones,
                                  G4int  nbrothers, 
                                  G4int  me,
                                  G4int  copyno ) : 
 J4VCALDetectorComponent( firstName, parent, nclones,
                                     nbrothers, me, copyno  ),
 fFirstName(firstName), fBlock(ptrBlock)
  //,rmin(0.), rmax(0.)
  //,nMiniCones(1), nMiniTowers(1), fMiniCones(0)
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALBlock::~J4CALBlock()
{
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALBlock::Assemble() 
{   
   //if(!GetLV()){
 
      //J4CALParameterList* list = OpenParameterList();
      //G4Sphere *mothertower = (G4Sphere *)(GetMother()->GetSolid());

      //G4double stheta = mothertower->GetStartThetaAngle();
      //G4double dtheta = mothertower->GetDeltaThetaAngle();
      //G4double sphi   = mothertower->GetStartPhiAngle();
      //G4double dphi   = mothertower->GetDeltaPhiAngle();
  	
      // MakeSolid ----------//
      //G4Sphere* block = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
      //Register(block);
      //SetSolid(block);
    
      // MakeLogicalVolume --//  
      //MakeLVWith(OpenMaterialStore()->Order(list->GetEMMaterial()));
    
      // SetVisAttribute ----//
      //PaintLV(list->GetEMVisAtt(), list->GetEMColor());

      // Install daughter PV //
//      for(G4int i = 0; i < nMiniCones; i++){
//	J4CALMiniCone* fMiniCones = new J4CALMiniCone(fBlock,1,nMiniCones,i);
//        Register(fMiniCones);
//        fMiniCone->InstallIn(fBlock);
//        SetDaughter(fMiniCones);
//      }
   //}
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CALBlock::Cabling()
{
  // if (!GetSD()) {
  //    J4CALBlockSD* sd = new J4CALBlockSD(this);
  //    Register(sd);
  //    SetSD(sd);
   //}
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALBlock::InstallIn(J4VComponent      *mother,
                        G4RotationMatrix     *prot, 
                        const G4ThreeVector  &tlate ) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
   // Placement function into mother object...

  SetPVPlacement();
   //SetPVPlacement();
   
   //Cabling(); 
  
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
