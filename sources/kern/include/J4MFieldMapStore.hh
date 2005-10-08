// $Id$
#ifndef __J4MFIELDMAPSTORE__
#define __J4MFIELDMAPSTORE__
//*************************************************************************
//* --------------------
//* J4MFieldMapStore
//* --------------------
//* (Description)
//* 	This class applies magnetic field.
//*     Mother class : G4MagneticField
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************
 
#include "globals.hh"
#include "G4MagneticField.hh"
#include "J4AttMFieldMap.hh"

// ====================================================================
// -----------------------
// class definition
// -----------------------
 
class J4MFieldMapStore : public G4MagneticField {

public: 
  inline static J4MFieldMapStore* GetInstance();

public:
  ~J4MFieldMapStore() { }
  virtual void GetFieldValue(const  G4double point[3], 
			     G4double* bfield ) const;  

  inline void AddMField(J4AttMFieldMap* map);
  inline void RemoveMField(J4AttMFieldMap* map);

  inline void NameList();

protected:
  J4MFieldMapStore();

private:
  static J4MFieldMapStore* fpInstance;

  int  fcurCount;
  J4AttMFieldMap** fmagCollection;

};

inline J4MFieldMapStore* J4MFieldMapStore::GetInstance () {
  if(!fpInstance) fpInstance=new J4MFieldMapStore();
  return fpInstance;
}

inline void J4MFieldMapStore::AddMField(J4AttMFieldMap* map){
  fmagCollection[fcurCount++]  = map; 
}

inline void J4MFieldMapStore::RemoveMField(J4AttMFieldMap* map){
  for ( G4int i = 0; i < fcurCount ; i++ ){
    if ( fmagCollection[i] == map ) fmagCollection[i] = 0;
  }
}
inline void J4MFieldMapStore::NameList () {
  std::cout << " ---J4MFieldMapStore:: NameList()--- "<< fcurCount <<std::endl; 
  for ( G4int i = 0; i < fcurCount ; i++){
    G4String* name = fmagCollection[i]->GetMFieldName();
    std::cout << i <<" "<< *name << std::endl;
  }
}
#endif
