#ifndef __J4PARAMETERTABLE__
#define __J4PARAMETERTABLE__
//********************************************************************
//* ---------------------
//* J4ParameterTable.hh
//* ---------------------
//* (Description)
//*     A static class to keep all parameter data readin from a file
//*     and to be used to get value corresponding to parameters
//*     
//* (Update Record)
//*	2005/04/13  A.Miyamoto  Original version.
//*$Id$
//********************************************************************
#include <string>
#include <vector>

class J4AParameter;

class J4ParameterTable
{
  protected:
    static bool fCollectDefaults;
    static std::vector<J4AParameter*> fParameters;
    static std::vector<J4AParameter*> fDefaults;
  public:
    J4ParameterTable();
    virtual ~J4ParameterTable(){}

    inline static bool CollectDefaults(){ return fCollectDefaults;}
    inline static void SetCollectDefaults(bool flag){ fCollectDefaults=flag; }
    static std::vector<J4AParameter*> *GetTable(){ return &fParameters; }
    static void PrintDefaults(const char *fname="jupiter.defaults");
    static void LoadFile(const char *fname);
    static void Print();
    static void SetVersionInfo();
    static J4AParameter *FindName(const char *name);
    static const double GetValue(const char *name, const double val);
    static const int    GetValue(const char *name, const int val);
    static const float  GetValue(const char *name, const float val);
    static const char  *GetValue(const char *name, const char *val);
    static const bool   GetValue(const char *name, const bool  val);
    static const std::vector<float> GetFValue(const char *name, const char *val, const int n);
    static const std::vector<double> GetDValue(const char *name, const char *val, const int n);
    static const std::vector<int> GetIValue(const char *name, const char *val, const int n);

};

#endif
