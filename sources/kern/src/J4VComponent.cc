// $Id$
//*************************************************************************
//* --------------------
//* J4VComponent
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "geomdefs.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "J4VComponent.hh"
#include "J4VSensitiveDetector.hh"
#include "J4PVPlacement.hh"
#include "J4PVReplica.hh"
#include "J4UnionSolid.hh"
#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
#endif

#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "J4SubtractionSolid.hh"
#include "G4Box.hh"
#include "J4Timer.hh"
#include "J4CommandArguments.hh"

#define __NMAXFAMILYMEMBERS__  500000

J4ComponentArray J4VComponent::fgFamilyMembers(__NMAXFAMILYMEMBERS__);

//************************************************************************
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -----------------------------------------------

J4VComponent::J4VComponent(const G4String&     groupname,
                           const G4String&     name,
                                 J4VComponent* parent,
                                 G4int         nclones,
                                 G4int         nbrothers,
                                 G4int         me,
                                 G4int         copyno):
                      J4Named(name),
                      fSubGroup(groupname), 
                      fMother(parent), fDaughters(64), fIsOn(FALSE), 
                      fIsInstalled(FALSE), fSolid(0), fLV(0), fPV(0), 
                      fNclones(nclones),
                      fNbrothers(nbrothers), fMyID(me),fCopyNo(copyno), 
                      fMyDepth(0)
{
   if (nclones < 1) {
      std::cerr<<"J4VComponent::constructor: No of clones must bigger than 0."<<std::endl;
   }
   if (nbrothers < 1) {
      std::cerr<<"J4VComponent::constructor: No of brothers must bigger than 0."<<std::endl;
   }
   if (nclones == 1) {
      // in this case, this component will not be replicated and copied.
      fCopyNo = 0;
   } 

   OpenMaterialStore();	
      
   SetName( name, fNbrothers, fMyID, fNclones, fCopyNo, fMother);
   
   if (fgFamilyMembers.entries() >= __NMAXFAMILYMEMBERS__) {
      std::cerr << "J4VComponent::constructor: Too many family members "
             << __NMAXFAMILYMEMBERS__ << " . abort. " << std::endl;
      abort();
   }
 
   fgFamilyMembers.append(this);
   
   if (!parent) {
      fMyDepth = 0;
   } else {
      fMyDepth = parent->GetMyDepth() - 1;
   }

#if 0
   Register(&fDaughters);
#endif
   
} 

//=====================================================================
//* destructor --------------------------------------------------------

J4VComponent::~J4VComponent()
{
#ifdef __GEANT451_OR_OLDER__
   // It's now G4's privilage to delete solids, pvs, lvs, and sds.

   if (Deregister(fSolid))  delete fSolid;
   if (Deregister(fPV))     delete fPV;
   if (fLV->GetSensitiveDetector()) { 
      if (Deregister(fLV->GetSensitiveDetector())) {
          delete fLV->GetSensitiveDetector();
      }
   }
   if (Deregister(fLV))     delete fLV;
#endif 
}


//=====================================================================
//* OutputAll ---------------------------------------------------------

void J4VComponent::OutputAll(G4HCofThisEvent* HCTE)
{
   if (GetSD()) {   	
      if (fIsOn) { 
          GetSD()->OutputAll(HCTE);
      }
   }

   G4int ndaughters = fDaughters.entries();

   G4int i;
 
   for( i=0; i<ndaughters; i++) {      	
      fDaughters[i]->OutputAll(HCTE);
   }
}

//=====================================================================
//* SwitchOn ----------------------------------------------------------
void J4VComponent::SwitchOn(G4String opt)
{
   if (GetSD()) {   	
      if (!fIsOn) fIsOn = TRUE;
      GetSD()->Activate( TRUE );
   }
   
   if (opt == "recursive") {
      G4int ndaughters = fDaughters.entries();
   
      G4int i;
      for(i=0; i<ndaughters; i++) {      	
         fDaughters[i]->J4VComponent::SwitchOn();
      }
   }
}

//=====================================================================
//* UnlockOutput ------------------------------------------------------

void J4VComponent::UnlockOutput()
{
   if (GetSD()) {     
      if (fIsOn) { 
          GetSD()->UnlockOutput();
      }
   }

   G4int ndaughters = fDaughters.entries();

   G4int i;
 
   for( i=0; i<ndaughters; i++) {             
      fDaughters[i]->UnlockOutput();
   }
}
 
