//
//

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "J4CommandArguments.hh"
#include "J4ParameterTable.hh"

int J4CommandArguments::fVerboseLevel=11;
bool J4CommandArguments::fHasMacroFile=false;
string J4CommandArguments::fMacroFileName="";
J4ParameterTable fgParaTable;  // Just a dummy to call J4ParameterTable construtor

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
    else if ( opts == string("-f") ) {
        i++;
        cerr << "Loading Parameter file :" << argv[i] << endl;
        J4ParameterTable::LoadFile(argv[i]);
    }
    else if ( opts == string("-w") ) {
        J4ParameterTable::SetCollectDefaults(true);
    }
    else if ( opts == string("-help") ) {
	cerr << "Jupiter [options] " << endl;
        cerr << "  -v N  :  Verbose level" << endl;
        cerr << "     0  :  Minimum message " << endl;
        cerr << "     6-10 : Print geometry initialization message of top two level" << endl;
        cerr << "    >10 :  Print message at every geometry creation " << endl;
        cerr << "  -f Parameter_File : File name to get parameters" << endl;
        cerr << "  -w    :  Print default parameters used to the file" << endl;
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
