// $Id$
//*************************************************************************
//* --------------------
//* J4IR
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4IR.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "J4UnionSolid.hh"
#include <math.h>

#include "J4IRQC1MField.hh"
#include "J4IRQC2MField.hh"
#include "J4IRSD0MField.hh"

#include "J4IRWMaskParameterList.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

G4String J4IR::fName("IR");

//=====================================================================
//---------------------
// Class Description
//---------------------

//=====================================================================
//* constructor -------------------------------------------------------

J4IR::J4IR(J4VAcceleratorComponent *parent,
                                          G4int  nclones,
                                          G4int  nbrothers, 
                                          G4int  me,
                                          G4int  copyno ) :
            J4VIRAcceleratorComponent( fName, parent, nclones,
                                    nbrothers, me, copyno  ) 
{   
}

//=====================================================================
//* destructor --------------------------------------------------------

J4IR::~J4IR()
{
  if(Deregister(fBeampipe)) delete fBeampipe;
  if(Deregister(fBeamConeR)) delete fBeamConeR;
  if(Deregister(fBeamConeL)) delete fBeamConeL;
  if(Deregister(fAlDrumR)) delete fAlDrumR;  
  if(Deregister(fAlDrumL)) delete fAlDrumL;  
  if(Deregister(fAlBeamPipeR)) delete fAlBeamPipeR;
  if(Deregister(fAlBeamPipeL)) delete fAlBeamPipeL;
  if(Deregister(fQC1R)) delete fQC1R;
  if(Deregister(fQC1L)) delete fQC1L;
  if(Deregister(fSD0R)) delete fSD0R;
  if(Deregister(fSD0L)) delete fSD0L;
  if(Deregister(fQC2R)) delete fQC2R;
  if(Deregister(fQC2L)) delete fQC2L;
  if(Deregister(fCH2MR)) delete fCH2MR;
  if(Deregister(fCH2ML)) delete fCH2ML;
  if(Deregister(fWM1R)) delete fWM1R;
  if(Deregister(fWM1L)) delete fWM1L;
  if(Deregister(fWM2R)) delete fWM2R;
  if(Deregister(fWM2L)) delete fWM2L;
  if(Deregister(fWSC1R)) delete fWSC1R;
  if(Deregister(fWSC1L)) delete fWSC1L;
  if(Deregister(fWSC2R)) delete fWSC2R;
  if(Deregister(fWSC2L)) delete fWSC2L;
  //if(Deregister(fPMNR)) delete fPMNR;
  //if(Deregister(fPMNL)) delete fPMNL;
}

//=====================================================================
//* Assemble   --------------------------------------------------------