//=====================================================================
//* SwitchOff ---------------------------------------------------------
void J4VComponent::SwitchOff(G4String opt)
{	

   if (GetSD()) {   	
      if (fIsOn) fIsOn = FALSE;
      GetSD()->Activate( FALSE );
   }
   
   if (opt == "recursive") {
      G4int ndaughters = fDaughters.entries();
   
      G4int i;
      for(i=0; i<ndaughters; i++) {      	
         fDaughters[i]->J4VComponent::SwitchOff();
      }
   }
}

//=====================================================================
//* SetDaughter -------------------------------------------------------
void J4VComponent::SetDaughter(J4VComponent* daughter)
{
   fDaughters.append(daughter);
}

//=====================================================================
//* SetMother ---------------------------------------------------------
void J4VComponent::SetMother(J4VComponent* mother)
{
   fMother = mother;
   SetName( GetName(), fNbrothers, fMyID, fNclones, fCopyNo, fMother);
   
}

//=====================================================================
//* SetSD -------------------------------------------------------------

void J4VComponent::SetSD(J4VSensitiveDetector* sd)
{
  static G4int timerID = -1;
  J4Timer timer( timerID, "J4VComponet", "SetSD()" );
  timer.Start(); 

  if (!fLV) Assemble(); 
  if (!fLV->GetSensitiveDetector()) {
     G4SDManager::GetSDMpointer()-> AddNewDetector(sd);
     fLV-> SetSensitiveDetector(sd);
  } else if (fCopyNo > 0) {
     std::cerr << "J4VComponent::SetSD at " << GetName() 
            << " SetSD failed because you are not the owner of your LogicalVolume."
            << "You must delete your sd created by new operator. abort." << std::endl;
     abort();
  } 
  timer.Stop();
}

//=====================================================================
//* SetName --------------------------------------------------------

void J4VComponent::SetName(const G4String&       name,
                                   G4int         nbrothers,
                                   G4int         me,
                                   G4int         nclones,
                                   G4int         copyno,
                                   J4VComponent *parent)
{
  // setting unique name to object. 

  G4int width1 = (G4int)std::log10(nbrothers + 0.1) + 1;   
  G4int width2 = (G4int)std::log10(nclones + 0.1) + 1;   

  G4String newname;

  if (nbrothers > 1) {
     if (nclones > 1 && copyno != -1) {   // if I will not be replica
        if (parent) { 
           newname = GetNewName(name, me, width1, copyno, width2, &(G4String &)(parent->GetName()));
        } else {
           newname = GetNewName(name, me, width1, copyno, width2);
        }
     } else {
        if (parent) {
           newname = GetNewName(name, me, width1, 0, 0, &(G4String &)(parent->GetName()));
        } else {
           newname = GetNewName(name, me, width1);
        }
     }
  } else {
    if (nclones > 1 && copyno != -1) {
       if (parent) {
          newname = GetNewName(name, 0, 0, copyno, width2, &(G4String &)(parent->GetName()));
       }else  {
          newname = GetNewName(name, 0, 0, copyno, width2);
       }
    } else {
       if (parent){
          newname = GetNewName(name, 0, 0, 0, 0, &(G4String &)(parent->GetName()));
       }else  {
          newname = GetNewName(name);
       }
    }
  } 
  J4Named::SetName(newname);
#if 0
  if ( J4CommandArguments::VerboseLevel() > 10 ) {
    std::cerr << " My name is " << GetName() << std::endl;
  }
  else if ( J4CommandArguments::VerboseLevel() > 5 ) {
    const char *name=GetName().data();
    int ncol=0;
    for(int k=0; k<strlen(name);k++) {
       if ( name[k] == '/' ) {
          ncol++;
       }          
    }  
    if ( ncol < J4CommandArguments::VerboseLevel() - 4 ) { 
      std::cerr << " My name is " << GetName() << std::endl;
    }
  }
#endif
}

//=====================================================================
//* MakeLVWith --------------------------------------------------------

void J4VComponent::MakeLVWith( G4Material* material, G4UserLimits* ulp)
{
  if (!fLV) {
     if (!fSolid) {
        std::cerr << "J4VComponent::MakeLVWith of " << GetName() 
             << " Solid does not exist. Create G4VSolid at first. return." << std::endl;
     }  

     fLV = new G4LogicalVolume(fSolid, material, GetName()); 
     Register(fLV);

     if (ulp) fLV->SetUserLimits(ulp);

  } else { 
        std::cerr << "J4VComponent::MakeLVWith at "  << GetName() 
             << " LogicalVolume already exists. return." << std::endl;
  }   
}

