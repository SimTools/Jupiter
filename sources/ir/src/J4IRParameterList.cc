// J4IRParameterList.cc
//*************************************************************************
//* --------------------
//* J4IRParameterList
//* --------------------
//* (Description)
//*     Class for describing his/her detector compornents.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//*************************************************************************
#define __VTXACFAREPCONF__  0
#define __VTXSTDCONF__      1
#define __VTX5LYRCONF__     0

#define __A0MRAD__ 0
#define __A7MRAD__ 1
#define __A20MRAD__ 0

#include "J4IRParameterList.hh"

J4IRParameterList* J4IRParameterList::fgInstance = 0;

//=====================================================================
//* public getter -----------------------------------------------------

J4IRParameterList* J4IRParameterList::GetInstance()
{
   if (!fgInstance) {
      fgInstance = new J4IRParameterList("IR");
   }
   return fgInstance;
}

//=====================================================================
//* protected constructor ---------------------------------------------

J4IRParameterList::J4IRParameterList(const G4String& name)
                  :J4VParameterList(name)
{
  fgInstance = this;

  SetSensitiveDetector();
  SetParameters();
  SetMaterials();
  SetVisAttributes();
  SetColors();
}

//=====================================================================
//* destructor -------------------------------------------------------

J4IRParameterList::~J4IRParameterList()
{

  delete  fIRColor;
  fgInstance = 0;

}

//=====================================================================
//* SetSensitiveDetector-----------------------------------------------
void J4IRParameterList::SetSensitiveDetector()
{
  SetPairMonitorSD(FALSE);
}
//=====================================================================
//* SetMaterials ------------------------------------------------------
void J4IRParameterList::SetMaterials()
{
  SetIRMaterial("Air");
}

//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRParameterList::SetParameters()
{
  SetDefaults();
  BuildParameters();
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRParameterList::SetDefaults()
{
  // Margin for avoiding volume intersection.
  SetDxyzMarginSize(G4ThreeVector(0.1*mm,0.1*mm,0.1*mm));
  SetDrMarginSize(0.5*mm);

  // Crossing Angle
#if __A0MRAD__
  SetCrossAngle(0.*milliradian);
#endif
#if __A7MRAD__ 
  SetCrossAngle(3.5*milliradian);
#endif
#if __A20MRAD__
  SetCrossAngle(10.*milliradian);
#endif
  //SetCrossAngle(0.*milliradian);
  //SetCrossAngle(-3.*milliradian);
  //SetCrossAngle(-3.5*milliradian);
  //SetCrossAngle(-4.*milliradian);
  //SetCrossAngle(-5.*milliradian);
  //SetCrossAngle(-10.*milliradian);

  // L*
#ifdef __GLD_V1__
  SetLStar(4300*mm);
#else
  SetLStar(3500*mm);
#endif
  // Z Maximum length
  SetIRZMax(800*cm); // Near end of QC1
  // Z Mid length
  SetIRZMid(500*cm);
  // Support Tube
#ifdef __GLD_V1__
  SetIRSupportInnerRadius(38*cm);
#else
  SetIRSupportInnerRadius(40*cm);
#endif
  // Be BeamPipe
#if __VTXACFAREPCONF__ 
  SetBeamPipeRadius(1.8*cm);
#endif
#if __VTXSTDCONF__  
  SetBeamPipeRadius(1.8*cm);
#endif
#if __VTX5LYRCONF__
  SetBeamPipeRadius(1.1*cm);
#endif
  SetBeamPipeThick(0.05*cm);
  // Minimum radius of IR = Outer of beam-pipe at IR
  SetIRMinimumRadius(GetBeamPipeRadius()+GetBeamPipeThick()+0.1*cm);
  // IR Theta max
#ifdef __GLD_V1__
  SetIRThetaMax(150*mrad);
#else
  SetIRThetaMax(200*mrad);
#endif
  // Acc tunnel box (half)
  SetDxyzIRBox(G4ThreeVector(3.99*m,3.99*m,(GetIRZMax()-GetIRZMid())/2.));
}
//=====================================================================
//* SetParameters ------------------------------------------------------
void J4IRParameterList::BuildParameters()
{
}
//=====================================================================
//* SetVtsAttributes ------------------------------------------------------
void J4IRParameterList::SetVisAttributes()
{
  fIRVisAtt       = TRUE;
}
//=====================================================================
//* SetColors ---------------------------------------------------------
void J4IRParameterList::SetColors()
{
  fIRColor       = new G4Color(0.5,0.5,0.5);  // gray
  //fIRColor       = new G4Color(1,0.,0.);  // red
}