void J4IR::Assemble() 
{   
  if(!GetLV()){

    J4IRParameterList* list = OpenParameterList();
    J4IRWMaskParameterList* wlist = new J4IRWMaskParameterList(list);

    // Calcurate parameters ----------
    G4double innersupporttubrad = list->GetIRSupportInnerRadius();
    G4double outerbeampiperad   = list->GetIRMinimumRadius();
    G4double beampipehalfzlen   = list->GetIRBeamPipeZLength()/2.;
    G4double conehalfz          = list->GetIRConeZLength()/2.;
    G4double cylinderhalfz      = list->GetIRDrumZLength()/2.;
    G4double boxhalfx           = list->GetDxyzIRBox().x();
    G4double boxhalfy           = list->GetDxyzIRBox().y();
    G4double boxhalfz           = list->GetDxyzIRBox().z();
    G4double coneglobalz        = list->GetIRConeZPosition();
    G4double cylinderglobalz    = list->GetIRDrumZPosition();
    G4double boxglobalz         = list->GetIRBoxZPosition();

    // MakeSolid ---------------
    
    G4String beampipename( GetName() );
    beampipename += ".Beampipe";
    G4VSolid *beampipe = new G4Tubs( beampipename, 0, outerbeampiperad,
                                     beampipehalfzlen, 0, 2*M_PI);  
    G4String irconerightname( GetName() );
    irconerightname += ".IRconeright";
    G4VSolid *irconeright = new G4Cons( irconerightname, 0, outerbeampiperad, 0,
                                        innersupporttubrad, conehalfz, 0, 2*M_PI); 
    G4String irconeleftname( GetName() );
    irconeleftname += ".IRconelert";
    G4VSolid *irconeleft = new G4Cons( irconeleftname, 0, innersupporttubrad, 0,
                                       outerbeampiperad, conehalfz, 0, 2*M_PI); 
    G4String ircylindername( GetName() );
    ircylindername += ".IRcylinder";
    G4VSolid *ircylinder = new G4Tubs( ircylindername, 0, innersupporttubrad,
                                       cylinderhalfz, 0, 2*M_PI);
    G4String irboxname( GetName() );
    irboxname += ".IRbox";
    G4VSolid *irbox = new G4Box( irboxname, boxhalfx, boxhalfy, boxhalfz);
    
    G4String tmpsolid1name( GetName() );
    tmpsolid1name += ".tmpsolid1";
    G4ThreeVector tmpsolid1tlate(0, 0, coneglobalz);
    G4VSolid *tmpsolid1 = new J4UnionSolid(tmpsolid1name, beampipe, irconeright,
                                       0, tmpsolid1tlate );
    G4String tmpsolid2name( GetName() );
    tmpsolid2name += ".tmpsolid2";
    G4ThreeVector tmpsolid2tlate(0, 0, -coneglobalz);
    G4VSolid *tmpsolid2 = new J4UnionSolid(tmpsolid2name, tmpsolid1, irconeleft,
                                       0, tmpsolid2tlate );
    G4String tmpsolid3name( GetName() );
    tmpsolid3name += ".tmpsolid3";
    G4ThreeVector tmpsolid3tlate(0, 0, cylinderglobalz);
    G4VSolid *tmpsolid3 = new J4UnionSolid(tmpsolid3name, tmpsolid2, ircylinder,
                                       0, tmpsolid3tlate );
    G4String tmpsolid4name( GetName() );
    tmpsolid4name += ".tmpsolid4";
    G4ThreeVector tmpsolid4tlate(0, 0, -cylinderglobalz);
    G4VSolid *tmpsolid4 = new J4UnionSolid(tmpsolid4name, tmpsolid3, ircylinder,
                                       0, tmpsolid4tlate );
    G4String tmpsolid5name( GetName() );
    tmpsolid5name += ".tmpsolid5";
    G4ThreeVector tmpsolid5tlate(0, 0, boxglobalz);
    G4VSolid *tmpsolid5 = new J4UnionSolid(tmpsolid5name, tmpsolid4, irbox,
                                       0, tmpsolid5tlate );

    G4ThreeVector lastsolidtlate(0, 0, -boxglobalz);
    G4VSolid *lastsolid = new J4UnionSolid(GetName(), tmpsolid5, irbox,
                                       0, lastsolidtlate );

    Register(lastsolid);
    SetSolid(lastsolid);	// Don't forgat call it!


    // MakeLogicalVolume -------------
    MakeLVWith(OpenMaterialStore()->Order(list->GetIRMaterial()));
    
    // SetVisAttribute ---------------
    PaintLV(list->GetIRVisAtt(),list->GetIRColor());
  	
    // Install daughter PV -----------
#if 1
    fBeampipe = new J4IRBPPipe(this,1,1,0,-1);
    Register(fBeampipe);
    fBeampipe->InstallIn(this);
    SetDaughter(fBeampipe);

    fBeamConeR = new J4IRBPCone(this,1,2,0,-1,FALSE);
    fBeamConeL = new J4IRBPCone(this,1,2,1,-1,TRUE);
    Register(fBeamConeR);
    Register(fBeamConeL);
    fBeamConeR->InstallIn(this);
    fBeamConeL->InstallIn(this);
    SetDaughter(fBeamConeR);
    SetDaughter(fBeamConeL);

    fAlDrumR =  new J4IRBPAlDrum(this,1,2,0,-1,FALSE);
    fAlDrumL =  new J4IRBPAlDrum(this,1,2,1,-1,TRUE);
    Register(fAlDrumR);
    Register(fAlDrumL);
    fAlDrumR->InstallIn(this);
    fAlDrumL->InstallIn(this);
    SetDaughter(fAlDrumR);
    SetDaughter(fAlDrumL);

    fAlBeamPipeR = new J4IRBPAlTube(this,1,2,0,-1,FALSE);
    fAlBeamPipeL = new J4IRBPAlTube(this,1,2,1,-1,TRUE);
    Register(fAlBeamPipeR);
    Register(fAlBeamPipeL);
    fAlBeamPipeR->InstallIn(this);
    fAlBeamPipeL->InstallIn(this);
    SetDaughter(fAlBeamPipeR);
    SetDaughter(fAlBeamPipeL);
#endif

#if 1
    J4IRQC1MField* qc1fielde = new J4IRQC1MField(250.*GeV,-0.1295329270206);
    J4IRQC1MField* qc1fieldp = new J4IRQC1MField(250.*GeV,+0.1295329270206);

    fQC1R = new J4IRQC1(this,1,2,0,-1);
    fQC1R->SetMField(qc1fielde);
    Register(fQC1R);
    fQC1R->InstallIn(this);
    SetDaughter(fQC1R);

    fQC1L = new J4IRQC1(this,1,2,1,-1,true);
    fQC1L->SetMField(qc1fieldp);
    Register(fQC1L);
    fQC1L->InstallIn(this);
    SetDaughter(fQC1L);
#endif

#if 0

    J4IRSD0MField* sd0fielde = new J4IRSD0MField(250.*GeV,-2.249174);
    J4IRSD0MField* sd0fieldp = new J4IRSD0MField(250.*GeV,+2.249174);

    fSD0R = new J4IRSD0(this,1,2,0,-1);
    fSD0R->SetMField(sd0fielde);
    fSD0L = new J4IRSD0(this,1,2,1,-1,true);
    fSD0L->SetMField(sd0fieldp);
    Register(fSD0R);
    Register(fSD0L);
    fSD0R->InstallIn(this);
    fSD0L->InstallIn(this);
    SetDaughter(fSD0R);
    SetDaughter(fSD0L);

    J4IRQC2MField* qc2fielde = new J4IRQC2MField(250.*GeV,+0.0537249);
    J4IRQC2MField* qc2fieldp = new J4IRQC2MField(250.*GeV,-0.0537249);

    fQC2R = new J4IRQC2(this,1,2,0,-1);
    fQC2R->SetMField(qc2fielde);
    fQC2L = new J4IRQC2(this,1,2,1,-1,true);
    fQC2L->SetMField(qc2fieldp);
    Register(fQC2R);
    Register(fQC2L);
    fQC2R->InstallIn(this);
    fQC2L->InstallIn(this);
    SetDaughter(fQC2R);
    SetDaughter(fQC2L);
#endif

#if 1
    fCH2MR = new J4IRCH2Mask(this,1,2,0,-1);
    fCH2ML = new J4IRCH2Mask(this,1,2,1,-1,true);
    Register(fCH2MR);
    Register(fCH2ML);
    fCH2MR->InstallIn(this);
    fCH2ML->InstallIn(this);
    SetDaughter(fCH2MR);
    SetDaughter(fCH2ML);
#endif


#if 1
    if( wlist->IsWMask1Valid() ){
      fWM1R = new J4IRWMask1(this,1,2,0,-1);
      fWM1L = new J4IRWMask1(this,1,2,1,-1,true);
      Register(fWM1R);
      Register(fWM1L);
      fWM1R->InstallIn(this);
      fWM1L->InstallIn(this);
      SetDaughter(fWM1R);
      SetDaughter(fWM1L);
    }

    fWM2R = new J4IRWMask2(this,1,2,0,-1);
    fWM2L = new J4IRWMask2(this,1,2,1,-1,true);
    Register(fWM2R);
    Register(fWM2L);
    fWM2R->InstallIn(this);
    fWM2L->InstallIn(this);
    SetDaughter(fWM2R);
    SetDaughter(fWM2L);
#endif

#if 0
    fPMNR = new J4IRPairMonitor(this,1,2,0,-1);
    fPMNL = new J4IRPairMonitor(this,1,2,1,-1,true);
    Register(fPMNR);
    Register(fPMNL);
    fPMNR->InstallIn(this);
    fPMNL->InstallIn(this);
    SetDaughter(fPMNR);
    SetDaughter(fPMNL);
#endif

#if 1
    fWSC1R = new J4IRWSiCAL1(this,1,2,0,-1);
    fWSC1L = new J4IRWSiCAL1(this,1,2,1,-1,true);
    Register(fWSC1R);
    Register(fWSC1L);
    fWSC1R->InstallIn(this);
    fWSC1L->InstallIn(this);
    SetDaughter(fWSC1R);
    SetDaughter(fWSC1L);

    if (wlist->IsWSiCAL2Valid()){
      fWSC2R = new J4IRWSiCAL2(this,1,2,0,-1);
      fWSC2L = new J4IRWSiCAL2(this,1,2,1,-1,true);
      Register(fWSC2R);
      Register(fWSC2L);
      fWSC2R->InstallIn(this);
      fWSC2L->InstallIn(this);
      SetDaughter(fWSC2R);
      SetDaughter(fWSC2L);
    }
#endif
  }     
}


//=====================================================================
//* Cabling  ----------------------------------------------------------

void J4IR::Cabling()
{
}

//=====================================================================
//* InstallIn  --------------------------------------------------------
/*
void J4IR::InstallIn(J4VComponent *mother,
                             G4RotationMatrix     *prot, 
                             const G4ThreeVector  &tlate )
{ 
  Assemble();			// You MUST call Assemble(); at first.
  				// 
  
  // Placement function into mother object...
  
  SetPVPlacement();
  
}
*/
//* Draw  --------------------------------------------------------
void J4IR::Draw()
{
  // set visualization attributes
  
}
	
//* Print  --------------------------------------------------------
void J4IR::Print() const
{
}

	
	