//=====================================================================
//* PaintLV   --------------------------------------------------------

void J4VComponent::PaintLV(G4bool visibility, const G4Color& color)
{
   if (fLV) {
      if (!fLV->GetVisAttributes()) {
         G4VisAttributes* visatt
            = new G4VisAttributes(visibility, color);
         Register(visatt);
         fLV-> SetVisAttributes(visatt);   
      } else {
         ((G4VisAttributes *)fLV->GetVisAttributes())->SetVisibility(visibility);
         ((G4VisAttributes *)fLV->GetVisAttributes())->SetColor(color);
      }
 
   } else {
      std::cerr << "J4VComponent::PrintLV at "
           << GetName() 
           << " You must create LogicalVolume first. return" << std::endl; 
   }
}


//=====================================================================
//* GetComponentPtrByName ---------------------------------------------
J4VComponent* 
	J4VComponent::GetComponentPtrByName(const G4String& name) 
{
   G4int n = fgFamilyMembers.entries();
   
   for (G4int i=0; i<n; i++) {   	
      if (name == fgFamilyMembers[i]->GetName()) {
          return fgFamilyMembers[i] ;
      } 	
   }

   std::cerr << " J4VComponent::GetComonentPtrByName " << std::endl
          << "      Cannot find object name " << name << std::endl;
   return 0;
}

//=====================================================================
//* SetPVPlacement ----------------------------------------------------

void J4VComponent::SetPVPlacement(G4RotationMatrix *pRot,
                                  const G4ThreeVector &tlate)
{
  if (fPV) {
     std::cerr << " J4VComponent::SetPVPlacement at " << GetName() 
            << " PhysicalVolume already exists. abort." << std::endl;
     abort();
  } 
  if (!fLV) {
     std::cerr << " J4VComponent::SetPVPlacement at " << GetName() 
            << " LogicalVolume does not exist. abort." << std::endl;
     abort();
  } 
      
  G4LogicalVolume*  motherLV = (fMother ? fMother->GetLV() : 0);
  
  fPV =  new J4PVPlacement(this,
		           pRot,		// Rotation matrix
    		     	   tlate, 		// Three vector of center position
    			   fLV, 		// Logical volume
    			   GetName(),	 	// Name of Physical volume
    		           motherLV,  		// Mother Logical
    			   FALSE,		// pMany
    			   fCopyNo ); 		// pCopyNo	

  Register(fPV);
}  

//=====================================================================
//* SetPVReplica   ----------------------------------------------------

void J4VComponent::SetPVReplica(const EAxis pAxis, G4double step,
  			                const G4double offset)
{ 
  if (fPV) {
     std::cerr << " J4VComponent::SetPVReplica at " << GetName() 
            << " PhysicalVolume already exists. abort." << std::endl;
     abort();
  } 
  if (!fLV) {
     std::cerr << " J4VComponent::SetPVPlacement at " << GetName() 
            << " LogicalVolume does not exist. abort." << std::endl;
     abort();
  } 

  if (fNclones < 2) {
     std::cerr << " J4VComponent::SetPVReplica at " << GetName()
          << " You shouldn't be replicated because "
          << "fNclones is less than 2. "
          << "Use SetPVPlacement(). return. " << std::endl;
     return;
  } else if (fCopyNo != -1) {
     std::cerr << "J4VComponent::SetPVReplica at " << GetName()
          << " You are copied component. Use SetPVPlacement(). return." << std::endl;
     return;
  }

  G4LogicalVolume*  motherLV = (fMother ? fMother->GetLV() : 0);
  
  G4double doffset = offset;
  if ( pAxis == kPhi )  doffset -= 0.5*step;

  fPV = new J4PVReplica( this,
		         GetName(),          // Name of Physical Volume
                         fLV,            // Logical Volume
                         motherLV,       // Mother Logical 
                         pAxis,          // Direction of replication
                         fNclones,       // Number of replicas
                         step,           // Distance between adjacent clones
                         doffset );      // Position of the first

  Register(fPV);

}

//=====================================================================
//* OrderNewTubs ------------------------------------------------------

