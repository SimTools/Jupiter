// $Id$
// GEANT4 tag $Name$
//
//*************************************************************************
//* --------------------
//* J4ParticleBeam
//* --------------------
//* (Description)
//* 	Class for Particle beam
//*
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************
 
#include "J4ParticleBeam.hh"
#include "G4PrimaryParticle.hh"
#include "J4ParticleBeamMessenger.hh"
#include "G4Event.hh"
#include "G4ios.hh"
#include "Randomize.hh" 

//#define _BEAMCONVERGENCEEXTENT_   _EXPHALLHALFX_ - 1.1*cm  
//#define _BEAMCONVERGENCEEXTENT_   5.0*cm
#define _BEAMCONVERGENCEEXTENT_   1.2*m

#if __CLHEPVERSION__ >= 2
using namespace CLHEP;
#endif

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4ParticleBeam::J4ParticleBeam()
               :fBeamType(kEIsotropic), 
	             fIsConvergenceMode(FALSE), fIsFlatProfile(FALSE), 
                fMeanMomentum(10.*GeV), fMomentumSigma(0.1*GeV),
                fDirectionSigma(0.01), fMeanPosition(0.,0.,0.),
                fNVerticesPerBeam(1), fNParticlesPerVertex(1)
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
                fMeanMomentum(10.*GeV), fMomentumSigma(0.1*GeV),
                fDirectionSigma(0.01), fMeanPosition(0.,0.,0.),
                fNVerticesPerBeam(1), fNParticlesPerVertex(1)

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
                fMeanMomentum(10.*GeV), fMomentumSigma(0.1*GeV), 
                fDirectionSigma(0.01), fMeanPosition(0.,0.,0.),
                fNVerticesPerBeam(1), fNParticlesPerVertex(1)

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

// ====================================================================
//* destructor --------------------------------------------------------

J4ParticleBeam::~J4ParticleBeam()
{
  delete fMessenger;
}

// ====================================================================
//* SetParticleMomentum -----------------------------------------------

void J4ParticleBeam::SetParticleMomentum(G4ParticleMomentum aMomentum)
{
  if (particle_definition==0)
  {
     std::cout <<"Particle Deinition not deined yet for J4ParticleBeam"<< std::endl;
     std::cout <<"Zero Mass is assumed"<<std::endl;
     particle_momentum_direction =  aMomentum.unit();
     particle_energy = aMomentum.mag();
  } 
  else 
  {
     G4double mass =  particle_definition->GetPDGMass();
     G4double p = aMomentum.mag();
     particle_momentum_direction =  aMomentum.unit();
     if ((particle_energy>0.0)&&(std::abs(particle_energy+mass-std::sqrt(p*p+mass*mass))>keV)) {
        std::cout << "J4ParticleBeam::" << particle_definition->GetParticleName() << std::endl;
        std::cout << "  KineticEnergy and Momentum could be inconsistent" << std::endl;
        std::cout << " (Momentum:" << p/GeV << " GeV/c";
        std::cout << "  Mass:" << mass/GeV << " GeV/c/c)" << std::endl;
        std::cout << "  KineticEnergy is overwritten!! ";
        std::cout << particle_energy/GeV << "->";
        std::cout << (std::sqrt(p*p+mass*mass)-mass)/GeV << "GeV" << std::endl;
     }
     particle_energy = std::sqrt(p*p+mass*mass)-mass;
  }
}

// ====================================================================
//* GenerateIsotopicBeam ----------------------------------------------
void J4ParticleBeam::GenerateIsotopicBeam(G4Event* evt)
{
 	std::cerr << "--------ParticleBeam:: Isotropic beamtype-------" << std::endl;
#if 0
	G4double phi      = RandFlat::shoot(0.,2*M_PI);
#else
	G4double phi      = RandFlat::shoot(fPhiRange[0], fPhiRange[1]);
#endif
	G4double costheta = RandFlat::shoot(fCosThetaRange[0],
                                       fCosThetaRange[1]);
   // G4double costheta = std::cos((2 * G4UniformRand() -1.) * M_PI);
   if (fIsFlatProfile) {
	   std::cerr << "beam profile  : phi = " << phi 
             << " rad, flat position " << std::endl;
   } else {
	   std::cerr << "beam profile  : phi = " << phi 
             << " rad, gaussian position " << std::endl;
   }

	G4double sintheta = std::sqrt((1-costheta)*(1+costheta));
	G4double mvx      = fMeanMomentum * sintheta * std::cos(phi);
	G4double mvy      = fMeanMomentum * sintheta * std::sin(phi);
   G4double mvz      = fMeanMomentum * costheta;
   G4ThreeVector mv(mvx,mvy,mvz);
	RefFrame ref;
	ref.SetRefFrame(mv);
			
   for (G4int i=0; i<fNParticlesPerVertex; i++) {
		// define momentam
	   G4double mom = RandGauss::shoot(fMeanMomentum, fMomentumSigma);
      G4double tmpmvx, tmpmvy, tmpmvz;
		tmpmvx = RandGauss::shoot(0.,fDirectionSigma);
		tmpmvy = RandGauss::shoot(0.,fDirectionSigma);
		tmpmvz = 1.;
		G4ThreeVector tmpmv(tmpmvx, tmpmvy, tmpmvz);
		tmpmv = mom*(tmpmv.unit());
		G4ThreeVector lastmv = ref.Transform(tmpmv);
					
		// define particle position
		G4ThreeVector pv   = particle_position; 
		if (fIsFlatProfile) {
         // Flat profile
         pv(0) = RandFlat::shoot(fPositionRange[0][0],fPositionRange[0][1]);
			pv(1) = RandFlat::shoot(fPositionRange[1][0],fPositionRange[1][1]);
			pv(2) = RandFlat::shoot(fPositionRange[2][0],fPositionRange[2][1]);
		} else {
         // Gaussian profile
			pv(0) = RandGauss::shoot(fMeanPosition.x(),fPositionSigma[0]);
			pv(1) = RandGauss::shoot(fMeanPosition.y(),fPositionSigma[1]);
			pv(2) = RandGauss::shoot(fMeanPosition.z(),fPositionSigma[2]);
		}
					
		if (fIsConvergenceMode) {
			pv  = _BEAMCONVERGENCEEXTENT_ * mv.unit() + particle_position;
         lastmv.set( - lastmv.x(),  - lastmv.y(),  - lastmv.z() );
		} 
					
		// create a new vertex
		G4PrimaryVertex   *vertex   = new G4PrimaryVertex(pv, particle_time);
      G4PrimaryParticle *particle = new G4PrimaryParticle(particle_definition,
                                                          lastmv.x(),
                                                          lastmv.y(),
                                                          lastmv.z());
      particle->SetMass(particle_definition->GetPDGMass());
      particle->SetCharge( particle_charge );
      particle->SetPolarization(particle_polarization.x(),
                                particle_polarization.y(),
                                particle_polarization.z());
      vertex->SetPrimary( particle );
      evt->AddPrimaryVertex( vertex );
      std::cerr << "J4ParticleBeam::GenerateIsotopicBeam: No., startp, momentum = " 
             << i << " , " << pv << " , " << lastmv << std::endl;
   }
}

