// $Id$
#ifndef __TBOOKKEEPER__
#define __TBOOKKEEPER__
//*************************************************************************
//* -----------------------
//* TBookKeeper
//* -----------------------
//* (Description)
//* 	Base class for all object .
//*     
//* (Update Record)
//*	2001/03/27  K.Hoshina	Original version.
//*	2004/06/14  K.Fujii	Rewritten with stl.
//*************************************************************************

#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include "G4ios.hh"


//=====================================================================
//---------------------
// class definition
//---------------------

class TBookKeeper {	// abstruct class
private:
  typedef std::pair<void *, void *> TPair;

  struct EqualTo : public std::binary_function<TPair, void *, bool> {
     bool operator()(TPair pair, void *child) const
     {
        return (pair.second == child);
     }
  };

public:
  typedef std::vector<TPair> TBook;

  TBookKeeper()
  {
     if (!fgBookKeeper) {
        fgBookKeeper = this;
     } else {
        std::cerr << " TBookKeeper is singleton. abort. " << std::endl;
        abort();
     }
  }		          
  
  virtual ~TBookKeeper(){}
  
  inline  void   Register   (void *parent, void *child);
  inline  bool   Deregister (void *child);
  inline  void*  GetParent  (void *child);

  inline static TBookKeeper* GetBookKeeper() { return fgBookKeeper; } 

private:

  static TBookKeeper *fgBookKeeper;
         TBook        fBook; 

};

//=============================
// inline functions
//=============================

void TBookKeeper::Register(void *parent, void *child) 
{
   TPair* pair = new TPair(parent, child);
   fBook.push_back(*pair); 
}

bool TBookKeeper::Deregister(void *child) 
{
   if (!child) return false;

   TBook::iterator ret = std::find_if(fBook.begin(), fBook.end(), 
                                   std::bind2nd(EqualTo(), child));
   if (ret != fBook.end()) {
      fBook.erase(ret);
      return true;
   }
   
#ifdef __DEBUG__
   std::cerr << " TBookKeeper::Deregister: The child ("
          << child
          << ") had already been orphaned !! " << std::endl;
#endif
   return false;
}

void* TBookKeeper::GetParent(void *child) 
{
   TBook::iterator ret = std::find_if(fBook.begin(), fBook.end(), 
                                   std::bind2nd(EqualTo(), child));
   if (ret != fBook.end()) return ret->first;
#ifdef __DEBUG__
   std::cerr << " TBookKeeper::GetParent: You ("
          << child
          << ") had already been orphaned !! " << std::endl;
#endif
   return 0;
}

#endif
