// $Id$
//*************************************************************************
//* --------------------
//* J4CALEM
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CALEM.hh"
//#include "J4CALEMSD.hh"
#include "J4CALParameterList.hh"
#include "G4Sphere.hh"
#include "J4CALMiniCone.hh"
//#include "J4CALBlock.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CALEM::firstName("EM");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CALEM::J4CALEM(J4VDetectorComponent *parent,
                                G4int  nclones,
                                G4int  nbrothers, 
                                G4int  me,
                                G4int  copyno ) 
  //: J4VCALDetectorComponent( fFirstName, parent, nclones,
   //                                 nbrothers, me, copyno  )
  : J4CALBlock( firstName, this, parent, nclones, nbrothers, me, copyno )
{   
  //std::cout << __FILE__ << __LINE__ << std::endl;
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CALEM::~J4CALEM()
{
  J4CALParameterList* list = OpenParameterList();
  G4int nMiniCones = list->GetEMMiniConeNClones();
  for(int i = 0; i < nMiniCones;i++){
    if(Deregister(fMiniCones[i])) delete fMiniCones[i];
  }
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CALEM::Assemble() 
{   
  if(!GetLV()){

    J4CALParameterList* ptrList = OpenParameterList();
    J4CALSubLayerParameterList* subList = ptrList -> GetSubLayerParam();
  
    G4Sphere *mother  = (G4Sphere *)(GetMother()->GetSolid()); 

    G4int nMiniCones  = ptrList->GetEMMiniConeNClones(); 
    G4double sphi     = mother->GetStartPhiAngle();
    G4double dphi     = mother->GetDeltaPhiAngle();
    G4double EMThickness = (ptrList->GetEMNLayers())*(subList->GetTotalLayerSize("EM"));
    G4double rmin   = mother->GetInsideRadius();
    G4double rmax   = rmin + EMThickness; 
    G4double dtheta = mother->GetDeltaThetaAngle(); 
    G4double stheta = mother->GetStartThetaAngle();

    G4Sphere* block = new G4Sphere(GetName(), rmin, rmax, sphi, dphi, stheta, dtheta);
    Register(block);
    SetSolid(block);

    MakeLVWith(OpenMaterialStore()->Order(ptrList->GetEMMaterial()));

    PaintLV(ptrList->GetEMVisAtt(), ptrList->GetEMColor());
      
//    J4CALBlock::Assemble();
 for(G4int i = 0; i < nMiniCones; i++){
   J4CALMiniCone* minicone = new J4CALMiniCone(fBlock,1,nMiniCones,i);
   fMiniCones.push_back(minicone);
   Register(minicone);
   minicone->InstallIn(fBlock);
   SetDaughter(minicone);
 }
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

//void J4CALEM::Cabling()
//{
//   if (!GetSD()) {
//      J4CALEMSD* sd = new J4CALEMSD(this);
//      Register(sd);
//      SetSD(sd);
//   }
//}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CALEM::InstallIn(J4VComponent         *mother,
                        G4RotationMatrix     *prot, 
                        const G4ThreeVector  &tlate ) 
{ 
   Assemble();			// You MUST call Assemble(); at first.
  				// 
  
   // Placement function into mother object...
   SetPVPlacement();
   
  // Cabling(); 
  
}


//* Draw  --------------------------------------------------------
void J4CALEM::Draw()
{
   // set visualization attributes
}
	
//* Print  --------------------------------------------------------
void J4CALEM::Print() const
{
}
