#ifndef __J4APARAMETER__
#define __J4APARAMETER__
//********************************************************************
//* ---------------------
//* J4AParameter.hh
//* ---------------------
//* (Description)
//* 	A class to store parameter.
//*     Each parameter data contains parameter name and parameter string
//*     
//* (Update Record)
//*	2005/04/13  A.Miyamoto  Original version.
//*$Id$
//********************************************************************
#include <string>

class J4AParameter 
{
  protected:
    std::string fPname;
    std::string fInput;
  public:
    J4AParameter(const char *name="default", const char *input="0");
    J4AParameter(const std::string name, const std::string input);
    virtual ~J4AParameter(){}

    inline std::string GetName(){ return fPname; }
    inline std::string GetInput(){ return fInput; }

    virtual const double GetValue(const double val);
    virtual const int    GetValue(const int val);
    virtual const float  GetValue(const float val);
    virtual const char*  GetValue(const char *val);
    virtual const bool   GetValue(const bool val);
};

#endif
