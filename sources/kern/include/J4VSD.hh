// $Id$
#ifndef __J4VSD__
#define __J4VSD__
//*************************************************************************
//* --------------------
//* J4VSD
//* --------------------
//* (Description)
//* 	Abstract class template for his/her sensitive detector.
//*	You must use template class for derivation.
//*	Mother class : G4VSensitiveDetector
//*     
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*************************************************************************


//  !!! HOMEWORK !!!
//  Change a fHitBuf pointer to an fHitBuf* pointer array.
//  SensitiveDetector can have several HitBuffer class.

#include "J4VSensitiveDetector.hh"
#include "J4VDetectorComponent.hh"
#include "J4VHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsCollection.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class G4HCofThisEvent;

template <class HitType> 
class J4VSD : public J4VSensitiveDetector 
{ 

 public:
  J4VSD(J4VDetectorComponent* detector)
			: J4VSensitiveDetector(detector)
  {  
  }
  
  J4VSD(const J4VSD<G4THitsCollection<HitType> >& right)
		: J4VSensitiveDetector(right)
  {
  }
	
  virtual ~J4VSD()
  {
  }

  virtual const J4VSD& operator=(const J4VSD<G4THitsCollection<HitType> >& right)
  {
    return (const J4VSD&)J4VSensitiveDetector::operator=(right);    
  } 
       
  virtual void MakeHitBuf(G4HCofThisEvent* HCTE)
  { 
  
//    G4cerr << "J4VSD::MakeHitBuf is called " << G4endl;  

    G4THitsCollection<HitType>* hitbuf; 
    hitbuf = new G4THitsCollection<HitType>(SensitiveDetectorName, collectionName[0]) ;
    SetHitBuf((G4VHitsCollection*)hitbuf);      
    G4int hcID = GetCollectionID(0); 
    HCTE->AddHitsCollection(hcID, GetHitBuf());
   
//    G4cerr << " ***hcID = " << hcID << G4endl;
     
  }  
  
  virtual void OutputAll(G4HCofThisEvent* HCTE)
  {  	
     if(GetHitBuf())
     {    	
        if (!IsOutputLocked()) {
           G4int nhits = ((G4THitsCollection<HitType>*)GetHitBuf())->entries();
           G4int i;
           G4THitsCollection<HitType>* hcp = (G4THitsCollection<HitType>*)GetHitBuf();

           if (nhits) {
              G4cerr << "J4VSD::OutputAll: nhits = " << nhits 
               << " for SDName " << ((J4VHit*)hcp->operator[](0))->GetComponentName()<< G4endl;
           } else {
              G4cerr << "*****J4VSD::OutputAll: No Hit! " << G4endl;
           }
       
           for(i=0; i<nhits; i++)
           {
              ((J4VHit*)hcp->operator[](i))->Output(HCTE);
           }
           LockOutput();
        }
     }
     else
     {
         G4cerr << "*****J4VSD::OutputAll: No HitBuf! " << G4endl;
     }
  }
  
    
  
  virtual void clear()
  {
  }

  virtual void DrawAll(){};
  virtual void PrintAll(){}; 

  // set/get functions
   
   

    
};


#endif