void J4VComponent::OrderNewTubs( G4double rmin,
                                 G4double rmax,
                                 G4double halfzlen,
                                 G4double totalphi,
                                 G4double endcaphalfthickness,
                                 G4double endcaprmin,
                                 G4double sphi,
                                 G4double leftrmin,
                                 G4double rightrmin )
{

  if (fSolid) {
     std::cerr << " J4VComponent::OrderNewTubs at " << GetName() 
            << " fSolid already exists. abort." << std::endl;
     abort();
  } 
  if (fNclones == 0) {
        std::cerr << " J4VComponent::OrderNewTubs at " << GetName()
               << " fNclones must be greater than 0 !! " << std::endl;
        abort();
  }

  G4double  dphi = (fNclones != 1 ? totalphi/fNclones : totalphi);
  
  if (sphi == DBL_MAX) {   
    sphi = (-dphi/2.);
  }
  
    
  if (!endcaphalfthickness) { 
  
    fSolid = new G4Tubs( GetName(), rmin, rmax, halfzlen, sphi, dphi );     
      
  } else { 
    
    if (endcaprmin == DBL_MAX) endcaprmin = rmin;
    
    std::cerr << "Endcap rmin = " << endcaprmin << std::endl;
    
    G4ThreeVector lefttranslation ( 0., 0., halfzlen - endcaphalfthickness);
    G4RotationMatrix rotation;
    G4Transform3D lefttransform   (rotation, lefttranslation);
    
    G4String cylindername(GetName());                       //* description of ccenter
    cylindername += ".Cylinder";
    std::cerr << "Make " << cylindername << std::endl;
#if 1
    G4double cylinderlen = halfzlen - endcaphalfthickness * 2;
#else
    G4double cylinderlen;
    if (leftrmin < 0) {
       cylinderlen = halfzlen - endcaphalfthickness * 2;
    } else {
       cylinderlen = halfzlen;
    }
#endif
    G4Tubs*  cylinder    
        = new G4Tubs( cylindername, rmin, rmax, cylinderlen, sphi, dphi );

    G4String leftendcapname(GetName());                     //* description of left
    leftendcapname += ".LeftEndcap";
    std::cerr << "Make " << leftendcapname << std::endl;

    G4VSolid* leftendcap;

    if (leftrmin < 0) {

      leftendcap 
          = new G4Tubs( leftendcapname, endcaprmin, rmax, endcaphalfthickness, sphi, dphi );
    } else {

      leftendcap 
          = new G4Cons( leftendcapname, endcaprmin, rmax, leftrmin, rmax, endcaphalfthickness, sphi, dphi );

    }
    
    G4String cupname(GetName());                            //* description of uniting
    cupname += ".Cup";
    std::cerr << "Make " << cupname << std::endl;
#if 1
    J4UnionSolid*  cup = new J4UnionSolid ( cupname, cylinder, leftendcap, lefttransform );
#else
    G4VSolid *cup = 0;
    if (leftrmin < 0) {
       cup = new J4UnionSolid ( cupname, cylinder, leftendcap, lefttransform );
    } else {
       cup = new J4UnionSolid ( cupname, cylinder, leftendcap, lefttransform );
    }
#endif
        
    G4String rightendcapname(GetName());                    //* description of right
    rightendcapname += ".RightEndcap";
    std::cerr << "Make " << rightendcapname << std::endl;

    G4VSolid* rightendcap;

    if (rightrmin < 0) {

      rightendcap 
          = new G4Tubs( rightendcapname, endcaprmin, rmax, endcaphalfthickness, sphi, dphi );

    } else {

      rightendcap
          = new G4Cons( rightendcapname, rightrmin, rmax, endcaprmin, rmax, endcaphalfthickness, sphi, dphi );

    }

                                                            //* description of uniting
    
    G4ThreeVector    righttranslation ( 0., 0., -(halfzlen - endcaphalfthickness));
    G4Transform3D    righttransform   (rotation, righttranslation);
    std::cerr << "Make " << GetName() << std::endl;
#if 1
    fSolid = new J4UnionSolid ( GetName(), cup, rightendcap, righttransform );    
#else
    if (leftrmin < 0) {
       fSolid = new J4UnionSolid ( GetName(), cup, rightendcap, righttransform );    
    } else {
       fSolid = new J4SubtractionSolid ( GetName(), cup, rightendcap, righttransform );    
    }
#endif
    
  }
 
  Register(fSolid); 
  
}

//=====================================================================
//* OrderNewBox -------------------------------------------------------

