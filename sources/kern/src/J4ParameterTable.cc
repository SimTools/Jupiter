//*************************************************************************
//* --------------------
//* J4AParameterTable
//* --------------------
//* (Description)
//*   J4AParameterTable is a static class to store all parameter values.
//*
//* (Update Record)
//*	2005/04/13  A.Miyamoto	Original version.
//$Id$
//*************************************************************************
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
using namespace std;
#include "J4AParameter.hh"
#include "J4ParameterTable.hh"

vector<J4AParameter*> J4ParameterTable::fParameters;
vector<J4AParameter*> J4ParameterTable::fDefaults;
bool J4ParameterTable::fCollectDefaults=false;

//------------------------------------------------------
J4ParameterTable::J4ParameterTable()
{
  fParameters.push_back((new J4AParameter("sample","4.5")));
  fParameters.push_back((new J4AParameter("sample2","Hello World")));

}

//------------------------------------------------------
void J4ParameterTable::Print()
{
  cout << "There are " << fParameters.size() << " parameters" << endl;
  vector<J4AParameter*>::iterator ip;
  for(ip=fParameters.begin();ip!=fParameters.end();ip++) {
    J4AParameter *p=*ip;
    cout << p->GetName() << ":" << p->GetInput() << endl;
  }


}

//------------------------------------------------------
void J4ParameterTable::PrintDefaults(const char *fname)
{
// This function should be used to print default parameter names and values
// used in the program

  ofstream fout(fname);
  fout << "#" << endl;
  fout << "#  Jupiter default parameter names and values " << endl;
  fout << "#  There are " << fDefaults.size() << " parameters " << endl;
  fout << "# " << endl;

  fout.setf(ios::left, ios::adjustfield );
  vector<J4AParameter*>::iterator ip;
  for(ip=fDefaults.begin();ip!=fDefaults.end();ip++) {
    J4AParameter *p=*ip;
    int lenw=(p->GetName()).length();
    if ( lenw < 30 ) lenw=30;
    fout.width(lenw);
    string nameout=p->GetName()+":";
    fout << nameout << p->GetInput() << endl;
  }
  fout.close();

}

//------------------------------------------------------
void J4ParameterTable::LoadFile(const char* fname)
{
  ifstream fin(fname);
  string instr;
  string pname;
  string pinput;
  char inbuf[2048];
  while( !fin.eof() ) {
     fin.getline(inbuf, 2048);
     if( inbuf[0] == '#' ) continue;
     instr=string(inbuf);
     int ip0=instr.find(':');
     if ( ip0 < 0 ) continue;
     string work=instr.substr(0,ip0);
     int ip0e=work.find_last_not_of(' ');
     if( ip0e >= 0 ) {
       pname=work.substr(0,ip0e+1);
     }
     else {
       pname=work;
     }

     int ip1 = instr.find_first_not_of(' ',ip0+1);
     pinput=instr.substr(ip1);
     fParameters.push_back((new J4AParameter(pname, pinput)));
  }
  fin.close();

}


//------------------------------------------------------
const double  J4ParameterTable::GetValue(const char *name, const double val)
{
   if( J4ParameterTable::CollectDefaults() ) {
     char buf[1000];
     sprintf(buf,"%f",val); 
     J4AParameter *p1=new J4AParameter(name, buf);
     fDefaults.push_back(p1);
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   if ( a->GetName() == string("???") ) { return val; }
   return a->GetValue(val) ;

}

//------------------------------------------------------
const int  J4ParameterTable::GetValue(const char *name, const int val)
{
   if( J4ParameterTable::CollectDefaults() ) { 
     char buf[1000];
     sprintf(buf, "%d",val);
     J4AParameter *p1=new J4AParameter(name, buf);
     fDefaults.push_back(p1);
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   if ( a->GetName() == string("???") ) { return val; }
   return a->GetValue(val) ;

}

//------------------------------------------------------
const float  J4ParameterTable::GetValue(const char *name, const float val)
{
   if( J4ParameterTable::CollectDefaults() ) { 
     char buf[1000];
     sprintf(buf, "%f",val);
     J4AParameter *p1=new J4AParameter(name, buf);
     fDefaults.push_back(p1);
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   if ( a->GetName() == string("???") ) { return val; }
   return a->GetValue(val) ;

}

//------------------------------------------------------
const char *J4ParameterTable::GetValue(const char *name, const char* val)
{
   if( J4ParameterTable::CollectDefaults() ) { 
     fDefaults.push_back((new J4AParameter(name, val)));
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   if ( a->GetName() == string("???") ) { return val; }
   return a->GetValue(val) ;

}

//------------------------------------------------------
const bool J4ParameterTable::GetValue(const char *name, const bool val)
{
   if( J4ParameterTable::CollectDefaults() ) { 
     if ( val ) { fDefaults.push_back(new J4AParameter(name,"true")); }
     else { fDefaults.push_back(new J4AParameter(name,"false")); }
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   if ( a->GetName() == string("???") ) { return val; }
   return a->GetValue(val) ;

}

//------------------------------------------------------
const vector<float> J4ParameterTable::GetFValue(const char *name, const char *val, const int n)
{
   if( J4ParameterTable::CollectDefaults() ) { 
     fDefaults.push_back((new J4AParameter(name, val)));
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   vector<float> vec(n);
   string fin(val);   
   if ( a->GetName() != string("???") ) { 
      fin=a->GetInput();   
   }  
   istringstream instream(fin);
   float x;
   for(int i=0;i<n;i++) {
     instream >> x ;
     vec[i]=x;
   }
   return vec;
}

//------------------------------------------------------
const vector<double> J4ParameterTable::GetDValue(const char *name, const char *val, const int n)
{
   if( J4ParameterTable::CollectDefaults() ) { 
     fDefaults.push_back((new J4AParameter(name, val)));
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   vector<double> vec(n);
   string fin(val);   
   if ( a->GetName() != string("???") ) { 
      fin=a->GetInput();   
   }  
   istringstream instream(fin);
   double x;
   for(int i=0;i<n;i++) {
     instream >> x ;
     vec[i]=x;
   }
   return vec;
}


//------------------------------------------------------
const vector<int> J4ParameterTable::GetIValue(const char *name, const char *val, const int n)
{
   if( J4ParameterTable::CollectDefaults() ) { 
     fDefaults.push_back((new J4AParameter(name, val)));
   } 
   J4AParameter *a=J4ParameterTable::FindName(name);
   vector<int> vec(n);
   string fin(val);   
   if ( a->GetName() != string("???") ) { 
      fin=a->GetInput();   
   }  
   istringstream instream(fin);
   int x;
   for(int i=0;i<n;i++) {
     instream >> x ;
     vec[i]=x;
   }
   return vec;
}

//------------------------------------------------------
J4AParameter *J4ParameterTable::FindName(const char *name)
{
  vector<J4AParameter*>::iterator ip;
  for(ip=fParameters.begin();ip!=fParameters.end();ip++) {
    J4AParameter *p=*ip;
    if ( p->GetName() == string(name) ) {
       return p;
    }
  }
  static J4AParameter notfind("???","");
  return &notfind;
}

