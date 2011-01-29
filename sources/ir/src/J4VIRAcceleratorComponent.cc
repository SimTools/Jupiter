// $id: J4VIRAcceleratorComponent.cc,v 1.1.1.1 2002/05/02 07:56:57 hoshina Exp $
//*************************************************************************
//* -----------------------
//* J4VIRAcceleratorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2002/09/13 T.Aso        Changed for IR 
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "G4UserLimits.hh"
#include "J4ParameterTable.hh"

J4IRMaterialStore* J4VIRAcceleratorComponent::fMaterialStore = 0;

G4String J4VIRAcceleratorComponent::fSubGroup("IR");

//=====================================================================
//---------------------
// class 
//---------------------

//=====================================================================
//* default constructor -----------------------------------------------

J4VIRAcceleratorComponent::J4VIRAcceleratorComponent(
                                const G4String       &name, 
  			   	J4VComponent *parent,
                                G4int                 nclones,
                                G4int                 nbrothers, 
                                G4int                 me,
                                G4int                 copyno,
				G4bool             reflection) :
                        J4VAcceleratorComponent(fSubGroup, name, 
                         		      parent, nclones,	 
						nbrothers, me, copyno ),
			fReflection(reflection)
{ 
}

//=====================================================================
//* destructor --------------------------------------------------------

J4VIRAcceleratorComponent::~J4VIRAcceleratorComponent()
{	
   if(Deregister(fMaterialStore)) delete fMaterialStore;
}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VIRAcceleratorComponent::OpenMaterialStore()
{
   if(!fMaterialStore) {
   	fMaterialStore = new J4IRMaterialStore();
	Register(fMaterialStore);
  	std::cerr << "*** Opend J4IRMaterialStore ***" << std::endl;
   }
    
   return fMaterialStore;
}
//=====================================================================
//*   --------------------------------------------------------
G4RotationMatrix* J4VIRAcceleratorComponent::GetRotation(){
  G4RotationMatrix* rot = new G4RotationMatrix;
  return rot;
}
G4ThreeVector&  J4VIRAcceleratorComponent::GetTranslation(){
  G4ThreeVector* p = new G4ThreeVector;
  return *p;
}
//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4VIRAcceleratorComponent::InstallIn(J4VComponent      *, // mother
                                          G4RotationMatrix  *prot,
                                    const G4ThreeVector     &tlate) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  G4UserLimits* myLimits = new G4UserLimits;
  //myLimits->SetMaxAllowedStep(100.*micrometer);
  //myLimits->SetMaxAllowedStep(1000.*micrometer);
  //myLimits->SetMaxAllowedStep(1.*mm);
  myLimits->SetMaxAllowedStep(10.*cm);
  G4double umaxtime= J4ParameterTable::GetValue("J4IR.UserMaxTime",1000.0)*nanosecond;
  myLimits->SetUserMaxTime(umaxtime);
  GetLV()->SetUserLimits(myLimits);

  // Placement function into mother object...
  G4ThreeVector position = tlate;
  G4RotationMatrix* rotation = prot;
  if ( prot == 0 && tlate==G4ThreeVector(0.) ) {
    rotation = GetRotation();
    position = GetTranslation();

    if ( fReflection ){
      position.setZ(-position.z());
      //      G4double angle = (rotation->getAxis()).y()*rotation->getDelta();
      //      angle = 180.*degree - angle*2.;
      //      rotation->rotateY(angle);
      rotation->rotateX(180.0*degree);
    } 
  }
  SetPVPlacement(rotation,position);

  //  if (!GetSD()) Cabling(); 

}

