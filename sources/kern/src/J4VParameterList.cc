// $Id$
//*************************************************************************
//* --------------------
//* J4VParameterList
//* --------------------
//* (Description)
//*
//* (Update Record)
//*	2002/12/20  K.Hoshina	Original version.
//*************************************************************************

#include "J4VParameterList.hh"
#include "J4ParameterListStore.hh"

//=====================================================================
//* constructor -------------------------------------------------------

J4VParameterList::J4VParameterList()
                 :J4Named("unnamed")
{

   J4ObjArray paramlists = J4ParameterListStore::GetParameterLists(); 

   if (paramlists.entries() >= paramlists.capacity()) {
      std::cerr << "J4VParameterLists::constructor:  " << std::endl;
      std::cerr << "   entries  : " << paramlists.entries() << std::endl;
      std::cerr << "   capacity : " << paramlists.capacity() << std::endl;
      std::cerr << "J4VParameterLists::constructor: Too many parameter lists "
             << " . abort. " << std::endl;
      abort();
   }

   paramlists.append(this);

}

J4VParameterList::J4VParameterList(const G4String &name)
                 :J4Named(name)
{

   J4ObjArray paramlists = J4ParameterListStore::GetParameterLists(); 

   if (paramlists.entries() >= paramlists.capacity()) {
      std::cerr << "J4VParameterLists::constructor:  " << std::endl;
      std::cerr << "   entries  : " << paramlists.entries() << std::endl;
      std::cerr << "   capacity : " << paramlists.capacity() << std::endl;
      std::cerr << "J4VParameterLists::constructor: Too many parameter lists "
             << " . abort. " << std::endl;
      abort();
   }

   paramlists.append(this);

}

//=====================================================================
//* destructor -------------------------------------------------------

J4VParameterList::~J4VParameterList()
{
}



