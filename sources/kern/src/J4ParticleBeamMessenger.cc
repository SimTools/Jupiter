// $Id$
// GEANT4 tag $Name$
//

#include "J4ParticleBeamMessenger.hh"
#include "J4ParticleBeam.hh"
#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"
#include "G4Tokenizer.hh"

#include "g4std/iomanip"               

J4ParticleBeamMessenger::J4ParticleBeamMessenger(J4ParticleBeam * fPtclBeam)
  :fParticleBeam(fPtclBeam),fShootIon(false)
{
  fParticleTable = G4ParticleTable::GetParticleTable();

  fGunDirectory = new G4UIdirectory("/jupiter/beam/");
  fGunDirectory->SetGuidance("Particle Beam control commands.");

  fListCmd = new G4UIcmdWithoutParameter("/jupiter/beam/List",this);
  fListCmd->SetGuidance("List available particles.");
  fListCmd->SetGuidance(" Invoke G4ParticleTable.");

  fParticleCmd = new G4UIcmdWithAString("/jupiter/beam/particle",this);
  fParticleCmd->SetGuidance("Set particle to be generated.");
  fParticleCmd->SetGuidance(" (geantino is default)");
  fParticleCmd->SetGuidance(" (ion can be specified for shooting ions)");
  fParticleCmd->SetParameterName("particleName",true);
  fParticleCmd->SetDefaultValue("geantino");
  G4String candidateList; 
  G4int nPtcl = fParticleTable->entries();
  for(G4int i=0;i<nPtcl;i++)
  {
    candidateList += fParticleTable->GetParticleName(i);
    candidateList += " ";
  }
  candidateList += "ion ";
  fParticleCmd->SetCandidates(candidateList);

  fBeamtypeCmd  = new G4UIcmdWithAnInteger("/jupiter/beam/beamtype",this);
  fBeamtypeCmd->SetGuidance("Set beamtype. Type 0 or 1.");
  fBeamtypeCmd->SetGuidance("0 : isotropic, 1 : gaussian");
  fBeamtypeCmd->SetParameterName("BeamType",true,true);
  fBeamtypeCmd->SetRange("BeamType>=0");
  fBeamtypeCmd->SetDefaultValue(0);

  fConvergenceCmd  = new G4UIcmdWithABool("/jupiter/beam/convergence",this);
  fConvergenceCmd->SetGuidance("Set beam convergence mode. Type 0 or 1.");
  fConvergenceCmd->SetGuidance("0 : divergence beam");
  fConvergenceCmd->SetGuidance("1 : injected from surrounding sphare to beam position");
  fConvergenceCmd->SetParameterName("IsConvergenceMode",true); 
  fConvergenceCmd->SetDefaultValue(false);

  fFlatPosCmd  = new G4UIcmdWithABool("/jupiter/beam/flatpos",this);
  fFlatPosCmd->SetGuidance("Set beam profile type. 0 or 1.");
  fFlatPosCmd->SetGuidance("0 : Gaussian profile");
  fFlatPosCmd->SetGuidance("1 : Flat profile");
  fFlatPosCmd->SetParameterName("IsFlatProfile",true); 
  fFlatPosCmd->SetDefaultValue(false);

  fDirectionCmd = new G4UIcmdWith3Vector("/jupiter/beam/direction",this);
  fDirectionCmd->SetGuidance("Set momentum direction.");
  fDirectionCmd->SetGuidance("Direction needs not to be a unit vector.");
  fDirectionCmd->SetParameterName("Px","Py","Pz",true,true); 
  fDirectionCmd->SetRange("Px != 0 || Py != 0 || Pz != 0");
  
  fEnergyCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/energy",this);
  fEnergyCmd->SetGuidance("Set kinetic energy.");
  fEnergyCmd->SetParameterName("Energy",true,true);
  fEnergyCmd->SetDefaultUnit("GeV");
  //fEnergyCmd->SetUnitCategory("Energy");
  //fEnergyCmd->SetUnitCandidates("eV keV MeV GeV TeV");

  fMomentumMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/minmomentum",this);
  fMomentumMinCmd->SetGuidance("Set minimum mementum.");
  fMomentumMinCmd->SetParameterName("MomentumMin" ,true,true);
  fMomentumMinCmd->SetDefaultUnit("GeV");

  fMomentumMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/maxmomentum",this);
  fMomentumMaxCmd->SetGuidance("Set maximum mementum.");
  fMomentumMaxCmd->SetParameterName("MomentumMax" ,true,true);
  fMomentumMaxCmd->SetDefaultUnit("GeV");

  fCosThetaMinCmd = new G4UIcmdWithADouble("/jupiter/beam/mincostheta",this);
  fCosThetaMinCmd->SetGuidance("Set minimum costheta.");
  fCosThetaMinCmd->SetParameterName("CosThetaMin" ,true,true);

  fCosThetaMaxCmd = new G4UIcmdWithADouble("/jupiter/beam/maxcostheta",this);
  fCosThetaMaxCmd->SetGuidance("Set maximum costheta.");
  fCosThetaMaxCmd->SetParameterName("CosThetaMax" ,true,true);

  fXMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/minx",this);
  fXMinCmd->SetGuidance("Set minimum x-position.");
  fXMinCmd->SetParameterName("XMin" ,true,true);
  fXMinCmd->SetDefaultUnit("cm");

  fXMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/maxx",this);
  fXMaxCmd->SetGuidance("Set maximum x-position.");
  fXMaxCmd->SetParameterName("XMax" ,true,true);
  fXMaxCmd->SetDefaultUnit("cm");

  fYMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/miny",this);
  fYMinCmd->SetGuidance("Set minimum y-position.");
  fYMinCmd->SetParameterName("YMin" ,true,true);
  fYMinCmd->SetDefaultUnit("cm");

  fYMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/maxy",this);
  fYMaxCmd->SetGuidance("Set maximum y-position.");
  fYMaxCmd->SetParameterName("YMax" ,true,true);
  fYMaxCmd->SetDefaultUnit("cm");

  fZMinCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/minz",this);
  fZMinCmd->SetGuidance("Set minimum z-position.");
  fZMinCmd->SetParameterName("ZMin" ,true,true);
  fZMinCmd->SetDefaultUnit("cm");

  fZMaxCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/maxz",this);
  fZMaxCmd->SetGuidance("Set maximum z-position.");
  fZMaxCmd->SetParameterName("ZMax" ,true,true);
  fZMaxCmd->SetDefaultUnit("cm");

  fMomentumSigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/momentumsig",this);
  fMomentumSigmaCmd->SetGuidance("Set momentumsigma.");
  fMomentumSigmaCmd->SetParameterName("MomentumSigma" ,true,true);
  fMomentumSigmaCmd->SetDefaultUnit("GeV");

  fDirectionSigmaCmd = new G4UIcmdWithADouble("/jupiter/beam/directionsig",this);
  fDirectionSigmaCmd->SetGuidance("Set directionsigma.");
  fDirectionSigmaCmd->SetParameterName("DirectionSigma" ,true,true);

  fPositionCmd = new G4UIcmdWith3VectorAndUnit("/jupiter/beam/position",this);
  fPositionCmd->SetGuidance("Set starting position of the particle.");
  fPositionCmd->SetParameterName("X","Y","Z",true,true);
  fPositionCmd->SetDefaultUnit("cm");
  //fPositionCmd->SetUnitCategory("Length");
  //fPositionCmd->SetUnitCandidates("microm mm cm m km");

  fXPositionSigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/xpossig",this);
  fXPositionSigmaCmd->SetGuidance("Set x-positionsigma.");
  fXPositionSigmaCmd->SetParameterName("XPositionSigma" ,true,true);
  fXPositionSigmaCmd->SetDefaultUnit("cm");

  fYPositionSigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/ypossig",this);
  fYPositionSigmaCmd->SetGuidance("Set y-positionsigma.");
  fYPositionSigmaCmd->SetParameterName("YPositionSigma" ,true,true);
  fYPositionSigmaCmd->SetDefaultUnit("cm");

  fZPositionSigmaCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/zpossig",this);
  fZPositionSigmaCmd->SetGuidance("Set z-positionsigma.");
  fZPositionSigmaCmd->SetParameterName("ZPositionSigma" ,true,true);
  fZPositionSigmaCmd->SetDefaultUnit("cm");

  fTimeCmd = new G4UIcmdWithADoubleAndUnit("/jupiter/beam/time",this);
  fTimeCmd->SetGuidance("Set initial time of the particle.");
  fTimeCmd->SetParameterName("t0",true,true);
  fTimeCmd->SetDefaultUnit("ns");
  //fTimeCmd->SetUnitCategory("Time");
  //fTimeCmd->SetUnitCandidates("ns ms s");
  
  fPolCmd = new G4UIcmdWith3Vector("/jupiter/beam/polarization",this);
  fPolCmd->SetGuidance("Set polarization.");
  fPolCmd->SetParameterName("Px","Py","Pz",true,true); 
  fPolCmd->SetRange("Px>=-1.&&Px<=1.&&Py>=-1.&&Py<=1.&&Pz>=-1.&&Pz<=1.");

  fNumberCmd = new G4UIcmdWithAnInteger("/jupiter/beam/number",this);
  fNumberCmd->SetGuidance("Set number of particles to be generated.");
  fNumberCmd->SetParameterName("N",true,true);
  fNumberCmd->SetRange("N>0");

  fIonCmd = new G4UIcommand("/jupiter/beam/ion",this);
  fIonCmd->SetGuidance("Set properties of ion to be generated.");
  fIonCmd->SetGuidance("[usage] /jupiter/beam/ion Z A Q");
  fIonCmd->SetGuidance("        Z:(int) AtomicNumber");
  fIonCmd->SetGuidance("        A:(int) AtomicMass");
  fIonCmd->SetGuidance("        Q:(int) Charge of Ion (in unit of e)");
  fIonCmd->SetGuidance("        E:(double) Excitation energy (in keV)");
  
  G4UIparameter* param;
  param = new G4UIparameter("Z",'i',false);
  param->SetDefaultValue("1");
  fIonCmd->SetParameter(param);
  param = new G4UIparameter("A",'i',false);
  param->SetDefaultValue("1");
  fIonCmd->SetParameter(param);
  param = new G4UIparameter("Q",'i',true);
  param->SetDefaultValue("0");
  fIonCmd->SetParameter(param);
  param = new G4UIparameter("E",'d',true);
  param->SetDefaultValue("0.0");
  fIonCmd->SetParameter(param);
  
  // set initial value to J4ParticleBeam
  fParticleBeam->SetParticleDefinition( G4Geantino::Geantino() );
  fParticleBeam->SetParticleMomentumDirection( G4ThreeVector(1.0,0.0,0.0) );
  fParticleBeam->SetParticleEnergy( 1.0*GeV );
  fParticleBeam->SetParticlePosition(G4ThreeVector(0.0*cm, 0.0*cm, 0.0*cm));
  fParticleBeam->SetParticleTime( 0.0*ns );
}

