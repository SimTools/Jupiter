// J4IRBPParameterList.hh
//
#ifndef __J4IRBPPARAMETERLIST__
#define __J4IRBPPARAMETERLIST__
//********************************************************************
//* ---------------------
//* J4IRBPParameterList.hh
//* ---------------------
//* (Description)
//*     Parameter class for IR.
//*     Define Geomtrical parameters for IR here.
//*
//* (Update Record)
//*     2002/11/19  T.Aso   Original version.
//********************************************************************

#include "G4Material.hh"
#include "G4Color.hh"
#include "G4ThreeVector.hh"
#include "J4VParameterList.hh"
#include "J4IRParameterList.hh"


// ====================================================================
// ----------------
// class definition
// ----------------

class J4IRBPParameterList : public J4VParameterList
{

public:
  J4IRBPParameterList(J4IRParameterList* irlist );
  virtual ~J4IRBPParameterList();
  virtual void PrintParameterList(){};

public:
  //*
  //* Set/GetFunctions
  //*
  // Materials
  inline void SetBPIPMaterial(G4String mat) {fBPIPMaterial=mat;}
  inline G4String GetBPIPMaterial() const { return fBPIPMaterial;}
  inline void SetBPSTDMaterial(G4String mat) {fBPSTDMaterial=mat;}
  inline G4String GetBPSTDMaterial() const { return fBPSTDMaterial;}
  // Color
  inline G4Color GetBPColor() const { return *fBPColor; }
  inline void SetBPColor(G4Color *c) { fBPColor =c; }
  // VisAtt  
  inline G4bool GetBPVisAtt() const { return fBPVisAtt; }
  inline void SetBPVisAtt(G4bool b) { fBPVisAtt=b; }

  //   Crossing Angle
  inline G4double GetCrossAngle() const { return fIRList->GetCrossAngle();} 
  //   L* position of QC1
  inline G4double GetLStar() const { return fIRList->GetLStar();} 

  inline G4double GetMargin() const { return fMargin; }
  inline void SetMargin(G4double m)  { fMargin = m; }

  //   Beam Pipe Radius
   // J4IRParameteList
  //inline void SetBPRadiusSmall(G4double r){ fBPRadiusSmall = r; }
  //inline G4double GetBPRadiusSmall(){ return fBPRadiusSmall; }
  inline G4double GetBPRadiusSmall(){ return fIRList->GetBeamPipeRadius(); }
  inline void SetBPRadiusLarge(G4double r){ fBPRadiusLarge = r; }
  inline G4double GetBPRadiusLarge(){ return fBPRadiusLarge; }
  //inline void SetBPBeThick(G4double th){ fBPBeThick = th; } 
  //inline G4double GetBPBeThick(){ return fBPBeThick; }  // J4IRParameteList
  inline G4double GetBPBeThick() { return fIRList->GetBeamPipeThick();}
  inline void SetBPAlThick(G4double th){ fBPAlThick = th; } 
  inline G4double GetBPAlThick(){ return fBPAlThick; } 

  // Structure 1 IP Pipe
  inline G4double GetBPIPRadius(){ return GetBPRadiusSmall(); }
  inline G4double GetBPIPThick(){ return GetBPBeThick(); }
  inline G4double GetBPIPZPosition(){ return fBPIPZPosition; }
  inline void SetBPIPZPosition(G4double zp){ fBPIPZPosition = zp; }
  inline G4double GetBPIPZLength(){ return fBPIPZLength; }
  inline void SetBPIPZLength(G4double zl){   fBPIPZLength = zl;  }

// Structure 2  Cone  (Be)
// Will be deribed to intermediate Structure1 and 2.

// Structure 3 small beam pipe at end. (Al)
  inline G4double GetBPENDRadius() { return fBPENDRadius; }
  inline void SetBPENDRadius(G4double r) { fBPENDRadius = r; }
  inline G4double GetBPENDThick() { return GetBPAlThick(); }
  inline G4double GetBPENDZLength() { return fBPENDZLength; }
  inline void  SetBPENDZLength(G4double zl) { fBPENDZLength = zl-GetMargin(); }
  inline G4double GetBPENDZPosition()
              { return fIRList->GetLStar()-GetBPENDZLength()-GetMargin();}

// Structure 4 DrumCap  (Al)
  inline G4double GetBPDrumcapRadius(){ return GetBPENDRadius(); }
  inline G4double GetBPDrumcapThick()
  { return GetBPRadiusLarge()+GetBPAlThick()-GetBPDrumcapRadius();}
  inline G4double GetBPDrumcapZLength(){ return fBPDrumcapZLength; }
  inline void SetBPDrumcapZLength(G4double zl){ fBPDrumcapZLength = zl; }
  inline G4double GetBPDrumcapZPosition()
  { return GetBPENDZPosition()-GetBPDrumcapZLength(); }

// Structure 5  Drum  (Al)
  inline G4double GetBPDrumRadius() { return GetBPRadiusLarge(); }
  inline G4double GetBPDrumThick() { return GetBPAlThick(); }
  inline G4double GetBPDrumZPosition() { return fBPDrumZPosition; }
  inline void SetBPDrumZPosition(G4double zp) { fBPDrumZPosition=zp; }
  inline G4double GetBPDrumZLength() 
  { return GetBPDrumcapZPosition() - GetBPDrumZPosition(); }

private:
  virtual void SetMaterials();
  virtual void SetVisAttributes();
  virtual void SetColors();
  virtual void SetParameters();
  virtual void SetDefaults();
  virtual void BuildParameters();

private:
  // IRParameterList
  J4IRParameterList* fIRList;

  // Materials
  G4String fBPIPMaterial;
  G4String fBPSTDMaterial;

  // Visual Attributes
  G4bool fBPVisAtt;

  // Visual Color
  G4Color* fBPColor;
  //
  // Geomrtries             (example)
  //      1) Size      --   fDxyz , fDr
  //      2) Position  --   fxyz  , fr
  // 
  G4double fBPRadiusLarge;
  //G4double fBPRadiusSmall;  //IRParameterList
  //G4double fBPBeThick;      //IRParameterList
  G4double fBPAlThick;
  G4double fBPIPZPosition;
  G4double fBPIPZLength;
  G4double fBPENDRadius;
  G4double fBPENDZLength;
  G4double fMargin;
  G4double fBPDrumcapZLength;
  G4double fBPDrumZPosition;
};

#endif

