// $Id$
// GEANT4 tag $Name$
//

#ifndef J4ParticleBeam_h
#define J4ParticleBeam_h 1


#include "globals.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4PrimaryVertex.hh"
#include "G4ParticleMomentum.hh"

class G4Event;
class J4ParticleBeamMessenger;

// class description:
//
//  This is a concrete class of G4VPrimaryGenerator. It shoots a particle of given type
// to a given direction with a given kinetic energy. 
//  The position and time of the primary particle must be set by the corresponding
// set methods of G4VPrimaryGenerator base class, otherwise zero will be set.
//
//  The FAQ to this class is for randomizing position/direction/kinetic energy of primary
// particle. But, J4ParticleBeam does NOT have any way of randomization. Instead, the user's
// concrete implementation of G4VUserPrimaryGeneratorAction which transmits G4Event object
// to this particle gun can randomize these quantities and set to this particle gun before
// invoking GeneratePrimaryVertex() method.
//  Note that, even if the particle gun shoots more than one particles at one invokation of
// GeneratePrimaryVertex() method, all particles have the same physical quantities. If the
// user wants to shoot two particles with different momentum, position, etc., invoke
// GeneratePrimaryVertex() method twice and set quantities on demand to the particle gun.
//

class J4ParticleBeam : public G4ParticleGun
{
  friend class J4ParticleBeamMessenger;

  public: // with description
     J4ParticleBeam();
     J4ParticleBeam(G4int numberofparticles);
     J4ParticleBeam(G4ParticleDefinition * particleDef, 
                   G4int numberofparticles = 1);
     // costructors. "numberofparticles" is number of particles to be shoot at one invokation
     // of GeneratePrimaryVertex() method. All paricles are shoot with the same physical
     // quantities.

  public:
     virtual ~J4ParticleBeam();
     J4ParticleBeam(const J4ParticleBeam &right);

     const J4ParticleBeam & operator=(const J4ParticleBeam &right);
     G4int operator==(const J4ParticleBeam &right) const;
     G4int operator!=(const J4ParticleBeam &right) const;

  public: // with description
     virtual void GeneratePrimaryVertex(G4Event* evt);
     // Creates a primary vertex at the given point and put primary particles to it.
     // Followings are set methods for the particle properties.
     //   SetParticleDefinition should be called first.  
     //   By using SetParticleMomentum(), both particle_momentum_direction and
     //   particle_energy(Kinetic Energy) are set.
     //   

     void SetParticleMomentum(G4ParticleMomentum aMomentum);
     void SetBeamType(G4int type) { fBeamType = (EBeamType)type; }
     void SetConvergenceMode(G4bool convergence = TRUE) 
                                       { fIsConvergenceMode = convergence; }
     void SetBeamProfileType(G4bool is) { fIsFlatProfile = is; }

  private:
     class RefFrame
     {
        public:
           void SetRefFrame(const G4ThreeVector &zdir)
           {
	      G4ThreeVector oldzaxis(0.,0.,1.);
              fAxes[2] = zdir.unit();
              if (fabs(fAxes[2].z()-1.) < 1.e-12) {
                 fAxes[0].set(1.,0.,0.);
              } else if (fabs(fAxes[2].z()+1.) < 1.e-12) {
                 fAxes[0].set(-1.,0.,0.);
              } else {
                 fAxes[0] = (oldzaxis.cross(fAxes[2])).unit();
              }
	      fAxes[1] = (fAxes[2].cross(fAxes[0])).unit();
           }

           G4ThreeVector Transform(const G4ThreeVector &v)
           {
              return (v.x()*fAxes[0] + v.y()*fAxes[1] + v.z()*fAxes[2]);
           }
        private:
           G4ThreeVector fAxes[3];
     };

  protected:  

     typedef enum EBeamType { kEIsotropic = 0, kEGaussian = 1 };

     EBeamType             fBeamType;
     G4bool                fIsConvergenceMode;
     G4bool                fIsFlatProfile;
     G4double              fMomentumRange[2];
     G4double              fCosThetaRange[2];
     G4double              fPositionRange[3][2];
     G4double              fMeanMomentum;
     G4double              fMomentumSigma;
     G4double              fDirectionSigma;
     G4ThreeVector         fMeanPosition;
     G4double              fPositionSigma[3];

  private:
     J4ParticleBeamMessenger* fMessenger;

};

#endif







