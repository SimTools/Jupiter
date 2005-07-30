// $Id$
//*************************************************************************
//* --------------------
//* J4ParameterList
//* --------------------
//* (Description)
//*
//* (Update Record)
//*	2002/12/20  K.Hoshina	Original version.
//*************************************************************************

#include "J4ParameterList.hh"
#include "J4ParameterTable.hh"
#include <vector>
 
J4ParameterList* J4ParameterList::fgInstance = 0;

//=====================================================================
//* public get function -----------------------------------------------
J4ParameterList* J4ParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4ParameterList("kern");
   } 
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4ParameterList::J4ParameterList(const G4String &name)
                :J4VParameterList(name)
{
   SetParameters();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4ParameterList::~J4ParameterList()
{
   fgInstance = 0;
}

//=====================================================================
//* SetParameters -----------------------------------------------------

void J4ParameterList::SetParameters()
{
   fEXPHallMaterial = J4ParameterTable::GetValue("J4.EXPHall.Material","Air");
   fEXPHallVisAtt   = J4ParameterTable::GetValue("J4.EXPHall.VisAtt",false);
   std::vector<double> col = J4ParameterTable::GetDValue("J4.EXPHall.Color","1.0 0.0 1.0 1.0", 4);
   SetEXPHallColor(G4Color(col[0], col[1], col[2], col[3]));

// GLD V1 
//   fBPOuterR = J4ParameterTable::GetValue("J4.BeamPipe.OuterRadius",1.8)*cm ; // OuterR of BeamPipe
//   fBPMargin = J4ParameterTable::GetValue("J4.BeamPipe.Margin",0.05)*cm ;     // Margin between beampipe and IR
//   fIRThetaMax  = J4ParameterTable::GetValue("J4.IR.ThetaMax",0.150)*radian ; // Theta Max of IR region
//   fIRBoxFrontZ = J4ParameterTable::GetValue("J4.IR.BoxFrontZ",500.0)*cm ;    // Front-z of IR box

//   fIRBoxEndZ =  J4ParameterTable::GetValue("J4.IR.BoxEndZ",850.0)*cm ; // End-z of IR box

   fSupportTubInnerR = J4ParameterTable::GetValue("J4.SupportTube.InnerRadius",38.0)*cm; // InnerR of Support Tub
   fSupportTubOuterR = J4ParameterTable::GetValue("J4.SupportTube.OuterRadius",39.5)*cm; // OuterR of Support Tub

    fIRNSolids  = J4ParameterTable::GetValue("J4.IR.NumSolides", 4);
    fIRREdges   = new G4double[fIRNSolids];
    std::vector<double> rmins;
    rmins = J4ParameterTable::GetDValue("J4.IR.REdges","1.525 8.1 38.0 38.0", fIRNSolids);
    for(int i=0;i<fIRNSolids;i++) { fIRREdges[i] = rmins[i]*cm; }

    fIRZEdges   = new G4double[fIRNSolids];
    std::vector<double> zposs;
    zposs = J4ParameterTable::GetDValue("J4.IR.ZEdges","7.0 80.0 220.0 850.0", fIRNSolids);
    for(int i=0;i<fIRNSolids;i++) { fIRZEdges[i] = zposs[i]*cm; }
    
    fIRBoxEndZ=fIRZEdges[fIRNSolids-1];

    fIRShapes   = new G4int[fIRNSolids];
    std::vector<int> ishape;
    ishape = J4ParameterTable::GetIValue("J4.IR.Shapes","0 1 0 0", fIRNSolids);  
//  0 for Tubs, 1 for Cons;
//  First value for Shapes is not valid ( allways assume Tubs )
    for(int i=0;i<fIRNSolids;i++) { fIRShapes[i] = ishape[i]; }

    fITZMax          = J4ParameterTable::GetValue("J4.IT.ZMax",200.0)*cm;

    
   fVTXOuterR        = J4ParameterTable::GetValue("J4.VTX.OuterRadius",8.0)*cm;       // OuterR of VTX
   fVTXZcoverage     = J4ParameterTable::GetValue("J4.VTX.ZCoverage",0.9015);       // z-coverage in cos_theta of VTX

   fITZcoverage     = J4ParameterTable::GetValue("J4.IT.ZCoverage",0.9000);       // z-coverage in cos_theta of IT

   fCDCOuterR   = J4ParameterTable::GetValue("J4.TPC.OuterRadius",206.0)*cm ; // OuterR of CDC
   fCDCHalfZ    = J4ParameterTable::GetValue("J4.TPC.HalfZ",260.0)*cm ;       // half z length of CDC 
 
   fTPCOuterR   = J4ParameterTable::GetValue("J4.TPC.OuterRadius",206.0)*cm ; // OuterR of TPC
   fTPCHalfZ    = J4ParameterTable::GetValue("J4.TPC.HalfZ",260.0)*cm ;       // half z length of TPC 
 
   fCALInnerR        = J4ParameterTable::GetValue("J4.CAL.InnderRadius",206.0)*cm; // InnerR of CAL
   fCALOuterR        = J4ParameterTable::GetValue("J4.CAL.OuterRadius",370.0)*cm;  // OuterR of CAL
   fCALInnerHalfZ    = J4ParameterTable::GetValue("J4.CAL.InnderHalfZ",265.0)*cm;  // half z length of innerface of CAL 
   fCALOuterHalfZ    = J4ParameterTable::GetValue("J4.CAL.OuterHalfZ",425.0)*cm;   // half z length of outersurface of CAL

   fSOLInnerR        = J4ParameterTable::GetValue("J4.SOL.InnerRadius",375.0)*cm;   // InnerR of Solenoid
   fSOLOuterR        = J4ParameterTable::GetValue("J4.SOL.OuterRadius",450.0)*cm;   // OuterR of Solenoid
   fSOLHalfZ         = J4ParameterTable::GetValue("J4.SOL.HalfZ",530.0)*cm;         // half z length of Solenoid

   fEXPHallHalfX    = J4ParameterTable::GetValue("J4.EXPHall.HalfX",1000.0)*cm;
   fEXPHallHalfY    = J4ParameterTable::GetValue("J4.EXPHall.HalfY",1000.0)*cm;
   fEXPHallHalfZ    = J4ParameterTable::GetValue("J4.EXPHall.HalfZ",1000.0)*cm;


}


