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

   fEXPHallMaterial = "Air";
   fEXPHallVisAtt   = FALSE;
   SetEXPHallColor(G4Color(1, 0, 1));

#if defined(__GLD_V1__) 
// GLD V1 

   fBPOuterR         = 1.8*cm;                 // OuterR of BeamPipe
   fBPMargin         = 0.05*cm;                // Margin between beampipe and IR
   fIRThetaMax       = 150*mrad;               // Theta Max of IR region
   fIRBoxFrontZ      = 500*cm;                 // Front-z of IR box
   fIRBoxEndZ        = 700*cm;                 // End-z of IR box

   fSupportTubInnerR = 38.0*cm;                  // InnerR of Support Tub
   fSupportTubOuterR = 39.5*cm;                  // OuterR of Support Tub

   fVTXOuterR        = 8.0*cm;                 // OuterR of VTX
   fVTXZcoverage     = 0.9015;                 // z-coverage in cos_theta of VTX

   fITZcoverage      = 0.90;                   // z-coverage in cos_theta of IT 

   fCDCOuterR        = 206*cm;                 // OuterR of CDC
   fCDCHalfZ         = 260*cm;                 // half z length of CDC

   fTPCOuterR        = 206*cm;                 // OuterR of TPC
   fTPCHalfZ         = 260*cm;                 // half z length of TPC

   fCALInnerR        = 206*cm;                 // InnerR of CAL
   fCALOuterR        = 370*cm;                 // OuterR of CAL
   fCALInnerHalfZ    = 265*cm;                 // half z length of innerface of CAL 
   fCALOuterHalfZ    = 425*cm;                 // half z length of outersurface of CAL

   fSOLInnerR        = 375*cm;                 // InnerR of Solenoid
   fSOLOuterR        = 450*cm;                 // OuterR of Solenoid
   fSOLHalfZ         = 425*cm;                 // half z length of Solenoid

   fEXPHallHalfX    = 10*m;
   fEXPHallHalfY    = 10*m;
   fEXPHallHalfZ    = 40*m;

#else
// GLC 3T version
   fBPOuterR         = 1.8*cm;                 // OuterR of BeamPipe
   fBPMargin         = 0.05*cm;                // Margin between beampipe and IR
   fIRThetaMax       = 200*mrad;               // Theta Max of IR region
   fIRBoxFrontZ      = 500*cm;                 // Front-z of IR box
   fIRBoxEndZ        = 700*cm;                 // End-z of IR box

   fSupportTubInnerR = 40*cm;                  // InnerR of Support Tub
   fSupportTubOuterR = 44*cm;                  // OuterR of Support Tub

   fVTXOuterR        = 8.0*cm;                 // OuterR of VTX
   fVTXZcoverage     = 0.9015;                 // z-coverage in cos_theta of VTX

   fITZcoverage      = 0.90;                   // z-coverage in cos_theta of IT 

   fCDCOuterR        = 157*cm;                 // OuterR of CDC
   fCDCHalfZ         = 160*cm;                 // half z length of CDC

   fTPCOuterR        = 157*cm;                 // OuterR of TPC
   fTPCHalfZ         = 160*cm;                 // half z length of TPC

   fCALInnerR        = 157*cm;                 // InnerR of CAL
   fCALOuterR        = 370*cm;                 // OuterR of CAL
   fCALInnerHalfZ    = 185*cm;                 // half z length of innerface of CAL 
   fCALOuterHalfZ    = 400*cm;                 // half z length of outersurface of CAL

   fSOLInnerR        = 375*cm;                 // InnerR of Solenoid
   fSOLOuterR        = 450*cm;                 // OuterR of Solenoid
   fSOLHalfZ         = 430*cm;                 // half z length of Solenoid

#if 0
   fEXPHallHalfX    = 40*m;
   fEXPHallHalfY    = 40*m;
   fEXPHallHalfZ    = 4000*m;
#else
   fEXPHallHalfX    = 10*m;
   fEXPHallHalfY    = 10*m;
   fEXPHallHalfZ    = 40*m;
#endif



#endif

}


