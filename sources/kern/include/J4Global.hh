// $Id$
#ifndef __J4GLOBAL__
#define __J4GLOBAL__
//*************************************************************************
//* -----------------------
//* J4Global
//* -----------------------
//* (Description)
//* 	 
//*     
//* (Update Record)
//*	2001/03/27  K.Hoshina	Original version.
//*************************************************************************

#include <fstream>
#include "G4ios.hh"
#include "G4String.hh"

// ====================================================================
// global valiables

#ifdef __THEBE__
#define J4cerr J4Global::GetErrorOutputStream()
#define J4endl G4endl; if (J4Global::GetErrorOutputDeviceID()) J4cerr<<G4std::flush
#else 
#define J4cerr G4cerr
#define J4endl G4endl
#endif

// ====================================================================
class J4GlobalMessenger;
class J4Global 
{
public:

  J4Global();
  virtual ~J4Global();
  
  static J4Global*        GetGlobal()               { return fGlobal;      }    
  
  static G4std::ostream&  GetErrorOutputStream();
  static G4std::ostream&  GetEndl(G4std::ostream& outs);
  static G4int            GetErrorCounter()        { return fErrorCounter; }
  static G4int            GetErrorNevents()        { return fErrorNevents; }
  static G4int            GetErrorOutputDeviceID() { return fErrorOutputDeviceID; }
  static G4String         GetErrorOutputFilename() { return fErrorOutputFilename; }
       
  static void             SetErrorOutputStream(G4std::ofstream& ofs) 
                                                   { fErrorOfs = &ofs;     }
  static void             SetErrorNevents(G4int n) { fErrorNevents = n;    }
  static void             SetErrorOutputDeviceID(G4int i)
                                                   { fErrorOutputDeviceID = i; }
  static void             SetErrorOutputFilename(G4String s)
                                                   { fErrorOutputFilename = s; }
  void                    CloseErrorOutputStream();
  
private:
  static J4Global          *fGlobal;
  static G4std::ofstream   *fErrorOfs;
  static G4int              fErrorCounter;
  static G4int              fErrorNevents;
  static G4int              fErrorOutputDeviceID;   // 0: cerr, 1:fileoutput
  static G4String           fErrorOutputFilename;
  J4GlobalMessenger        *fMessenger;
};

#endif
