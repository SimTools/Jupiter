//*************************************************************************
//* --------------------
//* J4AParameter
//* --------------------
//* (Description)
//*   J4AParameter is a class representing one set of parameter name
//*   and its value string
//*
//* (Update Record)
//*	2005/04/13  A.Miyamoto	Original version.
//$Id$
//*************************************************************************
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#include "J4AParameter.hh"


// --------------------------------------------------------
J4AParameter::J4AParameter(const char *name, const char *input)
{
  fPname=string(name);
  fInput=string(input);
}

// --------------------------------------------------------
J4AParameter::J4AParameter(const string name, const string input)
{
  fPname=name;
  fInput=input;
}

// --------------------------------------------------------
const double J4AParameter::GetValue(const double val)
{
   istringstream instream(fInput);
   double in=val;
   instream >> in;
   return in;
}

// --------------------------------------------------------
const int J4AParameter::GetValue(const int val)
{
   if( fInput.substr(0,1) == string("T") || fInput.substr(0,1) == string("t") ||
       fInput.substr(0,1) == string("Y") || fInput.substr(0,1) == string("y") ) {
       return true; 
   }
   else if( fInput.substr(0,1) == string("F") || fInput.substr(0,1) == string("f") ||
       fInput.substr(0,1) == string("N") || fInput.substr(0,1) == string("n") ) {
       return false; 
   }

   istringstream instream(fInput);
   int in=val;
   instream >> in;
   return in;
}

// --------------------------------------------------------
const float J4AParameter::GetValue(const float val)
{
   istringstream instream(fInput);
   float in=val;
   instream >> in;
   return in;
}

// --------------------------------------------------------
const char *J4AParameter::GetValue(const char *val)
{
   if ( 1 == 0 ) { cout << val << endl ; } // To avoid warning message
   return fInput.data();
}

// --------------------------------------------------------
const bool J4AParameter::GetValue(const bool val)
{
   if ( 1 == 0 ) { cout << val << endl; }  // To avoid warning message
   if ( fInput.substr(0,1) == string("T") || 
        fInput.substr(0,1) == string("t") ) { 
	return true;
   }
   else {
     return false;
   }
}



