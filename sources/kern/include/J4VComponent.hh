// $Id$
#ifndef __J4VCOMPONENT__
#define __J4VCOMPONENT__
//*************************************************************************
//* --------------------
//* J4VComponent
//* --------------------
//*     
//* (Update Record)
//*	2002/05/15  K.Hoshina	Original version.
//*************************************************************************

//_________________________________________________________________________
//
// Class description 
//
// This class is the abstract base class for all components.
// Use this class by inheriting from it and overriding the
// members, Assemble() and InstallIn(), etc.
//------------------------------------------------------------------------

#include "G4VSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4SDManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"
#include "G4Color.hh"
#include "J4Named.hh"
#include "J4TypeDef.hh"

class J4VMaterialStore;
class J4VComponent;
class J4VSensitiveDetector;
//=====================================================================
//---------------------
// class definition
//---------------------

class J4VComponent : public J4Named
{
public:

  //====== constructor
  J4VComponent(const G4String             &groupname,
                     const G4String       &name, 
                     J4VComponent         *parent    = 0,
                     G4int                 nclones   = 1,
                     G4int                 nbrothers = 1, 
                     G4int                 me        = 0,
                     G4int                 copyno    = -1);

  //===== copy constructor
          // If you want some copied objects, you should use this constructor
          // in order to save memoly. This constructor copies fLV pointer 
          // from original object, then original one and copied objects share
          // same LogicalVolume object. 
  inline J4VComponent(const J4VComponent &orig, G4int copyno);
  			
  //===== destructor
  virtual ~J4VComponent();

  //===== operators
  inline const J4VComponent &operator=(const J4VComponent &right);    

  //===== member functions 
  virtual void	 InstallIn(J4VComponent         *mother, 
                           G4RotationMatrix     *prot  = 0, 
                           const G4ThreeVector  &tlate = 0 ) = 0; 
  virtual void   Draw()        = 0;
  virtual void   Print() const = 0;
  virtual void   OutputAll(G4HCofThisEvent *HCTE     ) ;
  virtual void   UnlockOutput() ;
  virtual void   SwitchOn (G4String opt = "recursive") ; 
  virtual void   SwitchOff(G4String opt = "recursive") ;
   
  //===== get method
  inline virtual       G4VSolid             *GetSolid()     const { return fSolid;    }
  inline virtual       G4LogicalVolume      *GetLV()        const { return fLV;       }
  inline virtual       J4VSensitiveDetector *GetSD()        const 
                        {
                           return (J4VSensitiveDetector *)fLV->GetSensitiveDetector(); 
                        }
  inline virtual       G4VPhysicalVolume    *GetPV()        const { return fPV;       }
  inline virtual       J4VComponent         *GetMother()    const { return fMother;   }
  inline virtual       G4int                 GetNbrothers() const { return fNbrothers;}
  inline virtual       G4int                 GetMyID()      const { return fMyID;     } 
  inline virtual       G4int                 GetNclones()   const { return fNclones;  } 
  inline virtual       G4int                 GetCopyNo()    const { return fCopyNo;   } 
  inline virtual const G4String             &GetSubGroup()  const { return fSubGroup; }   
  inline virtual       G4int                 GetMyDepth()   const { return fMyDepth;  }

  inline virtual       G4bool                IsOn()         const { return fIsOn;        }
  inline virtual       G4bool                IsInstalled()  const { return fIsInstalled; }
  inline         const EPlacementType        GetPlacementType() const; 
  
  //===== set method
  inline virtual void SetSolid        (G4VSolid          *solid) { fSolid  = solid; }
  inline virtual void SetLV           (G4LogicalVolume   *lv   ) { fLV     = lv;    }
  inline virtual void SetPV           (G4VPhysicalVolume *pv   ) { fPV     = pv;    }
  inline virtual void SetIsOn         (G4bool             flag ) { fIsOn   = flag;  }    
         virtual void SetDaughter     (J4VComponent *daughter);
         virtual void SetMother       (J4VComponent *mother  );
         virtual void SetSD           (J4VSensitiveDetector *sd);

  			      				
  //===== static function
  static J4VComponent      *GetComponentPtrByName(const G4String& name);      
  static J4ComponentArray   GetFamilyMembers     () { return fgFamilyMembers; }     

protected:
  					     
  //===== PVPlacement method
  virtual void SetPVPlacement(G4RotationMatrix    *pRot  = 0,
                              const G4ThreeVector &tlate = 0);
  virtual void SetPVReplica  (const EAxis    pAxis, 
                              G4double       step,
                              const G4double offset = 0);
                            
