// $Id$
//*************************************************************************
//* --------------------
//* J4CDCStereoCell
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2004/08/26  K.Fujii	Fixed rotation direction.
//*************************************************************************

#include "J4CDCStereoCell.hh"
#include "J4CDCStereoDriftRegion.hh"
//#include "J4CDCDummyDriftRegion.hh"
#include "J4TwistedTubs.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4CDCStereoCell::fFirstName("StereoCell");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCStereoCell::J4CDCStereoCell(J4VDetectorComponent *parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
           J4VCDCCell(fFirstName, parent, nclones,
                      nbrothers, me, copyno  ),
           fDriftRegions(0) //, fDummyDriftRegions(0) 
{
   G4double motherdphi = GetDeltaPhi(parent);
   G4double step       = motherdphi / nclones;
   G4double sphi       = step * copyno;
   fRot.rotateZ(-sphi);   
}

J4CDCStereoCell::J4CDCStereoCell(const J4CDCStereoCell &orig, 
                                       G4int copyno)
                :J4VCDCCell(orig, copyno)
{
   G4double motherdphi = GetDeltaPhi(orig.GetMother());
   G4double step       = motherdphi / (orig.GetNclones());
   G4double sphi       = step * copyno;
   fRot.rotateZ(-sphi);
}


//=====================================================================
//* destructor --------------------------------------------------------

J4CDCStereoCell::~J4CDCStereoCell()
{
   if (fDriftRegions) {	
      for (G4int i = 0; i < OpenParameterList()->GetNdriftRegions(); i++) {
         if (Deregister(fDriftRegions[i])) delete fDriftRegions [i];
      } 
      if (Deregister(fDriftRegions)) delete [] fDriftRegions;
   }
#if 0
   if (fDummyDriftRegions) {	
      for (G4int i = 0; i < 2; i++) {
         if (Deregister(fDummyDriftRegions[i])) delete fDummyDriftRegions[i];
      } 
      if (Deregister(fDummyDriftRegions)) delete [] fDummyDriftRegions;
   }
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCStereoCell::Assemble() 
{   
  if (!GetLV())
  {	  
     J4CDCParameterList *list = OpenParameterList();
     
     // define geometry
     G4double shieldwidth = GetShieldWidth();
     G4double endinnerrad = GetInnerRadius(GetMother()) + shieldwidth;
     G4double endouterrad = GetOuterRadius(GetMother());
     G4double halfzlen    = GetZHalfLength(GetMother());
     G4double motherdphi  = GetDeltaPhi(GetMother());
     G4double twistedAng  = GetTwistedAngle();
        
     // MakeSolid ----------//
     J4TwistedTubs* cell = new J4TwistedTubs(GetName(),
                                             twistedAng,
                                             endinnerrad,
                                             endouterrad,
                                             halfzlen,
                                             GetNclones(),
                                             motherdphi);
     Register(cell);
     SetSolid(cell);                          
    
     // MakeLogicalVolume --//
     G4String material = list->GetCDCMaterial();
     MakeLVWith(OpenMaterialStore()->Order(material));

     // TwistedTubs MUST NOT OPTIMIZED !!
     GetLV()->SetOptimisation(FALSE);
    
     // SetVisAttribute ----//
     PaintLV(list->GetStereoCellVisAtt(), 
             list->GetStereoCellColor());    
        
     // Install daughter PV //
     // Install DriftRegion //
        
     G4int nDRbrothers = list->GetNdriftRegions();
     G4int nDRclones   = 1;
     fDriftRegions = new J4CDCStereoDriftRegion* [nDRbrothers];
     Register(fDriftRegions);
  
     for (G4int i = 0; i < nDRbrothers; i++) {
        fDriftRegions [i]
          = new J4CDCStereoDriftRegion(this, nDRclones, nDRbrothers, i);
        Register(fDriftRegions[i]);
        fDriftRegions [i]->InstallIn(this);   
        SetDaughter(fDriftRegions [i]);
     }    
    
#if 0
    // Install DummyDriftRegion //
        
    G4int nDDRbrothers = 2;
    G4int nDDRclones   = 1;

    fDummyDriftRegions = new J4CDCDummyDriftRegion* [nDDRbrothers];
    Register(fDummyDriftRegions);
  
    for (G4int i = 0; i < nDDRbrothers; i++) {
      fDummyDriftRegions [i]
        = new J4CDCDummyDriftRegion(this, nDDRclones, nDDRbrothers, i );
      Register(fDummyDriftRegions[i]);
      fDummyDriftRegions [i]->InstallIn(this);   
      
      SetDaughter(fDummyDriftRegions [i]);
    }  
#endif
  
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CDCStereoCell::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCStereoCell::InstallIn(J4VComponent        *,
                                G4RotationMatrix    *,
                                const G4ThreeVector &) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object -----//
  
  SetPVPlacement(&fRot);
  
}

//* Draw  --------------------------------------------------------
void J4CDCStereoCell::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDCStereoCell::Print() const
{
}
