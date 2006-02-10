#ifndef __J4CLXAddress__
#define __J4CLXAddress__

#include "J4VCLXCell.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CLXAddress {
public:
    J4CLXAddress(G4int blockID,
		 G4bool isEM,
		 G4int layerID,
		 G4int boardID,
		 G4int cellCloneID,
		 J4VCLXCell* ptrCellComponent);
    ~J4CLXAddress();

    G4int GetCellID();
    G4int GetLayerID();
    G4int GetLongID();
    G4ThreeVector GetCellPosition();

private:
    G4int fBlockID;
    G4int fIsEM;
    G4int fLayerID;
    G4int fBoardID;
    G4int fCellID;
    J4VCLXCell* fCellComponent;
};

#endif