  //===== user tools
  virtual void MakeLVWith   (G4Material* material, G4UserLimits *ulp = 0);
  virtual void PaintLV      (G4bool visibility, const G4Color &color); 
  virtual void OrderNewTubs ( G4double rmin,
  			      G4double rmax,
  			      G4double halfzlen,
  			      G4double totalphi = 360.*deg,
  			      G4double endcaphalfthickness = 0.,
  			      G4double endcaprmin = DBL_MAX,
  			      G4double sphi = DBL_MAX);	// If sphi=DBL_MAX,
  			      				// sphi is replaced
  			      				// to -(dphi/2.).
                            
  virtual void OrderNewBox ( G4double             outerboxhalfx,
                             G4double             outerboxhalfy,
                             G4double             outerboxhalfz,
                             G4double             innertubrad = 0,
                             G4RotationMatrix    *ptubrot = 0,
                             const G4ThreeVector &tubtlate = 0,
                             G4double             innerboxhalfx = 0,
                             G4double             innerboxhalfy = 0,
                             G4double             innerboxhalfx = 0,
                             G4RotationMatrix    *pboxrot = 0,
                             const G4ThreeVector &boxtlate = 0 );


private:
  			       
  virtual void              Assemble() = 0;
  virtual void              Cabling () = 0;
  virtual J4VMaterialStore *OpenMaterialStore();

  //===== naming functions
  virtual void              SetName(const G4String &name,
                                    G4int           nbrothers = 1,
                                    G4int           me        = 0,
                                    G4int           nclones   = 1,
                                    G4int           copyno    = 0,
                                    J4VComponent   *parent    = 0);		    	 
  virtual G4String          GetNewName(const G4String &middlename, 
                                       G4int           me         = 0, 
                                       G4int           width1     = 0, 
                                       G4int           copyno     = 0,
                                       G4int           width2     = 0,
                                       G4String       *parentname = 0);  
  					   
private: 

  //===== data members
  G4String               fSubGroup;               // subgroup name
  J4VComponent          *fMother;                 // pointer to mother detector component
  J4ComponentArray       fDaughters;              // pointer array to daughter detector components
  G4bool                 fIsOn;                   // switch flag of Sensitive Detector 
  G4bool                 fIsInstalled;            //   
  G4VSolid              *fSolid;                  // pointer to G4Solid
  G4LogicalVolume       *fLV;                     // pointer to G4LogicalVolume
  G4VPhysicalVolume     *fPV;                     // pointer to G4PhysicalVolume
  G4int                  fNclones;                // number of division 
  G4int                  fNbrothers;              // number of copy placed by PVPlacement 
  G4int                  fMyID;                   // my number in brothers 
  G4int                  fCopyNo;                 // copyNo of G4PVPlacement 
  G4int                  fMyDepth;                // my depth from world volume 

  //===== static data member
  static J4ComponentArray fgFamilyMembers;
      
};


//=====================================================================
//---------------------
// inline function
//---------------------

J4VComponent::J4VComponent(const J4VComponent& orig, G4int copyno)
{
  // This constructor makes copy object without making new LogecalVolume.
  // The original object and copied objects share a LogicalVolume.

  fSubGroup            = orig.fSubGroup   ;
  fMother              = orig.fMother     ;
  fDaughters           = orig.fDaughters  ;
  fIsInstalled         = orig.fIsInstalled;
  fSolid               = orig.fSolid      ;
  fLV                  = orig.fLV         ;
  fPV                  = 0                ;
  fNclones             = orig.fNclones    ;
  fNbrothers           = orig.fNbrothers  ;
  fMyID                = orig.fMyID       ;
  fCopyNo              = copyno           ;

  G4String origname = orig.GetName();
  G4int loc1 = origname.rfind(':');
  if (loc1 < 0) loc1 = 0;
  else          loc1 = loc1++;
  G4int loc2 = origname.rfind('_');
  if (loc2 < 0) loc2 = origname.length();
  else          loc2 = loc2--;
  G4String name(origname.substr(loc1,loc2-loc1+1));

  SetName( name, fNbrothers, fMyID, fNclones, fCopyNo, fMother);
  J4Named::SetName(name);

}

const J4VComponent& 
J4VComponent::operator= (const J4VComponent& right)
{

  fSubGroup            = right.fSubGroup   ;
  fMother              = right.fMother     ;
  fDaughters           = right.fDaughters  ;
  fIsInstalled         = right.fIsInstalled;
  fSolid               = right.fSolid      ;
  fLV                  = right.fLV         ;
  fPV                  = right.fPV         ;
  fNclones             = right.fNclones    ;
  fNbrothers           = right.fNbrothers  ;
  fMyID                = right.fMyID       ;
  fCopyNo              = right.fCopyNo     ;

  J4Named::SetName(right.GetName());
  
  return *this;
            
}

const EPlacementType
J4VComponent::GetPlacementType() const 
{
  if (fNclones < 2 ) return kSingle;
  if (fCopyNo == -1) return kReplicated;
  return kCopied;
}

#endif


