// $Id$
// GEANT4 tag $Name$
//

// J4ParticleBeam
#include "J4ParticleBeam.hh"
#include "G4PrimaryParticle.hh"
#include "J4ParticleBeamMessenger.hh"
#include "G4Event.hh"
#include "G4ios.hh"
#include "Randomize.hh" 
#include "J4Parameter.hh" 

//#define _BEAMCONVERGENCEEXTENT_   _EXPHALLHALFX_ - 1.1*cm  
//#define _BEAMCONVERGENCEEXTENT_   5.0*cm
#define _BEAMCONVERGENCEEXTENT_   1.2*m

J4ParticleBeam::J4ParticleBeam()
               :fBeamType(kEIsotropic), 
	        fIsConvergenceMode(FALSE), fIsFlatProfile(FALSE), 
		fMeanMomentum(10.*GeV),   fMomentumSigma(0.1*GeV), 
		fDirectionSigma(0.01),    fMeanPosition(0.,0.,0.)
{
   fMomentumRange[0] = 0.1*GeV;
   fMomentumRange[1] = 100.*GeV;
   fCosThetaRange[0] = -1.;
   fCosThetaRange[1] = +1.;

   for (G4int i=0; i<3; i++) {
      for (G4int j=0; j<2; j++) fPositionRange[i][j] = 0.;
      fPositionSigma[i] = 1.*mm;
   }

   fMessenger = new J4ParticleBeamMessenger(this);
}

J4ParticleBeam::J4ParticleBeam(G4int numberoparticles)
               :G4ParticleGun(numberoparticles), 
                fBeamType(kEIsotropic), 
	        fIsConvergenceMode(FALSE), fIsFlatProfile(FALSE), 
		fMeanMomentum(10.*GeV),   fMomentumSigma(0.1*GeV), 
		fDirectionSigma(0.01),    fMeanPosition(0.,0.,0.)
{
   fMomentumRange[0] = 0.1*GeV;
   fMomentumRange[1] = 100.*GeV;
   fCosThetaRange[0] = -1.;
   fCosThetaRange[1] = +1.;

   for (G4int i=0; i<3; i++) {
      for (G4int j=0; j<2; j++) fPositionRange[i][j] = 0.;
      fPositionSigma[i] = 1.*mm;
   }

   fMessenger = new J4ParticleBeamMessenger(this);
}

J4ParticleBeam::J4ParticleBeam(G4ParticleDefinition * particleDe,
                               G4int numberoparticles)
               :G4ParticleGun(particleDe, numberoparticles), 
                fBeamType(kEIsotropic), 
	        fIsConvergenceMode(FALSE), fIsFlatProfile(FALSE), 
		fMeanMomentum(10.*GeV),   fMomentumSigma(0.1*GeV), 
		fDirectionSigma(0.01),    fMeanPosition(0.,0.,0.)
{
   fMomentumRange[0] = 0.1*GeV;
   fMomentumRange[1] = 100.*GeV;
   fCosThetaRange[0] = -1.;
   fCosThetaRange[1] = +1.;

   for (G4int i=0; i<3; i++) {
      for (G4int j=0; j<2; j++) fPositionRange[i][j] = 0.;
      fPositionSigma[i] = 1.*mm;
   }

   fMessenger = new J4ParticleBeamMessenger(this);
}

J4ParticleBeam::~J4ParticleBeam()
{
  delete fMessenger;
}

void J4ParticleBeam::SetParticleMomentum(G4ParticleMomentum aMomentum)
{
  if (particle_definition==0)
  {
    G4cout <<"Particle Deinition not deined yet for J4ParticleBeam"<< G4endl;
    G4cout <<"Zero Mass is assumed"<<G4endl;
    particle_momentum_direction =  aMomentum.unit();
    particle_energy = aMomentum.mag();
  } 
  else 
  {
    G4double mass =  particle_definition->GetPDGMass();
    G4double p = aMomentum.mag();
    particle_momentum_direction =  aMomentum.unit();
    if ((particle_energy>0.0)&&(abs(particle_energy+mass-sqrt(p*p+mass*mass))>keV))
    {
      G4cout << "J4ParticleBeam::" << particle_definition->GetParticleName() << G4endl;
      G4cout << "  KineticEnergy and Momentum could be inconsistent" << G4endl;
      G4cout << " (Momentum:" << p/GeV << " GeV/c";
      G4cout << "  Mass:" << mass/GeV << " GeV/c/c)" << G4endl;
      G4cout << "  KineticEnergy is overwritten!! ";
      G4cout << particle_energy/GeV << "->";
      G4cout << (sqrt(p*p+mass*mass)-mass)/GeV << "GeV" << G4endl;
    }
    particle_energy = sqrt(p*p+mass*mass)-mass;
  }
}

