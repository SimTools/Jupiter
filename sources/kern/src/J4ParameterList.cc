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
 
J4ParameterList* J4ParameterList::fgParameterList = 0;

//=====================================================================
//* constructor -------------------------------------------------------

J4ParameterList::J4ParameterList()
                :J4VParameterList("kern")
{
   if (fgParameterList) { 
      G4Exception("J4ParameterList constructed twice."); 
   }

   SetParameters();
   fgParameterList = this;
}

//=====================================================================
//* destructor -------------------------------------------------------

J4ParameterList::~J4ParameterList()
{
   delete  fEXPHallColor;
}

//=====================================================================
//* SetParameters -----------------------------------------------------

void J4ParameterList::SetParameters()
{

   fEXPHallMaterial = "Air";
   fEXPHallVisAtt   = FALSE;
   fEXPHallColor    = new G4Color(1, 0, 1);


   fBPOuterRadius   = 1.8*cm;                  // OuterRadius of BeamPipe
   fBPMargin        = 0.05*cm;                 // Margin between beampipe and IR
   fIRThetaMax      = 200*mrad;                // Theta Max of IR region
   fIRBoxFrontZ     = 500*cm;                  // Front-z of IR box
   fIRBoxEndZ       = 700*cm;                  // End-z of IR box
   fIRBoxHalfX      = fEXPHallHalfX - 1.0*cm;  // half x-width of IR box
   fIRBoxHalfY      = fEXPHallHalfY - 1.0*cm;  // half y-width of IR box

   fSupportTubInnerRadius = 40*cm;             // InnerRadius of Support Tub
   fSupportTubOuterRadius = 44*cm;             // OuterRadius of Support Tub

   fVTXOuterRadius  = 8.0*cm;                  // OuterRadius of VTX
   fVTXAngle        = 10;                      // half z length of VTX

   fCDCOuterRadius  = 156*cm;                  // OuterRadius of CDC
   fCDCHalfZ        = 156*cm;                  // half z length of CDC

   fCALInnerRadius  = 160*cm;                  // InnerRadius of CAL
   fCALOuterRadius  = 290*cm;                  // OuterRadius of CAL
   fCALHalfZ        = 320*cm;                  // half z length of CAL

   fSOLInnerRadius  = 375*cm;                  // InnerRadius of Solenoid
   fSOLOuterRadius  = 450*cm;                  // OuterRadius of Solenoid
   fSOLHalfZ        = 340*cm;                  // half z length of Solenoid

#if 0
   fEXPHallHalfX    = 40*m;
   fEXPHallHalfY    = 40*m;
   fEXPHallHalfZ    = 4000*m;
#else
   fEXPHallHalfX    = 5*m;
   fEXPHallHalfY    = 5*m;
   fEXPHallHalfZ    = 5*m;
#endif


}


