// $Id$
//*************************************************************************
//* --------------------
//* J4CDCCell
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4CDCCell.hh"
#include "J4CDCDriftRegion.hh"
#if 0
#include "J4CDCDummyDriftRegion.hh"
#endif

#include "G4Tubs.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------


G4String J4CDCCell::fFirstName("Cell");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4CDCCell::J4CDCCell(J4VDetectorComponent *parent,
                                    G4int  nclones,
                                    G4int  nbrothers, 
                                    G4int  me,
                                    G4int  copyno ) :
           J4VCDCCell( fFirstName, parent, nclones,
                       nbrothers, me, copyno ),
           fDriftRegions(0), //fDummyDriftRegions(0), 
           fRmin(0), fRmax(0)
{
   G4double shieldwidth = GetShieldWidth();
   fRmin = GetInnerRadius(parent) + shieldwidth;
   fRmax = GetOuterRadius(parent);
}

J4CDCCell::J4CDCCell(const J4CDCCell &orig,
                           G4int      copyno ) :
           J4VCDCCell( orig, copyno ),
           fDriftRegions(0), //fDummyDriftRegions(0), 
           fRmin(0), fRmax(0)
{
   G4double shieldwidth = GetShieldWidth();
   J4VDetectorComponent *parent = (J4VDetectorComponent*)orig.GetMother();
   fRmin = GetInnerRadius(parent) + shieldwidth;
   fRmax = GetOuterRadius(parent);
}

//=====================================================================
//* destructor --------------------------------------------------------

J4CDCCell::~J4CDCCell()
{
   if (fDriftRegions) {	
      G4int i;  
      for (i = 0; i < OpenParameterList()->GetNdriftRegions(); i++) {
         if (Deregister(fDriftRegions[i])) delete fDriftRegions [i];
      } 
      if (Deregister(fDriftRegions)) delete [] fDriftRegions;
   }
#if 0
   if (fDummyDriftRegions) {	
      G4int i;  
      for (i = 0; i < 2 ; i++) {
         if (Deregister(fDummyDriftRegions[i])) delete fDummyDriftRegions[i];
      } 
      if (Deregister(fDummyDriftRegions)) delete [] fDummyDriftRegions;
   }
#endif
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4CDCCell::Assemble() 
{   
  if (!GetLV())
  {	  
     J4CDCParameterList *list = OpenParameterList();
     
     // define geometry
     G4double len        = GetZHalfLength(GetMother());
     G4double motherdphi = GetDeltaPhi(GetMother());
        
     // MakeSolid ----------//
     OrderNewTubs(fRmin, fRmax, len, motherdphi);
    
     // MakeLogicalVolume --//
     G4String material = list->GetCDCMaterial();
     MakeLVWith(OpenMaterialStore()->Order(material));
    
     // SetVisAttribute ----//
     PaintLV(list->GetCellVisAtt(), list->GetCellColor());    
        
     // Install daughter PV //
     // Install DriftRegion //
        
     G4int nDRbrothers = list->GetNdriftRegions();
     G4int nDRclones   = 1;
     fDriftRegions = new J4CDCDriftRegion* [nDRbrothers];
     Register(fDriftRegions);
     
     for (G4int i = 0; i < nDRbrothers; i++) {
        fDriftRegions [i]
          = new J4CDCDriftRegion(this, nDRclones, nDRbrothers, i);
        Register(fDriftRegions[i]);
        fDriftRegions [i]->InstallIn(this);   
        SetDaughter(fDriftRegions [i]);
     }    
    
    // Install DummyDriftRegion //
#if 0
    G4int nDDRbrothers = 2;
    G4int nDDRclones   = 1;

    fDummyDriftRegions = new J4CDCDummyDriftRegion* [nDDRbrothers];
    Register(fDummyDriftRegions);
  
    for (G4int i = 0; i < nDDRbrothers; i++) {
      fDummyDriftRegions [i]
        = new J4CDCDummyDriftRegion(this, nDDRclones, nDDRbrothers, i);
      Register(fDummyDriftRegions[i]);
      fDummyDriftRegions [i]->InstallIn(this);   
      
      SetDaughter(fDummyDriftRegions [i]);
    }  
#endif
  
  }
}

//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4CDCCell::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------

void J4CDCCell::InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot, 
                          const G4ThreeVector  &tlate) 
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object -----//
  
  G4double motherphi = ((G4Tubs *)GetMother()->GetLV()->GetSolid())->
  			GetDeltaPhiAngle();
  G4double step      = motherphi / GetNclones() ;

  SetPVReplica(kPhi, step);
  
}

//* Draw  --------------------------------------------------------
void J4CDCCell::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4CDCCell::Print() const
{
}