// ====================================================================
//* GenerateIsotopicBeam ----------------------------------------------
void J4ParticleBeam::GenerateGaussianBeam(G4Event* evt)
{
	std::cerr << "--------ParticleBeam:: Gaussian beamtype--------" << std::endl;
   
	for (G4int i=0; i<fNParticlesPerVertex; i++) {
 		// define momentam
	   G4double mom = RandGauss::shoot(fMeanMomentum,fMomentumSigma);
      G4double mvx = RandGauss::shoot(0.,fDirectionSigma);
      G4double mvy = RandGauss::shoot(0.,fDirectionSigma);
      G4double mvz = 1.;
      G4ThreeVector mv(mvx,mvy,mvz);
      mv = mom*(mv.unit());
      RefFrame ref;
      ref.SetRefFrame(particle_momentum_direction);
      G4ThreeVector lastmv = ref.Transform(mv);

		// define particle position
      G4ThreeVector pv = particle_position; 
      if (fIsFlatProfile) {
         // flat profile
         pv(0) = RandFlat::shoot(fPositionRange[0][0],fPositionRange[0][1]);
         pv(1) = RandFlat::shoot(fPositionRange[1][0],fPositionRange[1][1]);
         pv(2) = RandFlat::shoot(fPositionRange[2][0],fPositionRange[2][1]);
         std::cerr << "Flat beam position : minx = " << fPositionRange[0][0]  
                  << "  maxx = " << fPositionRange[0][1] << std::endl
                  << "           miny = " << fPositionRange[1][0] 
                  << "  maxy = " << fPositionRange[1][1] << std::endl
                  << "           minz = " << fPositionRange[2][0] 
                  << "  maxz = " << fPositionRange[2][1] << std::endl;
      } else {
         // gaussian profile
         pv(0) = RandGauss::shoot(fMeanPosition.x(),fPositionSigma[0]);
         pv(1) = RandGauss::shoot(fMeanPosition.y(),fPositionSigma[1]);
         pv(2) = RandGauss::shoot(fMeanPosition.z(),fPositionSigma[2]);
      }
      
		// create a new vertex
		G4PrimaryVertex   *vertex   = new G4PrimaryVertex(pv, particle_time);
      G4PrimaryParticle *particle = new G4PrimaryParticle(particle_definition,
                                                          lastmv.x(),
                                                          lastmv.y(),
                                                          lastmv.z());
      particle->SetMass(particle_definition->GetPDGMass());
      particle->SetCharge( particle_charge );
      particle->SetPolarization(particle_polarization.x(),
                                particle_polarization.y(),
                                particle_polarization.z());
      vertex->SetPrimary( particle );
      evt->AddPrimaryVertex( vertex );
      std::cerr << "J4ParticleBeam::GenerateGaussianBeam: No., startp, momentum = " 
             << i << " , " << pv << " , " << lastmv << std::endl;
   }
}
// ====================================================================
//* GeneratePrimaryVertex ---------------------------------------------

void J4ParticleBeam::GeneratePrimaryVertex(G4Event* evt)
{
   if (particle_definition == 0) return;

   // ---------------------------
   //  start loop over particles
   // ---------------------------
   
   for ( G4int i=0; i<fNVerticesPerBeam; i++ )
   
   {
      // Set mean momentum...
      G4double mass   = particle_definition->GetPDGMass();
      G4double energy = particle_energy + mass;
      G4double pmom   = std::sqrt((energy - mass)*(energy + mass));
      fMeanMomentum   = pmom;
  
      // ------------------------------
      //  switch on beam type
      // ------------------------------
      switch (fBeamType) {
         case kEIsotropic: 
				GenerateIsotopicBeam(evt);
            break; // end Isotropic case
         case kEGaussian:
				GenerateGaussianBeam(evt);
            break; // end Gaussian case
      } // end switch on beam type
  
   } // end loop over particles
	
}