J4ParticleBeamMessenger::~J4ParticleBeamMessenger()
{
  delete fListCmd;
  delete fParticleCmd;
  delete fDirectionCmd;
  delete fEnergyCmd;
  delete fPositionCmd;
  delete fTimeCmd;
  delete fPolCmd;
  delete fNumberCmd;
  delete fGunDirectory;
}

void J4ParticleBeamMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==fListCmd )
  { 
     fParticleTable->DumpTable();
  } else if( command==fParticleCmd ) {
    if (newValues =="ion") {
      fShootIon = true;
    } else {
      fShootIon = false;
      G4ParticleDefinition* pd = fParticleTable->FindParticle(newValues);
      if(pd != 0)
      { fParticleBeam->SetParticleDefinition( pd ); }
    }
  } else if( command==fBeamtypeCmd ) {
     fParticleBeam->SetBeamType((J4ParticleBeam::EBeamType)fBeamtypeCmd->GetNewIntValue(newValues)); 
  } else if( command==fConvergenceCmd ) {
     fParticleBeam->SetConvergenceMode(fConvergenceCmd->GetNewBoolValue(newValues)); 
  } else if( command==fDirectionCmd ) {
     fParticleBeam->SetParticleMomentumDirection(fDirectionCmd->GetNew3VectorValue(newValues)); 
  } else if( command==fEnergyCmd ) { 
     fParticleBeam->SetParticleEnergy(fEnergyCmd->GetNewDoubleValue(newValues)); 
  } else if( command==fMomentumMinCmd ) { 
     fParticleBeam->fMomentumRange[0] = fMomentumMinCmd->GetNewDoubleValue(newValues); 
  } else if( command==fMomentumMaxCmd ) { 
     fParticleBeam->fMomentumRange[1] = fMomentumMaxCmd->GetNewDoubleValue(newValues); 
  } else if( command==fCosThetaMinCmd ) { 
     fParticleBeam->fCosThetaRange[0] = fCosThetaMinCmd->GetNewDoubleValue(newValues); 
  } else if( command==fCosThetaMaxCmd ) { 
     fParticleBeam->fCosThetaRange[1] = fCosThetaMaxCmd->GetNewDoubleValue(newValues); 
  } else if( command==fXMinCmd ) { 
     fParticleBeam->fPositionRange[0][0] = fXMinCmd->GetNewDoubleValue(newValues); 
  } else if( command==fXMaxCmd ) { 
     fParticleBeam->fPositionRange[0][1] = fXMaxCmd->GetNewDoubleValue(newValues); 
  } else if( command==fYMinCmd ) { 
     fParticleBeam->fPositionRange[1][0] = fYMinCmd->GetNewDoubleValue(newValues); 
  } else if( command==fYMaxCmd ) { 
     fParticleBeam->fPositionRange[1][1] = fYMaxCmd->GetNewDoubleValue(newValues); 
  } else if( command==fZMinCmd ) { 
     fParticleBeam->fPositionRange[2][0] = fZMinCmd->GetNewDoubleValue(newValues); 
  } else if( command==fZMaxCmd ) { 
     fParticleBeam->fPositionRange[2][1] = fZMaxCmd->GetNewDoubleValue(newValues); 
  } else if( command==fMomentumSigmaCmd ) { 
     fParticleBeam->fMomentumSigma = fMomentumSigmaCmd->GetNewDoubleValue(newValues); 
  } else if( command==fDirectionSigmaCmd ) { 
     fParticleBeam->fDirectionSigma = fDirectionSigmaCmd->GetNewDoubleValue(newValues); 
  } else if( command==fPositionCmd ) { 
     fParticleBeam->SetParticlePosition(fPositionCmd->GetNew3VectorValue(newValues)); 
     fParticleBeam->fMeanPosition = fPositionCmd->GetNew3VectorValue(newValues);
  } else if( command==fXPositionSigmaCmd ) { 
     fParticleBeam->fPositionSigma[0] = fXPositionSigmaCmd->GetNewDoubleValue(newValues); 
  } else if( command==fYPositionSigmaCmd ) { 
     fParticleBeam->fPositionSigma[1] = fYPositionSigmaCmd->GetNewDoubleValue(newValues); 
  } else if( command==fZPositionSigmaCmd ) { 
     fParticleBeam->fPositionSigma[2] = fZPositionSigmaCmd->GetNewDoubleValue(newValues); 
  } else if( command==fTimeCmd ) { 
     fParticleBeam->SetParticleTime(fTimeCmd->GetNewDoubleValue(newValues)); 
  } else if( command==fPolCmd ) { 
     fParticleBeam->SetParticlePolarization(fPolCmd->GetNew3VectorValue(newValues)); 
  } else if( command==fNumberCmd ) { 
     fParticleBeam->SetNumberOfParticles(fNumberCmd->GetNewIntValue(newValues)); 
  } else if( command==fIonCmd ) { 
     IonCommand(newValues); 
  }
}

