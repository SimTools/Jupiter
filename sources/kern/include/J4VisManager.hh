// $Id$
// ====================================================================
//    J4VisManager.hh
//
//    An example of Visualization Manager with implementation of 
//    the virtual function, RegisterGraphicsSystems().  
//
//    Exploits C-pre-processor flags, G4VIS_USE_DAWN, etc., 
//    which are set in the GNUmakefile, "config/G4VIS_USE.gmk"
//    if environment variables of the same name are set.
//
//    All you have to do is to set environment variables of your 
//    favorite graphic system and to instantiate this class 
//    in your main().
//
//                                 .JLC-CDC, 2001
// ====================================================================
#ifndef J4_VIS_MANAGER_H
#define J4_VIS_MANAGER_H
 
#include "G4VisManager.hh"

// ====================================================================
//
// class definition
//
// ====================================================================

class J4VisManager : public G4VisManager {

public:
  J4VisManager();
  ~J4VisManager();

private:
  virtual void RegisterGraphicsSystems();

};

#endif

