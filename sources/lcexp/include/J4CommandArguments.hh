#ifndef __J4COMMANDARGUMENTS__
#define __J4COMMANDARGUMENTS__

//*************************************************************************
//* --------------------
//* J4CommandArguments
//* --------------------
//* (Description)
//*     Static class to keep command line arguments
//*     such as debug flag
//* (Update Record)
//*     2005/02/19  A.Miyamoto     Original version.
//*************************************************************************
//
#include <string>
 
class J4CommandArguments
{
   public:
	J4CommandArguments(){}
	virtual ~J4CommandArguments(){}
   private:
	static int fVerboseLevel;
	static bool fHasMacroFile;
        static std::string fMacroFileName;
   public:
	static bool ParseArguments(int argc, char **argv);
	
        inline static std::string GetMacroFileName(){ return fMacroFileName; }

        inline static bool HasMacroFile(){ return fHasMacroFile; }
	inline static int VerboseLevel(){ return fVerboseLevel; }
	inline static void SetVerboseLevel(int i){ fVerboseLevel=i; }
};

#endif 