G4String J4ParticleBeamMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==fDirectionCmd )
  { cv = fDirectionCmd->ConvertToString(fParticleBeam->GetParticleMomentumDirection()); }
  else if( command==fParticleCmd )
  { cv = fParticleBeam->GetParticleDefinition()->GetParticleName(); }
  else if( command==fEnergyCmd )
  { cv = fEnergyCmd->ConvertToString(fParticleBeam->GetParticleEnergy(),"GeV"); }
  else if( command==fMomentumMinCmd )
  { cv = fMomentumMinCmd->ConvertToString(fParticleBeam->fMomentumRange[0],"GeV"); }
  else if( command==fMomentumMaxCmd )
  { cv = fMomentumMaxCmd->ConvertToString(fParticleBeam->fMomentumRange[1],"GeV"); }
  else if( command==fCosThetaMinCmd )
  { cv = fCosThetaMinCmd->ConvertToString(fParticleBeam->fCosThetaRange[0]); }
  else if( command==fCosThetaMaxCmd )
  { cv = fCosThetaMaxCmd->ConvertToString(fParticleBeam->fCosThetaRange[1]); }
  else if( command==fXMinCmd )
  { cv = fXMinCmd->ConvertToString(fParticleBeam->fPositionRange[0][0],"cm"); }
  else if( command==fXMaxCmd )
  { cv = fXMaxCmd->ConvertToString(fParticleBeam->fPositionRange[0][1],"cm"); }
  else if( command==fYMinCmd )
  { cv = fYMinCmd->ConvertToString(fParticleBeam->fPositionRange[1][0],"cm"); }
  else if( command==fYMaxCmd )
  { cv = fYMaxCmd->ConvertToString(fParticleBeam->fPositionRange[1][1],"cm"); }
  else if( command==fZMinCmd )
  { cv = fZMinCmd->ConvertToString(fParticleBeam->fPositionRange[2][0],"cm"); }
  else if( command==fZMaxCmd )
  { cv = fZMaxCmd->ConvertToString(fParticleBeam->fPositionRange[2][1],"cm"); }
  else if( command==fMomentumSigmaCmd )
  { cv = fMomentumSigmaCmd->ConvertToString(fParticleBeam->fMomentumSigma,"GeV"); }
  else if( command==fDirectionSigmaCmd )
  { cv = fDirectionSigmaCmd->ConvertToString(fParticleBeam->fDirectionSigma); }
  else if( command==fPositionCmd )
  { cv = fPositionCmd->ConvertToString(fParticleBeam->GetParticlePosition(),"cm"); }
  else if( command==fXPositionSigmaCmd )
  { cv = fXPositionSigmaCmd->ConvertToString(fParticleBeam->fPositionSigma[0],"cm"); }
  else if( command==fYPositionSigmaCmd )
  { cv = fYPositionSigmaCmd->ConvertToString(fParticleBeam->fPositionSigma[1],"cm"); }
  else if( command==fZPositionSigmaCmd )
  { cv = fZPositionSigmaCmd->ConvertToString(fParticleBeam->fPositionSigma[2],"cm"); }
  else if( command==fTimeCmd )
  { cv = fTimeCmd->ConvertToString(fParticleBeam->GetParticleTime(),"ns"); }
  else if( command==fPolCmd )
  { cv = fPolCmd->ConvertToString(fParticleBeam->GetParticlePolarization()); }
  else if( command==fNumberCmd )
  { cv = fNumberCmd->ConvertToString(fParticleBeam->GetNumberOfParticles()); }
  else if( command==fIonCmd )
  { 
    if (fShootIon) {
      cv = ItoS(fAtomicNumber) + " " + ItoS(fAtomicMass) + " ";
      cv += ItoS(fIonCharge);
    } else {
      cv = "";
    }  
  }    
  return cv;
}

void J4ParticleBeamMessenger::IonCommand(G4String newValues)
{
  if (fShootIon) {
    G4Tokenizer next( newValues );
    // check argument
    fAtomicNumber = StoI(next());
    fAtomicMass = StoI(next());
    G4String sQ = next();
    if (sQ.isNull()) {
      fIonCharge = fAtomicNumber;
    } else {
	fIonCharge = StoI(sQ);
      sQ = next();
      if (sQ.isNull()) {
        fIonExciteEnergy = 0.0;
      } else {
        fIonExciteEnergy = StoD(sQ) * keV;
      }
    }

    G4ParticleDefinition* ion;
    ion =  fParticleTable->GetIon( fAtomicNumber, fAtomicMass, fIonExciteEnergy);
    if (ion==0) {
    G4cout << "Ion with Z=" << fAtomicNumber;
    G4cout << " A=" << fAtomicMass << "is not be defined" << G4endl;    
    } else {
      fParticleBeam->SetParticleDefinition(ion);
      fParticleBeam->SetParticleCharge(fIonCharge*eplus);
    }
  } else {
    G4cout << "Set /jupiter/beam/particle to ion before using /jupiter/beam/ion command";
    G4cout << G4endl; 
  }
}