void J4VComponent::OrderNewBox(
                              G4double             outerboxhalfx,
                              G4double             outerboxhalfy,
                              G4double             outerboxhalfz,
                              G4double             innertubrad,
                              G4RotationMatrix    *ptubrot,
                              const G4ThreeVector &tubtlate,
                              G4double             innerboxhalfx,
                              G4double             innerboxhalfy,
                              G4double             innerboxhalfz,
                              G4RotationMatrix    *pboxrot,
                              const G4ThreeVector &boxtlate     )
{

  // OrderNewBox makes a box with a cylindrycal hole and a boxy cavity.
  // To get a filled box, set innerrad=0 and innerbox palameters = 0.

  if (fSolid) {
     std::cerr << " J4VComponent::OrderNewBox at " << GetName() 
            << " fSolid already exists. abort." << std::endl;
     abort();
  } 

  // check arguments -------------------------
  if (outerboxhalfx == 0 || outerboxhalfy == 0 || outerboxhalfz == 0) {
    std::cerr << "J4VComponent::OrderNewBox: "
         << "argument error! outerbox variables must greater than 0. " << std::endl;
    abort(); 
  } else if (!(innerboxhalfx == 0 && innerboxhalfy == 0 && innerboxhalfz == 0)
              && innerboxhalfx * innerboxhalfy * innerboxhalfz == 0 ) {
    std::cerr << "J4VComponent::OrderNewBox: "
         << "argument error! innerbox must be 3-dimension" << std::endl;
    abort(); 
  }

  // construct solid -------------------------

  G4String outerboxname(GetName());
  outerboxname += ".Outerbox";
  G4VSolid *outerbox = new G4Box (outerboxname, outerboxhalfx, outerboxhalfy, outerboxhalfz );

  if (!innertubrad && !innerboxhalfx) {
    fSolid = outerbox;
    fSolid->SetName(GetName());

  } else if (innertubrad) {
    G4String innertubname(GetName());
    innertubname += ".Innertub";
    G4VSolid *innertub = new G4Tubs( innertubname, 0, innertubrad, outerboxhalfz, 0, 2*M_PI);

    if (!innerboxhalfx) {
      fSolid = new J4SubtractionSolid( GetName(), outerbox, innertub, ptubrot, tubtlate );

    } else {
      G4String holedboxname(GetName());
      holedboxname += ".Holedbox";
      G4VSolid *holedbox = new J4SubtractionSolid( holedboxname, outerbox,
                                                  innertub, ptubrot, tubtlate );
      G4String innerboxname(GetName());
      innerboxname += ".Innerbox";
      G4VSolid *innerbox = new G4Box( innerboxname, innerboxhalfx, innerboxhalfy, innerboxhalfz );

      fSolid = new J4SubtractionSolid( GetName(), holedbox, innerbox, pboxrot, boxtlate );
    }

  } else if (innerboxhalfx) {
    G4String innerboxname(GetName());
    innerboxname += ".Innerbox";
    G4VSolid *innerbox = new G4Box( innerboxname, innerboxhalfx, innerboxhalfy, innerboxhalfz );

    fSolid = new J4SubtractionSolid( GetName(), outerbox, innerbox, pboxrot, boxtlate );

  } else { 
    std::cerr << " J4VComponent::OrderNewBox: Program inconsistency! check program." << std::endl;
    abort();
  }

  Register(fSolid);

}

//=====================================================================
//* OpenMaterialStore -------------------------------------------------

J4VMaterialStore* J4VComponent::OpenMaterialStore()
{
    return 0;
}

//=====================================================================
//* GetNewName --------------------------------------------------------

G4String J4VComponent::GetNewName(const G4String &middlename, // component class name
                                  G4int           myID,       // I'm (firsthame)-th child
                                  G4int           width1,     // field width for firstname 
                                  G4int           cloneID,    // I'm (cloneID)-th clone 
                                  G4int           width2,     // field width for clone 
                                  G4String       *parentname) // parent component name
{
#ifdef __USEISOCXX__
  std::stringstream ost;
#else
  char tmpstr[1024];
  std::strstream ost(tmpstr, 1024);
#endif
//  if (parentname) ost << *parentname << ":";
  if (parentname) ost << *parentname << "/";
  ost << middlename;
  if (width1) ost << std::setw(width1) << std::setfill('0') << myID;
  if (width2) ost << "_" 
                  << std::setw(width2) << std::setfill('0') << cloneID;
#ifdef __USEISOCXX__
  G4String tempname(ost.str());
#else
  ost << std::ends;
  G4String tempname(tmpstr);
#endif
  return tempname;
}
