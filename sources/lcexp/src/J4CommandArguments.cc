//
//

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "J4CommandArguments.hh"

int J4CommandArguments::fVerboseLevel=11;
bool J4CommandArguments::fHasMacroFile=false;
string J4CommandArguments::fMacroFileName="";

bool J4CommandArguments::ParseArguments(int argc, char **argv)
{
  int i=1;
  istringstream inputs;
  while(i<argc) {
    string opts(argv[i]);
    if ( opts == string("-v") ) {
	i++;
        inputs.str(argv[i]);
        inputs >> fVerboseLevel ;
    } 
    else if ( opts == string("-help") ) {
	cerr << "Jupiter [options] " << endl;
        cerr << "  -v N  :  Verbose level" << endl;
        cerr << "  -help :  Print this message" << endl;
        return false;
    }
    else {
        fHasMacroFile=true;
	fMacroFileName=argv[i];
    }
    i++; 
  }
  return true;
}