void J4ParticleBeam::GeneratePrimaryVertex(G4Event* evt)
{
   if (particle_definition == 0) return;

   // ---------------------------
   //  start loop over particles
   // ---------------------------
   for ( G4int i=0; i<NumberOfParticlesToBeGenerated; i++ )
   {
      // create a new vertex
      G4PrimaryVertex* vertex = 
         new G4PrimaryVertex(particle_position,particle_time);

      // create new primaries and set them to the vertex
      G4double mass   = particle_definition->GetPDGMass();
      G4double energy = particle_energy + mass;
      G4double pmom   = sqrt((energy - mass)*(energy + mass));
      fMeanMomentum = pmom;

      G4double mvx, mvy, mvz;
  
      // ------------------------------
      //  switch on beam type
      // ------------------------------
      switch (fBeamType) {
         case kEIsotropic: {
	    G4cerr << "--------ParticleBeam:: Isotropic beamtype-------" << G4endl;
            G4double phi      = RandFlat::shoot(0.,2*M_PI);
            G4double costheta = RandFlat::shoot(fCosThetaRange[0],
                                                fCosThetaRange[1]);
            // G4double costheta = cos((2 * G4UniformRand() -1.) * M_PI);
   
            G4cerr << "J4ParticleBeam::GeneratePrimaries: phi = " 
                   << phi << " rad"<< G4endl;

            G4double sintheta = sqrt((1-costheta)*(1+costheta));

            mvx = pmom * sintheta * cos(phi);
            mvy = pmom * sintheta * sin(phi);
            mvz = pmom * costheta;
            G4ThreeVector mv(mvx, mvy, mvz);

            G4ThreeVector pv   = particle_position; 
            if (fIsFlatProfile) {
               pv(0) = RandFlat::shoot(fPositionRange[0][0],fPositionRange[0][1]);
               pv(1) = RandFlat::shoot(fPositionRange[1][0],fPositionRange[1][1]);
               pv(2) = RandFlat::shoot(fPositionRange[2][0],fPositionRange[2][1]);
            } else {
               pv(0) = RandGauss::shoot(fMeanPosition.x(),fPositionSigma[0]);
               pv(1) = RandGauss::shoot(fMeanPosition.y(),fPositionSigma[1]);
               pv(2) = RandGauss::shoot(fMeanPosition.z(),fPositionSigma[2]);
	    }

            if (fIsConvergenceMode) {
               pv  = _BEAMCONVERGENCEEXTENT_ * mv.unit() + particle_position;
               mvx = - mv.x();
               mvy = - mv.y();
               mvz = - mv.z();
            } 
            vertex->SetPosition(pv.x(), pv.y(), pv.z());

            G4cerr << "J4ParticleBeam::GeneratePrimaries: startp, momentum = " 
                   << pv << " , " << mv << G4endl;
	    break; // end Isotropic case
         }
         case kEGaussian: {
	    G4cerr << "--------ParticleBeam:: Gaussian beamtype--------" << G4endl;
            G4double mom   = RandGauss::shoot(fMeanMomentum,fMomentumSigma);
            mvx = RandGauss::shoot(0.,fDirectionSigma);
            mvy = RandGauss::shoot(0.,fDirectionSigma);
            mvz = 1.;
            G4ThreeVector mv(mvx,mvy,mvz);
            mv = mom*(mv.unit());
            RefFrame ref;
            ref.SetRefFrame(particle_momentum_direction);
            mv = ref.Transform(mv);

            mvx = mv.x();
            mvy = mv.y();
            mvz = mv.z();

            G4ThreeVector pv   = particle_position; 
            if (fIsFlatProfile) {
	       G4cerr << "Position is Flat." << G4endl;
               pv(0) = RandFlat::shoot(fPositionRange[0][0],fPositionRange[0][1]);
               pv(1) = RandFlat::shoot(fPositionRange[1][0],fPositionRange[1][1]);
               pv(2) = RandFlat::shoot(fPositionRange[2][0],fPositionRange[2][1]);
	       G4cerr << "position : minx = " << fPositionRange[0][0]  
		      << "  maxx = " << fPositionRange[0][1] << G4endl
		      << "           miny = " << fPositionRange[1][0] 
		      << "  maxy = " << fPositionRange[1][1] << G4endl
		      << "           minz = " << fPositionRange[2][0] 
		      << "  maxz = " << fPositionRange[2][1] << G4endl;
            } else {
	       G4cerr << "Position is Gaussian." << G4endl;
               pv(0) = RandGauss::shoot(fMeanPosition.x(),fPositionSigma[0]);
               pv(1) = RandGauss::shoot(fMeanPosition.y(),fPositionSigma[1]);
               pv(2) = RandGauss::shoot(fMeanPosition.z(),fPositionSigma[2]);
            }
            vertex->SetPosition(pv.x(), pv.y(), pv.z());

            G4cerr << "J4ParticleBeam::GeneratePrimaries: startp, momentum = " 
                   << pv << " , " << mv << G4endl;
            break; // end Gaussian case
         }
      } // end switch on beam type
  
      G4PrimaryParticle* particle =
         new G4PrimaryParticle(particle_definition,mvx,mvy,mvz);
      particle->SetMass( mass );
      particle->SetCharge( particle_charge );
      particle->SetPolarization(particle_polarization.x(),
                                particle_polarization.y(),
                                particle_polarization.z());
      vertex->SetPrimary( particle );
      evt->AddPrimaryVertex( vertex );
   }                                               // end loop over particles
}
