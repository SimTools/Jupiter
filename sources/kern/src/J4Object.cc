// $Id$
//*************************************************************************
//* --------------------
//* J4Object
//* --------------------
//* (Description)
//*    
//* (Update Record)
//*	2002/12/20  K.Hoshina       Original version.
//*************************************************************************

#include "G4String.hh" 
#include "J4Named.hh" 

//=====================================================================
//---------------------
// class description
//---------------------


G4bool J4Object::Deregister(void * child)
{
   if (child && TBookKeeper::GetBookKeeper()->GetParent(child) == this) {
      if (TBookKeeper::GetBookKeeper()->Deregister(child)) {
         return true;
      } else {
         G4String name("unnamed");
         if (dynamic_cast<J4Named *>(this)) {
            name = dynamic_cast<J4Named *>(this)->GetName();
         }
         std::cerr << " J4Object::Deregister of "
               << name
               << " failed to orphan the child ("
               << child
               << "). The child had already been orphaned !!"
               << std::endl;
      }
   }
   return false;
}


